#include "composition.hpp"

#include "helper.hpp"
#include "remote_cef_client.hpp"
#include "renderer.hpp"

namespace big
{
	composition::composition(std::shared_ptr<d3d11::Device> const& device, int width, int height) :
	    m_width(width),
	    m_height(height),
	    m_vsync(true),
	    m_device(device)
	{
		m_fps       = 0.0;
		m_time      = 0.0;
		m_frame     = 0;
		m_fps_start = cef_helper::time_now();

		g_renderer->add_wndproc_callback([this](HWND hwnd, UINT message, WPARAM wparam, LPARAM lp) {
			switch (message)
			{
			case WM_LBUTTONDOWN: mouse_click(MouseButton::Left, false, lp); break;
			case WM_LBUTTONUP: mouse_click(MouseButton::Left, true, lp); break;
			case WM_RBUTTONDOWN: mouse_click(MouseButton::Right, false, lp); break;
			case WM_RBUTTONUP: mouse_click(MouseButton::Right, true, lp); break;

			case WM_MOUSEMOVE: mouse_move(false, lp); break;
			}
		});
	}

	bool composition::is_vsync() const
	{
		return m_vsync;
	}

	double composition::time() const
	{
		return m_time;
	}

	double composition::fps() const
	{
		return m_fps;
	}

	void composition::add_layer(std::shared_ptr<layer> const& layer)
	{
		if (layer)
		{
			std::lock_guard<std::mutex> guard(m_lock);

			m_layers.push_back(layer);
		}
	}

	bool composition::remove_layer(std::shared_ptr<layer> const& layer)
	{
		size_t match = 0;
		if (layer)
		{
			std::lock_guard<std::mutex> guard(m_lock);
			for (auto i = m_layers.begin(); i != m_layers.end();)
			{
				if ((*i).get() == layer.get())
				{
					i = m_layers.erase(i);
					++match;
				}
				else
				{
					i++;
				}
			}
		}

		return (match > 0);
	}

	void composition::resize(bool vsync, int width, int height)
	{
		m_vsync  = vsync;
		m_width  = width;
		m_height = height;
	}

	void composition::tick(double t)
	{
		m_time = t;

		// don't hold a lock during tick()
		decltype(m_layers) layers;
		{
			std::lock_guard<std::mutex> guard(m_lock);
			layers.assign(m_layers.begin(), m_layers.end());
		}

		for (const auto& layer : layers)
		{
			layer->tick(t);
		}
	}

	void composition::render(const std::shared_ptr<d3d11::Context>& ctx)
	{
		// don't hold a lock during render()
		decltype(m_layers) layers;
		{
			std::lock_guard<std::mutex> guard(m_lock);
			layers.assign(m_layers.begin(), m_layers.end());
		}

		// pretty simple ... just use painter's algorithm and render
		// our layers in order (not doing any depth or 3D here)
		for (const auto& layer : layers)
		{
			layer->render(ctx);
		}

		m_frame++;
		const auto now = cef_helper::time_now();
		if ((now - m_fps_start) > 1000000)
		{
			m_fps = m_frame / double((now - m_fps_start) / 1000000.0);
			LOG(INFO) << "[composition] fps: " << m_fps << " layers: " << layers.size();
			m_frame     = 0;
			m_fps_start = cef_helper::time_now();
		}
	}

	// Forward WM_XXX notification to the layers
	// TODO CEF: This is broken, the cursor ends up in the wrong location
	void composition::mouse_click(MouseButton button, bool up, LPARAM lp)
	{
		auto x = ((int)(short)LOWORD(lp));
		auto y = ((int)(short)HIWORD(lp));

		const auto layer = layer_from_point(x, y);
		if (layer)
		{
			layer->mouse_click(button, up, x, y);
		}
	}

	void composition::mouse_move(bool leave, LPARAM lp)
	{
		auto x = ((int)(short)LOWORD(lp));
		auto y = ((int)(short)HIWORD(lp));

		const auto layer = layer_from_point(x, y);
		if (layer)
		{
			layer->mouse_move(leave, x, y);
		}
	}

	// forward to layer - also make x, y relative to layer
	std::shared_ptr<layer> composition::layer_from_point(int32_t& x, int32_t& y)
	{
		const auto w = width();
		const auto h = height();

		// get thread-safe copy
		decltype(m_layers) layers;
		{
			std::lock_guard<std::mutex> guard(m_lock);
			layers.assign(m_layers.begin(), m_layers.end());
		}

		// walk layers from front to back and find one
		// that contains the mouse point (and wants input)
		for (auto i = layers.rbegin(); i != layers.rend(); i++)
		{
			const auto l = (*i);
			if (l->want_input())
			{
				auto bounds = l->bounds();

				// convert to screen space
				const auto sx = static_cast<int32_t>(bounds.x * w);
				const auto sw = static_cast<int32_t>(bounds.width * w);
				const auto sy = static_cast<int32_t>(bounds.y * h);
				const auto sh = static_cast<int32_t>(bounds.height * h);
				if (x >= sx && x < (sx + sw))
				{
					if (y >= sy && y < (sy + sh))
					{
						// convert points to relative
						x = x - sx;
						y = y - sy;
						return l;
					}
				}
			}
		}

		return nullptr;
	}
}
