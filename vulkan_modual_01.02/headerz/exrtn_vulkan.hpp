
#ifndef EXTENSION_LOADER02_H
#define EXTENSION_LOADER02_H

#include <vector>
#include <unordered_map>
#include<cstring>
#include <iostream>

#if defined(_WIN32)
#include <Windows.h>
#elif defined(__linux__)
#define VK_USE_PLATFORM_XCB_KHR
#include <xcb/xcb.h>
#endif

#include <vulkan/vulkan.hpp>

namespace  external_vulkan{

// A basic debug callback. A more advanced one could be created, but this will do for basic debugging
VKAPI_ATTR VkBool32 VKAPI_CALL MyDebugReportCallback(
	VkDebugReportFlagsEXT       flags,
	VkDebugReportObjectTypeEXT  objectType,
	uint64_t                    object,
	size_t                      location,
	int32_t                     messageCode,
	const char*                 pLayerPrefix,
	const char*                 pMessage,
	void*                       pUserData);


VkDebugReportCallbackEXT CreateDebugger(const VkInstance& instance);
void DestroyDebugger(const VkInstance & instance, const VkDebugReportCallbackEXT & debugger);

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                     const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
                                    const VkAllocationCallbacks* pAllocator);

void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);



}

#endif
