/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   GL.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 08.10.2019

	Header file for GL functions
******************************************************************************/
#pragma once
#include <Graphics/Color4f.hpp>

namespace Graphics
{
    struct material;
    class Vertices;

    namespace GL
    {
        // should only be called once
        void setup() noexcept;
        // To do drawing for a frame call BeginDrawing() once at the very beginning.
        void begin_drawing() noexcept;
        // Call Draw() as many times as you need.
		void draw(const Vertices& vertices, const material& material) noexcept;
		// Call Instanced Draw. It is a optimized function call when you want to draw a lot of same object.
		void drawInstanced(const Vertices& vertices, const material& material) noexcept;
        // Lastly call EndDrawing() once at the very end.
        void end_drawing() noexcept;

        void set_clear_color(Color4f color) noexcept;
        void set_display_area(int pixels_width, int pixels_height, int left_x = 0, int bottom_y = 0) noexcept;
        void set_line_width(float line_width) noexcept;
        void enable_multiple_sampling(bool enable_it = true) noexcept;

        void print_context_information();
    };
}
