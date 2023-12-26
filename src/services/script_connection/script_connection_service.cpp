#include "script_connection_service.hpp"

namespace big
{
	script_connection* script_connection_service::get_connection(const std::string& script_name, std::optional<player_ptr> target)
	{
		auto hash = rage::joaat(script_name);

		for (auto& cxn : m_script_connections)
			if (cxn->get_script_hash() == hash
			    && ((!target && !cxn->get_target())
			        || (target && cxn->get_target() && target->get()->id() == cxn->get_target()->get()->id())))
				return cxn.get();

		return nullptr;
	}

	script_connection_service::script_connection_service()
	{
		g_script_connection_service = this;
	}

	script_connection_service::~script_connection_service()
	{
		g_script_connection_service = nullptr;
	}

	script_connection* script_connection_service::create_connection(const std::string& script_name, std::optional<player_ptr> target)
	{
		if (auto cxn = get_connection(script_name, target))
			return cxn;

		auto cxn = std::make_unique<script_connection>(script_name, target);
		auto ret = cxn.get();
		m_script_connections.push_back(std::move(cxn));

		return ret;
	}

	void script_connection_service::on_tick()
	{
		std::erase_if(m_script_connections, [](auto& cxn) {
			if (cxn.get()->should_cleanup())
			{
				cxn.get()->cleanup();
				return true;
			}

			return false;
		});
	}
}