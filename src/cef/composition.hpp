#pragma once

#include "d3d11.hpp"
#include "helper.hpp"

#include <mutex>
#include <vector>
#include "layer.hpp"

namespace big
{
	// A collection of layers.
	// A composition will render 1-N layers to a D3D11 device
	class composition : public std::enable_shared_from_this<composition>
	{
	private:
		std::shared_ptr<layer> layer_from_point(int32_t& x, int32_t& y);

		int m_width;
		int m_height;

		uint32_t m_frame;

		int64_t m_fps_start;
		double m_fps;
		double m_time;

		bool m_vsync;

		const std::shared_ptr<d3d11::Device> m_device;

		std::mutex m_lock;
		std::vector<std::shared_ptr<layer>> m_layers;

	public:
		composition(std::shared_ptr<d3d11::Device> const& device, int width, int height);

		int width() const
		{
			return m_width;
		}
		int height() const
		{
			return m_height;
		}

		double fps() const;
		double time() const;

		bool is_vsync() const;

		void tick(double time);
		void render(std::shared_ptr<d3d11::Context> const&);

		void add_layer(std::shared_ptr<layer> const& layer);
		bool remove_layer(std::shared_ptr<layer> const& layer);

		void resize(bool vsync, int width, int height);

		void mouse_click(MouseButton button, bool up, LPARAM lp);
		void mouse_move(bool leave, LPARAM lp);
	};
}
