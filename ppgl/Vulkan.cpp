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

#include <vulkan/vulkan.h>
#include "ppgl.h"

PPGL::Vulkan::Vulkan() {
    //Check for vulkan support, if not supported exception
    if(!glfwVulkanSupported()) {
        //get glfw error description
        glfwGetError(&description);
        std::cout << PPGL::Exception("Vulkan.h", 30, "glfwVulkanSupported()",
                                     (description == nullptr) ? "No vulkan support" : description);
        throw std::runtime_error("No Vulkan support!");
    }
}

void PPGL::Vulkan::init() {

    createInstanceOfAppInfo();
    createPhysicalDevice();
    getPhysicalDeviceQueueCreateInfo();
    createLogicalDevice();
}

void PPGL::Vulkan::createInstanceOfAppInfo() {
    if(!customAppInfo) {
        //Initialization of App info for Vulkan
        appInfo = {
                VK_STRUCTURE_TYPE_APPLICATION_INFO,
                nullptr,
                "Test",
                VK_MAKE_VERSION(1,0,0),
                "No Engine",
                VK_MAKE_VERSION(1,0,0),
                VK_API_VERSION_1_0
        };

        //Structure to specify parameters of a newly created instance
        //specify's parameters for the instance for appInfo
        instanceCreateInfo = {
                VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                nullptr,
                0,
                &appInfo,
                0,
                nullptr,
                glfwExtensionCount,
                glfwExtensions
        };
    }

    VkResult errorDescription;

    //Create instance of appInfo and check if creation went well
    errorDescription = vkCreateInstance(&instanceCreateInfo, nullptr, &instance);
    if(errorDescription != VK_SUCCESS) {
        std::cout << PPGL::Exception("Vulkan.cpp", 74, "vkCreateInstance()",
                                     ("VkResult: " + std::to_string(int(errorDescription))).c_str());
        throw std::runtime_error("Failed to create Instance for appInfo!");
    }
}

void PPGL::Vulkan::createPhysicalDevice() {
    VkResult errorDescription;

    //Get physical device count and resize physicalDevices to count
    vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);
    physicalDevices = new VkPhysicalDevice[physicalDeviceCount];
    //Create instance of Devices
    errorDescription = vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices);
    //Error checking
    switch (errorDescription) {
        case VK_SUCCESS:
            break;
        case VK_INCOMPLETE:
            break;
        default:
            std::cout << PPGL::Exception("Vulkan.cpp", 90, "vkEnumeratePhysicalDevices()",
                                         ("VkResult: " + std::to_string(int(errorDescription))).c_str());
            throw std::runtime_error("Failed to create physical devices!");
    }

    /*
     * create physical device properties
     */
    physicalDeviceProperties = new VkPhysicalDeviceProperties[physicalDeviceCount];
    // create physical device properties for every physical device
    for (int i = 0; i < physicalDeviceCount; ++i) {
        vkGetPhysicalDeviceProperties(physicalDevices[i], &physicalDeviceProperties[i]);
    }

    //TODO: choose best physical device
    usedPhysicalDevice = 0;
}

void PPGL::Vulkan::getPhysicalDeviceQueueCreateInfo() {
    /*
     * Get physical device queue family properties
     */
    //Get count
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevices[usedPhysicalDevice], &pQueueFamilyPropertyCount, nullptr);
    //Set array size
    pQueueFamilyProperties = new VkQueueFamilyProperties[pQueueFamilyPropertyCount];
    //Get physical device queue family properties
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevices[usedPhysicalDevice], &pQueueFamilyPropertyCount, pQueueFamilyProperties);

    /*
     * Get pQueueFamilyIndex
     */
    uint32_t pQueueFamilyIndex;
    //True if pQueueFamilyIndex was found
    bool foundPQueueFamilyIndex = false;
    //searching for a fitting pQueueFamilyIndex
    for (int i = 0; i < pQueueFamilyPropertyCount; ++i) {
        if(pQueueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            pQueueFamilyIndex = i;
            foundPQueueFamilyIndex = true;
        }
    }
    //Trough error if no pQueueFamilyIndex was found
    if(!foundPQueueFamilyIndex) {
        std::cout << PPGL::Exception("Vulkan.cpp", 172, "-",
                                     "Unable to find pQueueFamilyIndex");
        throw std::runtime_error("Unable to find pQueueFamilyIndex!");
    }

    /*
     * Create pQueueCreateInfo
     */
    //Specifying priorities of work that will be submitted to each created queue
    float queue_priorities[1] = {0.0};
    //create pQueueCreateInfo
    pQueueCreateInfo = {
            VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            nullptr,
            0,
            pQueueFamilyIndex,
            1,
            queue_priorities
    };
}

void PPGL::Vulkan::createLogicalDevice() {
    VkResult errorDescription;

    //Set pCreateInfo if no custom is used
    if(!customDeviceCreateInfo) {
        pDeviceCreateInfo = {
                VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO, //type of this structure
                nullptr,                              //NULL or a pointer to a structure extending this structure
                0,                                     //reserved for future use
                1,                        //unsigned integer size of the pQueueCreateInfos array
                &pQueueCreateInfo,                         //pointer to an array of VkDeviceQueueCreateInfo structures
                0,                          //deprecated and ignored
                nullptr,                  //deprecated and ignored
                0,                       //number of device extensions to enable
                nullptr,               //pointer to an array of enabledExtensionCount
                nullptr                      //pointer to a VkPhysicalDeviceFeatures
        };
    }

    //Create logical device
    errorDescription = vkCreateDevice(physicalDevices[0], &pDeviceCreateInfo, pAllocator, &pDevice);
    //Error checking
    if (errorDescription != VK_SUCCESS) {
        std::cout << PPGL::Exception("Vulkan.cpp", 185, "vkCreateDevice()",
                                     ("VkResult: " + std::to_string(int(errorDescription))).c_str());
        throw std::runtime_error("Failed to create logical device!");
    }
}

void PPGL::Vulkan::setCustomAppInfo(VkApplicationInfo appInfo, VkInstanceCreateInfo instanceCreateInfo) {
    this->appInfo = appInfo;
    this->instanceCreateInfo = instanceCreateInfo;

    customAppInfo = true;
}

void PPGL::Vulkan::setCustomDeviceCreateInfo(VkDeviceCreateInfo deviceCreateInfo) {
    this->pDeviceCreateInfo = deviceCreateInfo;
    customDeviceCreateInfo = true;
}

PPGL::Vulkan::~Vulkan() {
    //Destroy logical device
    vkDestroyDevice(pDevice, pAllocator);
    //Destroy instance for appInfo
    vkDestroyInstance(instance, nullptr);
}
