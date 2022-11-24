#pragma once

namespace big
{
    class hotkey_service
    {
    public:
        hotkey_service();
        ~hotkey_service();

        struct Hotkey
        {
            int* m_key;
            std::function<void()> m_cb;
        };

        void add(Hotkey);
        void check_keys();

    private:
        std::vector<Hotkey> m_keys;
    };

    inline hotkey_service* g_hotkey_service{};
}
