//
//  HTTPRequest
//

#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP
#pragma comment(lib, "ws2_32.lib")

#include <cctype>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <algorithm>
#include <array>
#include <chrono>
#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <system_error>
#include <type_traits>
#include <vector>

#ifdef _WIN32
#  pragma push_macro("WIN32_LEAN_AND_MEAN")
#  pragma push_macro("NOMINMAX")
#  ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN
#  endif // WIN32_LEAN_AND_MEAN
#  ifndef NOMINMAX
#    define NOMINMAX
#  endif // NOMINMAX
#  include <winsock2.h>
#  if _WIN32_WINNT < _WIN32_WINNT_WINXP
extern "C" char* _strdup(const char* strSource);
#    define strdup _strdup
#    include <wspiapi.h>
#  endif // _WIN32_WINNT < _WIN32_WINNT_WINXP
#  include <ws2tcpip.h>
#  pragma pop_macro("WIN32_LEAN_AND_MEAN")
#  pragma pop_macro("NOMINMAX")
#else
#  include <errno.h>
#  include <fcntl.h>
#  include <netinet/in.h>
#  include <netdb.h>
#  include <sys/select.h>
#  include <sys/socket.h>
#  include <unistd.h>
#endif // _WIN32

namespace http
{
    class RequestError final : public std::logic_error
    {
    public:
        explicit RequestError(const char* str) : std::logic_error{ str } {}
        explicit RequestError(const std::string& str) : std::logic_error{ str } {}
    };

    class ResponseError final : public std::runtime_error
    {
    public:
        explicit ResponseError(const char* str) : std::runtime_error{ str } {}
        explicit ResponseError(const std::string& str) : std::runtime_error{ str } {}
    };

    enum class InternetProtocol : std::uint8_t
    {
        V4,
        V6
    };

