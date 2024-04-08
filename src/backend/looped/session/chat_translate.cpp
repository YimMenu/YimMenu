#include "backend/looped/looped.hpp"
#include "gta_util.hpp"
#include "script_local.hpp"
#include "util/chat.hpp"
#include "services/api/api_service.hpp"
#include "thread_pool.hpp"

namespace big
{

	void looped::chat_translate()
	{
		while (!MsgQueue.empty() and !translate_lock and g.session.translatechat)
		{
			if (MsgQueue.size() >= 3)
			{
				LOG(WARNING) << "Message queue is too large, clearing it. Try using keyword blacklist to block spam.";
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
					switch (g.session.t_service_provider)
					{
						case 0:
							translatedt = g_api_service->get_translation_from_Bing(fmsg.content, g.session.Bing_target_lang);
							break;
						case 1:
						    translatedt = g_api_service->get_translation_from_Deeplx(fmsg.content, g.session.DeepL_target_lang);
							break;
					}
					
					translate_lock   = false;
					if (translatedt != "Error" && translatedt != "None")
						chat::send_message(translatedt, nullptr, true, true);
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
