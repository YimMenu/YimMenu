#pragma once

#include "cef/d3d11.hpp"
#include "logger/logger.hpp"

#include <cef/helper.hpp>
#include <mutex>

namespace big
{
	class frame_buffer
	{
	private:
		std::mutex m_lock;

		std::shared_ptr<d3d11::Texture2D> m_texture;
		const std::shared_ptr<d3d11::Device> m_device;

		bool m_dirty;

		// TODO CEF: reuse cef client id and suffix to the mapped memory name
		// in case we want to render multiple windows
		static inline constexpr auto mapped_memory_name = "Local\\YimCefTexture";
		HANDLE m_shared_memory_file_mapping             = nullptr;

		// Use a byte at the beginning of the shared memory to know whether or not we need to map the full buffer and copy it
		static inline constexpr uint8_t no_more_repaint_flag       = 0;
		static inline constexpr auto shared_memory_map_access_flag = FILE_MAP_ALL_ACCESS;

		bool open_file_mapping();
		void close_file_mapping();

		bool is_shared_memory_mappable();

		template<typename T>
		bool read_from_shared_memory(size_t buffer_size, T func);

		void make_texture(auto width, auto height, auto buffer_size);

	public:
		static inline constexpr size_t required_bytes_per_pixel = 4;

		frame_buffer(const std::shared_ptr<d3d11::Device>& device);

		std::shared_ptr<d3d11::Texture2D>& get_texture();

		size_t compute_texture_size(uint32_t width, uint32_t height);

		bool is_shared_memory_ready();

		auto width();

		auto height();

		// Called in response to Cef's OnPaint notification
		void on_paint(uint32_t width, uint32_t height, const std::shared_ptr<d3d11::Context>& d3d11_context);

		// Called in response to Cef's OnAcceleratedPaint notification
		// Note: This is dead code, as CEF currently have shared texture through dx11 broken.
		void on_gpu_paint(void* shared_handle);
	};
}
