#include "fiber_pool.hpp"
#include "util/session.hpp"
#include "views/view.hpp"

namespace big
{
	void view::session()
	{
		components::sub_title("Session Switcher");
		if (ImGui::ListBoxHeader("###session_switch"))
		{
			for (const auto& session_type : sessions)
			{
				components::selectable(session_type.name, false, [&session_type]
				{
					session::join_type(session_type.id);
				});
			}
			ImGui::EndListBox();
		}
	}
}
