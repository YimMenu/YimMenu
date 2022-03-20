#include "util/session.hpp"
#include "views/view.hpp"

namespace big
{
	void view::session() {
		
		for (const SessionType& session_type : sessions)
		{
			components::button(session_type.name, [session_type] {
				session::join_type(session_type);
				});
		}
	}
}