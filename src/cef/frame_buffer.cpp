#include "frame_buffer.hpp"

namespace big
{
	bool frame_buffer::open_file_mapping()
	{
		const auto handle = OpenFileMappingA(shared_memory_map_access_flag, false, mapped_memory_name);
		if (handle)
		{
			m_shared_memory_file_mapping = handle;

			return true;
		}

		LOG(WARNING) << GetLastError();

		return false;
	}

	void frame_buffer::close_file_mapping()
	{
		if (m_shared_memory_file_mapping)
		{
			CloseHandle(m_shared_memory_file_mapping);
		}
	}

	bool frame_buffer::is_shared_memory_mappable()
	{
		const auto shared_memory = MapViewOfFile(m_shared_memory_file_mapping, shared_memory_map_access_flag, 0, 0, sizeof(no_more_repaint_flag));
		if (!shared_memory)
		{
			return false;
		}

		UnmapViewOfFile(shared_memory);

		return true;
	}

	template<typename TFunc>
	bool frame_buffer::read_from_shared_memory(size_t texture_size, TFunc on_shared_memory_retrieved)
	{
		auto shared_memory_need_repaint_flag = static_cast<std::remove_const_t<decltype(no_more_repaint_flag)>*>(MapViewOfFile(m_shared_memory_file_mapping, shared_memory_map_access_flag, 0, 0, sizeof(no_more_repaint_flag)));
		if (!shared_memory_need_repaint_flag)
		{
			LOG(WARNING) << GetLastError();

			return false;
		}

		if (*shared_memory_need_repaint_flag)
		{
			*shared_memory_need_repaint_flag = no_more_repaint_flag;
			UnmapViewOfFile(shared_memory_need_repaint_flag);

			// allocation granularity is usually equal or more than 64kb,
			// just map from the beginning then just offset manually, doesnt really matter
			constexpr ULARGE_INTEGER file_offset{};
			const uint8_t* shared_memory = static_cast<const uint8_t*>(MapViewOfFile(m_shared_memory_file_mapping,
			                                   shared_memory_map_access_flag,
			                                   file_offset.HighPart,
			                                   file_offset.LowPart,
			                                   texture_size + sizeof(no_more_repaint_flag)))
			    + sizeof(no_more_repaint_flag);
			if (!shared_memory)
			{
				LOG(WARNING) << GetLastError();

				return false;
			}

			if constexpr (!std::is_same_v<TFunc, std::nullptr_t>)
			{
				on_shared_memory_retrieved(shared_memory);
			}

			UnmapViewOfFile(shared_memory);
		}

		return true;
	}

	frame_buffer::frame_buffer(const std::shared_ptr<d3d11::Device>& device) :
	    m_device(device),
	    m_dirty(false)
	{
	}

	std::shared_ptr<d3d11::Texture2D>& frame_buffer::get_texture()
	{
		return m_texture;
	}

	void frame_buffer::make_texture(auto width, auto height, auto buffer_size)
	{
		m_texture = m_device->create_texture(width, height, DXGI_FORMAT_B8G8R8A8_UNORM, nullptr, 0);
	}

	bool frame_buffer::is_shared_memory_ready()
	{
		if (open_file_mapping())
		{
			if (is_shared_memory_mappable())
			{
				return true;
			}
			else
			{
				close_file_mapping();
			}
		}

		return false;
	}

	auto frame_buffer::width()
	{
		return m_texture->width();
	}

	auto frame_buffer::height()
	{
		return m_texture->height();
	}

	size_t frame_buffer::compute_texture_size(uint32_t width, uint32_t height)
	{
		const auto stride = width * required_bytes_per_pixel;
		return stride * height;
	}

	void frame_buffer::on_paint(uint32_t width, uint32_t height, const std::shared_ptr<d3d11::Context>& d3d11_context)
	{
		size_t texture_size = compute_texture_size(width, height);

		if (!m_texture || (m_texture->width() != width) || (m_texture->height() != height))
		{
			make_texture(width, height, texture_size);
		}

		if (read_from_shared_memory(texture_size, [this, d3d11_context](const uint8_t* shared_memory) -> void {
			    d3d11::ScopedBinder<d3d11::Texture2D> binder(d3d11_context, m_texture);
			    m_texture->copy_from(shared_memory, m_texture->width() * required_bytes_per_pixel, m_texture->height());
		    }))
		{
			m_dirty = true;
		}
	}

	void frame_buffer::on_gpu_paint(void* shared_handle)
	{
		// Note: we're not handling keyed mutexes yet

		std::lock_guard<std::mutex> guard(m_lock);

		if (m_texture)
		{
			bool is_shared_texture_different = shared_handle != m_texture->share_handle();
			if (is_shared_texture_different)
			{
				m_texture.reset();
			}
		}
		else
		{
			m_texture = m_device->open_shared_texture((void*)shared_handle);
			if (!m_texture)
			{
				LOG(WARNING) << "Could not open shared texture!";
			}
		}

		m_dirty = true;
	}
}