    inline namespace detail
    {
#ifdef _WIN32
        class WinSock final
        {
        public:
            WinSock()
            {
                WSADATA wsaData;
                const auto error = WSAStartup(MAKEWORD(2, 2), &wsaData);
                if (error != 0)
                    throw std::system_error(error, std::system_category(), "WSAStartup failed");

                if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
                {
                    WSACleanup();
                    throw std::runtime_error("Invalid WinSock version");
                }

                started = true;
            }

            ~WinSock()
            {
                if (started) WSACleanup();
            }

            WinSock(WinSock&& other) noexcept :
                started{ other.started }
            {
                other.started = false;
            }

            WinSock& operator=(WinSock&& other) noexcept
            {
                if (&other == this) return *this;
                if (started) WSACleanup();
                started = other.started;
                other.started = false;
                return *this;
            }

        private:
            bool started = false;
        };
#endif // _WIN32

        inline int getLastError() noexcept
        {
#ifdef _WIN32
            return WSAGetLastError();
#else
            return errno;
#endif // _WIN32
        }

        constexpr int getAddressFamily(InternetProtocol internetProtocol)
        {
            return (internetProtocol == InternetProtocol::V4) ? AF_INET :
                (internetProtocol == InternetProtocol::V6) ? AF_INET6 :
                throw RequestError("Unsupported protocol");
        }

        class Socket final
        {
        public:
#ifdef _WIN32
            using Type = SOCKET;
            static constexpr Type invalid = INVALID_SOCKET;
#else
            using Type = int;
            static constexpr Type invalid = -1;
#endif // _WIN32

            explicit Socket(InternetProtocol internetProtocol) :
                endpoint{ socket(getAddressFamily(internetProtocol), SOCK_STREAM, IPPROTO_TCP) }
            {
                if (endpoint == invalid)
                    throw std::system_error(getLastError(), std::system_category(), "Failed to create socket");

#ifdef _WIN32
                unsigned long mode = 1;
                if (ioctlsocket(endpoint, FIONBIO, &mode) != 0)
                {
                    close();
                    throw std::system_error(WSAGetLastError(), std::system_category(), "Failed to get socket flags");
                }
#else
                const auto flags = fcntl(endpoint, F_GETFL);
                if (flags == -1)
                {
                    close();
                    throw std::system_error(errno, std::system_category(), "Failed to get socket flags");
                }

                if (fcntl(endpoint, F_SETFL, flags | O_NONBLOCK) == -1)
                {
                    close();
                    throw std::system_error(errno, std::system_category(), "Failed to set socket flags");
                }
#endif // _WIN32

#ifdef __APPLE__
                const int value = 1;
                if (setsockopt(endpoint, SOL_SOCKET, SO_NOSIGPIPE, &value, sizeof(value)) == -1)
                {
                    close();
                    throw std::system_error(errno, std::system_category(), "Failed to set socket option");
                }
#endif // __APPLE__
            }

            ~Socket()
            {
                if (endpoint != invalid) close();
            }

            Socket(Socket&& other) noexcept :
                endpoint{ other.endpoint }
            {
                other.endpoint = invalid;
            }

            Socket& operator=(Socket&& other) noexcept
            {
                if (&other == this) return *this;
                if (endpoint != invalid) close();
                endpoint = other.endpoint;
                other.endpoint = invalid;
                return *this;
            }

            void connect(const struct sockaddr* address, const socklen_t addressSize, const std::int64_t timeout)
            {
#ifdef _WIN32
                auto result = ::connect(endpoint, address, addressSize);
                while (result == -1 && WSAGetLastError() == WSAEINTR)
                    result = ::connect(endpoint, address, addressSize);

                if (result == -1)
                {
                    if (WSAGetLastError() == WSAEWOULDBLOCK)
                    {
                        select(SelectType::write, timeout);

                        char socketErrorPointer[sizeof(int)];
                        socklen_t optionLength = sizeof(socketErrorPointer);
                        if (getsockopt(endpoint, SOL_SOCKET, SO_ERROR, socketErrorPointer, &optionLength) == -1)
                            throw std::system_error(WSAGetLastError(), std::system_category(), "Failed to get socket option");

                        int socketError;
                        std::memcpy(&socketError, socketErrorPointer, sizeof(socketErrorPointer));

                        if (socketError != 0)
                            throw std::system_error(socketError, std::system_category(), "Failed to connect");
                    }
                    else
                        throw std::system_error(WSAGetLastError(), std::system_category(), "Failed to connect");
                }
#else
                auto result = ::connect(endpoint, address, addressSize);
                while (result == -1 && errno == EINTR)
                    result = ::connect(endpoint, address, addressSize);

                if (result == -1)
                {
                    if (errno == EINPROGRESS)
                    {
                        select(SelectType::write, timeout);

                        int socketError;
                        socklen_t optionLength = sizeof(socketError);
                        if (getsockopt(endpoint, SOL_SOCKET, SO_ERROR, &socketError, &optionLength) == -1)
                            throw std::system_error(errno, std::system_category(), "Failed to get socket option");

                        if (socketError != 0)
                            throw std::system_error(socketError, std::system_category(), "Failed to connect");
                    }
                    else
                        throw std::system_error(errno, std::system_category(), "Failed to connect");
                }
#endif // _WIN32
            }

            std::size_t send(const void* buffer, const std::size_t length, const std::int64_t timeout)
            {
                select(SelectType::write, timeout);
#ifdef _WIN32
                auto result = ::send(endpoint, reinterpret_cast<const char*>(buffer),
                    static_cast<int>(length), 0);

                while (result == -1 && WSAGetLastError() == WSAEINTR)
                    result = ::send(endpoint, reinterpret_cast<const char*>(buffer),
                        static_cast<int>(length), 0);

                if (result == -1)
                    throw std::system_error(WSAGetLastError(), std::system_category(), "Failed to send data");
#else
                auto result = ::send(endpoint, reinterpret_cast<const char*>(buffer),
                    length, noSignal);

                while (result == -1 && errno == EINTR)
                    result = ::send(endpoint, reinterpret_cast<const char*>(buffer),
                        length, noSignal);

                if (result == -1)
                    throw std::system_error(errno, std::system_category(), "Failed to send data");
#endif // _WIN32
                return static_cast<std::size_t>(result);
            }

            std::size_t recv(void* buffer, const std::size_t length, const std::int64_t timeout)
            {
                select(SelectType::read, timeout);
#ifdef _WIN32
                auto result = ::recv(endpoint, reinterpret_cast<char*>(buffer),
                    static_cast<int>(length), 0);

                while (result == -1 && WSAGetLastError() == WSAEINTR)
                    result = ::recv(endpoint, reinterpret_cast<char*>(buffer),
                        static_cast<int>(length), 0);

                if (result == -1)
                    throw std::system_error(WSAGetLastError(), std::system_category(), "Failed to read data");
#else
                auto result = ::recv(endpoint, reinterpret_cast<char*>(buffer),
                    length, noSignal);

                while (result == -1 && errno == EINTR)
                    result = ::recv(endpoint, reinterpret_cast<char*>(buffer),
                        length, noSignal);

                if (result == -1)
                    throw std::system_error(errno, std::system_category(), "Failed to read data");
#endif // _WIN32
                return static_cast<std::size_t>(result);
            }

            operator Type() const noexcept { return endpoint; }

        private:
            enum class SelectType
            {
                read,
                write
            };

            void select(const SelectType type, const std::int64_t timeout)
            {
                fd_set descriptorSet;
                FD_ZERO(&descriptorSet);
                FD_SET(endpoint, &descriptorSet);

                timeval selectTimeout{
                    static_cast<decltype(timeval::tv_sec)>(timeout / 1000),
                    static_cast<decltype(timeval::tv_usec)>((timeout % 1000) * 1000)
                };
#ifdef _WIN32
                auto count = ::select(0,
                    (type == SelectType::read) ? &descriptorSet : nullptr,
                    (type == SelectType::write) ? &descriptorSet : nullptr,
                    nullptr,
                    (timeout >= 0) ? &selectTimeout : nullptr);

                while (count == -1 && WSAGetLastError() == WSAEINTR)
                    count = ::select(0,
                        (type == SelectType::read) ? &descriptorSet : nullptr,
                        (type == SelectType::write) ? &descriptorSet : nullptr,
                        nullptr,
                        (timeout >= 0) ? &selectTimeout : nullptr);

                if (count == -1)
                    throw std::system_error(WSAGetLastError(), std::system_category(), "Failed to select socket");
                else if (count == 0)
                    throw ResponseError("Request timed out");
#else
                auto count = ::select(endpoint + 1,
                    (type == SelectType::read) ? &descriptorSet : nullptr,
                    (type == SelectType::write) ? &descriptorSet : nullptr,
                    nullptr,
                    (timeout >= 0) ? &selectTimeout : nullptr);

                while (count == -1 && errno == EINTR)
                    count = ::select(endpoint + 1,
                        (type == SelectType::read) ? &descriptorSet : nullptr,
                        (type == SelectType::write) ? &descriptorSet : nullptr,
                        nullptr,
                        (timeout >= 0) ? &selectTimeout : nullptr);

                if (count == -1)
                    throw std::system_error(errno, std::system_category(), "Failed to select socket");
                else if (count == 0)
                    throw ResponseError("Request timed out");
#endif // _WIN32
            }

            void close() noexcept
            {
#ifdef _WIN32
                closesocket(endpoint);
#else
                ::close(endpoint);
#endif // _WIN32
            }

#if defined(__unix__) && !defined(__APPLE__)
            static constexpr int noSignal = MSG_NOSIGNAL;
#else
            static constexpr int noSignal = 0;
#endif // defined(__unix__) && !defined(__APPLE__)

            Type endpoint = invalid;
        };
    }

