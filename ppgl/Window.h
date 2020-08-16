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
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "PPGL_Exception.h"

namespace PPGL {

    ////////////////////////////////////////////////////////////////
    ///
    /// \brief -
    /// \brief Stores the values for a glfw window
    /// \brief -
    ///
    /// \param width The desired width, in screen coordinates, of the window. This must be greater than zero.
    /// \param height The desired height, in screen coordinates, of the window. This must be greater than zero.
    /// \param title The initial, UTF-8 encoded window title.
    /// \param monitor The monitor to use for full screen mode, or NULL for windowed mode.
    /// \param share The window whose context to share resources with, or NULL to not share resources.
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
    /// \brief -
    /// \brief Represents a glfw window
    /// \brief -
    ///
    ////////////////////////////////////////////////////////////////
    class Window {
    public:
        //Constructor and destructor
        ////////////////////////////////////////////////////////////////
        ///
        /// \brief -
        /// \brief Initializes the glfw library
        /// \brief -
        ///
        ////////////////////////////////////////////////////////////////
        Window();

        ////////////////////////////////////////////////////////////////
        ///
        /// \brief -
        /// \brief Closes the window and terminates the glfw library
        /// \brief -
        ///
        ////////////////////////////////////////////////////////////////
        ~Window();

        //Functions
        ////////////////////////////////////////////////////////////////
        ///
        /// \brief -
        /// \brief Sets glfw window hint, hints need to be set before call of openWindow
        /// \brief -
        ///
        /// \param hint The glfw window hint to set.
        /// \param value The new value of the glfw window hint
        ///
        ////////////////////////////////////////////////////////////////
        void addWindowHint(int hint, int value);

        ////////////////////////////////////////////////////////////////
        ///
        /// \brief -
        /// \brief Creates glfw window
        /// \brief -
        ///
        /// \param width The desired width, in screen coordinates, of the window. This must be greater than zero.
        /// \param height The desired height, in screen coordinates, of the window. This must be greater than zero.
        /// \param title The initial, UTF-8 encoded window title.
        ///
        ////////////////////////////////////////////////////////////////
        void openWindow(int width, int height, const char *title);

        ////////////////////////////////////////////////////////////////
        ///
        /// \brief -
        /// \brief Sets glfw window hint and creates glfw window
        /// \brief -
        ///
        /// \param windowDummy The desired values, of the glfw window
        ///
        ////////////////////////////////////////////////////////////////
        void openWindow(WindowDummy &windowDummy);

        ////////////////////////////////////////////////////////////////
        ///
        /// \brief -
        /// \brief Needs to be called as long as the window
        /// \brief needs to process pending events.
        /// \brief -
        ///
        /// \return bool
        /// \return TRUE if window is open
        /// \return FALSE if window is closed
        ///
        ////////////////////////////////////////////////////////////////
        bool update();

    private:
        //glfw window
        GLFWwindow* window;

        //stores glfw error descriptions
        const char *description = nullptr;

        //stores PPGL exception
        Exception *exception = nullptr;

    };
}

#endif //PPGL_WINDOW_H
