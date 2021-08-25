
#ifndef EXTENSION_LOADER_H
#define EXTENSION_LOADER_H

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
#include "../3rd_party/glad/include/vk_platform.h"
//#include "glad/include/vulkan.h"
//#include <vulkan/vulkan.h>

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


// Attach a debugger to the application to give us validation feedback.
// This is usefull as it tells us about any issues without application


VkDebugReportCallbackEXT CreateDebugger(const VkInstance& instance);
void DestroyDebugger(const VkInstance & instance, const VkDebugReportCallbackEXT & debugger);

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                     const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
                                    const VkAllocationCallbacks* pAllocator);

void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

static bool  memory_type_from_properties(VkPhysicalDeviceMemoryProperties& dmemory_properties, uint32_t typeBits,
														 VkFlags requirements_mask, uint32_t *typeIndex);

}


/*

// VK_EXT_debug_utils
//////////////////////////////////

std::unordered_map< VkInstance, PFN_vkCreateDebugUtilsMessengerEXT > CreateDebugUtilsMessengerEXTDispatchTable;
std::unordered_map< VkInstance, PFN_vkDestroyDebugUtilsMessengerEXT > DestroyDebugUtilsMessengerEXTDispatchTable;
std::unordered_map< VkInstance, PFN_vkSubmitDebugUtilsMessageEXT > SubmitDebugUtilsMessageEXTDispatchTable;

void loadDebugUtilsCommands( VkInstance instance ){
	PFN_vkVoidFunction temp_fp;

	temp_fp = vkGetInstanceProcAddr( instance, "vkCreateDebugUtilsMessengerEXT" );
	if( !temp_fp ) throw "Failed to load vkCreateDebugUtilsMessengerEXT"; // check shouldn't be necessary (based on spec)
	CreateDebugUtilsMessengerEXTDispatchTable[instance] = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>( temp_fp );

	temp_fp = vkGetInstanceProcAddr( instance, "vkDestroyDebugUtilsMessengerEXT" );
	if( !temp_fp ) throw "Failed to load vkDestroyDebugUtilsMe  	{
  		// If the surface size is undefined, the size is set to
  		// the size of the images requested.
  		extent.width = width;
  		extent.height = height;
  	}
      else
  	{
  		// If the surface size is defined, the swap chain size must match
  		extent = swapchain_details.capabilities.currentExtent;
  		width = swapchain_details.capabilities.currentExtent.width;
  		height = swapchain_details.capabilities.currentExtent.height;
  	}ssengerEXT"; // check shouldn't be necessary (based on spec)
	DestroyDebugUtilsMessengerEXTDispatchTable[instance] = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>( temp_fp );

	temp_fp = vkGetInstanceProcAddr( instance, "vkSubmitDebugUtilsMessageEXT" );
	if( !temp_fp ) throw "Failed to load vkSubmitDebugUtilsMessageEXT"; // check shouldn't be necessary (based on spec)
	SubmitDebugUtilsMessageEXTDispatchTable[instance] = reinterpret_cast<PFN_vkSubmitDebugUtilsMessageEXT>( temp_fp );
}

void unloadDebugUtilsCommands( VkInstance instance ){
	CreateDebugUtilsMessengerEXTDispatchTable.erase( instance );
	DestroyDebugUtilsMessengerEXTDispatchTable.erase( instance );
	SubmitDebugUtilsMessageEXTDispatchTable.erase( instance );
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugUtilsMessengerEXT(
	VkInstance instance,
	const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
	const VkAllocationCallbacks* pAllocator,
	VkDebugUtilsMessengerEXT* pMessenger
){
	auto dispatched_cmd = CreateDebugUtilsMessengerEXTDispatchTable.at( instance );
	return dispatched_cmd( instance, pCreateInfo, pAllocator, pMessenger );
}

VKAPI_ATTR void VKAPI_CALL vkDestroyDebugUtilsMessengerEXT(
	VkInstance instance,
	VkDebugUtilsMessengerEXT messenger,
	const VkAllocationCallbacks* pAllocator
){
	auto dispatched_cmd = DestroyDebugUtilsMessengerEXTDispatchTable.at( instance );
	return dispatched_cmd( instance, messenger, pAllocator );
}

VKAPI_ATTR void VKAPI_CALL vkSubmitDebugUtilsMessageEXT(
	VkInstance instance,
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageTypes,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData
){
	auto dispatched_cmd = SubmitDebugUtilsMessageEXTDispatchTable.at( instance );
	return dispatched_cmd( instance, messageSeverity, messageTypes, pCallbackData );
}


*/
#endif
