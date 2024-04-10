#include "backend/looped/looped.hpp"
#include "gta_util.hpp"
#include "script_local.hpp"
#include "util/chat.hpp"
#include "services/api/api_service.hpp"
#include "thread_pool.hpp"

namespace big
{
	inline std::atomic_bool translate_lock{false};

	void looped::chat_translate()
	{
		while (!MsgQueue.empty() and !translate_lock and g.session.translatechat)
		{
			if (MsgQueue.size() >= 3)
			{
				LOG(WARNING) << "Message queue is too large, cleaning it...";
				while (!MsgQueue.empty())
					MsgQueue.pop();
				continue;
			}

			try
			{
				auto& fmsg     = MsgQueue.front();
				translate_lock = true;
				g_thread_pool->push([fmsg] {
					std::string translatedt;

					translatedt = g_api_service->get_translation_from_LibreT(fmsg.content, g.session.LibreT_target_lang);
					
					translate_lock   = false;
					if (translatedt != "Error" && translatedt != "None")
					{
						if (g.session.translatechat_send)
							chat::send_message(translatedt, nullptr, true, g.session.translatechat_send_team);
						if (g.session.translatechat_print)
							LOG(INFO) << "Translated chat message: " << translatedt;
					}
				});
				MsgQueue.pop();
			}

			catch (std::exception& e)
			{
				LOG(WARNING) << "Error: " << e.what();
			}
		}
	}
}
