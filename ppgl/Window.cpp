/*------------------------------------------------------------------------------------------
 * MIT License
 *
 * Copyright (c) 2022 Juna Knop
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

/*
 * Headers
 */
#include "Window.h"

PPGL::Window::Window() {
    //Initialize the glfw library, if initialization fails throw exception
    if(!glfwInit()) {
        //get glfw error description
        glfwGetError(&description);
        //Print exception
        std::cout << PPGL::Exception("Window.cpp", 33, "glfwInit()",
                                     description == nullptr ? "no info" : description) << std::endl;

        //throw exception
        throw std::runtime_error(description == nullptr ? "glfwInit() failed" : description);
     }
}

PPGL::Window::~Window() {
    //close window
    glfwDestroyWindow(window);
    //Terminate the glfw library
    glfwTerminate();
}

void PPGL::Window::addWindowHint(int hint, int value) {
    //set glfw window hints
    glfwWindowHint(hint, value);

    //get glfw error description
    glfwGetError(&description);
    //Check if hints got set properly
    if(description != nullptr) {
        //Print exception
        std::cout << PPGL::Exception("Window.cpp", 54, "glfwWindowHint()", description) << std::endl;

        //throw exception
        throw std::runtime_error(description == nullptr ? "glfwWindowHint() failed" : description);
    }
}

void PPGL::Window::openWindow(int width, int height, const char *title) {
    //Create a window dummy to pass it to openWindow
    WindowDummy windowDummy = {
            width,
            height,
            title,
            nullptr,
            nullptr
    };
    //adds glfw window hints to window
    addWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    //pass information to open Window
    openWindow(windowDummy);
}

void PPGL::Window::openWindow(WindowDummy &windowDummy) {
    //creat window
    window = glfwCreateWindow(windowDummy.width, windowDummy.height, windowDummy.title,
                              windowDummy.monitor, windowDummy.share);
    //Check if window got created properly
    if(!window) {
        //get glfw error description
        glfwGetError(&description);
        //Print exception
        std::cout << PPGL::Exception("Window.cpp", 89, "glfwCreateWindow()",
                                     description == nullptr ? "no info" : description) << std::endl;

        //destroy all remaining windows and cursors
        glfwTerminate();
        //throw exception
        throw std::runtime_error("Window was never opened!");
    }
}

bool PPGL::Window::update() {

    //check if window is open
    if(!glfwWindowShouldClose(window)) {
        //process events that are already in the event queue
        glfwPollEvents();
        //check for errors in Event poll
        glfwGetError(&description);
        if(description != nullptr) {
            exception = new PPGL::Exception("Window.cpp", 120, "glfwPollEvents()", description);
            //prints and throws error
            if (exception != nullptr) {
                std::cout << exception;
                //destroy all remaining windows and cursors
                glfwTerminate();
                throw std::runtime_error(description == nullptr ? "no info" : description);;
            }
        }

        //return true
        return true;
    }

    //if window is closed
    return false;
}