#include "remote_cef_client.hpp"

namespace big
{
	std::shared_ptr<remote_cef_client> remote_cef_client::make(const std::string& name, const std::string& url, int width, int height, const std::shared_ptr<d3d11::Device>& device, bool want_input)
	{
		constexpr auto create_cef_client_function_name = "create_cef_client";
		const auto is_success = g_cef_service->m_client->call(create_cef_client_function_name, name, url, width, height).as<bool>();

		LOG(INFO) << "create_cef_client return value: " << is_success;

		if (!is_success)
		{
			return nullptr;
		}

		return std::make_shared<remote_cef_client>("Yim Cef Client", url, width, height, device, want_input);
	}

	remote_cef_client::remote_cef_client(const std::string& name, const std::string& url, int width, int height, const std::shared_ptr<d3d11::Device>& device, bool want_input) :
	    layer(device, want_input, false)
	{
		m_name = name + " " + std::to_string(instance_count);

		m_url = url;

		m_width  = width;
		m_height = height;

		m_id = instance_count;
		instance_count++;
	}

	remote_cef_client::~remote_cef_client()
	{
		instance_count--;
	}

	std::shared_ptr<d3d11::Texture2D> remote_cef_client::texture(const std::shared_ptr<d3d11::Context>& ctx)
	{
		return m_frame_buffer->get_texture();
	}

	void remote_cef_client::render(const std::shared_ptr<d3d11::Context>& d3d11_context)
	{
		m_frame_buffer->on_paint(m_width, m_height, d3d11_context);

		render_texture(d3d11_context, texture(d3d11_context));
	}

	void remote_cef_client::mouse_click(MouseButton button, bool up, int32_t x, int32_t y)
	{
		constexpr auto function_name = "mouse_click";
		g_cef_service->m_client->send(function_name, m_id, static_cast<uint8_t>(button), up, x, y);
	}

	void remote_cef_client::mouse_move(bool leave, int32_t x, int32_t y)
	{
		constexpr auto function_name = "mouse_move";
		g_cef_service->m_client->send(function_name, m_id, leave, x, y);
	}
}