    struct Response final
    {
        enum Status
        {
            Continue = 100,
            SwitchingProtocol = 101,
            Processing = 102,
            EarlyHints = 103,

            Ok = 200,
            Created = 201,
            Accepted = 202,
            NonAuthoritativeInformation = 203,
            NoContent = 204,
            ResetContent = 205,
            PartialContent = 206,
            MultiStatus = 207,
            AlreadyReported = 208,
            ImUsed = 226,

            MultipleChoice = 300,
            MovedPermanently = 301,
            Found = 302,
            SeeOther = 303,
            NotModified = 304,
            UseProxy = 305,
            TemporaryRedirect = 307,
            PermanentRedirect = 308,

            BadRequest = 400,
            Unauthorized = 401,
            PaymentRequired = 402,
            Forbidden = 403,
            NotFound = 404,
            MethodNotAllowed = 405,
            NotAcceptable = 406,
            ProxyAuthenticationRequired = 407,
            RequestTimeout = 408,
            Conflict = 409,
            Gone = 410,
            LengthRequired = 411,
            PreconditionFailed = 412,
            PayloadTooLarge = 413,
            UriTooLong = 414,
            UnsupportedMediaType = 415,
            RangeNotSatisfiable = 416,
            ExpectationFailed = 417,
            MisdirectedRequest = 421,
            UnprocessableEntity = 422,
            Locked = 423,
            FailedDependency = 424,
            TooEarly = 425,
            UpgradeRequired = 426,
            PreconditionRequired = 428,
            TooManyRequests = 429,
            RequestHeaderFieldsTooLarge = 431,
            UnavailableForLegalReasons = 451,

