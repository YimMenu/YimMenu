#include "backend/looped/looped.hpp"
#include "pointers.hpp"
#include "rage/atSingleton.hpp"
#include "security/RageSecurity.hpp"

namespace big
{
    void looped::system_disable_sigscanner()
    {
        if (g_pointers->m_security->isValid())
        {
            g_pointers->m_security->getInstance()->m_interval = std::numeric_limits<std::uint32_t>::max();
        }
    }
}