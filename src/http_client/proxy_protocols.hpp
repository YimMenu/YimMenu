#pragma once

namespace big
{
	enum class ProxyProtocol : uint32_t
	{
		NONE,
		HTTP,
		HTTPS,
		SOCKS4,
		SOCKS4A,
		SOCKS5,
		SOCKS5H,
		FTP,
		SMTP,
		POP3,
		IMAP,
		DNS,
		FTP_GATEWAY,
		TELNET,
		SIP,
		WEBSOCKETS,
		RTSP,
		PPTP,
		L2TP,
		MPLS,
		IPSEC,
		REVERSE_PROXY,
		TRANSPARENT_PROXY,
		ANONYMIZING_PROXY,
		FORWARD_PROXY,
	};
	NLOHMANN_JSON_SERIALIZE_ENUM(ProxyProtocol, {{ProxyProtocol::NONE, "none"}, {ProxyProtocol::HTTP, "http"}, {ProxyProtocol::HTTPS, "https"}, {ProxyProtocol::SOCKS4, "socks4"}, {ProxyProtocol::SOCKS5, "socks5"}, {ProxyProtocol::FTP, "ftp"}, {ProxyProtocol::SMTP, "smtp"}, {ProxyProtocol::POP3, "pop3"}, {ProxyProtocol::IMAP, "imap"}, {ProxyProtocol::DNS, "dns"}, {ProxyProtocol::FTP_GATEWAY, "ftp_gateway"}, {ProxyProtocol::TELNET, "telnet"}, {ProxyProtocol::SIP, "sip"}, {ProxyProtocol::WEBSOCKETS, "websockets"}, {ProxyProtocol::RTSP, "rtsp"}, {ProxyProtocol::PPTP, "pptp"}, {ProxyProtocol::L2TP, "l2tp"}, {ProxyProtocol::MPLS, "mpls"}, {ProxyProtocol::IPSEC, "ipsec"}, {ProxyProtocol::REVERSE_PROXY, "reverse_proxy"}, {ProxyProtocol::TRANSPARENT_PROXY, "transparent_proxy"}, {ProxyProtocol::ANONYMIZING_PROXY, "anonymizing_proxy"}, {ProxyProtocol::FORWARD_PROXY, "forward_proxy"}})
}