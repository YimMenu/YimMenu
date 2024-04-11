#include "backend/looped/looped.hpp"
#include "util/chat.hpp"
#include "services/api/api_service.hpp"
#include "thread_pool.hpp"

namespace big
{
	inline std::atomic_bool translate_lock{false};

	void looped::session_chat_translator()
	{
		while (!translate_Queue.empty() and !translate_lock and g.session.chat_translator)
		{
			if (translate_Queue.size() >= 3)
			{
				LOG(WARNING) << "Message queue is too large, cleaning it. Try enabling spam timer.";
				translate_Queue.pop();
				continue;
			}

			auto& first_message     = translate_Queue.front();
			translate_lock = true;
			g_thread_pool->push([first_message] {
				std::string translate_result;
				std::string sender = "[T]" + first_message.sender;
				translate_result = g_api_service->get_translation_from_LibreTranslate(first_message.content, g.session.chat_translator_target);

				translate_lock = false;
				if (translate_result != "")
				{
					if (g.session.chat_translator_draw)
					{
						if (rage::tlsContext::get()->m_is_script_thread_active)
							chat::draw_chat(translate_result.c_str(), sender.c_str(), false);
						else
							g_fiber_pool->queue_job([translate_result, sender] {
								chat::draw_chat(translate_result.c_str(), sender.c_str(), false);
							});
					}
					if (g.session.chat_translator_print)
						LOG(INFO) << "[" << first_message.sender << "]" << first_message.content << " --> " << translate_result;
				}
			});
			translate_Queue.pop();
		}
	}
}
