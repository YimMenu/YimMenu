#include "gta/script_handler.hpp"

#include "hooking.hpp"

namespace big
{
	void hooking::hook_script_handler(CGameScriptHandler* handler)
	{
		Hash script_hash = handler->m_script_thread->m_context.m_script_hash;
		{
			auto hook = std::make_unique<vmt_hook>(handler, 20);
			hook->hook(0, &hooks::script_handler_dtor);
			hook->hook(6, &hooks::script_handler_is_networked);
			hook->enable();
			g_hooking->m_handler_hooks[handler] = std::move(hook);
		}
	}

	CGameScriptHandler* hooks::create_script_handler(CGameScriptHandlerMgr* _this, void* unk)
	{
		auto handler = g_hooking->get_original<hooks::create_script_handler>()(_this, unk);

		if (handler == nullptr || handler->m_script_thread == nullptr)
			return handler;

		g_hooking->hook_script_handler(handler);
		return handler;
	};

	bool hooks::script_handler_is_networked(CGameScriptHandler* _this)
	{
		return true;
	}

	bool hooks::script_handler_dtor(CGameScriptHandler* _this, bool free_memory)
	{
		vmt_hook* hook;

		if (g_hooking->m_handler_hooks.count(_this))
		{
			hook = g_hooking->m_handler_hooks[_this].get();

			if (!hook)
				return false;

			hook->disable();
			auto og_func = hook->get_original<decltype(&script_handler_dtor)>(0);
			g_hooking->m_handler_hooks.erase(_this);
			return og_func(_this, free_memory);
		}
		else
		{
			return false;
		}
	}
};
