#include "backend/looped/looped.hpp"
#include "util/chat.hpp"
#include "services/api/api_service.hpp"
#include "thread_pool.hpp"

namespace big
{
	inline std::atomic_bool translate_lock{false};

	void looped::session_chat_translator()
	{
		if (!translate_queue.empty() && !translate_lock && g.session.chat_translator.enabled)
		{
			if (translate_queue.size() >= 3)
			{
				LOG(WARNING) << "[Chat Translator]Message queue is too large, cleaning it. Try enabling spam timer.";
				translate_queue.pop();
				return;
			}

			auto& first_message     = translate_queue.front();
			translate_lock = true;
			g_thread_pool->push([first_message] {
				std::string translate_result;
				std::string sender = "[T]" + first_message.sender;
				translate_result   = g_api_service->get_translation(first_message.content, g.session.chat_translator.target_language);

				translate_lock = false;
				if (translate_result != "")
				{
					if (g.session.chat_translator.draw_result)
						chat::draw_chat(translate_result, sender, false);
					if (g.session.chat_translator.print_result)
						LOG(INFO) << "[" << first_message.sender << "]" << first_message.content << " --> " << translate_result;
				}
			});
			translate_queue.pop();
		}
	}
}
