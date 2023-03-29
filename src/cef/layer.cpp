#include "layer.hpp"

namespace big
{
	layer::layer(const std::shared_ptr<d3d11::Device>& device, bool want_input, bool flip) :
	    m_device(device),
	    m_flip(flip),
	    m_want_input(want_input)
	{
		m_bounds.x = m_bounds.y = m_bounds.width = m_bounds.height = 0.0f;

		make_geometry();

		// Todo CEF: only need to create those once, no?
		m_shaders = m_device->create_basic_shaders();
	}

	layer::~layer()
	{
	}

	Rect layer::bounds() const
	{
		return m_bounds;
	}

	bool layer::want_input() const
	{
		return m_want_input;
	}

	void layer::make_geometry()
	{
		m_geometry = m_device->create_quad(m_bounds.x, m_bounds.y, m_bounds.width, m_bounds.height, m_flip);
	}

	void layer::mouse_click(MouseButton, bool, int32_t, int32_t)
	{
		// default is to do nothing with input
	}

	void layer::mouse_move(bool, int32_t, int32_t)
	{
		// default is to do nothing with input
	}

	void layer::move(float x, float y, float width, float height)
	{
		m_bounds.x      = x;
		m_bounds.y      = y;
		m_bounds.width  = width;
		m_bounds.height = height;

		// obviously, it is not efficient to create the quad everytime we
		// move ... but for now we're just trying to get something on-screen
		make_geometry();
	}

	void layer::tick(double t)
	{
		// nothing to update in the base class
	}

	// helper method for derived classes to draw a textured-quad.
	void layer::render_texture(const std::shared_ptr<d3d11::Context>& ctx, const std::shared_ptr<d3d11::Texture2D>& texture)
	{
		if (texture)
		{
			// bind our states/resource to the pipeline
			d3d11::ScopedBinder<d3d11::Geometry> quad_binder(ctx, m_geometry);
			d3d11::ScopedBinder<d3d11::Effect> fx_binder(ctx, m_shaders);
			d3d11::ScopedBinder<d3d11::Texture2D> tex_binder(ctx, texture);

			// actually draw the quad
			m_geometry->draw();
		}
	}
}
