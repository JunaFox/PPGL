/*------------------------------------------------------------------------------------------
 * MIT License
 *
 * Copyright (c) 2020 Maximilian Knop
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * -----------------------------------------------------------------------------------------
 */

#ifndef PPGL_WINDOW_H
#define PPGL_WINDOW_H

/*
 * Headers
 */
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "PPGL_Exception.h"

namespace PPGL {

    ////////////////////////////////////////////////////////////////
    ///
    /// \brief Stores the values for a glfw window
    ///
    /// \param The desired width, in screen coordinates, of the window. This must be greater than zero.
    /// \param The desired height, in screen coordinates, of the window. This must be greater than zero.
    /// \param The initial, UTF-8 encoded window title.
    /// \param The monitor to use for full screen mode, or NULL for windowed mode.
    /// \param The window whose context to share resources with, or NULL to not share resources.s
    ///
    /// \param width window
    ///
    ////////////////////////////////////////////////////////////////
    struct WindowDummy {
        int width, height;
        const char *title;
        GLFWmonitor *monitor;
        GLFWwindow *share;
    };

    ////////////////////////////////////////////////////////////////
    ///
    /// \brief Represents a glfw window
    ///
    ////////////////////////////////////////////////////////////////
    class Window {
    public:
        ////////////////////////////////////////////////////////////////
        ///
        /// \brief Initializes the glfw library
        ///
        ////////////////////////////////////////////////////////////////
        Window();

        ////////////////////////////////////////////////////////////////
        ///
        /// \brief Terminates the glfw library
        ///
        ////////////////////////////////////////////////////////////////
        ~Window();

        ////////////////////////////////////////////////////////////////
        ///
        /// \brief Sets glfw window hint and creates glfw window
        ///
        /// \param The desired width, in screen coordinates, of the window. This must be greater than zero.
        /// \param The desired height, in screen coordinates, of the window. This must be greater than zero.
        /// \param The initial, UTF-8 encoded window title.
        ///
        ////////////////////////////////////////////////////////////////
        void openWindow(int width, int height, const char *title);

        ////////////////////////////////////////////////////////////////
        ///
        /// \brief Sets glfw window hint and creates glfw window
        ///
        /// \param windowDummy The desired values, of the glfw window
        /// \param hint The glfw window hint to set.
        /// \param value The new value of the glfw window hint
        ///
        ////////////////////////////////////////////////////////////////
        void openWindow(WindowDummy &windowDummy, int hint, int value);

    private:
        GLFWwindow* window;

    };
}

#endif //PPGL_WINDOW_H