            InternalServerError = 500,
            NotImplemented = 501,
            BadGateway = 502,
            ServiceUnavailable = 503,
            GatewayTimeout = 504,
            HttpVersionNotSupported = 505,
            VariantAlsoNegotiates = 506,
            InsufficientStorage = 507,
            LoopDetected = 508,
            NotExtended = 510,
            NetworkAuthenticationRequired = 511
        };

        int status = 0;
        std::string description;
        std::vector<std::string> headers;
        std::vector<std::uint8_t> body;
    };

    class Request final
    {
    public:
        explicit Request(const std::string& url,
            const InternetProtocol protocol = InternetProtocol::V4) :
            internetProtocol{ protocol }
        {
            const auto schemeEndPosition = url.find("://");

            if (schemeEndPosition != std::string::npos)
            {
                scheme = url.substr(0, schemeEndPosition);
                path = url.substr(schemeEndPosition + 3);
            }
            else
            {
                scheme = "http";
                path = url;
            }

            const auto fragmentPosition = path.find('#');

            // remove the fragment part
            if (fragmentPosition != std::string::npos)
                path.resize(fragmentPosition);

            const auto pathPosition = path.find('/');

            if (pathPosition == std::string::npos)
            {
                domain = path;
                path = "/";
            }
            else
            {
                domain = path.substr(0, pathPosition);
                path = path.substr(pathPosition);
            }

            const auto portPosition = domain.find(':');

            if (portPosition != std::string::npos)
            {
                port = domain.substr(portPosition + 1);
                domain.resize(portPosition);
            }
            else
                port = "80";
        }

        Response send(const std::string& method = "GET",
            const std::string& body = "",
            const std::vector<std::string>& headers = {},
            const std::chrono::milliseconds timeout = std::chrono::milliseconds{ -1 })
        {
            return send(method,
                std::vector<uint8_t>(body.begin(), body.end()),
                headers,
                timeout);
        }

