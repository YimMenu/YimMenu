#pragma once

#include "cef_service.hpp"
#include "composition.hpp"
#include "frame_buffer.hpp"
#include "helper.hpp"
#include "layer.hpp"
#include "rpc/client.h"

namespace big
{
	class remote_cef_client : public layer
	{
		size_t m_id;

		std::string m_name;
		std::string m_url;

		int m_width;
		int m_height;

		inline static size_t instance_count = 0;

	public:
		std::unique_ptr<frame_buffer> m_frame_buffer;

		remote_cef_client(const std::string& name, const std::string& url, int width, int height, const std::shared_ptr<d3d11::Device>& device, bool want_input);

		~remote_cef_client();

		static std::shared_ptr<remote_cef_client> make(const std::string& name, const std::string& url, int width, int height, const std::shared_ptr<d3d11::Device>& device, bool want_input);

		std::shared_ptr<d3d11::Texture2D> texture(const std::shared_ptr<d3d11::Context>& ctx);

		void render(const std::shared_ptr<d3d11::Context>& d3d11_context) override;

		void mouse_click(MouseButton button, bool up, int32_t x, int32_t y) override;

		void mouse_move(bool leave, int32_t x, int32_t y) override;
	};
}
