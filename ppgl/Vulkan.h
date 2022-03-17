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
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

#include "PPGL_Exception.h"

#ifndef PPGL_VULKAN_H
#define PPGL_VULKAN_H

namespace PPGL {
    class Vulkan {
    public:
        ////////////////////////////////////////////////////////////////
        ///
        /// \brief -
        /// \brief Checks for Vulkan support.
        /// \brief -
        ///
        ////////////////////////////////////////////////////////////////
        Vulkan();
        ~Vulkan();

        ////////////////////////////////////////////////////////////////
        ///
        /// \brief -
        /// \brief Creates the RenderPipeline.
        /// \brief -
        ///
        ////////////////////////////////////////////////////////////////
        void init();

        ////////////////////////////////////////////////////////////////
        ///
        /// \brief -
        /// \brief Overwrites the standard appInfo to the custom appInfo.
        /// \brief Has to be called before init.
        /// \brief -
        ///
        /// \param appInfo The custom appInfo.
        /// \param instanceCreateInfo The info to create the instance of appInfo.
        ///
        ////////////////////////////////////////////////////////////////
        void setCustomAppInfo(VkApplicationInfo appInfo, VkInstanceCreateInfo instanceCreateInfo);

        ////////////////////////////////////////////////////////////////
        ///
        /// \brief -
        /// \brief Overwrites the standard deviceCreateInfo to the custom deviceCreateInfo.
        /// \brief Has to be called before init.
        /// \brief -
        ///
        /// \param deviceCreateInfo The custom deviceCreateInfo.
        ///
        ////////////////////////////////////////////////////////////////
        void setCustomDeviceCreateInfo(VkDeviceCreateInfo deviceCreateInfo);

    private:

        ////////////////////////////////////////////////////////////////
        ///
        /// \brief -
        /// \brief Creates an Instance of AppInfo
        /// \brief -
        ///
        ////////////////////////////////////////////////////////////////
        void createInstanceOfAppInfo();

        ////////////////////////////////////////////////////////////////
        ///
        /// \brief -
        /// \brief Creates physical devices
        /// \brief -
        ///
        ////////////////////////////////////////////////////////////////
        void createPhysicalDevice();

        ////////////////////////////////////////////////////////////////
        ///
        /// \brief -
        /// \brief Gets the queue create info
        /// \brief -
        ///
        ////////////////////////////////////////////////////////////////
        void getPhysicalDeviceQueueCreateInfo();

        ////////////////////////////////////////////////////////////////
        ///
        /// \brief -
        /// \brief Creates a logical device
        /// \brief -
        ///
        ////////////////////////////////////////////////////////////////
        void createLogicalDevice();

        //stores glfw error descriptions
        const char *description = nullptr;

        //Vulkan instance
        VkInstance instance{};

        //Declaration of App info for Vulkan
        VkApplicationInfo appInfo{};
        bool customAppInfo = false;
        //Info for creating an Instance
        VkInstanceCreateInfo instanceCreateInfo{};

        //The number of global extensions to enable
        uint32_t glfwExtensionCount = 0;
        //Contains the names of extensions to enable
        const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        ///Devices and queues
        //Physical devices
        //Amount of physical device
        uint32_t physicalDeviceCount;
        //Position of used physical device in array
        uint32_t usedPhysicalDevice;
        //Physical device addresses
        VkPhysicalDevice *physicalDevices;
        //Physical device properties
        VkPhysicalDeviceProperties *physicalDeviceProperties;

        //Queue family
        //Count
        uint32_t pQueueFamilyPropertyCount;

        VkQueueFamilyProperties *pQueueFamilyProperties;
        //Pointer to an array of VkQueueFamilyProperties structures
        VkDeviceQueueCreateInfo pQueueCreateInfo = {};

        //Logical devices
        //Contains information about how to create the device
        VkDeviceCreateInfo pDeviceCreateInfo = {};
        bool customDeviceCreateInfo = false;
        //Controls host memory allocation
        const VkAllocationCallbacks *pAllocator;
        //Logical device
        VkDevice pDevice;
    };
}

#endif //PPGL_VULKAN_H