        Response send(const std::string& method,
            const std::vector<uint8_t>& body,
            const std::vector<std::string>& headers,
            const std::chrono::milliseconds timeout = std::chrono::milliseconds{ -1 })
        {
            const auto stopTime = std::chrono::steady_clock::now() + timeout;

            if (scheme != "http")
                throw RequestError("Only HTTP scheme is supported");

            addrinfo hints = {};
            hints.ai_family = getAddressFamily(internetProtocol);
            hints.ai_socktype = SOCK_STREAM;

            addrinfo* info;
            if (getaddrinfo(domain.c_str(), port.c_str(), &hints, &info) != 0)
                throw std::system_error(getLastError(), std::system_category(), "Failed to get address info of " + domain);

            std::unique_ptr<addrinfo, decltype(&freeaddrinfo)> addressInfo(info, freeaddrinfo);

            // RFC 7230, 3.1.1. Request Line
            std::string headerData = method + " " + path + " HTTP/1.1\r\n";

            for (const auto& header : headers)
                headerData += header + "\r\n";

            // RFC 7230, 3.2.  Header Fields
            headerData += "Host: " + domain + "\r\n"
                "Content-Length: " + std::to_string(body.size()) + "\r\n"
                "\r\n";

            std::vector<uint8_t> requestData(headerData.begin(), headerData.end());
            requestData.insert(requestData.end(), body.begin(), body.end());

            Socket socket(internetProtocol);

            // take the first address from the list
            socket.connect(addressInfo->ai_addr, static_cast<socklen_t>(addressInfo->ai_addrlen),
                (timeout.count() >= 0) ? getRemainingMilliseconds(stopTime) : -1);

            auto remaining = requestData.size();
            auto sendData = requestData.data();

            // send the request
            while (remaining > 0)
            {
                const auto size = socket.send(sendData, remaining,
                    (timeout.count() >= 0) ? getRemainingMilliseconds(stopTime) : -1);
                remaining -= size;
                sendData += size;
            }

            std::array<std::uint8_t, 4096> tempBuffer;
            constexpr std::array<std::uint8_t, 2> crlf = { '\r', '\n' };
            Response response;
            std::vector<std::uint8_t> responseData;
            enum class State
            {
                statusLine,
                headers,
                body
            } state = State::statusLine;
            bool contentLengthReceived = false;
            std::size_t contentLength = 0;
            bool chunkedResponse = false;
            std::size_t expectedChunkSize = 0;
            bool removeCrlfAfterChunk = false;

            // read the response
            for (;;)
            {
                const auto size = socket.recv(tempBuffer.data(), tempBuffer.size(),
                    (timeout.count() >= 0) ? getRemainingMilliseconds(stopTime) : -1);

                if (size == 0)
                {
                    // download complete
                    return response;
                }
                else if (size < 0)
                {
                    throw ResponseError("Socket error");
                }

                responseData.insert(responseData.end(), tempBuffer.begin(), tempBuffer.begin() + size);

                if (state != State::body)
                    for (;;)
                    {
                        // RFC 7230, 3. Message Format
                        const auto i = std::search(responseData.begin(), responseData.end(), crlf.begin(), crlf.end());

                        // didn't find a newline
                        if (i == responseData.end()) break;

                        const std::string line(responseData.begin(), i);
                        responseData.erase(responseData.begin(), i + 2);

                        // empty line indicates the end of the header section
                        if (line.empty())
                        {
                            state = State::body;
                            break;
                        }
                        else if (state == State::statusLine) // RFC 7230, 3.1.2. Status Line
                        {
                            state = State::headers;
                            std::size_t partNum = 0;

                            // tokenize the status line
                            for (auto beginIterator = line.begin(); beginIterator != line.end();)
                            {
                                const auto endIterator = std::find(beginIterator, line.end(), ' ');
                                const std::string part{ beginIterator, endIterator };

                                switch (++partNum)
                                {
                                case 2: response.status = std::stoi(part); break;
                                case 3: response.description = part; break;
                                }

                                if (endIterator == line.end()) break;
                                beginIterator = endIterator + 1;
                            }
                        }
                        else if (state == State::headers) // RFC 7230, 3.2.  Header Fields
                        {
                            response.headers.push_back(line);

                            const auto loumnPosition = line.find(':');

                            if (loumnPosition == std::string::npos)
                                throw ResponseError("Invalid header: " + line);

                            const auto headerName = line.substr(0, loumnPosition);
                            auto headerValue = line.substr(loumnPosition + 1);

                            // RFC 7230, Appendix B. Collected ABNF
                            auto isNotWhiteSpace = [](char c) {
                                return c != ' ' && c != '\t';
                            };

                            // ltrim
                            headerValue.erase(headerValue.begin(), std::find_if(headerValue.begin(), headerValue.end(), isNotWhiteSpace));

                            // rtrim
                            headerValue.erase(std::find_if(headerValue.rbegin(), headerValue.rend(), isNotWhiteSpace).base(), headerValue.end());

                            if (headerName == "Content-Length")
                            {
                                contentLength = std::stoul(headerValue);
                                contentLengthReceived = true;
                                response.body.reserve(contentLength);
                            }
                            else if (headerName == "Transfer-Encoding")
                            {
                                if (headerValue == "chunked")
                                    chunkedResponse = true;
                                else
                                    throw ResponseError("Unsupported transfer encoding: " + headerValue);
                            }
                        }
                    }

                if (state == State::body)
                {
                    if (method == "HEAD") // Body must be ignored for HEAD requests
                    {
                        return response;
                    }
                    else if (chunkedResponse) // Content-Length must be ignored if Transfer-Encoding is received
                    {
                        for (;;)
                        {
                            if (expectedChunkSize > 0)
                            {
                                const auto toWrite = (std::min)(expectedChunkSize, responseData.size());
                                response.body.insert(response.body.end(), responseData.begin(), responseData.begin() + static_cast<std::ptrdiff_t>(toWrite));
                                responseData.erase(responseData.begin(), responseData.begin() + static_cast<std::ptrdiff_t>(toWrite));
                                expectedChunkSize -= toWrite;

                                if (expectedChunkSize == 0) removeCrlfAfterChunk = true;
                                if (responseData.empty()) break;
                            }
                            else
                            {
                                if (removeCrlfAfterChunk)
                                {
                                    if (responseData.size() < 2) break;

                                    if (!std::equal(crlf.begin(), crlf.end(), responseData.begin()))
                                        throw ResponseError("Invalid chunk");

                                    removeCrlfAfterChunk = false;
                                    responseData.erase(responseData.begin(), responseData.begin() + 2);
                                }

                                const auto i = std::search(responseData.begin(), responseData.end(), crlf.begin(), crlf.end());

                                if (i == responseData.end()) break;

                                const std::string line(responseData.begin(), i);
                                responseData.erase(responseData.begin(), i + 2);

                                expectedChunkSize = std::stoul(line, nullptr, 16);
                                if (expectedChunkSize == 0)
                                    return response;
                            }
                        }
                    }
                    else
                    {
                        response.body.insert(response.body.end(), responseData.begin(), responseData.end());
                        responseData.clear();

                        // got the whole content
                        if (contentLengthReceived && response.body.size() >= contentLength)
                            return response;
                    }
                }
            }

            return response;
        }

    private:
        static std::int64_t getRemainingMilliseconds(const std::chrono::steady_clock::time_point time)
        {
            const auto now = std::chrono::steady_clock::now();
            const auto remainingTime = std::chrono::duration_cast<std::chrono::milliseconds>(time - now);
            return (remainingTime.count() > 0) ? remainingTime.count() : 0;
        }

#ifdef _WIN32
        WinSock winSock;
#endif // _WIN32
        InternetProtocol internetProtocol;
        std::string scheme;
        std::string domain;
        std::string port;
        std::string path;
    };
}

#endif // HTTPREQUEST_HPP