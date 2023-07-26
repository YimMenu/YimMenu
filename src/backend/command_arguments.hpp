#pragma once
#include <concepts>
#include <stdexcept>
#include <type_traits>

namespace big
{
    template<typename T>
    concept ArgumentLimit = sizeof(T) <= sizeof(uint64_t);

    class command_arguments 
    {
    private:
        const std::size_t m_argument_count;
        std::vector<uint64_t> m_argument_data;
        mutable std::size_t m_idx;

    public:
        command_arguments(std::size_t argument_count = 0) :
            m_argument_count(argument_count),
            m_argument_data(),
            m_idx(0)
        {
            m_argument_data.reserve(argument_count);
        }

        command_arguments(std::size_t argument_count, const command_arguments& other) :
            command_arguments(argument_count)
        {
            std::copy_n(other.m_argument_data.begin(), std::min(argument_count, other.m_argument_data.size()), m_argument_data.begin());
        }

        command_arguments(const std::vector<uint64_t>& vec) :
            command_arguments(vec.size())
        {
            m_argument_data = vec;
        }

        template<typename T = uint64_t>
            requires ArgumentLimit<T>
        T get(std::size_t idx) const
        {
            return reinterpret_cast<const T&>(m_argument_data[idx]);
        }

        template<typename T = uint64_t>
            requires ArgumentLimit<T>
        std::enable_if_t<std::is_pointer_v<T>, T> get(std::size_t idx) const
        {
            return static_cast<T>(m_argument_data[idx]);
        }

        template<typename T = uint64_t>
            requires ArgumentLimit<T>
        T shift() const
        {
            if (m_idx >= m_argument_count)
            {
                throw std::runtime_error("Attempted to shift argument beyond allocated argument size.");
            }

            return reinterpret_cast<const T&>(m_argument_data[m_idx++]);
        }

        template<typename T = uint64_t>
            requires ArgumentLimit<T>
        std::enable_if_t<std::is_pointer_v<T>, T> shift() const
        {
            if (m_idx >= m_argument_count)
            {
                throw std::runtime_error("Attempted to shift argument beyond allocated argument size.");
            }

            return static_cast<const T>(m_argument_data[m_idx++]);
        }

        template<typename T = uint64_t>
            requires ArgumentLimit<T>
        void push(T arg)
        {
            if (m_idx++ >= m_argument_count)
            {
                throw std::runtime_error("Attempted to push argument beyond allocated argument size.");
            }

            m_argument_data.push_back(reinterpret_cast<uint64_t&>(arg));
        }

        template<typename T = uint64_t>
            requires ArgumentLimit<T>
        void set(std::size_t idx, T arg)
        {
            if (idx >= m_argument_count)
            {
                throw std::runtime_error("Attempted to set argument beyond allocated argument size.");
            }

            m_argument_data[idx] = reinterpret_cast<uint64_t&>(arg);
        }

        command_arguments& reset_idx()
        {
            m_idx = 0;

            return *this;
        }

        std::size_t size() const
        {
            return m_argument_data.size();
        }

    };
}