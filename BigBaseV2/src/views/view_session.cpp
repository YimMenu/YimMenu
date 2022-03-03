#include "util/session.hpp"
#include "views/view.hpp"

namespace big
{
	void view::session() {

		if (ImGui::TreeNode("Session Switcher"))
		{
			for (const SessionType& session_type : sessions)
			{
				components::button(session_type.name, [session_type] {
					session::join_type(session_type);
					});
			}

			ImGui::TreePop();

		}
	}
}