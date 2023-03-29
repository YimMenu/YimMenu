#pragma once
#include "rect.hpp"
#include "helper.hpp"
#include "d3d11.hpp"

namespace big
{
	class composition;

	// A simple abstraction for a 2D layer within a composition
	class layer
	{
	protected:
		bool m_flip;
		Rect m_bounds;
		bool m_want_input;

		std::shared_ptr<d3d11::Geometry> m_geometry;
		std::shared_ptr<d3d11::Effect> m_shaders;
		const std::shared_ptr<d3d11::Device> m_device;

		void render_texture(const std::shared_ptr<d3d11::Context>& ctx, const std::shared_ptr<d3d11::Texture2D>& texture);

	public:
		layer(const std::shared_ptr<d3d11::Device>& device, bool want_input, bool flip);
		~layer();

		virtual void make_geometry();

		virtual void move(float x, float y, float width, float height);

		virtual void tick(double);
		virtual void render(const std::shared_ptr<d3d11::Context>& d3d11_context) = 0;

		virtual void mouse_click(MouseButton button, bool up, int32_t x, int32_t y);
		virtual void mouse_move(bool leave, int32_t x, int32_t y);

		Rect bounds() const;

		bool want_input() const;
	};
}
