#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__linux__)
#define VK_USE_PLATFORM_XCB_KHR

#include <X11/Xutil.h>
#include <xcb/xcb.h>
#endif

#include "../include/vulkan.h"
#include "../include/vk_platform.h"



//#include <glad/vulkan.h>

#ifndef GLAD_IMPL_UTIL_C_
#define GLAD_IMPL_UTIL_C_

#ifdef _MSC_VER
#define GLAD_IMPL_UTIL_SSCANF sscanf_s
#else
#define GLAD_IMPL_UTIL_SSCANF sscanf
#endif

#endif /* GLAD_IMPL_UTIL_C_ */

#ifdef __cplusplus
extern "C" {
#endif




static GLADapiproc glad_vulkan_internal_loader_get_proc(const char *name);
static GLADloadfunc glad_global_on_demand_vulkan_loader_func = glad_vulkan_internal_loader_get_proc;

void gladSetVulkanOnDemandLoader(GLADloadfunc loader) {
    glad_global_on_demand_vulkan_loader_func = loader;
}

static GLADapiproc glad_vk_on_demand_loader(const char *name) {
    GLADapiproc result = NULL;
    if (result == NULL && glad_global_on_demand_vulkan_loader_func != NULL) {
        result = glad_global_on_demand_vulkan_loader_func(name);
    }
    /* this provokes a segmentation fault if there was no loader or no loader returned something useful */
    return result;
}

static void _pre_call_vulkan_callback_default(const char *name, GLADapiproc apiproc, int len_args, ...) {
    (void) name;
    (void) apiproc;
    (void) len_args;
}
static void _post_call_vulkan_callback_default(void *ret, const char *name, GLADapiproc apiproc, int len_args, ...) {
    (void) ret;
    (void) name;
    (void) apiproc;
    (void) len_args;
}

static GLADprecallback _pre_call_vulkan_callback = _pre_call_vulkan_callback_default;
void gladSetVulkanPreCallback(GLADprecallback cb) {
    _pre_call_vulkan_callback = cb;
}
static GLADpostcallback _post_call_vulkan_callback = _post_call_vulkan_callback_default;
void gladSetVulkanPostCallback(GLADpostcallback cb) {
    _post_call_vulkan_callback = cb;
}

static VkResult GLAD_API_PTR glad_on_demand_impl_vkAcquireNextImage2KHR(VkDevice device, const VkAcquireNextImageInfoKHR * pAcquireInfo, uint32_t * pImageIndex) {
    glad_vkAcquireNextImage2KHR = (PFN_vkAcquireNextImage2KHR) glad_vk_on_demand_loader("vkAcquireNextImage2KHR");
    return glad_vkAcquireNextImage2KHR(device, pAcquireInfo, pImageIndex);
}
PFN_vkAcquireNextImage2KHR glad_vkAcquireNextImage2KHR = glad_on_demand_impl_vkAcquireNextImage2KHR;
static VkResult GLAD_API_PTR glad_debug_impl_vkAcquireNextImage2KHR(VkDevice device, const VkAcquireNextImageInfoKHR * pAcquireInfo, uint32_t * pImageIndex) {
    VkResult ret;
    _pre_call_vulkan_callback("vkAcquireNextImage2KHR", (GLADapiproc) glad_vkAcquireNextImage2KHR, 3, device, pAcquireInfo, pImageIndex);
    ret = glad_vkAcquireNextImage2KHR(device, pAcquireInfo, pImageIndex);
    _post_call_vulkan_callback((void*) &ret, "vkAcquireNextImage2KHR", (GLADapiproc) glad_vkAcquireNextImage2KHR, 3, device, pAcquireInfo, pImageIndex);
    return ret;
}
PFN_vkAcquireNextImage2KHR glad_debug_vkAcquireNextImage2KHR = glad_debug_impl_vkAcquireNextImage2KHR;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkAcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t * pImageIndex) {
    glad_vkAcquireNextImageKHR = (PFN_vkAcquireNextImageKHR) glad_vk_on_demand_loader("vkAcquireNextImageKHR");
    return glad_vkAcquireNextImageKHR(device, swapchain, timeout, semaphore, fence, pImageIndex);
}
PFN_vkAcquireNextImageKHR glad_vkAcquireNextImageKHR = glad_on_demand_impl_vkAcquireNextImageKHR;
static VkResult GLAD_API_PTR glad_debug_impl_vkAcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t * pImageIndex) {
    VkResult ret;
    _pre_call_vulkan_callback("vkAcquireNextImageKHR", (GLADapiproc) glad_vkAcquireNextImageKHR, 6, device, swapchain, timeout, semaphore, fence, pImageIndex);
    ret = glad_vkAcquireNextImageKHR(device, swapchain, timeout, semaphore, fence, pImageIndex);
    _post_call_vulkan_callback((void*) &ret, "vkAcquireNextImageKHR", (GLADapiproc) glad_vkAcquireNextImageKHR, 6, device, swapchain, timeout, semaphore, fence, pImageIndex);
    return ret;
}
PFN_vkAcquireNextImageKHR glad_debug_vkAcquireNextImageKHR = glad_debug_impl_vkAcquireNextImageKHR;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkAcquireProfilingLockKHR(VkDevice device, const VkAcquireProfilingLockInfoKHR * pInfo) {
    glad_vkAcquireProfilingLockKHR = (PFN_vkAcquireProfilingLockKHR) glad_vk_on_demand_loader("vkAcquireProfilingLockKHR");
    return glad_vkAcquireProfilingLockKHR(device, pInfo);
}
PFN_vkAcquireProfilingLockKHR glad_vkAcquireProfilingLockKHR = glad_on_demand_impl_vkAcquireProfilingLockKHR;
static VkResult GLAD_API_PTR glad_debug_impl_vkAcquireProfilingLockKHR(VkDevice device, const VkAcquireProfilingLockInfoKHR * pInfo) {
    VkResult ret;
    _pre_call_vulkan_callback("vkAcquireProfilingLockKHR", (GLADapiproc) glad_vkAcquireProfilingLockKHR, 2, device, pInfo);
    ret = glad_vkAcquireProfilingLockKHR(device, pInfo);
    _post_call_vulkan_callback((void*) &ret, "vkAcquireProfilingLockKHR", (GLADapiproc) glad_vkAcquireProfilingLockKHR, 2, device, pInfo);
    return ret;
}
PFN_vkAcquireProfilingLockKHR glad_debug_vkAcquireProfilingLockKHR = glad_debug_impl_vkAcquireProfilingLockKHR;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkAllocateCommandBuffers(VkDevice device, const VkCommandBufferAllocateInfo * pAllocateInfo, VkCommandBuffer * pCommandBuffers) {
    glad_vkAllocateCommandBuffers = (PFN_vkAllocateCommandBuffers) glad_vk_on_demand_loader("vkAllocateCommandBuffers");
    return glad_vkAllocateCommandBuffers(device, pAllocateInfo, pCommandBuffers);
}
PFN_vkAllocateCommandBuffers glad_vkAllocateCommandBuffers = glad_on_demand_impl_vkAllocateCommandBuffers;
static VkResult GLAD_API_PTR glad_debug_impl_vkAllocateCommandBuffers(VkDevice device, const VkCommandBufferAllocateInfo * pAllocateInfo, VkCommandBuffer * pCommandBuffers) {
    VkResult ret;
    _pre_call_vulkan_callback("vkAllocateCommandBuffers", (GLADapiproc) glad_vkAllocateCommandBuffers, 3, device, pAllocateInfo, pCommandBuffers);
    ret = glad_vkAllocateCommandBuffers(device, pAllocateInfo, pCommandBuffers);
    _post_call_vulkan_callback((void*) &ret, "vkAllocateCommandBuffers", (GLADapiproc) glad_vkAllocateCommandBuffers, 3, device, pAllocateInfo, pCommandBuffers);
    return ret;
}
PFN_vkAllocateCommandBuffers glad_debug_vkAllocateCommandBuffers = glad_debug_impl_vkAllocateCommandBuffers;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkAllocateDescriptorSets(VkDevice device, const VkDescriptorSetAllocateInfo * pAllocateInfo, VkDescriptorSet * pDescriptorSets) {
    glad_vkAllocateDescriptorSets = (PFN_vkAllocateDescriptorSets) glad_vk_on_demand_loader("vkAllocateDescriptorSets");
    return glad_vkAllocateDescriptorSets(device, pAllocateInfo, pDescriptorSets);
}
PFN_vkAllocateDescriptorSets glad_vkAllocateDescriptorSets = glad_on_demand_impl_vkAllocateDescriptorSets;
static VkResult GLAD_API_PTR glad_debug_impl_vkAllocateDescriptorSets(VkDevice device, const VkDescriptorSetAllocateInfo * pAllocateInfo, VkDescriptorSet * pDescriptorSets) {
    VkResult ret;
    _pre_call_vulkan_callback("vkAllocateDescriptorSets", (GLADapiproc) glad_vkAllocateDescriptorSets, 3, device, pAllocateInfo, pDescriptorSets);
    ret = glad_vkAllocateDescriptorSets(device, pAllocateInfo, pDescriptorSets);
    _post_call_vulkan_callback((void*) &ret, "vkAllocateDescriptorSets", (GLADapiproc) glad_vkAllocateDescriptorSets, 3, device, pAllocateInfo, pDescriptorSets);
    return ret;
}
PFN_vkAllocateDescriptorSets glad_debug_vkAllocateDescriptorSets = glad_debug_impl_vkAllocateDescriptorSets;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkAllocateMemory(VkDevice device, const VkMemoryAllocateInfo * pAllocateInfo, const VkAllocationCallbacks * pAllocator, VkDeviceMemory * pMemory) {
    glad_vkAllocateMemory = (PFN_vkAllocateMemory) glad_vk_on_demand_loader("vkAllocateMemory");
    return glad_vkAllocateMemory(device, pAllocateInfo, pAllocator, pMemory);
}
PFN_vkAllocateMemory glad_vkAllocateMemory = glad_on_demand_impl_vkAllocateMemory;
static VkResult GLAD_API_PTR glad_debug_impl_vkAllocateMemory(VkDevice device, const VkMemoryAllocateInfo * pAllocateInfo, const VkAllocationCallbacks * pAllocator, VkDeviceMemory * pMemory) {
    VkResult ret;
    _pre_call_vulkan_callback("vkAllocateMemory", (GLADapiproc) glad_vkAllocateMemory, 4, device, pAllocateInfo, pAllocator, pMemory);
    ret = glad_vkAllocateMemory(device, pAllocateInfo, pAllocator, pMemory);
    _post_call_vulkan_callback((void*) &ret, "vkAllocateMemory", (GLADapiproc) glad_vkAllocateMemory, 4, device, pAllocateInfo, pAllocator, pMemory);
    return ret;
}
PFN_vkAllocateMemory glad_debug_vkAllocateMemory = glad_debug_impl_vkAllocateMemory;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkBeginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo * pBeginInfo) {
    glad_vkBeginCommandBuffer = (PFN_vkBeginCommandBuffer) glad_vk_on_demand_loader("vkBeginCommandBuffer");
    return glad_vkBeginCommandBuffer(commandBuffer, pBeginInfo);
}
PFN_vkBeginCommandBuffer glad_vkBeginCommandBuffer = glad_on_demand_impl_vkBeginCommandBuffer;
static VkResult GLAD_API_PTR glad_debug_impl_vkBeginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo * pBeginInfo) {
    VkResult ret;
    _pre_call_vulkan_callback("vkBeginCommandBuffer", (GLADapiproc) glad_vkBeginCommandBuffer, 2, commandBuffer, pBeginInfo);
    ret = glad_vkBeginCommandBuffer(commandBuffer, pBeginInfo);
    _post_call_vulkan_callback((void*) &ret, "vkBeginCommandBuffer", (GLADapiproc) glad_vkBeginCommandBuffer, 2, commandBuffer, pBeginInfo);
    return ret;
}
PFN_vkBeginCommandBuffer glad_debug_vkBeginCommandBuffer = glad_debug_impl_vkBeginCommandBuffer;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkBindBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset) {
    glad_vkBindBufferMemory = (PFN_vkBindBufferMemory) glad_vk_on_demand_loader("vkBindBufferMemory");
    return glad_vkBindBufferMemory(device, buffer, memory, memoryOffset);
}
PFN_vkBindBufferMemory glad_vkBindBufferMemory = glad_on_demand_impl_vkBindBufferMemory;
static VkResult GLAD_API_PTR glad_debug_impl_vkBindBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset) {
    VkResult ret;
    _pre_call_vulkan_callback("vkBindBufferMemory", (GLADapiproc) glad_vkBindBufferMemory, 4, device, buffer, memory, memoryOffset);
    ret = glad_vkBindBufferMemory(device, buffer, memory, memoryOffset);
    _post_call_vulkan_callback((void*) &ret, "vkBindBufferMemory", (GLADapiproc) glad_vkBindBufferMemory, 4, device, buffer, memory, memoryOffset);
    return ret;
}
PFN_vkBindBufferMemory glad_debug_vkBindBufferMemory = glad_debug_impl_vkBindBufferMemory;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkBindBufferMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo * pBindInfos) {
    glad_vkBindBufferMemory2 = (PFN_vkBindBufferMemory2) glad_vk_on_demand_loader("vkBindBufferMemory2");
    return glad_vkBindBufferMemory2(device, bindInfoCount, pBindInfos);
}
PFN_vkBindBufferMemory2 glad_vkBindBufferMemory2 = glad_on_demand_impl_vkBindBufferMemory2;
static VkResult GLAD_API_PTR glad_debug_impl_vkBindBufferMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo * pBindInfos) {
    VkResult ret;
    _pre_call_vulkan_callback("vkBindBufferMemory2", (GLADapiproc) glad_vkBindBufferMemory2, 3, device, bindInfoCount, pBindInfos);
    ret = glad_vkBindBufferMemory2(device, bindInfoCount, pBindInfos);
    _post_call_vulkan_callback((void*) &ret, "vkBindBufferMemory2", (GLADapiproc) glad_vkBindBufferMemory2, 3, device, bindInfoCount, pBindInfos);
    return ret;
}
PFN_vkBindBufferMemory2 glad_debug_vkBindBufferMemory2 = glad_debug_impl_vkBindBufferMemory2;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkBindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset) {
    glad_vkBindImageMemory = (PFN_vkBindImageMemory) glad_vk_on_demand_loader("vkBindImageMemory");
    return glad_vkBindImageMemory(device, image, memory, memoryOffset);
}
PFN_vkBindImageMemory glad_vkBindImageMemory = glad_on_demand_impl_vkBindImageMemory;
static VkResult GLAD_API_PTR glad_debug_impl_vkBindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset) {
    VkResult ret;
    _pre_call_vulkan_callback("vkBindImageMemory", (GLADapiproc) glad_vkBindImageMemory, 4, device, image, memory, memoryOffset);
    ret = glad_vkBindImageMemory(device, image, memory, memoryOffset);
    _post_call_vulkan_callback((void*) &ret, "vkBindImageMemory", (GLADapiproc) glad_vkBindImageMemory, 4, device, image, memory, memoryOffset);
    return ret;
}
PFN_vkBindImageMemory glad_debug_vkBindImageMemory = glad_debug_impl_vkBindImageMemory;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkBindImageMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo * pBindInfos) {
    glad_vkBindImageMemory2 = (PFN_vkBindImageMemory2) glad_vk_on_demand_loader("vkBindImageMemory2");
    return glad_vkBindImageMemory2(device, bindInfoCount, pBindInfos);
}
PFN_vkBindImageMemory2 glad_vkBindImageMemory2 = glad_on_demand_impl_vkBindImageMemory2;
static VkResult GLAD_API_PTR glad_debug_impl_vkBindImageMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo * pBindInfos) {
    VkResult ret;
    _pre_call_vulkan_callback("vkBindImageMemory2", (GLADapiproc) glad_vkBindImageMemory2, 3, device, bindInfoCount, pBindInfos);
    ret = glad_vkBindImageMemory2(device, bindInfoCount, pBindInfos);
    _post_call_vulkan_callback((void*) &ret, "vkBindImageMemory2", (GLADapiproc) glad_vkBindImageMemory2, 3, device, bindInfoCount, pBindInfos);
    return ret;
}
PFN_vkBindImageMemory2 glad_debug_vkBindImageMemory2 = glad_debug_impl_vkBindImageMemory2;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT * pLabelInfo) {
    glad_vkCmdBeginDebugUtilsLabelEXT = (PFN_vkCmdBeginDebugUtilsLabelEXT) glad_vk_on_demand_loader("vkCmdBeginDebugUtilsLabelEXT");
    glad_vkCmdBeginDebugUtilsLabelEXT(commandBuffer, pLabelInfo);
}
PFN_vkCmdBeginDebugUtilsLabelEXT glad_vkCmdBeginDebugUtilsLabelEXT = glad_on_demand_impl_vkCmdBeginDebugUtilsLabelEXT;
static void GLAD_API_PTR glad_debug_impl_vkCmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT * pLabelInfo) {
    _pre_call_vulkan_callback("vkCmdBeginDebugUtilsLabelEXT", (GLADapiproc) glad_vkCmdBeginDebugUtilsLabelEXT, 2, commandBuffer, pLabelInfo);
    glad_vkCmdBeginDebugUtilsLabelEXT(commandBuffer, pLabelInfo);
    _post_call_vulkan_callback(NULL, "vkCmdBeginDebugUtilsLabelEXT", (GLADapiproc) glad_vkCmdBeginDebugUtilsLabelEXT, 2, commandBuffer, pLabelInfo);
    
}
PFN_vkCmdBeginDebugUtilsLabelEXT glad_debug_vkCmdBeginDebugUtilsLabelEXT = glad_debug_impl_vkCmdBeginDebugUtilsLabelEXT;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdBeginQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags) {
    glad_vkCmdBeginQuery = (PFN_vkCmdBeginQuery) glad_vk_on_demand_loader("vkCmdBeginQuery");
    glad_vkCmdBeginQuery(commandBuffer, queryPool, query, flags);
}
PFN_vkCmdBeginQuery glad_vkCmdBeginQuery = glad_on_demand_impl_vkCmdBeginQuery;
static void GLAD_API_PTR glad_debug_impl_vkCmdBeginQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags) {
    _pre_call_vulkan_callback("vkCmdBeginQuery", (GLADapiproc) glad_vkCmdBeginQuery, 4, commandBuffer, queryPool, query, flags);
    glad_vkCmdBeginQuery(commandBuffer, queryPool, query, flags);
    _post_call_vulkan_callback(NULL, "vkCmdBeginQuery", (GLADapiproc) glad_vkCmdBeginQuery, 4, commandBuffer, queryPool, query, flags);
    
}
PFN_vkCmdBeginQuery glad_debug_vkCmdBeginQuery = glad_debug_impl_vkCmdBeginQuery;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdBeginRenderPass(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo * pRenderPassBegin, VkSubpassContents contents) {
    glad_vkCmdBeginRenderPass = (PFN_vkCmdBeginRenderPass) glad_vk_on_demand_loader("vkCmdBeginRenderPass");
    glad_vkCmdBeginRenderPass(commandBuffer, pRenderPassBegin, contents);
}
PFN_vkCmdBeginRenderPass glad_vkCmdBeginRenderPass = glad_on_demand_impl_vkCmdBeginRenderPass;
static void GLAD_API_PTR glad_debug_impl_vkCmdBeginRenderPass(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo * pRenderPassBegin, VkSubpassContents contents) {
    _pre_call_vulkan_callback("vkCmdBeginRenderPass", (GLADapiproc) glad_vkCmdBeginRenderPass, 3, commandBuffer, pRenderPassBegin, contents);
    glad_vkCmdBeginRenderPass(commandBuffer, pRenderPassBegin, contents);
    _post_call_vulkan_callback(NULL, "vkCmdBeginRenderPass", (GLADapiproc) glad_vkCmdBeginRenderPass, 3, commandBuffer, pRenderPassBegin, contents);
    
}
PFN_vkCmdBeginRenderPass glad_debug_vkCmdBeginRenderPass = glad_debug_impl_vkCmdBeginRenderPass;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdBeginRenderPass2(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo * pRenderPassBegin, const VkSubpassBeginInfo * pSubpassBeginInfo) {
    glad_vkCmdBeginRenderPass2 = (PFN_vkCmdBeginRenderPass2) glad_vk_on_demand_loader("vkCmdBeginRenderPass2");
    glad_vkCmdBeginRenderPass2(commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
}
PFN_vkCmdBeginRenderPass2 glad_vkCmdBeginRenderPass2 = glad_on_demand_impl_vkCmdBeginRenderPass2;
static void GLAD_API_PTR glad_debug_impl_vkCmdBeginRenderPass2(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo * pRenderPassBegin, const VkSubpassBeginInfo * pSubpassBeginInfo) {
    _pre_call_vulkan_callback("vkCmdBeginRenderPass2", (GLADapiproc) glad_vkCmdBeginRenderPass2, 3, commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
    glad_vkCmdBeginRenderPass2(commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
    _post_call_vulkan_callback(NULL, "vkCmdBeginRenderPass2", (GLADapiproc) glad_vkCmdBeginRenderPass2, 3, commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
    
}
PFN_vkCmdBeginRenderPass2 glad_debug_vkCmdBeginRenderPass2 = glad_debug_impl_vkCmdBeginRenderPass2;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet * pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t * pDynamicOffsets) {
    glad_vkCmdBindDescriptorSets = (PFN_vkCmdBindDescriptorSets) glad_vk_on_demand_loader("vkCmdBindDescriptorSets");
    glad_vkCmdBindDescriptorSets(commandBuffer, pipelineBindPoint, layout, firstSet, descriptorSetCount, pDescriptorSets, dynamicOffsetCount, pDynamicOffsets);
}
PFN_vkCmdBindDescriptorSets glad_vkCmdBindDescriptorSets = glad_on_demand_impl_vkCmdBindDescriptorSets;
static void GLAD_API_PTR glad_debug_impl_vkCmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet * pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t * pDynamicOffsets) {
    _pre_call_vulkan_callback("vkCmdBindDescriptorSets", (GLADapiproc) glad_vkCmdBindDescriptorSets, 8, commandBuffer, pipelineBindPoint, layout, firstSet, descriptorSetCount, pDescriptorSets, dynamicOffsetCount, pDynamicOffsets);
    glad_vkCmdBindDescriptorSets(commandBuffer, pipelineBindPoint, layout, firstSet, descriptorSetCount, pDescriptorSets, dynamicOffsetCount, pDynamicOffsets);
    _post_call_vulkan_callback(NULL, "vkCmdBindDescriptorSets", (GLADapiproc) glad_vkCmdBindDescriptorSets, 8, commandBuffer, pipelineBindPoint, layout, firstSet, descriptorSetCount, pDescriptorSets, dynamicOffsetCount, pDynamicOffsets);
    
}
PFN_vkCmdBindDescriptorSets glad_debug_vkCmdBindDescriptorSets = glad_debug_impl_vkCmdBindDescriptorSets;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType) {
    glad_vkCmdBindIndexBuffer = (PFN_vkCmdBindIndexBuffer) glad_vk_on_demand_loader("vkCmdBindIndexBuffer");
    glad_vkCmdBindIndexBuffer(commandBuffer, buffer, offset, indexType);
}
PFN_vkCmdBindIndexBuffer glad_vkCmdBindIndexBuffer = glad_on_demand_impl_vkCmdBindIndexBuffer;
static void GLAD_API_PTR glad_debug_impl_vkCmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType) {
    _pre_call_vulkan_callback("vkCmdBindIndexBuffer", (GLADapiproc) glad_vkCmdBindIndexBuffer, 4, commandBuffer, buffer, offset, indexType);
    glad_vkCmdBindIndexBuffer(commandBuffer, buffer, offset, indexType);
    _post_call_vulkan_callback(NULL, "vkCmdBindIndexBuffer", (GLADapiproc) glad_vkCmdBindIndexBuffer, 4, commandBuffer, buffer, offset, indexType);
    
}
PFN_vkCmdBindIndexBuffer glad_debug_vkCmdBindIndexBuffer = glad_debug_impl_vkCmdBindIndexBuffer;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline) {
    glad_vkCmdBindPipeline = (PFN_vkCmdBindPipeline) glad_vk_on_demand_loader("vkCmdBindPipeline");
    glad_vkCmdBindPipeline(commandBuffer, pipelineBindPoint, pipeline);
}
PFN_vkCmdBindPipeline glad_vkCmdBindPipeline = glad_on_demand_impl_vkCmdBindPipeline;
static void GLAD_API_PTR glad_debug_impl_vkCmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline) {
    _pre_call_vulkan_callback("vkCmdBindPipeline", (GLADapiproc) glad_vkCmdBindPipeline, 3, commandBuffer, pipelineBindPoint, pipeline);
    glad_vkCmdBindPipeline(commandBuffer, pipelineBindPoint, pipeline);
    _post_call_vulkan_callback(NULL, "vkCmdBindPipeline", (GLADapiproc) glad_vkCmdBindPipeline, 3, commandBuffer, pipelineBindPoint, pipeline);
    
}
PFN_vkCmdBindPipeline glad_debug_vkCmdBindPipeline = glad_debug_impl_vkCmdBindPipeline;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer * pBuffers, const VkDeviceSize * pOffsets) {
    glad_vkCmdBindVertexBuffers = (PFN_vkCmdBindVertexBuffers) glad_vk_on_demand_loader("vkCmdBindVertexBuffers");
    glad_vkCmdBindVertexBuffers(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets);
}
PFN_vkCmdBindVertexBuffers glad_vkCmdBindVertexBuffers = glad_on_demand_impl_vkCmdBindVertexBuffers;
static void GLAD_API_PTR glad_debug_impl_vkCmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer * pBuffers, const VkDeviceSize * pOffsets) {
    _pre_call_vulkan_callback("vkCmdBindVertexBuffers", (GLADapiproc) glad_vkCmdBindVertexBuffers, 5, commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets);
    glad_vkCmdBindVertexBuffers(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets);
    _post_call_vulkan_callback(NULL, "vkCmdBindVertexBuffers", (GLADapiproc) glad_vkCmdBindVertexBuffers, 5, commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets);
    
}
PFN_vkCmdBindVertexBuffers glad_debug_vkCmdBindVertexBuffers = glad_debug_impl_vkCmdBindVertexBuffers;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageBlit * pRegions, VkFilter filter) {
    glad_vkCmdBlitImage = (PFN_vkCmdBlitImage) glad_vk_on_demand_loader("vkCmdBlitImage");
    glad_vkCmdBlitImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter);
}
PFN_vkCmdBlitImage glad_vkCmdBlitImage = glad_on_demand_impl_vkCmdBlitImage;
static void GLAD_API_PTR glad_debug_impl_vkCmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageBlit * pRegions, VkFilter filter) {
    _pre_call_vulkan_callback("vkCmdBlitImage", (GLADapiproc) glad_vkCmdBlitImage, 8, commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter);
    glad_vkCmdBlitImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter);
    _post_call_vulkan_callback(NULL, "vkCmdBlitImage", (GLADapiproc) glad_vkCmdBlitImage, 8, commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter);
    
}
PFN_vkCmdBlitImage glad_debug_vkCmdBlitImage = glad_debug_impl_vkCmdBlitImage;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, const VkClearAttachment * pAttachments, uint32_t rectCount, const VkClearRect * pRects) {
    glad_vkCmdClearAttachments = (PFN_vkCmdClearAttachments) glad_vk_on_demand_loader("vkCmdClearAttachments");
    glad_vkCmdClearAttachments(commandBuffer, attachmentCount, pAttachments, rectCount, pRects);
}
PFN_vkCmdClearAttachments glad_vkCmdClearAttachments = glad_on_demand_impl_vkCmdClearAttachments;
static void GLAD_API_PTR glad_debug_impl_vkCmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, const VkClearAttachment * pAttachments, uint32_t rectCount, const VkClearRect * pRects) {
    _pre_call_vulkan_callback("vkCmdClearAttachments", (GLADapiproc) glad_vkCmdClearAttachments, 5, commandBuffer, attachmentCount, pAttachments, rectCount, pRects);
    glad_vkCmdClearAttachments(commandBuffer, attachmentCount, pAttachments, rectCount, pRects);
    _post_call_vulkan_callback(NULL, "vkCmdClearAttachments", (GLADapiproc) glad_vkCmdClearAttachments, 5, commandBuffer, attachmentCount, pAttachments, rectCount, pRects);
    
}
PFN_vkCmdClearAttachments glad_debug_vkCmdClearAttachments = glad_debug_impl_vkCmdClearAttachments;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearColorValue * pColor, uint32_t rangeCount, const VkImageSubresourceRange * pRanges) {
    glad_vkCmdClearColorImage = (PFN_vkCmdClearColorImage) glad_vk_on_demand_loader("vkCmdClearColorImage");
    glad_vkCmdClearColorImage(commandBuffer, image, imageLayout, pColor, rangeCount, pRanges);
}
PFN_vkCmdClearColorImage glad_vkCmdClearColorImage = glad_on_demand_impl_vkCmdClearColorImage;
static void GLAD_API_PTR glad_debug_impl_vkCmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearColorValue * pColor, uint32_t rangeCount, const VkImageSubresourceRange * pRanges) {
    _pre_call_vulkan_callback("vkCmdClearColorImage", (GLADapiproc) glad_vkCmdClearColorImage, 6, commandBuffer, image, imageLayout, pColor, rangeCount, pRanges);
    glad_vkCmdClearColorImage(commandBuffer, image, imageLayout, pColor, rangeCount, pRanges);
    _post_call_vulkan_callback(NULL, "vkCmdClearColorImage", (GLADapiproc) glad_vkCmdClearColorImage, 6, commandBuffer, image, imageLayout, pColor, rangeCount, pRanges);
    
}
PFN_vkCmdClearColorImage glad_debug_vkCmdClearColorImage = glad_debug_impl_vkCmdClearColorImage;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearDepthStencilValue * pDepthStencil, uint32_t rangeCount, const VkImageSubresourceRange * pRanges) {
    glad_vkCmdClearDepthStencilImage = (PFN_vkCmdClearDepthStencilImage) glad_vk_on_demand_loader("vkCmdClearDepthStencilImage");
    glad_vkCmdClearDepthStencilImage(commandBuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges);
}
PFN_vkCmdClearDepthStencilImage glad_vkCmdClearDepthStencilImage = glad_on_demand_impl_vkCmdClearDepthStencilImage;
static void GLAD_API_PTR glad_debug_impl_vkCmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearDepthStencilValue * pDepthStencil, uint32_t rangeCount, const VkImageSubresourceRange * pRanges) {
    _pre_call_vulkan_callback("vkCmdClearDepthStencilImage", (GLADapiproc) glad_vkCmdClearDepthStencilImage, 6, commandBuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges);
    glad_vkCmdClearDepthStencilImage(commandBuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges);
    _post_call_vulkan_callback(NULL, "vkCmdClearDepthStencilImage", (GLADapiproc) glad_vkCmdClearDepthStencilImage, 6, commandBuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges);
    
}
PFN_vkCmdClearDepthStencilImage glad_debug_vkCmdClearDepthStencilImage = glad_debug_impl_vkCmdClearDepthStencilImage;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy * pRegions) {
    glad_vkCmdCopyBuffer = (PFN_vkCmdCopyBuffer) glad_vk_on_demand_loader("vkCmdCopyBuffer");
    glad_vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions);
}
PFN_vkCmdCopyBuffer glad_vkCmdCopyBuffer = glad_on_demand_impl_vkCmdCopyBuffer;
static void GLAD_API_PTR glad_debug_impl_vkCmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy * pRegions) {
    _pre_call_vulkan_callback("vkCmdCopyBuffer", (GLADapiproc) glad_vkCmdCopyBuffer, 5, commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions);
    glad_vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions);
    _post_call_vulkan_callback(NULL, "vkCmdCopyBuffer", (GLADapiproc) glad_vkCmdCopyBuffer, 5, commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions);
    
}
PFN_vkCmdCopyBuffer glad_debug_vkCmdCopyBuffer = glad_debug_impl_vkCmdCopyBuffer;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy * pRegions) {
    glad_vkCmdCopyBufferToImage = (PFN_vkCmdCopyBufferToImage) glad_vk_on_demand_loader("vkCmdCopyBufferToImage");
    glad_vkCmdCopyBufferToImage(commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions);
}
PFN_vkCmdCopyBufferToImage glad_vkCmdCopyBufferToImage = glad_on_demand_impl_vkCmdCopyBufferToImage;
static void GLAD_API_PTR glad_debug_impl_vkCmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy * pRegions) {
    _pre_call_vulkan_callback("vkCmdCopyBufferToImage", (GLADapiproc) glad_vkCmdCopyBufferToImage, 6, commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions);
    glad_vkCmdCopyBufferToImage(commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions);
    _post_call_vulkan_callback(NULL, "vkCmdCopyBufferToImage", (GLADapiproc) glad_vkCmdCopyBufferToImage, 6, commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions);
    
}
PFN_vkCmdCopyBufferToImage glad_debug_vkCmdCopyBufferToImage = glad_debug_impl_vkCmdCopyBufferToImage;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageCopy * pRegions) {
    glad_vkCmdCopyImage = (PFN_vkCmdCopyImage) glad_vk_on_demand_loader("vkCmdCopyImage");
    glad_vkCmdCopyImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
}
PFN_vkCmdCopyImage glad_vkCmdCopyImage = glad_on_demand_impl_vkCmdCopyImage;
static void GLAD_API_PTR glad_debug_impl_vkCmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageCopy * pRegions) {
    _pre_call_vulkan_callback("vkCmdCopyImage", (GLADapiproc) glad_vkCmdCopyImage, 7, commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
    glad_vkCmdCopyImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
    _post_call_vulkan_callback(NULL, "vkCmdCopyImage", (GLADapiproc) glad_vkCmdCopyImage, 7, commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
    
}
PFN_vkCmdCopyImage glad_debug_vkCmdCopyImage = glad_debug_impl_vkCmdCopyImage;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy * pRegions) {
    glad_vkCmdCopyImageToBuffer = (PFN_vkCmdCopyImageToBuffer) glad_vk_on_demand_loader("vkCmdCopyImageToBuffer");
    glad_vkCmdCopyImageToBuffer(commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions);
}
PFN_vkCmdCopyImageToBuffer glad_vkCmdCopyImageToBuffer = glad_on_demand_impl_vkCmdCopyImageToBuffer;
static void GLAD_API_PTR glad_debug_impl_vkCmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy * pRegions) {
    _pre_call_vulkan_callback("vkCmdCopyImageToBuffer", (GLADapiproc) glad_vkCmdCopyImageToBuffer, 6, commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions);
    glad_vkCmdCopyImageToBuffer(commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions);
    _post_call_vulkan_callback(NULL, "vkCmdCopyImageToBuffer", (GLADapiproc) glad_vkCmdCopyImageToBuffer, 6, commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions);
    
}
PFN_vkCmdCopyImageToBuffer glad_debug_vkCmdCopyImageToBuffer = glad_debug_impl_vkCmdCopyImageToBuffer;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags) {
    glad_vkCmdCopyQueryPoolResults = (PFN_vkCmdCopyQueryPoolResults) glad_vk_on_demand_loader("vkCmdCopyQueryPoolResults");
    glad_vkCmdCopyQueryPoolResults(commandBuffer, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags);
}
PFN_vkCmdCopyQueryPoolResults glad_vkCmdCopyQueryPoolResults = glad_on_demand_impl_vkCmdCopyQueryPoolResults;
static void GLAD_API_PTR glad_debug_impl_vkCmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags) {
    _pre_call_vulkan_callback("vkCmdCopyQueryPoolResults", (GLADapiproc) glad_vkCmdCopyQueryPoolResults, 8, commandBuffer, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags);
    glad_vkCmdCopyQueryPoolResults(commandBuffer, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags);
    _post_call_vulkan_callback(NULL, "vkCmdCopyQueryPoolResults", (GLADapiproc) glad_vkCmdCopyQueryPoolResults, 8, commandBuffer, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags);
    
}
PFN_vkCmdCopyQueryPoolResults glad_debug_vkCmdCopyQueryPoolResults = glad_debug_impl_vkCmdCopyQueryPoolResults;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdDebugMarkerBeginEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT * pMarkerInfo) {
    glad_vkCmdDebugMarkerBeginEXT = (PFN_vkCmdDebugMarkerBeginEXT) glad_vk_on_demand_loader("vkCmdDebugMarkerBeginEXT");
    glad_vkCmdDebugMarkerBeginEXT(commandBuffer, pMarkerInfo);
}
PFN_vkCmdDebugMarkerBeginEXT glad_vkCmdDebugMarkerBeginEXT = glad_on_demand_impl_vkCmdDebugMarkerBeginEXT;
static void GLAD_API_PTR glad_debug_impl_vkCmdDebugMarkerBeginEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT * pMarkerInfo) {
    _pre_call_vulkan_callback("vkCmdDebugMarkerBeginEXT", (GLADapiproc) glad_vkCmdDebugMarkerBeginEXT, 2, commandBuffer, pMarkerInfo);
    glad_vkCmdDebugMarkerBeginEXT(commandBuffer, pMarkerInfo);
    _post_call_vulkan_callback(NULL, "vkCmdDebugMarkerBeginEXT", (GLADapiproc) glad_vkCmdDebugMarkerBeginEXT, 2, commandBuffer, pMarkerInfo);
    
}
PFN_vkCmdDebugMarkerBeginEXT glad_debug_vkCmdDebugMarkerBeginEXT = glad_debug_impl_vkCmdDebugMarkerBeginEXT;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdDebugMarkerEndEXT(VkCommandBuffer commandBuffer) {
    glad_vkCmdDebugMarkerEndEXT = (PFN_vkCmdDebugMarkerEndEXT) glad_vk_on_demand_loader("vkCmdDebugMarkerEndEXT");
    glad_vkCmdDebugMarkerEndEXT(commandBuffer);
}
PFN_vkCmdDebugMarkerEndEXT glad_vkCmdDebugMarkerEndEXT = glad_on_demand_impl_vkCmdDebugMarkerEndEXT;
static void GLAD_API_PTR glad_debug_impl_vkCmdDebugMarkerEndEXT(VkCommandBuffer commandBuffer) {
    _pre_call_vulkan_callback("vkCmdDebugMarkerEndEXT", (GLADapiproc) glad_vkCmdDebugMarkerEndEXT, 1, commandBuffer);
    glad_vkCmdDebugMarkerEndEXT(commandBuffer);
    _post_call_vulkan_callback(NULL, "vkCmdDebugMarkerEndEXT", (GLADapiproc) glad_vkCmdDebugMarkerEndEXT, 1, commandBuffer);
    
}
PFN_vkCmdDebugMarkerEndEXT glad_debug_vkCmdDebugMarkerEndEXT = glad_debug_impl_vkCmdDebugMarkerEndEXT;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdDebugMarkerInsertEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT * pMarkerInfo) {
    glad_vkCmdDebugMarkerInsertEXT = (PFN_vkCmdDebugMarkerInsertEXT) glad_vk_on_demand_loader("vkCmdDebugMarkerInsertEXT");
    glad_vkCmdDebugMarkerInsertEXT(commandBuffer, pMarkerInfo);
}
PFN_vkCmdDebugMarkerInsertEXT glad_vkCmdDebugMarkerInsertEXT = glad_on_demand_impl_vkCmdDebugMarkerInsertEXT;
static void GLAD_API_PTR glad_debug_impl_vkCmdDebugMarkerInsertEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT * pMarkerInfo) {
    _pre_call_vulkan_callback("vkCmdDebugMarkerInsertEXT", (GLADapiproc) glad_vkCmdDebugMarkerInsertEXT, 2, commandBuffer, pMarkerInfo);
    glad_vkCmdDebugMarkerInsertEXT(commandBuffer, pMarkerInfo);
    _post_call_vulkan_callback(NULL, "vkCmdDebugMarkerInsertEXT", (GLADapiproc) glad_vkCmdDebugMarkerInsertEXT, 2, commandBuffer, pMarkerInfo);
    
}
PFN_vkCmdDebugMarkerInsertEXT glad_debug_vkCmdDebugMarkerInsertEXT = glad_debug_impl_vkCmdDebugMarkerInsertEXT;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdDispatch(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) {
    glad_vkCmdDispatch = (PFN_vkCmdDispatch) glad_vk_on_demand_loader("vkCmdDispatch");
    glad_vkCmdDispatch(commandBuffer, groupCountX, groupCountY, groupCountZ);
}
PFN_vkCmdDispatch glad_vkCmdDispatch = glad_on_demand_impl_vkCmdDispatch;
static void GLAD_API_PTR glad_debug_impl_vkCmdDispatch(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) {
    _pre_call_vulkan_callback("vkCmdDispatch", (GLADapiproc) glad_vkCmdDispatch, 4, commandBuffer, groupCountX, groupCountY, groupCountZ);
    glad_vkCmdDispatch(commandBuffer, groupCountX, groupCountY, groupCountZ);
    _post_call_vulkan_callback(NULL, "vkCmdDispatch", (GLADapiproc) glad_vkCmdDispatch, 4, commandBuffer, groupCountX, groupCountY, groupCountZ);
    
}
PFN_vkCmdDispatch glad_debug_vkCmdDispatch = glad_debug_impl_vkCmdDispatch;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdDispatchBase(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) {
    glad_vkCmdDispatchBase = (PFN_vkCmdDispatchBase) glad_vk_on_demand_loader("vkCmdDispatchBase");
    glad_vkCmdDispatchBase(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
}
PFN_vkCmdDispatchBase glad_vkCmdDispatchBase = glad_on_demand_impl_vkCmdDispatchBase;
static void GLAD_API_PTR glad_debug_impl_vkCmdDispatchBase(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) {
    _pre_call_vulkan_callback("vkCmdDispatchBase", (GLADapiproc) glad_vkCmdDispatchBase, 7, commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
    glad_vkCmdDispatchBase(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
    _post_call_vulkan_callback(NULL, "vkCmdDispatchBase", (GLADapiproc) glad_vkCmdDispatchBase, 7, commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
    
}
PFN_vkCmdDispatchBase glad_debug_vkCmdDispatchBase = glad_debug_impl_vkCmdDispatchBase;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdDispatchBaseKHR(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) {
    glad_vkCmdDispatchBaseKHR = (PFN_vkCmdDispatchBaseKHR) glad_vk_on_demand_loader("vkCmdDispatchBaseKHR");
    glad_vkCmdDispatchBaseKHR(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
}
PFN_vkCmdDispatchBaseKHR glad_vkCmdDispatchBaseKHR = glad_on_demand_impl_vkCmdDispatchBaseKHR;
static void GLAD_API_PTR glad_debug_impl_vkCmdDispatchBaseKHR(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) {
    _pre_call_vulkan_callback("vkCmdDispatchBaseKHR", (GLADapiproc) glad_vkCmdDispatchBaseKHR, 7, commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
    glad_vkCmdDispatchBaseKHR(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
    _post_call_vulkan_callback(NULL, "vkCmdDispatchBaseKHR", (GLADapiproc) glad_vkCmdDispatchBaseKHR, 7, commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
    
}
PFN_vkCmdDispatchBaseKHR glad_debug_vkCmdDispatchBaseKHR = glad_debug_impl_vkCmdDispatchBaseKHR;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdDispatchIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) {
    glad_vkCmdDispatchIndirect = (PFN_vkCmdDispatchIndirect) glad_vk_on_demand_loader("vkCmdDispatchIndirect");
    glad_vkCmdDispatchIndirect(commandBuffer, buffer, offset);
}
PFN_vkCmdDispatchIndirect glad_vkCmdDispatchIndirect = glad_on_demand_impl_vkCmdDispatchIndirect;
static void GLAD_API_PTR glad_debug_impl_vkCmdDispatchIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) {
    _pre_call_vulkan_callback("vkCmdDispatchIndirect", (GLADapiproc) glad_vkCmdDispatchIndirect, 3, commandBuffer, buffer, offset);
    glad_vkCmdDispatchIndirect(commandBuffer, buffer, offset);
    _post_call_vulkan_callback(NULL, "vkCmdDispatchIndirect", (GLADapiproc) glad_vkCmdDispatchIndirect, 3, commandBuffer, buffer, offset);
    
}
PFN_vkCmdDispatchIndirect glad_debug_vkCmdDispatchIndirect = glad_debug_impl_vkCmdDispatchIndirect;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
    glad_vkCmdDraw = (PFN_vkCmdDraw) glad_vk_on_demand_loader("vkCmdDraw");
    glad_vkCmdDraw(commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
}
PFN_vkCmdDraw glad_vkCmdDraw = glad_on_demand_impl_vkCmdDraw;
static void GLAD_API_PTR glad_debug_impl_vkCmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
    _pre_call_vulkan_callback("vkCmdDraw", (GLADapiproc) glad_vkCmdDraw, 5, commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
    glad_vkCmdDraw(commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
    _post_call_vulkan_callback(NULL, "vkCmdDraw", (GLADapiproc) glad_vkCmdDraw, 5, commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
    
}
PFN_vkCmdDraw glad_debug_vkCmdDraw = glad_debug_impl_vkCmdDraw;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdDrawIndexed(VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) {
    glad_vkCmdDrawIndexed = (PFN_vkCmdDrawIndexed) glad_vk_on_demand_loader("vkCmdDrawIndexed");
    glad_vkCmdDrawIndexed(commandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
}
PFN_vkCmdDrawIndexed glad_vkCmdDrawIndexed = glad_on_demand_impl_vkCmdDrawIndexed;
static void GLAD_API_PTR glad_debug_impl_vkCmdDrawIndexed(VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) {
    _pre_call_vulkan_callback("vkCmdDrawIndexed", (GLADapiproc) glad_vkCmdDrawIndexed, 6, commandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
    glad_vkCmdDrawIndexed(commandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
    _post_call_vulkan_callback(NULL, "vkCmdDrawIndexed", (GLADapiproc) glad_vkCmdDrawIndexed, 6, commandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
    
}
PFN_vkCmdDrawIndexed glad_debug_vkCmdDrawIndexed = glad_debug_impl_vkCmdDrawIndexed;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdDrawIndexedIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) {
    glad_vkCmdDrawIndexedIndirect = (PFN_vkCmdDrawIndexedIndirect) glad_vk_on_demand_loader("vkCmdDrawIndexedIndirect");
    glad_vkCmdDrawIndexedIndirect(commandBuffer, buffer, offset, drawCount, stride);
}
PFN_vkCmdDrawIndexedIndirect glad_vkCmdDrawIndexedIndirect = glad_on_demand_impl_vkCmdDrawIndexedIndirect;
static void GLAD_API_PTR glad_debug_impl_vkCmdDrawIndexedIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) {
    _pre_call_vulkan_callback("vkCmdDrawIndexedIndirect", (GLADapiproc) glad_vkCmdDrawIndexedIndirect, 5, commandBuffer, buffer, offset, drawCount, stride);
    glad_vkCmdDrawIndexedIndirect(commandBuffer, buffer, offset, drawCount, stride);
    _post_call_vulkan_callback(NULL, "vkCmdDrawIndexedIndirect", (GLADapiproc) glad_vkCmdDrawIndexedIndirect, 5, commandBuffer, buffer, offset, drawCount, stride);
    
}
PFN_vkCmdDrawIndexedIndirect glad_debug_vkCmdDrawIndexedIndirect = glad_debug_impl_vkCmdDrawIndexedIndirect;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdDrawIndexedIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) {
    glad_vkCmdDrawIndexedIndirectCount = (PFN_vkCmdDrawIndexedIndirectCount) glad_vk_on_demand_loader("vkCmdDrawIndexedIndirectCount");
    glad_vkCmdDrawIndexedIndirectCount(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}
PFN_vkCmdDrawIndexedIndirectCount glad_vkCmdDrawIndexedIndirectCount = glad_on_demand_impl_vkCmdDrawIndexedIndirectCount;
static void GLAD_API_PTR glad_debug_impl_vkCmdDrawIndexedIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) {
    _pre_call_vulkan_callback("vkCmdDrawIndexedIndirectCount", (GLADapiproc) glad_vkCmdDrawIndexedIndirectCount, 7, commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    glad_vkCmdDrawIndexedIndirectCount(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    _post_call_vulkan_callback(NULL, "vkCmdDrawIndexedIndirectCount", (GLADapiproc) glad_vkCmdDrawIndexedIndirectCount, 7, commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    
}
PFN_vkCmdDrawIndexedIndirectCount glad_debug_vkCmdDrawIndexedIndirectCount = glad_debug_impl_vkCmdDrawIndexedIndirectCount;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdDrawIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) {
    glad_vkCmdDrawIndirect = (PFN_vkCmdDrawIndirect) glad_vk_on_demand_loader("vkCmdDrawIndirect");
    glad_vkCmdDrawIndirect(commandBuffer, buffer, offset, drawCount, stride);
}
PFN_vkCmdDrawIndirect glad_vkCmdDrawIndirect = glad_on_demand_impl_vkCmdDrawIndirect;
static void GLAD_API_PTR glad_debug_impl_vkCmdDrawIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) {
    _pre_call_vulkan_callback("vkCmdDrawIndirect", (GLADapiproc) glad_vkCmdDrawIndirect, 5, commandBuffer, buffer, offset, drawCount, stride);
    glad_vkCmdDrawIndirect(commandBuffer, buffer, offset, drawCount, stride);
    _post_call_vulkan_callback(NULL, "vkCmdDrawIndirect", (GLADapiproc) glad_vkCmdDrawIndirect, 5, commandBuffer, buffer, offset, drawCount, stride);
    
}
PFN_vkCmdDrawIndirect glad_debug_vkCmdDrawIndirect = glad_debug_impl_vkCmdDrawIndirect;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdDrawIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) {
    glad_vkCmdDrawIndirectCount = (PFN_vkCmdDrawIndirectCount) glad_vk_on_demand_loader("vkCmdDrawIndirectCount");
    glad_vkCmdDrawIndirectCount(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}
PFN_vkCmdDrawIndirectCount glad_vkCmdDrawIndirectCount = glad_on_demand_impl_vkCmdDrawIndirectCount;
static void GLAD_API_PTR glad_debug_impl_vkCmdDrawIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) {
    _pre_call_vulkan_callback("vkCmdDrawIndirectCount", (GLADapiproc) glad_vkCmdDrawIndirectCount, 7, commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    glad_vkCmdDrawIndirectCount(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    _post_call_vulkan_callback(NULL, "vkCmdDrawIndirectCount", (GLADapiproc) glad_vkCmdDrawIndirectCount, 7, commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    
}
PFN_vkCmdDrawIndirectCount glad_debug_vkCmdDrawIndirectCount = glad_debug_impl_vkCmdDrawIndirectCount;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdEndDebugUtilsLabelEXT(VkCommandBuffer commandBuffer) {
    glad_vkCmdEndDebugUtilsLabelEXT = (PFN_vkCmdEndDebugUtilsLabelEXT) glad_vk_on_demand_loader("vkCmdEndDebugUtilsLabelEXT");
    glad_vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}
PFN_vkCmdEndDebugUtilsLabelEXT glad_vkCmdEndDebugUtilsLabelEXT = glad_on_demand_impl_vkCmdEndDebugUtilsLabelEXT;
static void GLAD_API_PTR glad_debug_impl_vkCmdEndDebugUtilsLabelEXT(VkCommandBuffer commandBuffer) {
    _pre_call_vulkan_callback("vkCmdEndDebugUtilsLabelEXT", (GLADapiproc) glad_vkCmdEndDebugUtilsLabelEXT, 1, commandBuffer);
    glad_vkCmdEndDebugUtilsLabelEXT(commandBuffer);
    _post_call_vulkan_callback(NULL, "vkCmdEndDebugUtilsLabelEXT", (GLADapiproc) glad_vkCmdEndDebugUtilsLabelEXT, 1, commandBuffer);
    
}
PFN_vkCmdEndDebugUtilsLabelEXT glad_debug_vkCmdEndDebugUtilsLabelEXT = glad_debug_impl_vkCmdEndDebugUtilsLabelEXT;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdEndQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query) {
    glad_vkCmdEndQuery = (PFN_vkCmdEndQuery) glad_vk_on_demand_loader("vkCmdEndQuery");
    glad_vkCmdEndQuery(commandBuffer, queryPool, query);
}
PFN_vkCmdEndQuery glad_vkCmdEndQuery = glad_on_demand_impl_vkCmdEndQuery;
static void GLAD_API_PTR glad_debug_impl_vkCmdEndQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query) {
    _pre_call_vulkan_callback("vkCmdEndQuery", (GLADapiproc) glad_vkCmdEndQuery, 3, commandBuffer, queryPool, query);
    glad_vkCmdEndQuery(commandBuffer, queryPool, query);
    _post_call_vulkan_callback(NULL, "vkCmdEndQuery", (GLADapiproc) glad_vkCmdEndQuery, 3, commandBuffer, queryPool, query);
    
}
PFN_vkCmdEndQuery glad_debug_vkCmdEndQuery = glad_debug_impl_vkCmdEndQuery;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdEndRenderPass(VkCommandBuffer commandBuffer) {
    glad_vkCmdEndRenderPass = (PFN_vkCmdEndRenderPass) glad_vk_on_demand_loader("vkCmdEndRenderPass");
    glad_vkCmdEndRenderPass(commandBuffer);
}
PFN_vkCmdEndRenderPass glad_vkCmdEndRenderPass = glad_on_demand_impl_vkCmdEndRenderPass;
static void GLAD_API_PTR glad_debug_impl_vkCmdEndRenderPass(VkCommandBuffer commandBuffer) {
    _pre_call_vulkan_callback("vkCmdEndRenderPass", (GLADapiproc) glad_vkCmdEndRenderPass, 1, commandBuffer);
    glad_vkCmdEndRenderPass(commandBuffer);
    _post_call_vulkan_callback(NULL, "vkCmdEndRenderPass", (GLADapiproc) glad_vkCmdEndRenderPass, 1, commandBuffer);
    
}
PFN_vkCmdEndRenderPass glad_debug_vkCmdEndRenderPass = glad_debug_impl_vkCmdEndRenderPass;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdEndRenderPass2(VkCommandBuffer commandBuffer, const VkSubpassEndInfo * pSubpassEndInfo) {
    glad_vkCmdEndRenderPass2 = (PFN_vkCmdEndRenderPass2) glad_vk_on_demand_loader("vkCmdEndRenderPass2");
    glad_vkCmdEndRenderPass2(commandBuffer, pSubpassEndInfo);
}
PFN_vkCmdEndRenderPass2 glad_vkCmdEndRenderPass2 = glad_on_demand_impl_vkCmdEndRenderPass2;
static void GLAD_API_PTR glad_debug_impl_vkCmdEndRenderPass2(VkCommandBuffer commandBuffer, const VkSubpassEndInfo * pSubpassEndInfo) {
    _pre_call_vulkan_callback("vkCmdEndRenderPass2", (GLADapiproc) glad_vkCmdEndRenderPass2, 2, commandBuffer, pSubpassEndInfo);
    glad_vkCmdEndRenderPass2(commandBuffer, pSubpassEndInfo);
    _post_call_vulkan_callback(NULL, "vkCmdEndRenderPass2", (GLADapiproc) glad_vkCmdEndRenderPass2, 2, commandBuffer, pSubpassEndInfo);
    
}
PFN_vkCmdEndRenderPass2 glad_debug_vkCmdEndRenderPass2 = glad_debug_impl_vkCmdEndRenderPass2;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdExecuteCommands(VkCommandBuffer commandBuffer, uint32_t commandBufferCount, const VkCommandBuffer * pCommandBuffers) {
    glad_vkCmdExecuteCommands = (PFN_vkCmdExecuteCommands) glad_vk_on_demand_loader("vkCmdExecuteCommands");
    glad_vkCmdExecuteCommands(commandBuffer, commandBufferCount, pCommandBuffers);
}
PFN_vkCmdExecuteCommands glad_vkCmdExecuteCommands = glad_on_demand_impl_vkCmdExecuteCommands;
static void GLAD_API_PTR glad_debug_impl_vkCmdExecuteCommands(VkCommandBuffer commandBuffer, uint32_t commandBufferCount, const VkCommandBuffer * pCommandBuffers) {
    _pre_call_vulkan_callback("vkCmdExecuteCommands", (GLADapiproc) glad_vkCmdExecuteCommands, 3, commandBuffer, commandBufferCount, pCommandBuffers);
    glad_vkCmdExecuteCommands(commandBuffer, commandBufferCount, pCommandBuffers);
    _post_call_vulkan_callback(NULL, "vkCmdExecuteCommands", (GLADapiproc) glad_vkCmdExecuteCommands, 3, commandBuffer, commandBufferCount, pCommandBuffers);
    
}
PFN_vkCmdExecuteCommands glad_debug_vkCmdExecuteCommands = glad_debug_impl_vkCmdExecuteCommands;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data) {
    glad_vkCmdFillBuffer = (PFN_vkCmdFillBuffer) glad_vk_on_demand_loader("vkCmdFillBuffer");
    glad_vkCmdFillBuffer(commandBuffer, dstBuffer, dstOffset, size, data);
}
PFN_vkCmdFillBuffer glad_vkCmdFillBuffer = glad_on_demand_impl_vkCmdFillBuffer;
static void GLAD_API_PTR glad_debug_impl_vkCmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data) {
    _pre_call_vulkan_callback("vkCmdFillBuffer", (GLADapiproc) glad_vkCmdFillBuffer, 5, commandBuffer, dstBuffer, dstOffset, size, data);
    glad_vkCmdFillBuffer(commandBuffer, dstBuffer, dstOffset, size, data);
    _post_call_vulkan_callback(NULL, "vkCmdFillBuffer", (GLADapiproc) glad_vkCmdFillBuffer, 5, commandBuffer, dstBuffer, dstOffset, size, data);
    
}
PFN_vkCmdFillBuffer glad_debug_vkCmdFillBuffer = glad_debug_impl_vkCmdFillBuffer;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT * pLabelInfo) {
    glad_vkCmdInsertDebugUtilsLabelEXT = (PFN_vkCmdInsertDebugUtilsLabelEXT) glad_vk_on_demand_loader("vkCmdInsertDebugUtilsLabelEXT");
    glad_vkCmdInsertDebugUtilsLabelEXT(commandBuffer, pLabelInfo);
}
PFN_vkCmdInsertDebugUtilsLabelEXT glad_vkCmdInsertDebugUtilsLabelEXT = glad_on_demand_impl_vkCmdInsertDebugUtilsLabelEXT;
static void GLAD_API_PTR glad_debug_impl_vkCmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT * pLabelInfo) {
    _pre_call_vulkan_callback("vkCmdInsertDebugUtilsLabelEXT", (GLADapiproc) glad_vkCmdInsertDebugUtilsLabelEXT, 2, commandBuffer, pLabelInfo);
    glad_vkCmdInsertDebugUtilsLabelEXT(commandBuffer, pLabelInfo);
    _post_call_vulkan_callback(NULL, "vkCmdInsertDebugUtilsLabelEXT", (GLADapiproc) glad_vkCmdInsertDebugUtilsLabelEXT, 2, commandBuffer, pLabelInfo);
    
}
PFN_vkCmdInsertDebugUtilsLabelEXT glad_debug_vkCmdInsertDebugUtilsLabelEXT = glad_debug_impl_vkCmdInsertDebugUtilsLabelEXT;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdNextSubpass(VkCommandBuffer commandBuffer, VkSubpassContents contents) {
    glad_vkCmdNextSubpass = (PFN_vkCmdNextSubpass) glad_vk_on_demand_loader("vkCmdNextSubpass");
    glad_vkCmdNextSubpass(commandBuffer, contents);
}
PFN_vkCmdNextSubpass glad_vkCmdNextSubpass = glad_on_demand_impl_vkCmdNextSubpass;
static void GLAD_API_PTR glad_debug_impl_vkCmdNextSubpass(VkCommandBuffer commandBuffer, VkSubpassContents contents) {
    _pre_call_vulkan_callback("vkCmdNextSubpass", (GLADapiproc) glad_vkCmdNextSubpass, 2, commandBuffer, contents);
    glad_vkCmdNextSubpass(commandBuffer, contents);
    _post_call_vulkan_callback(NULL, "vkCmdNextSubpass", (GLADapiproc) glad_vkCmdNextSubpass, 2, commandBuffer, contents);
    
}
PFN_vkCmdNextSubpass glad_debug_vkCmdNextSubpass = glad_debug_impl_vkCmdNextSubpass;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdNextSubpass2(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo * pSubpassBeginInfo, const VkSubpassEndInfo * pSubpassEndInfo) {
    glad_vkCmdNextSubpass2 = (PFN_vkCmdNextSubpass2) glad_vk_on_demand_loader("vkCmdNextSubpass2");
    glad_vkCmdNextSubpass2(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo);
}
PFN_vkCmdNextSubpass2 glad_vkCmdNextSubpass2 = glad_on_demand_impl_vkCmdNextSubpass2;
static void GLAD_API_PTR glad_debug_impl_vkCmdNextSubpass2(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo * pSubpassBeginInfo, const VkSubpassEndInfo * pSubpassEndInfo) {
    _pre_call_vulkan_callback("vkCmdNextSubpass2", (GLADapiproc) glad_vkCmdNextSubpass2, 3, commandBuffer, pSubpassBeginInfo, pSubpassEndInfo);
    glad_vkCmdNextSubpass2(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo);
    _post_call_vulkan_callback(NULL, "vkCmdNextSubpass2", (GLADapiproc) glad_vkCmdNextSubpass2, 3, commandBuffer, pSubpassBeginInfo, pSubpassEndInfo);
    
}
PFN_vkCmdNextSubpass2 glad_debug_vkCmdNextSubpass2 = glad_debug_impl_vkCmdNextSubpass2;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier * pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier * pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier * pImageMemoryBarriers) {
    glad_vkCmdPipelineBarrier = (PFN_vkCmdPipelineBarrier) glad_vk_on_demand_loader("vkCmdPipelineBarrier");
    glad_vkCmdPipelineBarrier(commandBuffer, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
}
PFN_vkCmdPipelineBarrier glad_vkCmdPipelineBarrier = glad_on_demand_impl_vkCmdPipelineBarrier;
static void GLAD_API_PTR glad_debug_impl_vkCmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier * pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier * pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier * pImageMemoryBarriers) {
    _pre_call_vulkan_callback("vkCmdPipelineBarrier", (GLADapiproc) glad_vkCmdPipelineBarrier, 10, commandBuffer, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
    glad_vkCmdPipelineBarrier(commandBuffer, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
    _post_call_vulkan_callback(NULL, "vkCmdPipelineBarrier", (GLADapiproc) glad_vkCmdPipelineBarrier, 10, commandBuffer, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
    
}
PFN_vkCmdPipelineBarrier glad_debug_vkCmdPipelineBarrier = glad_debug_impl_vkCmdPipelineBarrier;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void * pValues) {
    glad_vkCmdPushConstants = (PFN_vkCmdPushConstants) glad_vk_on_demand_loader("vkCmdPushConstants");
    glad_vkCmdPushConstants(commandBuffer, layout, stageFlags, offset, size, pValues);
}
PFN_vkCmdPushConstants glad_vkCmdPushConstants = glad_on_demand_impl_vkCmdPushConstants;
static void GLAD_API_PTR glad_debug_impl_vkCmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void * pValues) {
    _pre_call_vulkan_callback("vkCmdPushConstants", (GLADapiproc) glad_vkCmdPushConstants, 6, commandBuffer, layout, stageFlags, offset, size, pValues);
    glad_vkCmdPushConstants(commandBuffer, layout, stageFlags, offset, size, pValues);
    _post_call_vulkan_callback(NULL, "vkCmdPushConstants", (GLADapiproc) glad_vkCmdPushConstants, 6, commandBuffer, layout, stageFlags, offset, size, pValues);
    
}
PFN_vkCmdPushConstants glad_debug_vkCmdPushConstants = glad_debug_impl_vkCmdPushConstants;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdResetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) {
    glad_vkCmdResetEvent = (PFN_vkCmdResetEvent) glad_vk_on_demand_loader("vkCmdResetEvent");
    glad_vkCmdResetEvent(commandBuffer, event, stageMask);
}
PFN_vkCmdResetEvent glad_vkCmdResetEvent = glad_on_demand_impl_vkCmdResetEvent;
static void GLAD_API_PTR glad_debug_impl_vkCmdResetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) {
    _pre_call_vulkan_callback("vkCmdResetEvent", (GLADapiproc) glad_vkCmdResetEvent, 3, commandBuffer, event, stageMask);
    glad_vkCmdResetEvent(commandBuffer, event, stageMask);
    _post_call_vulkan_callback(NULL, "vkCmdResetEvent", (GLADapiproc) glad_vkCmdResetEvent, 3, commandBuffer, event, stageMask);
    
}
PFN_vkCmdResetEvent glad_debug_vkCmdResetEvent = glad_debug_impl_vkCmdResetEvent;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdResetQueryPool(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) {
    glad_vkCmdResetQueryPool = (PFN_vkCmdResetQueryPool) glad_vk_on_demand_loader("vkCmdResetQueryPool");
    glad_vkCmdResetQueryPool(commandBuffer, queryPool, firstQuery, queryCount);
}
PFN_vkCmdResetQueryPool glad_vkCmdResetQueryPool = glad_on_demand_impl_vkCmdResetQueryPool;
static void GLAD_API_PTR glad_debug_impl_vkCmdResetQueryPool(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) {
    _pre_call_vulkan_callback("vkCmdResetQueryPool", (GLADapiproc) glad_vkCmdResetQueryPool, 4, commandBuffer, queryPool, firstQuery, queryCount);
    glad_vkCmdResetQueryPool(commandBuffer, queryPool, firstQuery, queryCount);
    _post_call_vulkan_callback(NULL, "vkCmdResetQueryPool", (GLADapiproc) glad_vkCmdResetQueryPool, 4, commandBuffer, queryPool, firstQuery, queryCount);
    
}
PFN_vkCmdResetQueryPool glad_debug_vkCmdResetQueryPool = glad_debug_impl_vkCmdResetQueryPool;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageResolve * pRegions) {
    glad_vkCmdResolveImage = (PFN_vkCmdResolveImage) glad_vk_on_demand_loader("vkCmdResolveImage");
    glad_vkCmdResolveImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
}
PFN_vkCmdResolveImage glad_vkCmdResolveImage = glad_on_demand_impl_vkCmdResolveImage;
static void GLAD_API_PTR glad_debug_impl_vkCmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageResolve * pRegions) {
    _pre_call_vulkan_callback("vkCmdResolveImage", (GLADapiproc) glad_vkCmdResolveImage, 7, commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
    glad_vkCmdResolveImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
    _post_call_vulkan_callback(NULL, "vkCmdResolveImage", (GLADapiproc) glad_vkCmdResolveImage, 7, commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
    
}
PFN_vkCmdResolveImage glad_debug_vkCmdResolveImage = glad_debug_impl_vkCmdResolveImage;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdSetBlendConstants(VkCommandBuffer commandBuffer, const float blendConstants [4]) {
    glad_vkCmdSetBlendConstants = (PFN_vkCmdSetBlendConstants) glad_vk_on_demand_loader("vkCmdSetBlendConstants");
    glad_vkCmdSetBlendConstants(commandBuffer, blendConstants);
}
PFN_vkCmdSetBlendConstants glad_vkCmdSetBlendConstants = glad_on_demand_impl_vkCmdSetBlendConstants;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetBlendConstants(VkCommandBuffer commandBuffer, const float blendConstants [4]) {
    _pre_call_vulkan_callback("vkCmdSetBlendConstants", (GLADapiproc) glad_vkCmdSetBlendConstants, 2, commandBuffer, blendConstants);
    glad_vkCmdSetBlendConstants(commandBuffer, blendConstants);
    _post_call_vulkan_callback(NULL, "vkCmdSetBlendConstants", (GLADapiproc) glad_vkCmdSetBlendConstants, 2, commandBuffer, blendConstants);
    
}
PFN_vkCmdSetBlendConstants glad_debug_vkCmdSetBlendConstants = glad_debug_impl_vkCmdSetBlendConstants;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdSetDepthBias(VkCommandBuffer commandBuffer, float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor) {
    glad_vkCmdSetDepthBias = (PFN_vkCmdSetDepthBias) glad_vk_on_demand_loader("vkCmdSetDepthBias");
    glad_vkCmdSetDepthBias(commandBuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor);
}
PFN_vkCmdSetDepthBias glad_vkCmdSetDepthBias = glad_on_demand_impl_vkCmdSetDepthBias;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetDepthBias(VkCommandBuffer commandBuffer, float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor) {
    _pre_call_vulkan_callback("vkCmdSetDepthBias", (GLADapiproc) glad_vkCmdSetDepthBias, 4, commandBuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor);
    glad_vkCmdSetDepthBias(commandBuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor);
    _post_call_vulkan_callback(NULL, "vkCmdSetDepthBias", (GLADapiproc) glad_vkCmdSetDepthBias, 4, commandBuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor);
    
}
PFN_vkCmdSetDepthBias glad_debug_vkCmdSetDepthBias = glad_debug_impl_vkCmdSetDepthBias;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdSetDepthBounds(VkCommandBuffer commandBuffer, float minDepthBounds, float maxDepthBounds) {
    glad_vkCmdSetDepthBounds = (PFN_vkCmdSetDepthBounds) glad_vk_on_demand_loader("vkCmdSetDepthBounds");
    glad_vkCmdSetDepthBounds(commandBuffer, minDepthBounds, maxDepthBounds);
}
PFN_vkCmdSetDepthBounds glad_vkCmdSetDepthBounds = glad_on_demand_impl_vkCmdSetDepthBounds;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetDepthBounds(VkCommandBuffer commandBuffer, float minDepthBounds, float maxDepthBounds) {
    _pre_call_vulkan_callback("vkCmdSetDepthBounds", (GLADapiproc) glad_vkCmdSetDepthBounds, 3, commandBuffer, minDepthBounds, maxDepthBounds);
    glad_vkCmdSetDepthBounds(commandBuffer, minDepthBounds, maxDepthBounds);
    _post_call_vulkan_callback(NULL, "vkCmdSetDepthBounds", (GLADapiproc) glad_vkCmdSetDepthBounds, 3, commandBuffer, minDepthBounds, maxDepthBounds);
    
}
PFN_vkCmdSetDepthBounds glad_debug_vkCmdSetDepthBounds = glad_debug_impl_vkCmdSetDepthBounds;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdSetDeviceMask(VkCommandBuffer commandBuffer, uint32_t deviceMask) {
    glad_vkCmdSetDeviceMask = (PFN_vkCmdSetDeviceMask) glad_vk_on_demand_loader("vkCmdSetDeviceMask");
    glad_vkCmdSetDeviceMask(commandBuffer, deviceMask);
}
PFN_vkCmdSetDeviceMask glad_vkCmdSetDeviceMask = glad_on_demand_impl_vkCmdSetDeviceMask;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetDeviceMask(VkCommandBuffer commandBuffer, uint32_t deviceMask) {
    _pre_call_vulkan_callback("vkCmdSetDeviceMask", (GLADapiproc) glad_vkCmdSetDeviceMask, 2, commandBuffer, deviceMask);
    glad_vkCmdSetDeviceMask(commandBuffer, deviceMask);
    _post_call_vulkan_callback(NULL, "vkCmdSetDeviceMask", (GLADapiproc) glad_vkCmdSetDeviceMask, 2, commandBuffer, deviceMask);
    
}
PFN_vkCmdSetDeviceMask glad_debug_vkCmdSetDeviceMask = glad_debug_impl_vkCmdSetDeviceMask;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdSetDeviceMaskKHR(VkCommandBuffer commandBuffer, uint32_t deviceMask) {
    glad_vkCmdSetDeviceMaskKHR = (PFN_vkCmdSetDeviceMaskKHR) glad_vk_on_demand_loader("vkCmdSetDeviceMaskKHR");
    glad_vkCmdSetDeviceMaskKHR(commandBuffer, deviceMask);
}
PFN_vkCmdSetDeviceMaskKHR glad_vkCmdSetDeviceMaskKHR = glad_on_demand_impl_vkCmdSetDeviceMaskKHR;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetDeviceMaskKHR(VkCommandBuffer commandBuffer, uint32_t deviceMask) {
    _pre_call_vulkan_callback("vkCmdSetDeviceMaskKHR", (GLADapiproc) glad_vkCmdSetDeviceMaskKHR, 2, commandBuffer, deviceMask);
    glad_vkCmdSetDeviceMaskKHR(commandBuffer, deviceMask);
    _post_call_vulkan_callback(NULL, "vkCmdSetDeviceMaskKHR", (GLADapiproc) glad_vkCmdSetDeviceMaskKHR, 2, commandBuffer, deviceMask);
    
}
PFN_vkCmdSetDeviceMaskKHR glad_debug_vkCmdSetDeviceMaskKHR = glad_debug_impl_vkCmdSetDeviceMaskKHR;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdSetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) {
    glad_vkCmdSetEvent = (PFN_vkCmdSetEvent) glad_vk_on_demand_loader("vkCmdSetEvent");
    glad_vkCmdSetEvent(commandBuffer, event, stageMask);
}
PFN_vkCmdSetEvent glad_vkCmdSetEvent = glad_on_demand_impl_vkCmdSetEvent;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) {
    _pre_call_vulkan_callback("vkCmdSetEvent", (GLADapiproc) glad_vkCmdSetEvent, 3, commandBuffer, event, stageMask);
    glad_vkCmdSetEvent(commandBuffer, event, stageMask);
    _post_call_vulkan_callback(NULL, "vkCmdSetEvent", (GLADapiproc) glad_vkCmdSetEvent, 3, commandBuffer, event, stageMask);
    
}
PFN_vkCmdSetEvent glad_debug_vkCmdSetEvent = glad_debug_impl_vkCmdSetEvent;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdSetLineWidth(VkCommandBuffer commandBuffer, float lineWidth) {
    glad_vkCmdSetLineWidth = (PFN_vkCmdSetLineWidth) glad_vk_on_demand_loader("vkCmdSetLineWidth");
    glad_vkCmdSetLineWidth(commandBuffer, lineWidth);
}
PFN_vkCmdSetLineWidth glad_vkCmdSetLineWidth = glad_on_demand_impl_vkCmdSetLineWidth;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetLineWidth(VkCommandBuffer commandBuffer, float lineWidth) {
    _pre_call_vulkan_callback("vkCmdSetLineWidth", (GLADapiproc) glad_vkCmdSetLineWidth, 2, commandBuffer, lineWidth);
    glad_vkCmdSetLineWidth(commandBuffer, lineWidth);
    _post_call_vulkan_callback(NULL, "vkCmdSetLineWidth", (GLADapiproc) glad_vkCmdSetLineWidth, 2, commandBuffer, lineWidth);
    
}
PFN_vkCmdSetLineWidth glad_debug_vkCmdSetLineWidth = glad_debug_impl_vkCmdSetLineWidth;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, const VkRect2D * pScissors) {
    glad_vkCmdSetScissor = (PFN_vkCmdSetScissor) glad_vk_on_demand_loader("vkCmdSetScissor");
    glad_vkCmdSetScissor(commandBuffer, firstScissor, scissorCount, pScissors);
}
PFN_vkCmdSetScissor glad_vkCmdSetScissor = glad_on_demand_impl_vkCmdSetScissor;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, const VkRect2D * pScissors) {
    _pre_call_vulkan_callback("vkCmdSetScissor", (GLADapiproc) glad_vkCmdSetScissor, 4, commandBuffer, firstScissor, scissorCount, pScissors);
    glad_vkCmdSetScissor(commandBuffer, firstScissor, scissorCount, pScissors);
    _post_call_vulkan_callback(NULL, "vkCmdSetScissor", (GLADapiproc) glad_vkCmdSetScissor, 4, commandBuffer, firstScissor, scissorCount, pScissors);
    
}
PFN_vkCmdSetScissor glad_debug_vkCmdSetScissor = glad_debug_impl_vkCmdSetScissor;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdSetStencilCompareMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t compareMask) {
    glad_vkCmdSetStencilCompareMask = (PFN_vkCmdSetStencilCompareMask) glad_vk_on_demand_loader("vkCmdSetStencilCompareMask");
    glad_vkCmdSetStencilCompareMask(commandBuffer, faceMask, compareMask);
}
PFN_vkCmdSetStencilCompareMask glad_vkCmdSetStencilCompareMask = glad_on_demand_impl_vkCmdSetStencilCompareMask;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetStencilCompareMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t compareMask) {
    _pre_call_vulkan_callback("vkCmdSetStencilCompareMask", (GLADapiproc) glad_vkCmdSetStencilCompareMask, 3, commandBuffer, faceMask, compareMask);
    glad_vkCmdSetStencilCompareMask(commandBuffer, faceMask, compareMask);
    _post_call_vulkan_callback(NULL, "vkCmdSetStencilCompareMask", (GLADapiproc) glad_vkCmdSetStencilCompareMask, 3, commandBuffer, faceMask, compareMask);
    
}
PFN_vkCmdSetStencilCompareMask glad_debug_vkCmdSetStencilCompareMask = glad_debug_impl_vkCmdSetStencilCompareMask;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdSetStencilReference(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t reference) {
    glad_vkCmdSetStencilReference = (PFN_vkCmdSetStencilReference) glad_vk_on_demand_loader("vkCmdSetStencilReference");
    glad_vkCmdSetStencilReference(commandBuffer, faceMask, reference);
}
PFN_vkCmdSetStencilReference glad_vkCmdSetStencilReference = glad_on_demand_impl_vkCmdSetStencilReference;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetStencilReference(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t reference) {
    _pre_call_vulkan_callback("vkCmdSetStencilReference", (GLADapiproc) glad_vkCmdSetStencilReference, 3, commandBuffer, faceMask, reference);
    glad_vkCmdSetStencilReference(commandBuffer, faceMask, reference);
    _post_call_vulkan_callback(NULL, "vkCmdSetStencilReference", (GLADapiproc) glad_vkCmdSetStencilReference, 3, commandBuffer, faceMask, reference);
    
}
PFN_vkCmdSetStencilReference glad_debug_vkCmdSetStencilReference = glad_debug_impl_vkCmdSetStencilReference;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdSetStencilWriteMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t writeMask) {
    glad_vkCmdSetStencilWriteMask = (PFN_vkCmdSetStencilWriteMask) glad_vk_on_demand_loader("vkCmdSetStencilWriteMask");
    glad_vkCmdSetStencilWriteMask(commandBuffer, faceMask, writeMask);
}
PFN_vkCmdSetStencilWriteMask glad_vkCmdSetStencilWriteMask = glad_on_demand_impl_vkCmdSetStencilWriteMask;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetStencilWriteMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t writeMask) {
    _pre_call_vulkan_callback("vkCmdSetStencilWriteMask", (GLADapiproc) glad_vkCmdSetStencilWriteMask, 3, commandBuffer, faceMask, writeMask);
    glad_vkCmdSetStencilWriteMask(commandBuffer, faceMask, writeMask);
    _post_call_vulkan_callback(NULL, "vkCmdSetStencilWriteMask", (GLADapiproc) glad_vkCmdSetStencilWriteMask, 3, commandBuffer, faceMask, writeMask);
    
}
PFN_vkCmdSetStencilWriteMask glad_debug_vkCmdSetStencilWriteMask = glad_debug_impl_vkCmdSetStencilWriteMask;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewport * pViewports) {
    glad_vkCmdSetViewport = (PFN_vkCmdSetViewport) glad_vk_on_demand_loader("vkCmdSetViewport");
    glad_vkCmdSetViewport(commandBuffer, firstViewport, viewportCount, pViewports);
}
PFN_vkCmdSetViewport glad_vkCmdSetViewport = glad_on_demand_impl_vkCmdSetViewport;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewport * pViewports) {
    _pre_call_vulkan_callback("vkCmdSetViewport", (GLADapiproc) glad_vkCmdSetViewport, 4, commandBuffer, firstViewport, viewportCount, pViewports);
    glad_vkCmdSetViewport(commandBuffer, firstViewport, viewportCount, pViewports);
    _post_call_vulkan_callback(NULL, "vkCmdSetViewport", (GLADapiproc) glad_vkCmdSetViewport, 4, commandBuffer, firstViewport, viewportCount, pViewports);
    
}
PFN_vkCmdSetViewport glad_debug_vkCmdSetViewport = glad_debug_impl_vkCmdSetViewport;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdUpdateBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, const void * pData) {
    glad_vkCmdUpdateBuffer = (PFN_vkCmdUpdateBuffer) glad_vk_on_demand_loader("vkCmdUpdateBuffer");
    glad_vkCmdUpdateBuffer(commandBuffer, dstBuffer, dstOffset, dataSize, pData);
}
PFN_vkCmdUpdateBuffer glad_vkCmdUpdateBuffer = glad_on_demand_impl_vkCmdUpdateBuffer;
static void GLAD_API_PTR glad_debug_impl_vkCmdUpdateBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, const void * pData) {
    _pre_call_vulkan_callback("vkCmdUpdateBuffer", (GLADapiproc) glad_vkCmdUpdateBuffer, 5, commandBuffer, dstBuffer, dstOffset, dataSize, pData);
    glad_vkCmdUpdateBuffer(commandBuffer, dstBuffer, dstOffset, dataSize, pData);
    _post_call_vulkan_callback(NULL, "vkCmdUpdateBuffer", (GLADapiproc) glad_vkCmdUpdateBuffer, 5, commandBuffer, dstBuffer, dstOffset, dataSize, pData);
    
}
PFN_vkCmdUpdateBuffer glad_debug_vkCmdUpdateBuffer = glad_debug_impl_vkCmdUpdateBuffer;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent * pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const VkMemoryBarrier * pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier * pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier * pImageMemoryBarriers) {
    glad_vkCmdWaitEvents = (PFN_vkCmdWaitEvents) glad_vk_on_demand_loader("vkCmdWaitEvents");
    glad_vkCmdWaitEvents(commandBuffer, eventCount, pEvents, srcStageMask, dstStageMask, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
}
PFN_vkCmdWaitEvents glad_vkCmdWaitEvents = glad_on_demand_impl_vkCmdWaitEvents;
static void GLAD_API_PTR glad_debug_impl_vkCmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent * pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const VkMemoryBarrier * pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier * pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier * pImageMemoryBarriers) {
    _pre_call_vulkan_callback("vkCmdWaitEvents", (GLADapiproc) glad_vkCmdWaitEvents, 11, commandBuffer, eventCount, pEvents, srcStageMask, dstStageMask, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
    glad_vkCmdWaitEvents(commandBuffer, eventCount, pEvents, srcStageMask, dstStageMask, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
    _post_call_vulkan_callback(NULL, "vkCmdWaitEvents", (GLADapiproc) glad_vkCmdWaitEvents, 11, commandBuffer, eventCount, pEvents, srcStageMask, dstStageMask, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
    
}
PFN_vkCmdWaitEvents glad_debug_vkCmdWaitEvents = glad_debug_impl_vkCmdWaitEvents;
static void GLAD_API_PTR glad_on_demand_impl_vkCmdWriteTimestamp(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query) {
    glad_vkCmdWriteTimestamp = (PFN_vkCmdWriteTimestamp) glad_vk_on_demand_loader("vkCmdWriteTimestamp");
    glad_vkCmdWriteTimestamp(commandBuffer, pipelineStage, queryPool, query);
}
PFN_vkCmdWriteTimestamp glad_vkCmdWriteTimestamp = glad_on_demand_impl_vkCmdWriteTimestamp;
static void GLAD_API_PTR glad_debug_impl_vkCmdWriteTimestamp(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query) {
    _pre_call_vulkan_callback("vkCmdWriteTimestamp", (GLADapiproc) glad_vkCmdWriteTimestamp, 4, commandBuffer, pipelineStage, queryPool, query);
    glad_vkCmdWriteTimestamp(commandBuffer, pipelineStage, queryPool, query);
    _post_call_vulkan_callback(NULL, "vkCmdWriteTimestamp", (GLADapiproc) glad_vkCmdWriteTimestamp, 4, commandBuffer, pipelineStage, queryPool, query);
    
}
PFN_vkCmdWriteTimestamp glad_debug_vkCmdWriteTimestamp = glad_debug_impl_vkCmdWriteTimestamp;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateBuffer(VkDevice device, const VkBufferCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkBuffer * pBuffer) {
    glad_vkCreateBuffer = (PFN_vkCreateBuffer) glad_vk_on_demand_loader("vkCreateBuffer");
    return glad_vkCreateBuffer(device, pCreateInfo, pAllocator, pBuffer);
}
PFN_vkCreateBuffer glad_vkCreateBuffer = glad_on_demand_impl_vkCreateBuffer;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateBuffer(VkDevice device, const VkBufferCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkBuffer * pBuffer) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateBuffer", (GLADapiproc) glad_vkCreateBuffer, 4, device, pCreateInfo, pAllocator, pBuffer);
    ret = glad_vkCreateBuffer(device, pCreateInfo, pAllocator, pBuffer);
    _post_call_vulkan_callback((void*) &ret, "vkCreateBuffer", (GLADapiproc) glad_vkCreateBuffer, 4, device, pCreateInfo, pAllocator, pBuffer);
    return ret;
}
PFN_vkCreateBuffer glad_debug_vkCreateBuffer = glad_debug_impl_vkCreateBuffer;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateBufferView(VkDevice device, const VkBufferViewCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkBufferView * pView) {
    glad_vkCreateBufferView = (PFN_vkCreateBufferView) glad_vk_on_demand_loader("vkCreateBufferView");
    return glad_vkCreateBufferView(device, pCreateInfo, pAllocator, pView);
}
PFN_vkCreateBufferView glad_vkCreateBufferView = glad_on_demand_impl_vkCreateBufferView;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateBufferView(VkDevice device, const VkBufferViewCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkBufferView * pView) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateBufferView", (GLADapiproc) glad_vkCreateBufferView, 4, device, pCreateInfo, pAllocator, pView);
    ret = glad_vkCreateBufferView(device, pCreateInfo, pAllocator, pView);
    _post_call_vulkan_callback((void*) &ret, "vkCreateBufferView", (GLADapiproc) glad_vkCreateBufferView, 4, device, pCreateInfo, pAllocator, pView);
    return ret;
}
PFN_vkCreateBufferView glad_debug_vkCreateBufferView = glad_debug_impl_vkCreateBufferView;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkCommandPool * pCommandPool) {
    glad_vkCreateCommandPool = (PFN_vkCreateCommandPool) glad_vk_on_demand_loader("vkCreateCommandPool");
    return glad_vkCreateCommandPool(device, pCreateInfo, pAllocator, pCommandPool);
}
PFN_vkCreateCommandPool glad_vkCreateCommandPool = glad_on_demand_impl_vkCreateCommandPool;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkCommandPool * pCommandPool) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateCommandPool", (GLADapiproc) glad_vkCreateCommandPool, 4, device, pCreateInfo, pAllocator, pCommandPool);
    ret = glad_vkCreateCommandPool(device, pCreateInfo, pAllocator, pCommandPool);
    _post_call_vulkan_callback((void*) &ret, "vkCreateCommandPool", (GLADapiproc) glad_vkCreateCommandPool, 4, device, pCreateInfo, pAllocator, pCommandPool);
    return ret;
}
PFN_vkCreateCommandPool glad_debug_vkCreateCommandPool = glad_debug_impl_vkCreateCommandPool;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkComputePipelineCreateInfo * pCreateInfos, const VkAllocationCallbacks * pAllocator, VkPipeline * pPipelines) {
    glad_vkCreateComputePipelines = (PFN_vkCreateComputePipelines) glad_vk_on_demand_loader("vkCreateComputePipelines");
    return glad_vkCreateComputePipelines(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
}
PFN_vkCreateComputePipelines glad_vkCreateComputePipelines = glad_on_demand_impl_vkCreateComputePipelines;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkComputePipelineCreateInfo * pCreateInfos, const VkAllocationCallbacks * pAllocator, VkPipeline * pPipelines) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateComputePipelines", (GLADapiproc) glad_vkCreateComputePipelines, 6, device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
    ret = glad_vkCreateComputePipelines(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
    _post_call_vulkan_callback((void*) &ret, "vkCreateComputePipelines", (GLADapiproc) glad_vkCreateComputePipelines, 6, device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
    return ret;
}
PFN_vkCreateComputePipelines glad_debug_vkCreateComputePipelines = glad_debug_impl_vkCreateComputePipelines;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkDebugReportCallbackEXT * pCallback) {
    glad_vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT) glad_vk_on_demand_loader("vkCreateDebugReportCallbackEXT");
    return glad_vkCreateDebugReportCallbackEXT(instance, pCreateInfo, pAllocator, pCallback);
}
PFN_vkCreateDebugReportCallbackEXT glad_vkCreateDebugReportCallbackEXT = glad_on_demand_impl_vkCreateDebugReportCallbackEXT;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkDebugReportCallbackEXT * pCallback) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateDebugReportCallbackEXT", (GLADapiproc) glad_vkCreateDebugReportCallbackEXT, 4, instance, pCreateInfo, pAllocator, pCallback);
    ret = glad_vkCreateDebugReportCallbackEXT(instance, pCreateInfo, pAllocator, pCallback);
    _post_call_vulkan_callback((void*) &ret, "vkCreateDebugReportCallbackEXT", (GLADapiproc) glad_vkCreateDebugReportCallbackEXT, 4, instance, pCreateInfo, pAllocator, pCallback);
    return ret;
}
PFN_vkCreateDebugReportCallbackEXT glad_debug_vkCreateDebugReportCallbackEXT = glad_debug_impl_vkCreateDebugReportCallbackEXT;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkDebugUtilsMessengerEXT * pMessenger) {
    glad_vkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT) glad_vk_on_demand_loader("vkCreateDebugUtilsMessengerEXT");
    return glad_vkCreateDebugUtilsMessengerEXT(instance, pCreateInfo, pAllocator, pMessenger);
}
PFN_vkCreateDebugUtilsMessengerEXT glad_vkCreateDebugUtilsMessengerEXT = glad_on_demand_impl_vkCreateDebugUtilsMessengerEXT;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkDebugUtilsMessengerEXT * pMessenger) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateDebugUtilsMessengerEXT", (GLADapiproc) glad_vkCreateDebugUtilsMessengerEXT, 4, instance, pCreateInfo, pAllocator, pMessenger);
    ret = glad_vkCreateDebugUtilsMessengerEXT(instance, pCreateInfo, pAllocator, pMessenger);
    _post_call_vulkan_callback((void*) &ret, "vkCreateDebugUtilsMessengerEXT", (GLADapiproc) glad_vkCreateDebugUtilsMessengerEXT, 4, instance, pCreateInfo, pAllocator, pMessenger);
    return ret;
}
PFN_vkCreateDebugUtilsMessengerEXT glad_debug_vkCreateDebugUtilsMessengerEXT = glad_debug_impl_vkCreateDebugUtilsMessengerEXT;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkDescriptorPool * pDescriptorPool) {
    glad_vkCreateDescriptorPool = (PFN_vkCreateDescriptorPool) glad_vk_on_demand_loader("vkCreateDescriptorPool");
    return glad_vkCreateDescriptorPool(device, pCreateInfo, pAllocator, pDescriptorPool);
}
PFN_vkCreateDescriptorPool glad_vkCreateDescriptorPool = glad_on_demand_impl_vkCreateDescriptorPool;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkDescriptorPool * pDescriptorPool) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateDescriptorPool", (GLADapiproc) glad_vkCreateDescriptorPool, 4, device, pCreateInfo, pAllocator, pDescriptorPool);
    ret = glad_vkCreateDescriptorPool(device, pCreateInfo, pAllocator, pDescriptorPool);
    _post_call_vulkan_callback((void*) &ret, "vkCreateDescriptorPool", (GLADapiproc) glad_vkCreateDescriptorPool, 4, device, pCreateInfo, pAllocator, pDescriptorPool);
    return ret;
}
PFN_vkCreateDescriptorPool glad_debug_vkCreateDescriptorPool = glad_debug_impl_vkCreateDescriptorPool;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateDescriptorSetLayout(VkDevice device, const VkDescriptorSetLayoutCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkDescriptorSetLayout * pSetLayout) {
    glad_vkCreateDescriptorSetLayout = (PFN_vkCreateDescriptorSetLayout) glad_vk_on_demand_loader("vkCreateDescriptorSetLayout");
    return glad_vkCreateDescriptorSetLayout(device, pCreateInfo, pAllocator, pSetLayout);
}
PFN_vkCreateDescriptorSetLayout glad_vkCreateDescriptorSetLayout = glad_on_demand_impl_vkCreateDescriptorSetLayout;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateDescriptorSetLayout(VkDevice device, const VkDescriptorSetLayoutCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkDescriptorSetLayout * pSetLayout) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateDescriptorSetLayout", (GLADapiproc) glad_vkCreateDescriptorSetLayout, 4, device, pCreateInfo, pAllocator, pSetLayout);
    ret = glad_vkCreateDescriptorSetLayout(device, pCreateInfo, pAllocator, pSetLayout);
    _post_call_vulkan_callback((void*) &ret, "vkCreateDescriptorSetLayout", (GLADapiproc) glad_vkCreateDescriptorSetLayout, 4, device, pCreateInfo, pAllocator, pSetLayout);
    return ret;
}
PFN_vkCreateDescriptorSetLayout glad_debug_vkCreateDescriptorSetLayout = glad_debug_impl_vkCreateDescriptorSetLayout;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateDescriptorUpdateTemplate(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkDescriptorUpdateTemplate * pDescriptorUpdateTemplate) {
    glad_vkCreateDescriptorUpdateTemplate = (PFN_vkCreateDescriptorUpdateTemplate) glad_vk_on_demand_loader("vkCreateDescriptorUpdateTemplate");
    return glad_vkCreateDescriptorUpdateTemplate(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate);
}
PFN_vkCreateDescriptorUpdateTemplate glad_vkCreateDescriptorUpdateTemplate = glad_on_demand_impl_vkCreateDescriptorUpdateTemplate;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateDescriptorUpdateTemplate(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkDescriptorUpdateTemplate * pDescriptorUpdateTemplate) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateDescriptorUpdateTemplate", (GLADapiproc) glad_vkCreateDescriptorUpdateTemplate, 4, device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate);
    ret = glad_vkCreateDescriptorUpdateTemplate(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate);
    _post_call_vulkan_callback((void*) &ret, "vkCreateDescriptorUpdateTemplate", (GLADapiproc) glad_vkCreateDescriptorUpdateTemplate, 4, device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate);
    return ret;
}
PFN_vkCreateDescriptorUpdateTemplate glad_debug_vkCreateDescriptorUpdateTemplate = glad_debug_impl_vkCreateDescriptorUpdateTemplate;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkDevice * pDevice) {
    glad_vkCreateDevice = (PFN_vkCreateDevice) glad_vk_on_demand_loader("vkCreateDevice");
    return glad_vkCreateDevice(physicalDevice, pCreateInfo, pAllocator, pDevice);
}
PFN_vkCreateDevice glad_vkCreateDevice = glad_on_demand_impl_vkCreateDevice;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkDevice * pDevice) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateDevice", (GLADapiproc) glad_vkCreateDevice, 4, physicalDevice, pCreateInfo, pAllocator, pDevice);
    ret = glad_vkCreateDevice(physicalDevice, pCreateInfo, pAllocator, pDevice);
    _post_call_vulkan_callback((void*) &ret, "vkCreateDevice", (GLADapiproc) glad_vkCreateDevice, 4, physicalDevice, pCreateInfo, pAllocator, pDevice);
    return ret;
}
PFN_vkCreateDevice glad_debug_vkCreateDevice = glad_debug_impl_vkCreateDevice;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateEvent(VkDevice device, const VkEventCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkEvent * pEvent) {
    glad_vkCreateEvent = (PFN_vkCreateEvent) glad_vk_on_demand_loader("vkCreateEvent");
    return glad_vkCreateEvent(device, pCreateInfo, pAllocator, pEvent);
}
PFN_vkCreateEvent glad_vkCreateEvent = glad_on_demand_impl_vkCreateEvent;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateEvent(VkDevice device, const VkEventCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkEvent * pEvent) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateEvent", (GLADapiproc) glad_vkCreateEvent, 4, device, pCreateInfo, pAllocator, pEvent);
    ret = glad_vkCreateEvent(device, pCreateInfo, pAllocator, pEvent);
    _post_call_vulkan_callback((void*) &ret, "vkCreateEvent", (GLADapiproc) glad_vkCreateEvent, 4, device, pCreateInfo, pAllocator, pEvent);
    return ret;
}
PFN_vkCreateEvent glad_debug_vkCreateEvent = glad_debug_impl_vkCreateEvent;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateFence(VkDevice device, const VkFenceCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkFence * pFence) {
    glad_vkCreateFence = (PFN_vkCreateFence) glad_vk_on_demand_loader("vkCreateFence");
    return glad_vkCreateFence(device, pCreateInfo, pAllocator, pFence);
}
PFN_vkCreateFence glad_vkCreateFence = glad_on_demand_impl_vkCreateFence;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateFence(VkDevice device, const VkFenceCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkFence * pFence) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateFence", (GLADapiproc) glad_vkCreateFence, 4, device, pCreateInfo, pAllocator, pFence);
    ret = glad_vkCreateFence(device, pCreateInfo, pAllocator, pFence);
    _post_call_vulkan_callback((void*) &ret, "vkCreateFence", (GLADapiproc) glad_vkCreateFence, 4, device, pCreateInfo, pAllocator, pFence);
    return ret;
}
PFN_vkCreateFence glad_debug_vkCreateFence = glad_debug_impl_vkCreateFence;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateFramebuffer(VkDevice device, const VkFramebufferCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkFramebuffer * pFramebuffer) {
    glad_vkCreateFramebuffer = (PFN_vkCreateFramebuffer) glad_vk_on_demand_loader("vkCreateFramebuffer");
    return glad_vkCreateFramebuffer(device, pCreateInfo, pAllocator, pFramebuffer);
}
PFN_vkCreateFramebuffer glad_vkCreateFramebuffer = glad_on_demand_impl_vkCreateFramebuffer;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateFramebuffer(VkDevice device, const VkFramebufferCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkFramebuffer * pFramebuffer) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateFramebuffer", (GLADapiproc) glad_vkCreateFramebuffer, 4, device, pCreateInfo, pAllocator, pFramebuffer);
    ret = glad_vkCreateFramebuffer(device, pCreateInfo, pAllocator, pFramebuffer);
    _post_call_vulkan_callback((void*) &ret, "vkCreateFramebuffer", (GLADapiproc) glad_vkCreateFramebuffer, 4, device, pCreateInfo, pAllocator, pFramebuffer);
    return ret;
}
PFN_vkCreateFramebuffer glad_debug_vkCreateFramebuffer = glad_debug_impl_vkCreateFramebuffer;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo * pCreateInfos, const VkAllocationCallbacks * pAllocator, VkPipeline * pPipelines) {
    glad_vkCreateGraphicsPipelines = (PFN_vkCreateGraphicsPipelines) glad_vk_on_demand_loader("vkCreateGraphicsPipelines");
    return glad_vkCreateGraphicsPipelines(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
}
PFN_vkCreateGraphicsPipelines glad_vkCreateGraphicsPipelines = glad_on_demand_impl_vkCreateGraphicsPipelines;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo * pCreateInfos, const VkAllocationCallbacks * pAllocator, VkPipeline * pPipelines) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateGraphicsPipelines", (GLADapiproc) glad_vkCreateGraphicsPipelines, 6, device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
    ret = glad_vkCreateGraphicsPipelines(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
    _post_call_vulkan_callback((void*) &ret, "vkCreateGraphicsPipelines", (GLADapiproc) glad_vkCreateGraphicsPipelines, 6, device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
    return ret;
}
PFN_vkCreateGraphicsPipelines glad_debug_vkCreateGraphicsPipelines = glad_debug_impl_vkCreateGraphicsPipelines;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateImage(VkDevice device, const VkImageCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkImage * pImage) {
    glad_vkCreateImage = (PFN_vkCreateImage) glad_vk_on_demand_loader("vkCreateImage");
    return glad_vkCreateImage(device, pCreateInfo, pAllocator, pImage);
}
PFN_vkCreateImage glad_vkCreateImage = glad_on_demand_impl_vkCreateImage;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateImage(VkDevice device, const VkImageCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkImage * pImage) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateImage", (GLADapiproc) glad_vkCreateImage, 4, device, pCreateInfo, pAllocator, pImage);
    ret = glad_vkCreateImage(device, pCreateInfo, pAllocator, pImage);
    _post_call_vulkan_callback((void*) &ret, "vkCreateImage", (GLADapiproc) glad_vkCreateImage, 4, device, pCreateInfo, pAllocator, pImage);
    return ret;
}
PFN_vkCreateImage glad_debug_vkCreateImage = glad_debug_impl_vkCreateImage;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateImageView(VkDevice device, const VkImageViewCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkImageView * pView) {
    glad_vkCreateImageView = (PFN_vkCreateImageView) glad_vk_on_demand_loader("vkCreateImageView");
    return glad_vkCreateImageView(device, pCreateInfo, pAllocator, pView);
}
PFN_vkCreateImageView glad_vkCreateImageView = glad_on_demand_impl_vkCreateImageView;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateImageView(VkDevice device, const VkImageViewCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkImageView * pView) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateImageView", (GLADapiproc) glad_vkCreateImageView, 4, device, pCreateInfo, pAllocator, pView);
    ret = glad_vkCreateImageView(device, pCreateInfo, pAllocator, pView);
    _post_call_vulkan_callback((void*) &ret, "vkCreateImageView", (GLADapiproc) glad_vkCreateImageView, 4, device, pCreateInfo, pAllocator, pView);
    return ret;
}
PFN_vkCreateImageView glad_debug_vkCreateImageView = glad_debug_impl_vkCreateImageView;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateInstance(const VkInstanceCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkInstance * pInstance) {
    glad_vkCreateInstance = (PFN_vkCreateInstance) glad_vk_on_demand_loader("vkCreateInstance");
    return glad_vkCreateInstance(pCreateInfo, pAllocator, pInstance);
}
PFN_vkCreateInstance glad_vkCreateInstance = glad_on_demand_impl_vkCreateInstance;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateInstance(const VkInstanceCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkInstance * pInstance) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateInstance", (GLADapiproc) glad_vkCreateInstance, 3, pCreateInfo, pAllocator, pInstance);
    ret = glad_vkCreateInstance(pCreateInfo, pAllocator, pInstance);
    _post_call_vulkan_callback((void*) &ret, "vkCreateInstance", (GLADapiproc) glad_vkCreateInstance, 3, pCreateInfo, pAllocator, pInstance);
    return ret;
}
PFN_vkCreateInstance glad_debug_vkCreateInstance = glad_debug_impl_vkCreateInstance;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreatePipelineCache(VkDevice device, const VkPipelineCacheCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkPipelineCache * pPipelineCache) {
    glad_vkCreatePipelineCache = (PFN_vkCreatePipelineCache) glad_vk_on_demand_loader("vkCreatePipelineCache");
    return glad_vkCreatePipelineCache(device, pCreateInfo, pAllocator, pPipelineCache);
}
PFN_vkCreatePipelineCache glad_vkCreatePipelineCache = glad_on_demand_impl_vkCreatePipelineCache;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreatePipelineCache(VkDevice device, const VkPipelineCacheCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkPipelineCache * pPipelineCache) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreatePipelineCache", (GLADapiproc) glad_vkCreatePipelineCache, 4, device, pCreateInfo, pAllocator, pPipelineCache);
    ret = glad_vkCreatePipelineCache(device, pCreateInfo, pAllocator, pPipelineCache);
    _post_call_vulkan_callback((void*) &ret, "vkCreatePipelineCache", (GLADapiproc) glad_vkCreatePipelineCache, 4, device, pCreateInfo, pAllocator, pPipelineCache);
    return ret;
}
PFN_vkCreatePipelineCache glad_debug_vkCreatePipelineCache = glad_debug_impl_vkCreatePipelineCache;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkPipelineLayout * pPipelineLayout) {
    glad_vkCreatePipelineLayout = (PFN_vkCreatePipelineLayout) glad_vk_on_demand_loader("vkCreatePipelineLayout");
    return glad_vkCreatePipelineLayout(device, pCreateInfo, pAllocator, pPipelineLayout);
}
PFN_vkCreatePipelineLayout glad_vkCreatePipelineLayout = glad_on_demand_impl_vkCreatePipelineLayout;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkPipelineLayout * pPipelineLayout) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreatePipelineLayout", (GLADapiproc) glad_vkCreatePipelineLayout, 4, device, pCreateInfo, pAllocator, pPipelineLayout);
    ret = glad_vkCreatePipelineLayout(device, pCreateInfo, pAllocator, pPipelineLayout);
    _post_call_vulkan_callback((void*) &ret, "vkCreatePipelineLayout", (GLADapiproc) glad_vkCreatePipelineLayout, 4, device, pCreateInfo, pAllocator, pPipelineLayout);
    return ret;
}
PFN_vkCreatePipelineLayout glad_debug_vkCreatePipelineLayout = glad_debug_impl_vkCreatePipelineLayout;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkQueryPool * pQueryPool) {
    glad_vkCreateQueryPool = (PFN_vkCreateQueryPool) glad_vk_on_demand_loader("vkCreateQueryPool");
    return glad_vkCreateQueryPool(device, pCreateInfo, pAllocator, pQueryPool);
}
PFN_vkCreateQueryPool glad_vkCreateQueryPool = glad_on_demand_impl_vkCreateQueryPool;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkQueryPool * pQueryPool) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateQueryPool", (GLADapiproc) glad_vkCreateQueryPool, 4, device, pCreateInfo, pAllocator, pQueryPool);
    ret = glad_vkCreateQueryPool(device, pCreateInfo, pAllocator, pQueryPool);
    _post_call_vulkan_callback((void*) &ret, "vkCreateQueryPool", (GLADapiproc) glad_vkCreateQueryPool, 4, device, pCreateInfo, pAllocator, pQueryPool);
    return ret;
}
PFN_vkCreateQueryPool glad_debug_vkCreateQueryPool = glad_debug_impl_vkCreateQueryPool;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateRenderPass(VkDevice device, const VkRenderPassCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkRenderPass * pRenderPass) {
    glad_vkCreateRenderPass = (PFN_vkCreateRenderPass) glad_vk_on_demand_loader("vkCreateRenderPass");
    return glad_vkCreateRenderPass(device, pCreateInfo, pAllocator, pRenderPass);
}
PFN_vkCreateRenderPass glad_vkCreateRenderPass = glad_on_demand_impl_vkCreateRenderPass;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateRenderPass(VkDevice device, const VkRenderPassCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkRenderPass * pRenderPass) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateRenderPass", (GLADapiproc) glad_vkCreateRenderPass, 4, device, pCreateInfo, pAllocator, pRenderPass);
    ret = glad_vkCreateRenderPass(device, pCreateInfo, pAllocator, pRenderPass);
    _post_call_vulkan_callback((void*) &ret, "vkCreateRenderPass", (GLADapiproc) glad_vkCreateRenderPass, 4, device, pCreateInfo, pAllocator, pRenderPass);
    return ret;
}
PFN_vkCreateRenderPass glad_debug_vkCreateRenderPass = glad_debug_impl_vkCreateRenderPass;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateRenderPass2(VkDevice device, const VkRenderPassCreateInfo2 * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkRenderPass * pRenderPass) {
    glad_vkCreateRenderPass2 = (PFN_vkCreateRenderPass2) glad_vk_on_demand_loader("vkCreateRenderPass2");
    return glad_vkCreateRenderPass2(device, pCreateInfo, pAllocator, pRenderPass);
}
PFN_vkCreateRenderPass2 glad_vkCreateRenderPass2 = glad_on_demand_impl_vkCreateRenderPass2;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateRenderPass2(VkDevice device, const VkRenderPassCreateInfo2 * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkRenderPass * pRenderPass) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateRenderPass2", (GLADapiproc) glad_vkCreateRenderPass2, 4, device, pCreateInfo, pAllocator, pRenderPass);
    ret = glad_vkCreateRenderPass2(device, pCreateInfo, pAllocator, pRenderPass);
    _post_call_vulkan_callback((void*) &ret, "vkCreateRenderPass2", (GLADapiproc) glad_vkCreateRenderPass2, 4, device, pCreateInfo, pAllocator, pRenderPass);
    return ret;
}
PFN_vkCreateRenderPass2 glad_debug_vkCreateRenderPass2 = glad_debug_impl_vkCreateRenderPass2;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateSampler(VkDevice device, const VkSamplerCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkSampler * pSampler) {
    glad_vkCreateSampler = (PFN_vkCreateSampler) glad_vk_on_demand_loader("vkCreateSampler");
    return glad_vkCreateSampler(device, pCreateInfo, pAllocator, pSampler);
}
PFN_vkCreateSampler glad_vkCreateSampler = glad_on_demand_impl_vkCreateSampler;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateSampler(VkDevice device, const VkSamplerCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkSampler * pSampler) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateSampler", (GLADapiproc) glad_vkCreateSampler, 4, device, pCreateInfo, pAllocator, pSampler);
    ret = glad_vkCreateSampler(device, pCreateInfo, pAllocator, pSampler);
    _post_call_vulkan_callback((void*) &ret, "vkCreateSampler", (GLADapiproc) glad_vkCreateSampler, 4, device, pCreateInfo, pAllocator, pSampler);
    return ret;
}
PFN_vkCreateSampler glad_debug_vkCreateSampler = glad_debug_impl_vkCreateSampler;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateSamplerYcbcrConversion(VkDevice device, const VkSamplerYcbcrConversionCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkSamplerYcbcrConversion * pYcbcrConversion) {
    glad_vkCreateSamplerYcbcrConversion = (PFN_vkCreateSamplerYcbcrConversion) glad_vk_on_demand_loader("vkCreateSamplerYcbcrConversion");
    return glad_vkCreateSamplerYcbcrConversion(device, pCreateInfo, pAllocator, pYcbcrConversion);
}
PFN_vkCreateSamplerYcbcrConversion glad_vkCreateSamplerYcbcrConversion = glad_on_demand_impl_vkCreateSamplerYcbcrConversion;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateSamplerYcbcrConversion(VkDevice device, const VkSamplerYcbcrConversionCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkSamplerYcbcrConversion * pYcbcrConversion) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateSamplerYcbcrConversion", (GLADapiproc) glad_vkCreateSamplerYcbcrConversion, 4, device, pCreateInfo, pAllocator, pYcbcrConversion);
    ret = glad_vkCreateSamplerYcbcrConversion(device, pCreateInfo, pAllocator, pYcbcrConversion);
    _post_call_vulkan_callback((void*) &ret, "vkCreateSamplerYcbcrConversion", (GLADapiproc) glad_vkCreateSamplerYcbcrConversion, 4, device, pCreateInfo, pAllocator, pYcbcrConversion);
    return ret;
}
PFN_vkCreateSamplerYcbcrConversion glad_debug_vkCreateSamplerYcbcrConversion = glad_debug_impl_vkCreateSamplerYcbcrConversion;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkSemaphore * pSemaphore) {
    glad_vkCreateSemaphore = (PFN_vkCreateSemaphore) glad_vk_on_demand_loader("vkCreateSemaphore");
    return glad_vkCreateSemaphore(device, pCreateInfo, pAllocator, pSemaphore);
}
PFN_vkCreateSemaphore glad_vkCreateSemaphore = glad_on_demand_impl_vkCreateSemaphore;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkSemaphore * pSemaphore) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateSemaphore", (GLADapiproc) glad_vkCreateSemaphore, 4, device, pCreateInfo, pAllocator, pSemaphore);
    ret = glad_vkCreateSemaphore(device, pCreateInfo, pAllocator, pSemaphore);
    _post_call_vulkan_callback((void*) &ret, "vkCreateSemaphore", (GLADapiproc) glad_vkCreateSemaphore, 4, device, pCreateInfo, pAllocator, pSemaphore);
    return ret;
}
PFN_vkCreateSemaphore glad_debug_vkCreateSemaphore = glad_debug_impl_vkCreateSemaphore;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkShaderModule * pShaderModule) {
    glad_vkCreateShaderModule = (PFN_vkCreateShaderModule) glad_vk_on_demand_loader("vkCreateShaderModule");
    return glad_vkCreateShaderModule(device, pCreateInfo, pAllocator, pShaderModule);
}
PFN_vkCreateShaderModule glad_vkCreateShaderModule = glad_on_demand_impl_vkCreateShaderModule;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkShaderModule * pShaderModule) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateShaderModule", (GLADapiproc) glad_vkCreateShaderModule, 4, device, pCreateInfo, pAllocator, pShaderModule);
    ret = glad_vkCreateShaderModule(device, pCreateInfo, pAllocator, pShaderModule);
    _post_call_vulkan_callback((void*) &ret, "vkCreateShaderModule", (GLADapiproc) glad_vkCreateShaderModule, 4, device, pCreateInfo, pAllocator, pShaderModule);
    return ret;
}
PFN_vkCreateShaderModule glad_debug_vkCreateShaderModule = glad_debug_impl_vkCreateShaderModule;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkSwapchainKHR * pSwapchain) {
    glad_vkCreateSwapchainKHR = (PFN_vkCreateSwapchainKHR) glad_vk_on_demand_loader("vkCreateSwapchainKHR");
    return glad_vkCreateSwapchainKHR(device, pCreateInfo, pAllocator, pSwapchain);
}
PFN_vkCreateSwapchainKHR glad_vkCreateSwapchainKHR = glad_on_demand_impl_vkCreateSwapchainKHR;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkSwapchainKHR * pSwapchain) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateSwapchainKHR", (GLADapiproc) glad_vkCreateSwapchainKHR, 4, device, pCreateInfo, pAllocator, pSwapchain);
    ret = glad_vkCreateSwapchainKHR(device, pCreateInfo, pAllocator, pSwapchain);
    _post_call_vulkan_callback((void*) &ret, "vkCreateSwapchainKHR", (GLADapiproc) glad_vkCreateSwapchainKHR, 4, device, pCreateInfo, pAllocator, pSwapchain);
    return ret;
}
PFN_vkCreateSwapchainKHR glad_debug_vkCreateSwapchainKHR = glad_debug_impl_vkCreateSwapchainKHR;
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateWaylandSurfaceKHR(VkInstance instance, const VkWaylandSurfaceCreateInfoKHR * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkSurfaceKHR * pSurface) {
    glad_vkCreateWaylandSurfaceKHR = (PFN_vkCreateWaylandSurfaceKHR) glad_vk_on_demand_loader("vkCreateWaylandSurfaceKHR");
    return glad_vkCreateWaylandSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
}
PFN_vkCreateWaylandSurfaceKHR glad_vkCreateWaylandSurfaceKHR = glad_on_demand_impl_vkCreateWaylandSurfaceKHR;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateWaylandSurfaceKHR(VkInstance instance, const VkWaylandSurfaceCreateInfoKHR * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkSurfaceKHR * pSurface) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateWaylandSurfaceKHR", (GLADapiproc) glad_vkCreateWaylandSurfaceKHR, 4, instance, pCreateInfo, pAllocator, pSurface);
    ret = glad_vkCreateWaylandSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
    _post_call_vulkan_callback((void*) &ret, "vkCreateWaylandSurfaceKHR", (GLADapiproc) glad_vkCreateWaylandSurfaceKHR, 4, instance, pCreateInfo, pAllocator, pSurface);
    return ret;
}
PFN_vkCreateWaylandSurfaceKHR glad_debug_vkCreateWaylandSurfaceKHR = glad_debug_impl_vkCreateWaylandSurfaceKHR;
#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateWin32SurfaceKHR(VkInstance instance, const VkWin32SurfaceCreateInfoKHR * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkSurfaceKHR * pSurface) {
    glad_vkCreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR) glad_vk_on_demand_loader("vkCreateWin32SurfaceKHR");
    return glad_vkCreateWin32SurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
}
PFN_vkCreateWin32SurfaceKHR glad_vkCreateWin32SurfaceKHR = glad_on_demand_impl_vkCreateWin32SurfaceKHR;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateWin32SurfaceKHR(VkInstance instance, const VkWin32SurfaceCreateInfoKHR * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkSurfaceKHR * pSurface) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateWin32SurfaceKHR", (GLADapiproc) glad_vkCreateWin32SurfaceKHR, 4, instance, pCreateInfo, pAllocator, pSurface);
    ret = glad_vkCreateWin32SurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
    _post_call_vulkan_callback((void*) &ret, "vkCreateWin32SurfaceKHR", (GLADapiproc) glad_vkCreateWin32SurfaceKHR, 4, instance, pCreateInfo, pAllocator, pSurface);
    return ret;
}
PFN_vkCreateWin32SurfaceKHR glad_debug_vkCreateWin32SurfaceKHR = glad_debug_impl_vkCreateWin32SurfaceKHR;
#endif
#if defined(VK_USE_PLATFORM_XCB_KHR)
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateXcbSurfaceKHR(VkInstance instance, const VkXcbSurfaceCreateInfoKHR * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkSurfaceKHR * pSurface) {
    glad_vkCreateXcbSurfaceKHR = (PFN_vkCreateXcbSurfaceKHR) glad_vk_on_demand_loader("vkCreateXcbSurfaceKHR");
    return glad_vkCreateXcbSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
}
PFN_vkCreateXcbSurfaceKHR glad_vkCreateXcbSurfaceKHR = glad_on_demand_impl_vkCreateXcbSurfaceKHR;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateXcbSurfaceKHR(VkInstance instance, const VkXcbSurfaceCreateInfoKHR * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkSurfaceKHR * pSurface) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateXcbSurfaceKHR", (GLADapiproc) glad_vkCreateXcbSurfaceKHR, 4, instance, pCreateInfo, pAllocator, pSurface);
    ret = glad_vkCreateXcbSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
    _post_call_vulkan_callback((void*) &ret, "vkCreateXcbSurfaceKHR", (GLADapiproc) glad_vkCreateXcbSurfaceKHR, 4, instance, pCreateInfo, pAllocator, pSurface);
    return ret;
}
PFN_vkCreateXcbSurfaceKHR glad_debug_vkCreateXcbSurfaceKHR = glad_debug_impl_vkCreateXcbSurfaceKHR;
#endif
#if defined(VK_USE_PLATFORM_XLIB_KHR)
static VkResult GLAD_API_PTR glad_on_demand_impl_vkCreateXlibSurfaceKHR(VkInstance instance, const VkXlibSurfaceCreateInfoKHR * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkSurfaceKHR * pSurface) {
    glad_vkCreateXlibSurfaceKHR = (PFN_vkCreateXlibSurfaceKHR) glad_vk_on_demand_loader("vkCreateXlibSurfaceKHR");
    return glad_vkCreateXlibSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
}
PFN_vkCreateXlibSurfaceKHR glad_vkCreateXlibSurfaceKHR = glad_on_demand_impl_vkCreateXlibSurfaceKHR;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateXlibSurfaceKHR(VkInstance instance, const VkXlibSurfaceCreateInfoKHR * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkSurfaceKHR * pSurface) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateXlibSurfaceKHR", (GLADapiproc) glad_vkCreateXlibSurfaceKHR, 4, instance, pCreateInfo, pAllocator, pSurface);
    ret = glad_vkCreateXlibSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
    _post_call_vulkan_callback((void*) &ret, "vkCreateXlibSurfaceKHR", (GLADapiproc) glad_vkCreateXlibSurfaceKHR, 4, instance, pCreateInfo, pAllocator, pSurface);
    return ret;
}
PFN_vkCreateXlibSurfaceKHR glad_debug_vkCreateXlibSurfaceKHR = glad_debug_impl_vkCreateXlibSurfaceKHR;
#endif
static VkResult GLAD_API_PTR glad_on_demand_impl_vkDebugMarkerSetObjectNameEXT(VkDevice device, const VkDebugMarkerObjectNameInfoEXT * pNameInfo) {
    glad_vkDebugMarkerSetObjectNameEXT = (PFN_vkDebugMarkerSetObjectNameEXT) glad_vk_on_demand_loader("vkDebugMarkerSetObjectNameEXT");
    return glad_vkDebugMarkerSetObjectNameEXT(device, pNameInfo);
}
PFN_vkDebugMarkerSetObjectNameEXT glad_vkDebugMarkerSetObjectNameEXT = glad_on_demand_impl_vkDebugMarkerSetObjectNameEXT;
static VkResult GLAD_API_PTR glad_debug_impl_vkDebugMarkerSetObjectNameEXT(VkDevice device, const VkDebugMarkerObjectNameInfoEXT * pNameInfo) {
    VkResult ret;
    _pre_call_vulkan_callback("vkDebugMarkerSetObjectNameEXT", (GLADapiproc) glad_vkDebugMarkerSetObjectNameEXT, 2, device, pNameInfo);
    ret = glad_vkDebugMarkerSetObjectNameEXT(device, pNameInfo);
    _post_call_vulkan_callback((void*) &ret, "vkDebugMarkerSetObjectNameEXT", (GLADapiproc) glad_vkDebugMarkerSetObjectNameEXT, 2, device, pNameInfo);
    return ret;
}
PFN_vkDebugMarkerSetObjectNameEXT glad_debug_vkDebugMarkerSetObjectNameEXT = glad_debug_impl_vkDebugMarkerSetObjectNameEXT;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkDebugMarkerSetObjectTagEXT(VkDevice device, const VkDebugMarkerObjectTagInfoEXT * pTagInfo) {
    glad_vkDebugMarkerSetObjectTagEXT = (PFN_vkDebugMarkerSetObjectTagEXT) glad_vk_on_demand_loader("vkDebugMarkerSetObjectTagEXT");
    return glad_vkDebugMarkerSetObjectTagEXT(device, pTagInfo);
}
PFN_vkDebugMarkerSetObjectTagEXT glad_vkDebugMarkerSetObjectTagEXT = glad_on_demand_impl_vkDebugMarkerSetObjectTagEXT;
static VkResult GLAD_API_PTR glad_debug_impl_vkDebugMarkerSetObjectTagEXT(VkDevice device, const VkDebugMarkerObjectTagInfoEXT * pTagInfo) {
    VkResult ret;
    _pre_call_vulkan_callback("vkDebugMarkerSetObjectTagEXT", (GLADapiproc) glad_vkDebugMarkerSetObjectTagEXT, 2, device, pTagInfo);
    ret = glad_vkDebugMarkerSetObjectTagEXT(device, pTagInfo);
    _post_call_vulkan_callback((void*) &ret, "vkDebugMarkerSetObjectTagEXT", (GLADapiproc) glad_vkDebugMarkerSetObjectTagEXT, 2, device, pTagInfo);
    return ret;
}
PFN_vkDebugMarkerSetObjectTagEXT glad_debug_vkDebugMarkerSetObjectTagEXT = glad_debug_impl_vkDebugMarkerSetObjectTagEXT;
static void GLAD_API_PTR glad_on_demand_impl_vkDebugReportMessageEXT(VkInstance instance, VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char * pLayerPrefix, const char * pMessage) {
    glad_vkDebugReportMessageEXT = (PFN_vkDebugReportMessageEXT) glad_vk_on_demand_loader("vkDebugReportMessageEXT");
    glad_vkDebugReportMessageEXT(instance, flags, objectType, object, location, messageCode, pLayerPrefix, pMessage);
}
PFN_vkDebugReportMessageEXT glad_vkDebugReportMessageEXT = glad_on_demand_impl_vkDebugReportMessageEXT;
static void GLAD_API_PTR glad_debug_impl_vkDebugReportMessageEXT(VkInstance instance, VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char * pLayerPrefix, const char * pMessage) {
    _pre_call_vulkan_callback("vkDebugReportMessageEXT", (GLADapiproc) glad_vkDebugReportMessageEXT, 8, instance, flags, objectType, object, location, messageCode, pLayerPrefix, pMessage);
    glad_vkDebugReportMessageEXT(instance, flags, objectType, object, location, messageCode, pLayerPrefix, pMessage);
    _post_call_vulkan_callback(NULL, "vkDebugReportMessageEXT", (GLADapiproc) glad_vkDebugReportMessageEXT, 8, instance, flags, objectType, object, location, messageCode, pLayerPrefix, pMessage);
    
}
PFN_vkDebugReportMessageEXT glad_debug_vkDebugReportMessageEXT = glad_debug_impl_vkDebugReportMessageEXT;
static void GLAD_API_PTR glad_on_demand_impl_vkDestroyBuffer(VkDevice device, VkBuffer buffer, const VkAllocationCallbacks * pAllocator) {
    glad_vkDestroyBuffer = (PFN_vkDestroyBuffer) glad_vk_on_demand_loader("vkDestroyBuffer");
    glad_vkDestroyBuffer(device, buffer, pAllocator);
}
PFN_vkDestroyBuffer glad_vkDestroyBuffer = glad_on_demand_impl_vkDestroyBuffer;
static void GLAD_API_PTR glad_debug_impl_vkDestroyBuffer(VkDevice device, VkBuffer buffer, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyBuffer", (GLADapiproc) glad_vkDestroyBuffer, 3, device, buffer, pAllocator);
    glad_vkDestroyBuffer(device, buffer, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyBuffer", (GLADapiproc) glad_vkDestroyBuffer, 3, device, buffer, pAllocator);
    
}
PFN_vkDestroyBuffer glad_debug_vkDestroyBuffer = glad_debug_impl_vkDestroyBuffer;
static void GLAD_API_PTR glad_on_demand_impl_vkDestroyBufferView(VkDevice device, VkBufferView bufferView, const VkAllocationCallbacks * pAllocator) {
    glad_vkDestroyBufferView = (PFN_vkDestroyBufferView) glad_vk_on_demand_loader("vkDestroyBufferView");
    glad_vkDestroyBufferView(device, bufferView, pAllocator);
}
PFN_vkDestroyBufferView glad_vkDestroyBufferView = glad_on_demand_impl_vkDestroyBufferView;
static void GLAD_API_PTR glad_debug_impl_vkDestroyBufferView(VkDevice device, VkBufferView bufferView, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyBufferView", (GLADapiproc) glad_vkDestroyBufferView, 3, device, bufferView, pAllocator);
    glad_vkDestroyBufferView(device, bufferView, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyBufferView", (GLADapiproc) glad_vkDestroyBufferView, 3, device, bufferView, pAllocator);
    
}
PFN_vkDestroyBufferView glad_debug_vkDestroyBufferView = glad_debug_impl_vkDestroyBufferView;
static void GLAD_API_PTR glad_on_demand_impl_vkDestroyCommandPool(VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks * pAllocator) {
    glad_vkDestroyCommandPool = (PFN_vkDestroyCommandPool) glad_vk_on_demand_loader("vkDestroyCommandPool");
    glad_vkDestroyCommandPool(device, commandPool, pAllocator);
}
PFN_vkDestroyCommandPool glad_vkDestroyCommandPool = glad_on_demand_impl_vkDestroyCommandPool;
static void GLAD_API_PTR glad_debug_impl_vkDestroyCommandPool(VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyCommandPool", (GLADapiproc) glad_vkDestroyCommandPool, 3, device, commandPool, pAllocator);
    glad_vkDestroyCommandPool(device, commandPool, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyCommandPool", (GLADapiproc) glad_vkDestroyCommandPool, 3, device, commandPool, pAllocator);
    
}
PFN_vkDestroyCommandPool glad_debug_vkDestroyCommandPool = glad_debug_impl_vkDestroyCommandPool;
static void GLAD_API_PTR glad_on_demand_impl_vkDestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks * pAllocator) {
    glad_vkDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT) glad_vk_on_demand_loader("vkDestroyDebugReportCallbackEXT");
    glad_vkDestroyDebugReportCallbackEXT(instance, callback, pAllocator);
}
PFN_vkDestroyDebugReportCallbackEXT glad_vkDestroyDebugReportCallbackEXT = glad_on_demand_impl_vkDestroyDebugReportCallbackEXT;
static void GLAD_API_PTR glad_debug_impl_vkDestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyDebugReportCallbackEXT", (GLADapiproc) glad_vkDestroyDebugReportCallbackEXT, 3, instance, callback, pAllocator);
    glad_vkDestroyDebugReportCallbackEXT(instance, callback, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyDebugReportCallbackEXT", (GLADapiproc) glad_vkDestroyDebugReportCallbackEXT, 3, instance, callback, pAllocator);
    
}
PFN_vkDestroyDebugReportCallbackEXT glad_debug_vkDestroyDebugReportCallbackEXT = glad_debug_impl_vkDestroyDebugReportCallbackEXT;
static void GLAD_API_PTR glad_on_demand_impl_vkDestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT messenger, const VkAllocationCallbacks * pAllocator) {
    glad_vkDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT) glad_vk_on_demand_loader("vkDestroyDebugUtilsMessengerEXT");
    glad_vkDestroyDebugUtilsMessengerEXT(instance, messenger, pAllocator);
}
PFN_vkDestroyDebugUtilsMessengerEXT glad_vkDestroyDebugUtilsMessengerEXT = glad_on_demand_impl_vkDestroyDebugUtilsMessengerEXT;
static void GLAD_API_PTR glad_debug_impl_vkDestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT messenger, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyDebugUtilsMessengerEXT", (GLADapiproc) glad_vkDestroyDebugUtilsMessengerEXT, 3, instance, messenger, pAllocator);
    glad_vkDestroyDebugUtilsMessengerEXT(instance, messenger, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyDebugUtilsMessengerEXT", (GLADapiproc) glad_vkDestroyDebugUtilsMessengerEXT, 3, instance, messenger, pAllocator);
    
}
PFN_vkDestroyDebugUtilsMessengerEXT glad_debug_vkDestroyDebugUtilsMessengerEXT = glad_debug_impl_vkDestroyDebugUtilsMessengerEXT;
static void GLAD_API_PTR glad_on_demand_impl_vkDestroyDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, const VkAllocationCallbacks * pAllocator) {
    glad_vkDestroyDescriptorPool = (PFN_vkDestroyDescriptorPool) glad_vk_on_demand_loader("vkDestroyDescriptorPool");
    glad_vkDestroyDescriptorPool(device, descriptorPool, pAllocator);
}
PFN_vkDestroyDescriptorPool glad_vkDestroyDescriptorPool = glad_on_demand_impl_vkDestroyDescriptorPool;
static void GLAD_API_PTR glad_debug_impl_vkDestroyDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyDescriptorPool", (GLADapiproc) glad_vkDestroyDescriptorPool, 3, device, descriptorPool, pAllocator);
    glad_vkDestroyDescriptorPool(device, descriptorPool, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyDescriptorPool", (GLADapiproc) glad_vkDestroyDescriptorPool, 3, device, descriptorPool, pAllocator);
    
}
PFN_vkDestroyDescriptorPool glad_debug_vkDestroyDescriptorPool = glad_debug_impl_vkDestroyDescriptorPool;
static void GLAD_API_PTR glad_on_demand_impl_vkDestroyDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout, const VkAllocationCallbacks * pAllocator) {
    glad_vkDestroyDescriptorSetLayout = (PFN_vkDestroyDescriptorSetLayout) glad_vk_on_demand_loader("vkDestroyDescriptorSetLayout");
    glad_vkDestroyDescriptorSetLayout(device, descriptorSetLayout, pAllocator);
}
PFN_vkDestroyDescriptorSetLayout glad_vkDestroyDescriptorSetLayout = glad_on_demand_impl_vkDestroyDescriptorSetLayout;
static void GLAD_API_PTR glad_debug_impl_vkDestroyDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyDescriptorSetLayout", (GLADapiproc) glad_vkDestroyDescriptorSetLayout, 3, device, descriptorSetLayout, pAllocator);
    glad_vkDestroyDescriptorSetLayout(device, descriptorSetLayout, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyDescriptorSetLayout", (GLADapiproc) glad_vkDestroyDescriptorSetLayout, 3, device, descriptorSetLayout, pAllocator);
    
}
PFN_vkDestroyDescriptorSetLayout glad_debug_vkDestroyDescriptorSetLayout = glad_debug_impl_vkDestroyDescriptorSetLayout;
static void GLAD_API_PTR glad_on_demand_impl_vkDestroyDescriptorUpdateTemplate(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks * pAllocator) {
    glad_vkDestroyDescriptorUpdateTemplate = (PFN_vkDestroyDescriptorUpdateTemplate) glad_vk_on_demand_loader("vkDestroyDescriptorUpdateTemplate");
    glad_vkDestroyDescriptorUpdateTemplate(device, descriptorUpdateTemplate, pAllocator);
}
PFN_vkDestroyDescriptorUpdateTemplate glad_vkDestroyDescriptorUpdateTemplate = glad_on_demand_impl_vkDestroyDescriptorUpdateTemplate;
static void GLAD_API_PTR glad_debug_impl_vkDestroyDescriptorUpdateTemplate(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyDescriptorUpdateTemplate", (GLADapiproc) glad_vkDestroyDescriptorUpdateTemplate, 3, device, descriptorUpdateTemplate, pAllocator);
    glad_vkDestroyDescriptorUpdateTemplate(device, descriptorUpdateTemplate, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyDescriptorUpdateTemplate", (GLADapiproc) glad_vkDestroyDescriptorUpdateTemplate, 3, device, descriptorUpdateTemplate, pAllocator);
    
}
PFN_vkDestroyDescriptorUpdateTemplate glad_debug_vkDestroyDescriptorUpdateTemplate = glad_debug_impl_vkDestroyDescriptorUpdateTemplate;
static void GLAD_API_PTR glad_on_demand_impl_vkDestroyDevice(VkDevice device, const VkAllocationCallbacks * pAllocator) {
    glad_vkDestroyDevice = (PFN_vkDestroyDevice) glad_vk_on_demand_loader("vkDestroyDevice");
    glad_vkDestroyDevice(device, pAllocator);
}
PFN_vkDestroyDevice glad_vkDestroyDevice = glad_on_demand_impl_vkDestroyDevice;
static void GLAD_API_PTR glad_debug_impl_vkDestroyDevice(VkDevice device, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyDevice", (GLADapiproc) glad_vkDestroyDevice, 2, device, pAllocator);
    glad_vkDestroyDevice(device, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyDevice", (GLADapiproc) glad_vkDestroyDevice, 2, device, pAllocator);
    
}
PFN_vkDestroyDevice glad_debug_vkDestroyDevice = glad_debug_impl_vkDestroyDevice;
static void GLAD_API_PTR glad_on_demand_impl_vkDestroyEvent(VkDevice device, VkEvent event, const VkAllocationCallbacks * pAllocator) {
    glad_vkDestroyEvent = (PFN_vkDestroyEvent) glad_vk_on_demand_loader("vkDestroyEvent");
    glad_vkDestroyEvent(device, event, pAllocator);
}
PFN_vkDestroyEvent glad_vkDestroyEvent = glad_on_demand_impl_vkDestroyEvent;
static void GLAD_API_PTR glad_debug_impl_vkDestroyEvent(VkDevice device, VkEvent event, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyEvent", (GLADapiproc) glad_vkDestroyEvent, 3, device, event, pAllocator);
    glad_vkDestroyEvent(device, event, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyEvent", (GLADapiproc) glad_vkDestroyEvent, 3, device, event, pAllocator);
    
}
PFN_vkDestroyEvent glad_debug_vkDestroyEvent = glad_debug_impl_vkDestroyEvent;
static void GLAD_API_PTR glad_on_demand_impl_vkDestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks * pAllocator) {
    glad_vkDestroyFence = (PFN_vkDestroyFence) glad_vk_on_demand_loader("vkDestroyFence");
    glad_vkDestroyFence(device, fence, pAllocator);
}
PFN_vkDestroyFence glad_vkDestroyFence = glad_on_demand_impl_vkDestroyFence;
static void GLAD_API_PTR glad_debug_impl_vkDestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyFence", (GLADapiproc) glad_vkDestroyFence, 3, device, fence, pAllocator);
    glad_vkDestroyFence(device, fence, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyFence", (GLADapiproc) glad_vkDestroyFence, 3, device, fence, pAllocator);
    
}
PFN_vkDestroyFence glad_debug_vkDestroyFence = glad_debug_impl_vkDestroyFence;
static void GLAD_API_PTR glad_on_demand_impl_vkDestroyFramebuffer(VkDevice device, VkFramebuffer framebuffer, const VkAllocationCallbacks * pAllocator) {
    glad_vkDestroyFramebuffer = (PFN_vkDestroyFramebuffer) glad_vk_on_demand_loader("vkDestroyFramebuffer");
    glad_vkDestroyFramebuffer(device, framebuffer, pAllocator);
}
PFN_vkDestroyFramebuffer glad_vkDestroyFramebuffer = glad_on_demand_impl_vkDestroyFramebuffer;
static void GLAD_API_PTR glad_debug_impl_vkDestroyFramebuffer(VkDevice device, VkFramebuffer framebuffer, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyFramebuffer", (GLADapiproc) glad_vkDestroyFramebuffer, 3, device, framebuffer, pAllocator);
    glad_vkDestroyFramebuffer(device, framebuffer, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyFramebuffer", (GLADapiproc) glad_vkDestroyFramebuffer, 3, device, framebuffer, pAllocator);
    
}
PFN_vkDestroyFramebuffer glad_debug_vkDestroyFramebuffer = glad_debug_impl_vkDestroyFramebuffer;
static void GLAD_API_PTR glad_on_demand_impl_vkDestroyImage(VkDevice device, VkImage image, const VkAllocationCallbacks * pAllocator) {
    glad_vkDestroyImage = (PFN_vkDestroyImage) glad_vk_on_demand_loader("vkDestroyImage");
    glad_vkDestroyImage(device, image, pAllocator);
}
PFN_vkDestroyImage glad_vkDestroyImage = glad_on_demand_impl_vkDestroyImage;
static void GLAD_API_PTR glad_debug_impl_vkDestroyImage(VkDevice device, VkImage image, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyImage", (GLADapiproc) glad_vkDestroyImage, 3, device, image, pAllocator);
    glad_vkDestroyImage(device, image, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyImage", (GLADapiproc) glad_vkDestroyImage, 3, device, image, pAllocator);
    
}
PFN_vkDestroyImage glad_debug_vkDestroyImage = glad_debug_impl_vkDestroyImage;
static void GLAD_API_PTR glad_on_demand_impl_vkDestroyImageView(VkDevice device, VkImageView imageView, const VkAllocationCallbacks * pAllocator) {
    glad_vkDestroyImageView = (PFN_vkDestroyImageView) glad_vk_on_demand_loader("vkDestroyImageView");
    glad_vkDestroyImageView(device, imageView, pAllocator);
}
PFN_vkDestroyImageView glad_vkDestroyImageView = glad_on_demand_impl_vkDestroyImageView;
static void GLAD_API_PTR glad_debug_impl_vkDestroyImageView(VkDevice device, VkImageView imageView, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyImageView", (GLADapiproc) glad_vkDestroyImageView, 3, device, imageView, pAllocator);
    glad_vkDestroyImageView(device, imageView, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyImageView", (GLADapiproc) glad_vkDestroyImageView, 3, device, imageView, pAllocator);
    
}
PFN_vkDestroyImageView glad_debug_vkDestroyImageView = glad_debug_impl_vkDestroyImageView;
static void GLAD_API_PTR glad_on_demand_impl_vkDestroyInstance(VkInstance instance, const VkAllocationCallbacks * pAllocator) {
    glad_vkDestroyInstance = (PFN_vkDestroyInstance) glad_vk_on_demand_loader("vkDestroyInstance");
    glad_vkDestroyInstance(instance, pAllocator);
}
PFN_vkDestroyInstance glad_vkDestroyInstance = glad_on_demand_impl_vkDestroyInstance;
static void GLAD_API_PTR glad_debug_impl_vkDestroyInstance(VkInstance instance, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyInstance", (GLADapiproc) glad_vkDestroyInstance, 2, instance, pAllocator);
    glad_vkDestroyInstance(instance, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyInstance", (GLADapiproc) glad_vkDestroyInstance, 2, instance, pAllocator);
    
}
PFN_vkDestroyInstance glad_debug_vkDestroyInstance = glad_debug_impl_vkDestroyInstance;
static void GLAD_API_PTR glad_on_demand_impl_vkDestroyPipeline(VkDevice device, VkPipeline pipeline, const VkAllocationCallbacks * pAllocator) {
    glad_vkDestroyPipeline = (PFN_vkDestroyPipeline) glad_vk_on_demand_loader("vkDestroyPipeline");
    glad_vkDestroyPipeline(device, pipeline, pAllocator);
}
PFN_vkDestroyPipeline glad_vkDestroyPipeline = glad_on_demand_impl_vkDestroyPipeline;
static void GLAD_API_PTR glad_debug_impl_vkDestroyPipeline(VkDevice device, VkPipeline pipeline, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyPipeline", (GLADapiproc) glad_vkDestroyPipeline, 3, device, pipeline, pAllocator);
    glad_vkDestroyPipeline(device, pipeline, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyPipeline", (GLADapiproc) glad_vkDestroyPipeline, 3, device, pipeline, pAllocator);
    
}
PFN_vkDestroyPipeline glad_debug_vkDestroyPipeline = glad_debug_impl_vkDestroyPipeline;
static void GLAD_API_PTR glad_on_demand_impl_vkDestroyPipelineCache(VkDevice device, VkPipelineCache pipelineCache, const VkAllocationCallbacks * pAllocator) {
    glad_vkDestroyPipelineCache = (PFN_vkDestroyPipelineCache) glad_vk_on_demand_loader("vkDestroyPipelineCache");
    glad_vkDestroyPipelineCache(device, pipelineCache, pAllocator);
}
PFN_vkDestroyPipelineCache glad_vkDestroyPipelineCache = glad_on_demand_impl_vkDestroyPipelineCache;
static void GLAD_API_PTR glad_debug_impl_vkDestroyPipelineCache(VkDevice device, VkPipelineCache pipelineCache, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyPipelineCache", (GLADapiproc) glad_vkDestroyPipelineCache, 3, device, pipelineCache, pAllocator);
    glad_vkDestroyPipelineCache(device, pipelineCache, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyPipelineCache", (GLADapiproc) glad_vkDestroyPipelineCache, 3, device, pipelineCache, pAllocator);
    
}
PFN_vkDestroyPipelineCache glad_debug_vkDestroyPipelineCache = glad_debug_impl_vkDestroyPipelineCache;
static void GLAD_API_PTR glad_on_demand_impl_vkDestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks * pAllocator) {
    glad_vkDestroyPipelineLayout = (PFN_vkDestroyPipelineLayout) glad_vk_on_demand_loader("vkDestroyPipelineLayout");
    glad_vkDestroyPipelineLayout(device, pipelineLayout, pAllocator);
}
PFN_vkDestroyPipelineLayout glad_vkDestroyPipelineLayout = glad_on_demand_impl_vkDestroyPipelineLayout;
static void GLAD_API_PTR glad_debug_impl_vkDestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyPipelineLayout", (GLADapiproc) glad_vkDestroyPipelineLayout, 3, device, pipelineLayout, pAllocator);
    glad_vkDestroyPipelineLayout(device, pipelineLayout, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyPipelineLayout", (GLADapiproc) glad_vkDestroyPipelineLayout, 3, device, pipelineLayout, pAllocator);
    
}
PFN_vkDestroyPipelineLayout glad_debug_vkDestroyPipelineLayout = glad_debug_impl_vkDestroyPipelineLayout;
static void GLAD_API_PTR glad_on_demand_impl_vkDestroyQueryPool(VkDevice device, VkQueryPool queryPool, const VkAllocationCallbacks * pAllocator) {
    glad_vkDestroyQueryPool = (PFN_vkDestroyQueryPool) glad_vk_on_demand_loader("vkDestroyQueryPool");
    glad_vkDestroyQueryPool(device, queryPool, pAllocator);
}
PFN_vkDestroyQueryPool glad_vkDestroyQueryPool = glad_on_demand_impl_vkDestroyQueryPool;
static void GLAD_API_PTR glad_debug_impl_vkDestroyQueryPool(VkDevice device, VkQueryPool queryPool, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyQueryPool", (GLADapiproc) glad_vkDestroyQueryPool, 3, device, queryPool, pAllocator);
    glad_vkDestroyQueryPool(device, queryPool, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyQueryPool", (GLADapiproc) glad_vkDestroyQueryPool, 3, device, queryPool, pAllocator);
    
}
PFN_vkDestroyQueryPool glad_debug_vkDestroyQueryPool = glad_debug_impl_vkDestroyQueryPool;
static void GLAD_API_PTR glad_on_demand_impl_vkDestroyRenderPass(VkDevice device, VkRenderPass renderPass, const VkAllocationCallbacks * pAllocator) {
    glad_vkDestroyRenderPass = (PFN_vkDestroyRenderPass) glad_vk_on_demand_loader("vkDestroyRenderPass");
    glad_vkDestroyRenderPass(device, renderPass, pAllocator);
}
PFN_vkDestroyRenderPass glad_vkDestroyRenderPass = glad_on_demand_impl_vkDestroyRenderPass;
static void GLAD_API_PTR glad_debug_impl_vkDestroyRenderPass(VkDevice device, VkRenderPass renderPass, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyRenderPass", (GLADapiproc) glad_vkDestroyRenderPass, 3, device, renderPass, pAllocator);
    glad_vkDestroyRenderPass(device, renderPass, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyRenderPass", (GLADapiproc) glad_vkDestroyRenderPass, 3, device, renderPass, pAllocator);
    
}
PFN_vkDestroyRenderPass glad_debug_vkDestroyRenderPass = glad_debug_impl_vkDestroyRenderPass;
static void GLAD_API_PTR glad_on_demand_impl_vkDestroySampler(VkDevice device, VkSampler sampler, const VkAllocationCallbacks * pAllocator) {
    glad_vkDestroySampler = (PFN_vkDestroySampler) glad_vk_on_demand_loader("vkDestroySampler");
    glad_vkDestroySampler(device, sampler, pAllocator);
}
PFN_vkDestroySampler glad_vkDestroySampler = glad_on_demand_impl_vkDestroySampler;
static void GLAD_API_PTR glad_debug_impl_vkDestroySampler(VkDevice device, VkSampler sampler, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroySampler", (GLADapiproc) glad_vkDestroySampler, 3, device, sampler, pAllocator);
    glad_vkDestroySampler(device, sampler, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroySampler", (GLADapiproc) glad_vkDestroySampler, 3, device, sampler, pAllocator);
    
}
PFN_vkDestroySampler glad_debug_vkDestroySampler = glad_debug_impl_vkDestroySampler;
static void GLAD_API_PTR glad_on_demand_impl_vkDestroySamplerYcbcrConversion(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks * pAllocator) {
    glad_vkDestroySamplerYcbcrConversion = (PFN_vkDestroySamplerYcbcrConversion) glad_vk_on_demand_loader("vkDestroySamplerYcbcrConversion");
    glad_vkDestroySamplerYcbcrConversion(device, ycbcrConversion, pAllocator);
}
PFN_vkDestroySamplerYcbcrConversion glad_vkDestroySamplerYcbcrConversion = glad_on_demand_impl_vkDestroySamplerYcbcrConversion;
static void GLAD_API_PTR glad_debug_impl_vkDestroySamplerYcbcrConversion(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroySamplerYcbcrConversion", (GLADapiproc) glad_vkDestroySamplerYcbcrConversion, 3, device, ycbcrConversion, pAllocator);
    glad_vkDestroySamplerYcbcrConversion(device, ycbcrConversion, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroySamplerYcbcrConversion", (GLADapiproc) glad_vkDestroySamplerYcbcrConversion, 3, device, ycbcrConversion, pAllocator);
    
}
PFN_vkDestroySamplerYcbcrConversion glad_debug_vkDestroySamplerYcbcrConversion = glad_debug_impl_vkDestroySamplerYcbcrConversion;
static void GLAD_API_PTR glad_on_demand_impl_vkDestroySemaphore(VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks * pAllocator) {
    glad_vkDestroySemaphore = (PFN_vkDestroySemaphore) glad_vk_on_demand_loader("vkDestroySemaphore");
    glad_vkDestroySemaphore(device, semaphore, pAllocator);
}
PFN_vkDestroySemaphore glad_vkDestroySemaphore = glad_on_demand_impl_vkDestroySemaphore;
static void GLAD_API_PTR glad_debug_impl_vkDestroySemaphore(VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroySemaphore", (GLADapiproc) glad_vkDestroySemaphore, 3, device, semaphore, pAllocator);
    glad_vkDestroySemaphore(device, semaphore, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroySemaphore", (GLADapiproc) glad_vkDestroySemaphore, 3, device, semaphore, pAllocator);
    
}
PFN_vkDestroySemaphore glad_debug_vkDestroySemaphore = glad_debug_impl_vkDestroySemaphore;
static void GLAD_API_PTR glad_on_demand_impl_vkDestroyShaderModule(VkDevice device, VkShaderModule shaderModule, const VkAllocationCallbacks * pAllocator) {
    glad_vkDestroyShaderModule = (PFN_vkDestroyShaderModule) glad_vk_on_demand_loader("vkDestroyShaderModule");
    glad_vkDestroyShaderModule(device, shaderModule, pAllocator);
}
PFN_vkDestroyShaderModule glad_vkDestroyShaderModule = glad_on_demand_impl_vkDestroyShaderModule;
static void GLAD_API_PTR glad_debug_impl_vkDestroyShaderModule(VkDevice device, VkShaderModule shaderModule, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyShaderModule", (GLADapiproc) glad_vkDestroyShaderModule, 3, device, shaderModule, pAllocator);
    glad_vkDestroyShaderModule(device, shaderModule, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyShaderModule", (GLADapiproc) glad_vkDestroyShaderModule, 3, device, shaderModule, pAllocator);
    
}
PFN_vkDestroyShaderModule glad_debug_vkDestroyShaderModule = glad_debug_impl_vkDestroyShaderModule;
static void GLAD_API_PTR glad_on_demand_impl_vkDestroySurfaceKHR(VkInstance instance, VkSurfaceKHR surface, const VkAllocationCallbacks * pAllocator) {
    glad_vkDestroySurfaceKHR = (PFN_vkDestroySurfaceKHR) glad_vk_on_demand_loader("vkDestroySurfaceKHR");
    glad_vkDestroySurfaceKHR(instance, surface, pAllocator);
}
PFN_vkDestroySurfaceKHR glad_vkDestroySurfaceKHR = glad_on_demand_impl_vkDestroySurfaceKHR;
static void GLAD_API_PTR glad_debug_impl_vkDestroySurfaceKHR(VkInstance instance, VkSurfaceKHR surface, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroySurfaceKHR", (GLADapiproc) glad_vkDestroySurfaceKHR, 3, instance, surface, pAllocator);
    glad_vkDestroySurfaceKHR(instance, surface, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroySurfaceKHR", (GLADapiproc) glad_vkDestroySurfaceKHR, 3, instance, surface, pAllocator);
    
}
PFN_vkDestroySurfaceKHR glad_debug_vkDestroySurfaceKHR = glad_debug_impl_vkDestroySurfaceKHR;
static void GLAD_API_PTR glad_on_demand_impl_vkDestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks * pAllocator) {
    glad_vkDestroySwapchainKHR = (PFN_vkDestroySwapchainKHR) glad_vk_on_demand_loader("vkDestroySwapchainKHR");
    glad_vkDestroySwapchainKHR(device, swapchain, pAllocator);
}
PFN_vkDestroySwapchainKHR glad_vkDestroySwapchainKHR = glad_on_demand_impl_vkDestroySwapchainKHR;
static void GLAD_API_PTR glad_debug_impl_vkDestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroySwapchainKHR", (GLADapiproc) glad_vkDestroySwapchainKHR, 3, device, swapchain, pAllocator);
    glad_vkDestroySwapchainKHR(device, swapchain, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroySwapchainKHR", (GLADapiproc) glad_vkDestroySwapchainKHR, 3, device, swapchain, pAllocator);
    
}
PFN_vkDestroySwapchainKHR glad_debug_vkDestroySwapchainKHR = glad_debug_impl_vkDestroySwapchainKHR;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkDeviceWaitIdle(VkDevice device) {
    glad_vkDeviceWaitIdle = (PFN_vkDeviceWaitIdle) glad_vk_on_demand_loader("vkDeviceWaitIdle");
    return glad_vkDeviceWaitIdle(device);
}
PFN_vkDeviceWaitIdle glad_vkDeviceWaitIdle = glad_on_demand_impl_vkDeviceWaitIdle;
static VkResult GLAD_API_PTR glad_debug_impl_vkDeviceWaitIdle(VkDevice device) {
    VkResult ret;
    _pre_call_vulkan_callback("vkDeviceWaitIdle", (GLADapiproc) glad_vkDeviceWaitIdle, 1, device);
    ret = glad_vkDeviceWaitIdle(device);
    _post_call_vulkan_callback((void*) &ret, "vkDeviceWaitIdle", (GLADapiproc) glad_vkDeviceWaitIdle, 1, device);
    return ret;
}
PFN_vkDeviceWaitIdle glad_debug_vkDeviceWaitIdle = glad_debug_impl_vkDeviceWaitIdle;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkEndCommandBuffer(VkCommandBuffer commandBuffer) {
    glad_vkEndCommandBuffer = (PFN_vkEndCommandBuffer) glad_vk_on_demand_loader("vkEndCommandBuffer");
    return glad_vkEndCommandBuffer(commandBuffer);
}
PFN_vkEndCommandBuffer glad_vkEndCommandBuffer = glad_on_demand_impl_vkEndCommandBuffer;
static VkResult GLAD_API_PTR glad_debug_impl_vkEndCommandBuffer(VkCommandBuffer commandBuffer) {
    VkResult ret;
    _pre_call_vulkan_callback("vkEndCommandBuffer", (GLADapiproc) glad_vkEndCommandBuffer, 1, commandBuffer);
    ret = glad_vkEndCommandBuffer(commandBuffer);
    _post_call_vulkan_callback((void*) &ret, "vkEndCommandBuffer", (GLADapiproc) glad_vkEndCommandBuffer, 1, commandBuffer);
    return ret;
}
PFN_vkEndCommandBuffer glad_debug_vkEndCommandBuffer = glad_debug_impl_vkEndCommandBuffer;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkEnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice, const char * pLayerName, uint32_t * pPropertyCount, VkExtensionProperties * pProperties) {
    glad_vkEnumerateDeviceExtensionProperties = (PFN_vkEnumerateDeviceExtensionProperties) glad_vk_on_demand_loader("vkEnumerateDeviceExtensionProperties");
    return glad_vkEnumerateDeviceExtensionProperties(physicalDevice, pLayerName, pPropertyCount, pProperties);
}
PFN_vkEnumerateDeviceExtensionProperties glad_vkEnumerateDeviceExtensionProperties = glad_on_demand_impl_vkEnumerateDeviceExtensionProperties;
static VkResult GLAD_API_PTR glad_debug_impl_vkEnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice, const char * pLayerName, uint32_t * pPropertyCount, VkExtensionProperties * pProperties) {
    VkResult ret;
    _pre_call_vulkan_callback("vkEnumerateDeviceExtensionProperties", (GLADapiproc) glad_vkEnumerateDeviceExtensionProperties, 4, physicalDevice, pLayerName, pPropertyCount, pProperties);
    ret = glad_vkEnumerateDeviceExtensionProperties(physicalDevice, pLayerName, pPropertyCount, pProperties);
    _post_call_vulkan_callback((void*) &ret, "vkEnumerateDeviceExtensionProperties", (GLADapiproc) glad_vkEnumerateDeviceExtensionProperties, 4, physicalDevice, pLayerName, pPropertyCount, pProperties);
    return ret;
}
PFN_vkEnumerateDeviceExtensionProperties glad_debug_vkEnumerateDeviceExtensionProperties = glad_debug_impl_vkEnumerateDeviceExtensionProperties;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkEnumerateDeviceLayerProperties(VkPhysicalDevice physicalDevice, uint32_t * pPropertyCount, VkLayerProperties * pProperties) {
    glad_vkEnumerateDeviceLayerProperties = (PFN_vkEnumerateDeviceLayerProperties) glad_vk_on_demand_loader("vkEnumerateDeviceLayerProperties");
    return glad_vkEnumerateDeviceLayerProperties(physicalDevice, pPropertyCount, pProperties);
}
PFN_vkEnumerateDeviceLayerProperties glad_vkEnumerateDeviceLayerProperties = glad_on_demand_impl_vkEnumerateDeviceLayerProperties;
static VkResult GLAD_API_PTR glad_debug_impl_vkEnumerateDeviceLayerProperties(VkPhysicalDevice physicalDevice, uint32_t * pPropertyCount, VkLayerProperties * pProperties) {
    VkResult ret;
    _pre_call_vulkan_callback("vkEnumerateDeviceLayerProperties", (GLADapiproc) glad_vkEnumerateDeviceLayerProperties, 3, physicalDevice, pPropertyCount, pProperties);
    ret = glad_vkEnumerateDeviceLayerProperties(physicalDevice, pPropertyCount, pProperties);
    _post_call_vulkan_callback((void*) &ret, "vkEnumerateDeviceLayerProperties", (GLADapiproc) glad_vkEnumerateDeviceLayerProperties, 3, physicalDevice, pPropertyCount, pProperties);
    return ret;
}
PFN_vkEnumerateDeviceLayerProperties glad_debug_vkEnumerateDeviceLayerProperties = glad_debug_impl_vkEnumerateDeviceLayerProperties;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkEnumerateInstanceExtensionProperties(const char * pLayerName, uint32_t * pPropertyCount, VkExtensionProperties * pProperties) {
    glad_vkEnumerateInstanceExtensionProperties = (PFN_vkEnumerateInstanceExtensionProperties) glad_vk_on_demand_loader("vkEnumerateInstanceExtensionProperties");
    return glad_vkEnumerateInstanceExtensionProperties(pLayerName, pPropertyCount, pProperties);
}
PFN_vkEnumerateInstanceExtensionProperties glad_vkEnumerateInstanceExtensionProperties = glad_on_demand_impl_vkEnumerateInstanceExtensionProperties;
static VkResult GLAD_API_PTR glad_debug_impl_vkEnumerateInstanceExtensionProperties(const char * pLayerName, uint32_t * pPropertyCount, VkExtensionProperties * pProperties) {
    VkResult ret;
    _pre_call_vulkan_callback("vkEnumerateInstanceExtensionProperties", (GLADapiproc) glad_vkEnumerateInstanceExtensionProperties, 3, pLayerName, pPropertyCount, pProperties);
    ret = glad_vkEnumerateInstanceExtensionProperties(pLayerName, pPropertyCount, pProperties);
    _post_call_vulkan_callback((void*) &ret, "vkEnumerateInstanceExtensionProperties", (GLADapiproc) glad_vkEnumerateInstanceExtensionProperties, 3, pLayerName, pPropertyCount, pProperties);
    return ret;
}
PFN_vkEnumerateInstanceExtensionProperties glad_debug_vkEnumerateInstanceExtensionProperties = glad_debug_impl_vkEnumerateInstanceExtensionProperties;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkEnumerateInstanceLayerProperties(uint32_t * pPropertyCount, VkLayerProperties * pProperties) {
    glad_vkEnumerateInstanceLayerProperties = (PFN_vkEnumerateInstanceLayerProperties) glad_vk_on_demand_loader("vkEnumerateInstanceLayerProperties");
    return glad_vkEnumerateInstanceLayerProperties(pPropertyCount, pProperties);
}
PFN_vkEnumerateInstanceLayerProperties glad_vkEnumerateInstanceLayerProperties = glad_on_demand_impl_vkEnumerateInstanceLayerProperties;
static VkResult GLAD_API_PTR glad_debug_impl_vkEnumerateInstanceLayerProperties(uint32_t * pPropertyCount, VkLayerProperties * pProperties) {
    VkResult ret;
    _pre_call_vulkan_callback("vkEnumerateInstanceLayerProperties", (GLADapiproc) glad_vkEnumerateInstanceLayerProperties, 2, pPropertyCount, pProperties);
    ret = glad_vkEnumerateInstanceLayerProperties(pPropertyCount, pProperties);
    _post_call_vulkan_callback((void*) &ret, "vkEnumerateInstanceLayerProperties", (GLADapiproc) glad_vkEnumerateInstanceLayerProperties, 2, pPropertyCount, pProperties);
    return ret;
}
PFN_vkEnumerateInstanceLayerProperties glad_debug_vkEnumerateInstanceLayerProperties = glad_debug_impl_vkEnumerateInstanceLayerProperties;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkEnumerateInstanceVersion(uint32_t * pApiVersion) {
    glad_vkEnumerateInstanceVersion = (PFN_vkEnumerateInstanceVersion) glad_vk_on_demand_loader("vkEnumerateInstanceVersion");
    return glad_vkEnumerateInstanceVersion(pApiVersion);
}
PFN_vkEnumerateInstanceVersion glad_vkEnumerateInstanceVersion = glad_on_demand_impl_vkEnumerateInstanceVersion;
static VkResult GLAD_API_PTR glad_debug_impl_vkEnumerateInstanceVersion(uint32_t * pApiVersion) {
    VkResult ret;
    _pre_call_vulkan_callback("vkEnumerateInstanceVersion", (GLADapiproc) glad_vkEnumerateInstanceVersion, 1, pApiVersion);
    ret = glad_vkEnumerateInstanceVersion(pApiVersion);
    _post_call_vulkan_callback((void*) &ret, "vkEnumerateInstanceVersion", (GLADapiproc) glad_vkEnumerateInstanceVersion, 1, pApiVersion);
    return ret;
}
PFN_vkEnumerateInstanceVersion glad_debug_vkEnumerateInstanceVersion = glad_debug_impl_vkEnumerateInstanceVersion;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkEnumeratePhysicalDeviceGroups(VkInstance instance, uint32_t * pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupProperties * pPhysicalDeviceGroupProperties) {
    glad_vkEnumeratePhysicalDeviceGroups = (PFN_vkEnumeratePhysicalDeviceGroups) glad_vk_on_demand_loader("vkEnumeratePhysicalDeviceGroups");
    return glad_vkEnumeratePhysicalDeviceGroups(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
}
PFN_vkEnumeratePhysicalDeviceGroups glad_vkEnumeratePhysicalDeviceGroups = glad_on_demand_impl_vkEnumeratePhysicalDeviceGroups;
static VkResult GLAD_API_PTR glad_debug_impl_vkEnumeratePhysicalDeviceGroups(VkInstance instance, uint32_t * pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupProperties * pPhysicalDeviceGroupProperties) {
    VkResult ret;
    _pre_call_vulkan_callback("vkEnumeratePhysicalDeviceGroups", (GLADapiproc) glad_vkEnumeratePhysicalDeviceGroups, 3, instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
    ret = glad_vkEnumeratePhysicalDeviceGroups(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
    _post_call_vulkan_callback((void*) &ret, "vkEnumeratePhysicalDeviceGroups", (GLADapiproc) glad_vkEnumeratePhysicalDeviceGroups, 3, instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
    return ret;
}
PFN_vkEnumeratePhysicalDeviceGroups glad_debug_vkEnumeratePhysicalDeviceGroups = glad_debug_impl_vkEnumeratePhysicalDeviceGroups;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, uint32_t * pCounterCount, VkPerformanceCounterKHR * pCounters, VkPerformanceCounterDescriptionKHR * pCounterDescriptions) {
    glad_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = (PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR) glad_vk_on_demand_loader("vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR");
    return glad_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(physicalDevice, queueFamilyIndex, pCounterCount, pCounters, pCounterDescriptions);
}
PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR glad_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = glad_on_demand_impl_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR;
static VkResult GLAD_API_PTR glad_debug_impl_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, uint32_t * pCounterCount, VkPerformanceCounterKHR * pCounters, VkPerformanceCounterDescriptionKHR * pCounterDescriptions) {
    VkResult ret;
    _pre_call_vulkan_callback("vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR", (GLADapiproc) glad_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR, 5, physicalDevice, queueFamilyIndex, pCounterCount, pCounters, pCounterDescriptions);
    ret = glad_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(physicalDevice, queueFamilyIndex, pCounterCount, pCounters, pCounterDescriptions);
    _post_call_vulkan_callback((void*) &ret, "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR", (GLADapiproc) glad_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR, 5, physicalDevice, queueFamilyIndex, pCounterCount, pCounters, pCounterDescriptions);
    return ret;
}
PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR glad_debug_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = glad_debug_impl_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkEnumeratePhysicalDevices(VkInstance instance, uint32_t * pPhysicalDeviceCount, VkPhysicalDevice * pPhysicalDevices) {
    glad_vkEnumeratePhysicalDevices = (PFN_vkEnumeratePhysicalDevices) glad_vk_on_demand_loader("vkEnumeratePhysicalDevices");
    return glad_vkEnumeratePhysicalDevices(instance, pPhysicalDeviceCount, pPhysicalDevices);
}
PFN_vkEnumeratePhysicalDevices glad_vkEnumeratePhysicalDevices = glad_on_demand_impl_vkEnumeratePhysicalDevices;
static VkResult GLAD_API_PTR glad_debug_impl_vkEnumeratePhysicalDevices(VkInstance instance, uint32_t * pPhysicalDeviceCount, VkPhysicalDevice * pPhysicalDevices) {
    VkResult ret;
    _pre_call_vulkan_callback("vkEnumeratePhysicalDevices", (GLADapiproc) glad_vkEnumeratePhysicalDevices, 3, instance, pPhysicalDeviceCount, pPhysicalDevices);
    ret = glad_vkEnumeratePhysicalDevices(instance, pPhysicalDeviceCount, pPhysicalDevices);
    _post_call_vulkan_callback((void*) &ret, "vkEnumeratePhysicalDevices", (GLADapiproc) glad_vkEnumeratePhysicalDevices, 3, instance, pPhysicalDeviceCount, pPhysicalDevices);
    return ret;
}
PFN_vkEnumeratePhysicalDevices glad_debug_vkEnumeratePhysicalDevices = glad_debug_impl_vkEnumeratePhysicalDevices;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkFlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange * pMemoryRanges) {
    glad_vkFlushMappedMemoryRanges = (PFN_vkFlushMappedMemoryRanges) glad_vk_on_demand_loader("vkFlushMappedMemoryRanges");
    return glad_vkFlushMappedMemoryRanges(device, memoryRangeCount, pMemoryRanges);
}
PFN_vkFlushMappedMemoryRanges glad_vkFlushMappedMemoryRanges = glad_on_demand_impl_vkFlushMappedMemoryRanges;
static VkResult GLAD_API_PTR glad_debug_impl_vkFlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange * pMemoryRanges) {
    VkResult ret;
    _pre_call_vulkan_callback("vkFlushMappedMemoryRanges", (GLADapiproc) glad_vkFlushMappedMemoryRanges, 3, device, memoryRangeCount, pMemoryRanges);
    ret = glad_vkFlushMappedMemoryRanges(device, memoryRangeCount, pMemoryRanges);
    _post_call_vulkan_callback((void*) &ret, "vkFlushMappedMemoryRanges", (GLADapiproc) glad_vkFlushMappedMemoryRanges, 3, device, memoryRangeCount, pMemoryRanges);
    return ret;
}
PFN_vkFlushMappedMemoryRanges glad_debug_vkFlushMappedMemoryRanges = glad_debug_impl_vkFlushMappedMemoryRanges;
static void GLAD_API_PTR glad_on_demand_impl_vkFreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, const VkCommandBuffer * pCommandBuffers) {
    glad_vkFreeCommandBuffers = (PFN_vkFreeCommandBuffers) glad_vk_on_demand_loader("vkFreeCommandBuffers");
    glad_vkFreeCommandBuffers(device, commandPool, commandBufferCount, pCommandBuffers);
}
PFN_vkFreeCommandBuffers glad_vkFreeCommandBuffers = glad_on_demand_impl_vkFreeCommandBuffers;
static void GLAD_API_PTR glad_debug_impl_vkFreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, const VkCommandBuffer * pCommandBuffers) {
    _pre_call_vulkan_callback("vkFreeCommandBuffers", (GLADapiproc) glad_vkFreeCommandBuffers, 4, device, commandPool, commandBufferCount, pCommandBuffers);
    glad_vkFreeCommandBuffers(device, commandPool, commandBufferCount, pCommandBuffers);
    _post_call_vulkan_callback(NULL, "vkFreeCommandBuffers", (GLADapiproc) glad_vkFreeCommandBuffers, 4, device, commandPool, commandBufferCount, pCommandBuffers);
    
}
PFN_vkFreeCommandBuffers glad_debug_vkFreeCommandBuffers = glad_debug_impl_vkFreeCommandBuffers;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkFreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool, uint32_t descriptorSetCount, const VkDescriptorSet * pDescriptorSets) {
    glad_vkFreeDescriptorSets = (PFN_vkFreeDescriptorSets) glad_vk_on_demand_loader("vkFreeDescriptorSets");
    return glad_vkFreeDescriptorSets(device, descriptorPool, descriptorSetCount, pDescriptorSets);
}
PFN_vkFreeDescriptorSets glad_vkFreeDescriptorSets = glad_on_demand_impl_vkFreeDescriptorSets;
static VkResult GLAD_API_PTR glad_debug_impl_vkFreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool, uint32_t descriptorSetCount, const VkDescriptorSet * pDescriptorSets) {
    VkResult ret;
    _pre_call_vulkan_callback("vkFreeDescriptorSets", (GLADapiproc) glad_vkFreeDescriptorSets, 4, device, descriptorPool, descriptorSetCount, pDescriptorSets);
    ret = glad_vkFreeDescriptorSets(device, descriptorPool, descriptorSetCount, pDescriptorSets);
    _post_call_vulkan_callback((void*) &ret, "vkFreeDescriptorSets", (GLADapiproc) glad_vkFreeDescriptorSets, 4, device, descriptorPool, descriptorSetCount, pDescriptorSets);
    return ret;
}
PFN_vkFreeDescriptorSets glad_debug_vkFreeDescriptorSets = glad_debug_impl_vkFreeDescriptorSets;
static void GLAD_API_PTR glad_on_demand_impl_vkFreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks * pAllocator) {
    glad_vkFreeMemory = (PFN_vkFreeMemory) glad_vk_on_demand_loader("vkFreeMemory");
    glad_vkFreeMemory(device, memory, pAllocator);
}
PFN_vkFreeMemory glad_vkFreeMemory = glad_on_demand_impl_vkFreeMemory;
static void GLAD_API_PTR glad_debug_impl_vkFreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkFreeMemory", (GLADapiproc) glad_vkFreeMemory, 3, device, memory, pAllocator);
    glad_vkFreeMemory(device, memory, pAllocator);
    _post_call_vulkan_callback(NULL, "vkFreeMemory", (GLADapiproc) glad_vkFreeMemory, 3, device, memory, pAllocator);
    
}
PFN_vkFreeMemory glad_debug_vkFreeMemory = glad_debug_impl_vkFreeMemory;
static VkDeviceAddress GLAD_API_PTR glad_on_demand_impl_vkGetBufferDeviceAddress(VkDevice device, const VkBufferDeviceAddressInfo * pInfo) {
    glad_vkGetBufferDeviceAddress = (PFN_vkGetBufferDeviceAddress) glad_vk_on_demand_loader("vkGetBufferDeviceAddress");
    return glad_vkGetBufferDeviceAddress(device, pInfo);
}
PFN_vkGetBufferDeviceAddress glad_vkGetBufferDeviceAddress = glad_on_demand_impl_vkGetBufferDeviceAddress;
static VkDeviceAddress GLAD_API_PTR glad_debug_impl_vkGetBufferDeviceAddress(VkDevice device, const VkBufferDeviceAddressInfo * pInfo) {
    VkDeviceAddress ret;
    _pre_call_vulkan_callback("vkGetBufferDeviceAddress", (GLADapiproc) glad_vkGetBufferDeviceAddress, 2, device, pInfo);
    ret = glad_vkGetBufferDeviceAddress(device, pInfo);
    _post_call_vulkan_callback((void*) &ret, "vkGetBufferDeviceAddress", (GLADapiproc) glad_vkGetBufferDeviceAddress, 2, device, pInfo);
    return ret;
}
PFN_vkGetBufferDeviceAddress glad_debug_vkGetBufferDeviceAddress = glad_debug_impl_vkGetBufferDeviceAddress;
static void GLAD_API_PTR glad_on_demand_impl_vkGetBufferMemoryRequirements(VkDevice device, VkBuffer buffer, VkMemoryRequirements * pMemoryRequirements) {
    glad_vkGetBufferMemoryRequirements = (PFN_vkGetBufferMemoryRequirements) glad_vk_on_demand_loader("vkGetBufferMemoryRequirements");
    glad_vkGetBufferMemoryRequirements(device, buffer, pMemoryRequirements);
}
PFN_vkGetBufferMemoryRequirements glad_vkGetBufferMemoryRequirements = glad_on_demand_impl_vkGetBufferMemoryRequirements;
static void GLAD_API_PTR glad_debug_impl_vkGetBufferMemoryRequirements(VkDevice device, VkBuffer buffer, VkMemoryRequirements * pMemoryRequirements) {
    _pre_call_vulkan_callback("vkGetBufferMemoryRequirements", (GLADapiproc) glad_vkGetBufferMemoryRequirements, 3, device, buffer, pMemoryRequirements);
    glad_vkGetBufferMemoryRequirements(device, buffer, pMemoryRequirements);
    _post_call_vulkan_callback(NULL, "vkGetBufferMemoryRequirements", (GLADapiproc) glad_vkGetBufferMemoryRequirements, 3, device, buffer, pMemoryRequirements);
    
}
PFN_vkGetBufferMemoryRequirements glad_debug_vkGetBufferMemoryRequirements = glad_debug_impl_vkGetBufferMemoryRequirements;
static void GLAD_API_PTR glad_on_demand_impl_vkGetBufferMemoryRequirements2(VkDevice device, const VkBufferMemoryRequirementsInfo2 * pInfo, VkMemoryRequirements2 * pMemoryRequirements) {
    glad_vkGetBufferMemoryRequirements2 = (PFN_vkGetBufferMemoryRequirements2) glad_vk_on_demand_loader("vkGetBufferMemoryRequirements2");
    glad_vkGetBufferMemoryRequirements2(device, pInfo, pMemoryRequirements);
}
PFN_vkGetBufferMemoryRequirements2 glad_vkGetBufferMemoryRequirements2 = glad_on_demand_impl_vkGetBufferMemoryRequirements2;
static void GLAD_API_PTR glad_debug_impl_vkGetBufferMemoryRequirements2(VkDevice device, const VkBufferMemoryRequirementsInfo2 * pInfo, VkMemoryRequirements2 * pMemoryRequirements) {
    _pre_call_vulkan_callback("vkGetBufferMemoryRequirements2", (GLADapiproc) glad_vkGetBufferMemoryRequirements2, 3, device, pInfo, pMemoryRequirements);
    glad_vkGetBufferMemoryRequirements2(device, pInfo, pMemoryRequirements);
    _post_call_vulkan_callback(NULL, "vkGetBufferMemoryRequirements2", (GLADapiproc) glad_vkGetBufferMemoryRequirements2, 3, device, pInfo, pMemoryRequirements);
    
}
PFN_vkGetBufferMemoryRequirements2 glad_debug_vkGetBufferMemoryRequirements2 = glad_debug_impl_vkGetBufferMemoryRequirements2;
static uint64_t GLAD_API_PTR glad_on_demand_impl_vkGetBufferOpaqueCaptureAddress(VkDevice device, const VkBufferDeviceAddressInfo * pInfo) {
    glad_vkGetBufferOpaqueCaptureAddress = (PFN_vkGetBufferOpaqueCaptureAddress) glad_vk_on_demand_loader("vkGetBufferOpaqueCaptureAddress");
    return glad_vkGetBufferOpaqueCaptureAddress(device, pInfo);
}
PFN_vkGetBufferOpaqueCaptureAddress glad_vkGetBufferOpaqueCaptureAddress = glad_on_demand_impl_vkGetBufferOpaqueCaptureAddress;
static uint64_t GLAD_API_PTR glad_debug_impl_vkGetBufferOpaqueCaptureAddress(VkDevice device, const VkBufferDeviceAddressInfo * pInfo) {
    uint64_t ret;
    _pre_call_vulkan_callback("vkGetBufferOpaqueCaptureAddress", (GLADapiproc) glad_vkGetBufferOpaqueCaptureAddress, 2, device, pInfo);
    ret = glad_vkGetBufferOpaqueCaptureAddress(device, pInfo);
    _post_call_vulkan_callback((void*) &ret, "vkGetBufferOpaqueCaptureAddress", (GLADapiproc) glad_vkGetBufferOpaqueCaptureAddress, 2, device, pInfo);
    return ret;
}
PFN_vkGetBufferOpaqueCaptureAddress glad_debug_vkGetBufferOpaqueCaptureAddress = glad_debug_impl_vkGetBufferOpaqueCaptureAddress;
static void GLAD_API_PTR glad_on_demand_impl_vkGetDescriptorSetLayoutSupport(VkDevice device, const VkDescriptorSetLayoutCreateInfo * pCreateInfo, VkDescriptorSetLayoutSupport * pSupport) {
    glad_vkGetDescriptorSetLayoutSupport = (PFN_vkGetDescriptorSetLayoutSupport) glad_vk_on_demand_loader("vkGetDescriptorSetLayoutSupport");
    glad_vkGetDescriptorSetLayoutSupport(device, pCreateInfo, pSupport);
}
PFN_vkGetDescriptorSetLayoutSupport glad_vkGetDescriptorSetLayoutSupport = glad_on_demand_impl_vkGetDescriptorSetLayoutSupport;
static void GLAD_API_PTR glad_debug_impl_vkGetDescriptorSetLayoutSupport(VkDevice device, const VkDescriptorSetLayoutCreateInfo * pCreateInfo, VkDescriptorSetLayoutSupport * pSupport) {
    _pre_call_vulkan_callback("vkGetDescriptorSetLayoutSupport", (GLADapiproc) glad_vkGetDescriptorSetLayoutSupport, 3, device, pCreateInfo, pSupport);
    glad_vkGetDescriptorSetLayoutSupport(device, pCreateInfo, pSupport);
    _post_call_vulkan_callback(NULL, "vkGetDescriptorSetLayoutSupport", (GLADapiproc) glad_vkGetDescriptorSetLayoutSupport, 3, device, pCreateInfo, pSupport);
    
}
PFN_vkGetDescriptorSetLayoutSupport glad_debug_vkGetDescriptorSetLayoutSupport = glad_debug_impl_vkGetDescriptorSetLayoutSupport;
static void GLAD_API_PTR glad_on_demand_impl_vkGetDeviceGroupPeerMemoryFeatures(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags * pPeerMemoryFeatures) {
    glad_vkGetDeviceGroupPeerMemoryFeatures = (PFN_vkGetDeviceGroupPeerMemoryFeatures) glad_vk_on_demand_loader("vkGetDeviceGroupPeerMemoryFeatures");
    glad_vkGetDeviceGroupPeerMemoryFeatures(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
}
PFN_vkGetDeviceGroupPeerMemoryFeatures glad_vkGetDeviceGroupPeerMemoryFeatures = glad_on_demand_impl_vkGetDeviceGroupPeerMemoryFeatures;
static void GLAD_API_PTR glad_debug_impl_vkGetDeviceGroupPeerMemoryFeatures(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags * pPeerMemoryFeatures) {
    _pre_call_vulkan_callback("vkGetDeviceGroupPeerMemoryFeatures", (GLADapiproc) glad_vkGetDeviceGroupPeerMemoryFeatures, 5, device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
    glad_vkGetDeviceGroupPeerMemoryFeatures(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
    _post_call_vulkan_callback(NULL, "vkGetDeviceGroupPeerMemoryFeatures", (GLADapiproc) glad_vkGetDeviceGroupPeerMemoryFeatures, 5, device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
    
}
PFN_vkGetDeviceGroupPeerMemoryFeatures glad_debug_vkGetDeviceGroupPeerMemoryFeatures = glad_debug_impl_vkGetDeviceGroupPeerMemoryFeatures;
static void GLAD_API_PTR glad_on_demand_impl_vkGetDeviceGroupPeerMemoryFeaturesKHR(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags * pPeerMemoryFeatures) {
    glad_vkGetDeviceGroupPeerMemoryFeaturesKHR = (PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR) glad_vk_on_demand_loader("vkGetDeviceGroupPeerMemoryFeaturesKHR");
    glad_vkGetDeviceGroupPeerMemoryFeaturesKHR(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
}
PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR glad_vkGetDeviceGroupPeerMemoryFeaturesKHR = glad_on_demand_impl_vkGetDeviceGroupPeerMemoryFeaturesKHR;
static void GLAD_API_PTR glad_debug_impl_vkGetDeviceGroupPeerMemoryFeaturesKHR(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags * pPeerMemoryFeatures) {
    _pre_call_vulkan_callback("vkGetDeviceGroupPeerMemoryFeaturesKHR", (GLADapiproc) glad_vkGetDeviceGroupPeerMemoryFeaturesKHR, 5, device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
    glad_vkGetDeviceGroupPeerMemoryFeaturesKHR(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
    _post_call_vulkan_callback(NULL, "vkGetDeviceGroupPeerMemoryFeaturesKHR", (GLADapiproc) glad_vkGetDeviceGroupPeerMemoryFeaturesKHR, 5, device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
    
}
PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR glad_debug_vkGetDeviceGroupPeerMemoryFeaturesKHR = glad_debug_impl_vkGetDeviceGroupPeerMemoryFeaturesKHR;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkGetDeviceGroupPresentCapabilitiesKHR(VkDevice device, VkDeviceGroupPresentCapabilitiesKHR * pDeviceGroupPresentCapabilities) {
    glad_vkGetDeviceGroupPresentCapabilitiesKHR = (PFN_vkGetDeviceGroupPresentCapabilitiesKHR) glad_vk_on_demand_loader("vkGetDeviceGroupPresentCapabilitiesKHR");
    return glad_vkGetDeviceGroupPresentCapabilitiesKHR(device, pDeviceGroupPresentCapabilities);
}
PFN_vkGetDeviceGroupPresentCapabilitiesKHR glad_vkGetDeviceGroupPresentCapabilitiesKHR = glad_on_demand_impl_vkGetDeviceGroupPresentCapabilitiesKHR;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetDeviceGroupPresentCapabilitiesKHR(VkDevice device, VkDeviceGroupPresentCapabilitiesKHR * pDeviceGroupPresentCapabilities) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetDeviceGroupPresentCapabilitiesKHR", (GLADapiproc) glad_vkGetDeviceGroupPresentCapabilitiesKHR, 2, device, pDeviceGroupPresentCapabilities);
    ret = glad_vkGetDeviceGroupPresentCapabilitiesKHR(device, pDeviceGroupPresentCapabilities);
    _post_call_vulkan_callback((void*) &ret, "vkGetDeviceGroupPresentCapabilitiesKHR", (GLADapiproc) glad_vkGetDeviceGroupPresentCapabilitiesKHR, 2, device, pDeviceGroupPresentCapabilities);
    return ret;
}
PFN_vkGetDeviceGroupPresentCapabilitiesKHR glad_debug_vkGetDeviceGroupPresentCapabilitiesKHR = glad_debug_impl_vkGetDeviceGroupPresentCapabilitiesKHR;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkGetDeviceGroupSurfacePresentModesKHR(VkDevice device, VkSurfaceKHR surface, VkDeviceGroupPresentModeFlagsKHR * pModes) {
    glad_vkGetDeviceGroupSurfacePresentModesKHR = (PFN_vkGetDeviceGroupSurfacePresentModesKHR) glad_vk_on_demand_loader("vkGetDeviceGroupSurfacePresentModesKHR");
    return glad_vkGetDeviceGroupSurfacePresentModesKHR(device, surface, pModes);
}
PFN_vkGetDeviceGroupSurfacePresentModesKHR glad_vkGetDeviceGroupSurfacePresentModesKHR = glad_on_demand_impl_vkGetDeviceGroupSurfacePresentModesKHR;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetDeviceGroupSurfacePresentModesKHR(VkDevice device, VkSurfaceKHR surface, VkDeviceGroupPresentModeFlagsKHR * pModes) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetDeviceGroupSurfacePresentModesKHR", (GLADapiproc) glad_vkGetDeviceGroupSurfacePresentModesKHR, 3, device, surface, pModes);
    ret = glad_vkGetDeviceGroupSurfacePresentModesKHR(device, surface, pModes);
    _post_call_vulkan_callback((void*) &ret, "vkGetDeviceGroupSurfacePresentModesKHR", (GLADapiproc) glad_vkGetDeviceGroupSurfacePresentModesKHR, 3, device, surface, pModes);
    return ret;
}
PFN_vkGetDeviceGroupSurfacePresentModesKHR glad_debug_vkGetDeviceGroupSurfacePresentModesKHR = glad_debug_impl_vkGetDeviceGroupSurfacePresentModesKHR;
static void GLAD_API_PTR glad_on_demand_impl_vkGetDeviceMemoryCommitment(VkDevice device, VkDeviceMemory memory, VkDeviceSize * pCommittedMemoryInBytes) {
    glad_vkGetDeviceMemoryCommitment = (PFN_vkGetDeviceMemoryCommitment) glad_vk_on_demand_loader("vkGetDeviceMemoryCommitment");
    glad_vkGetDeviceMemoryCommitment(device, memory, pCommittedMemoryInBytes);
}
PFN_vkGetDeviceMemoryCommitment glad_vkGetDeviceMemoryCommitment = glad_on_demand_impl_vkGetDeviceMemoryCommitment;
static void GLAD_API_PTR glad_debug_impl_vkGetDeviceMemoryCommitment(VkDevice device, VkDeviceMemory memory, VkDeviceSize * pCommittedMemoryInBytes) {
    _pre_call_vulkan_callback("vkGetDeviceMemoryCommitment", (GLADapiproc) glad_vkGetDeviceMemoryCommitment, 3, device, memory, pCommittedMemoryInBytes);
    glad_vkGetDeviceMemoryCommitment(device, memory, pCommittedMemoryInBytes);
    _post_call_vulkan_callback(NULL, "vkGetDeviceMemoryCommitment", (GLADapiproc) glad_vkGetDeviceMemoryCommitment, 3, device, memory, pCommittedMemoryInBytes);
    
}
PFN_vkGetDeviceMemoryCommitment glad_debug_vkGetDeviceMemoryCommitment = glad_debug_impl_vkGetDeviceMemoryCommitment;
static uint64_t GLAD_API_PTR glad_on_demand_impl_vkGetDeviceMemoryOpaqueCaptureAddress(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo * pInfo) {
    glad_vkGetDeviceMemoryOpaqueCaptureAddress = (PFN_vkGetDeviceMemoryOpaqueCaptureAddress) glad_vk_on_demand_loader("vkGetDeviceMemoryOpaqueCaptureAddress");
    return glad_vkGetDeviceMemoryOpaqueCaptureAddress(device, pInfo);
}
PFN_vkGetDeviceMemoryOpaqueCaptureAddress glad_vkGetDeviceMemoryOpaqueCaptureAddress = glad_on_demand_impl_vkGetDeviceMemoryOpaqueCaptureAddress;
static uint64_t GLAD_API_PTR glad_debug_impl_vkGetDeviceMemoryOpaqueCaptureAddress(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo * pInfo) {
    uint64_t ret;
    _pre_call_vulkan_callback("vkGetDeviceMemoryOpaqueCaptureAddress", (GLADapiproc) glad_vkGetDeviceMemoryOpaqueCaptureAddress, 2, device, pInfo);
    ret = glad_vkGetDeviceMemoryOpaqueCaptureAddress(device, pInfo);
    _post_call_vulkan_callback((void*) &ret, "vkGetDeviceMemoryOpaqueCaptureAddress", (GLADapiproc) glad_vkGetDeviceMemoryOpaqueCaptureAddress, 2, device, pInfo);
    return ret;
}
PFN_vkGetDeviceMemoryOpaqueCaptureAddress glad_debug_vkGetDeviceMemoryOpaqueCaptureAddress = glad_debug_impl_vkGetDeviceMemoryOpaqueCaptureAddress;
static PFN_vkVoidFunction GLAD_API_PTR glad_on_demand_impl_vkGetDeviceProcAddr(VkDevice device, const char * pName) {
    glad_vkGetDeviceProcAddr = (PFN_vkGetDeviceProcAddr) glad_vk_on_demand_loader("vkGetDeviceProcAddr");
    return glad_vkGetDeviceProcAddr(device, pName);
}
PFN_vkGetDeviceProcAddr glad_vkGetDeviceProcAddr = glad_on_demand_impl_vkGetDeviceProcAddr;
static PFN_vkVoidFunction GLAD_API_PTR glad_debug_impl_vkGetDeviceProcAddr(VkDevice device, const char * pName) {
    PFN_vkVoidFunction ret;
    _pre_call_vulkan_callback("vkGetDeviceProcAddr", (GLADapiproc) glad_vkGetDeviceProcAddr, 2, device, pName);
    ret = glad_vkGetDeviceProcAddr(device, pName);
    _post_call_vulkan_callback((void*) &ret, "vkGetDeviceProcAddr", (GLADapiproc) glad_vkGetDeviceProcAddr, 2, device, pName);
    return ret;
}
PFN_vkGetDeviceProcAddr glad_debug_vkGetDeviceProcAddr = glad_debug_impl_vkGetDeviceProcAddr;
static void GLAD_API_PTR glad_on_demand_impl_vkGetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue * pQueue) {
    glad_vkGetDeviceQueue = (PFN_vkGetDeviceQueue) glad_vk_on_demand_loader("vkGetDeviceQueue");
    glad_vkGetDeviceQueue(device, queueFamilyIndex, queueIndex, pQueue);
}
PFN_vkGetDeviceQueue glad_vkGetDeviceQueue = glad_on_demand_impl_vkGetDeviceQueue;
static void GLAD_API_PTR glad_debug_impl_vkGetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue * pQueue) {
    _pre_call_vulkan_callback("vkGetDeviceQueue", (GLADapiproc) glad_vkGetDeviceQueue, 4, device, queueFamilyIndex, queueIndex, pQueue);
    glad_vkGetDeviceQueue(device, queueFamilyIndex, queueIndex, pQueue);
    _post_call_vulkan_callback(NULL, "vkGetDeviceQueue", (GLADapiproc) glad_vkGetDeviceQueue, 4, device, queueFamilyIndex, queueIndex, pQueue);
    
}
PFN_vkGetDeviceQueue glad_debug_vkGetDeviceQueue = glad_debug_impl_vkGetDeviceQueue;
static void GLAD_API_PTR glad_on_demand_impl_vkGetDeviceQueue2(VkDevice device, const VkDeviceQueueInfo2 * pQueueInfo, VkQueue * pQueue) {
    glad_vkGetDeviceQueue2 = (PFN_vkGetDeviceQueue2) glad_vk_on_demand_loader("vkGetDeviceQueue2");
    glad_vkGetDeviceQueue2(device, pQueueInfo, pQueue);
}
PFN_vkGetDeviceQueue2 glad_vkGetDeviceQueue2 = glad_on_demand_impl_vkGetDeviceQueue2;
static void GLAD_API_PTR glad_debug_impl_vkGetDeviceQueue2(VkDevice device, const VkDeviceQueueInfo2 * pQueueInfo, VkQueue * pQueue) {
    _pre_call_vulkan_callback("vkGetDeviceQueue2", (GLADapiproc) glad_vkGetDeviceQueue2, 3, device, pQueueInfo, pQueue);
    glad_vkGetDeviceQueue2(device, pQueueInfo, pQueue);
    _post_call_vulkan_callback(NULL, "vkGetDeviceQueue2", (GLADapiproc) glad_vkGetDeviceQueue2, 3, device, pQueueInfo, pQueue);
    
}
PFN_vkGetDeviceQueue2 glad_debug_vkGetDeviceQueue2 = glad_debug_impl_vkGetDeviceQueue2;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkGetEventStatus(VkDevice device, VkEvent event) {
    glad_vkGetEventStatus = (PFN_vkGetEventStatus) glad_vk_on_demand_loader("vkGetEventStatus");
    return glad_vkGetEventStatus(device, event);
}
PFN_vkGetEventStatus glad_vkGetEventStatus = glad_on_demand_impl_vkGetEventStatus;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetEventStatus(VkDevice device, VkEvent event) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetEventStatus", (GLADapiproc) glad_vkGetEventStatus, 2, device, event);
    ret = glad_vkGetEventStatus(device, event);
    _post_call_vulkan_callback((void*) &ret, "vkGetEventStatus", (GLADapiproc) glad_vkGetEventStatus, 2, device, event);
    return ret;
}
PFN_vkGetEventStatus glad_debug_vkGetEventStatus = glad_debug_impl_vkGetEventStatus;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkGetFenceStatus(VkDevice device, VkFence fence) {
    glad_vkGetFenceStatus = (PFN_vkGetFenceStatus) glad_vk_on_demand_loader("vkGetFenceStatus");
    return glad_vkGetFenceStatus(device, fence);
}
PFN_vkGetFenceStatus glad_vkGetFenceStatus = glad_on_demand_impl_vkGetFenceStatus;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetFenceStatus(VkDevice device, VkFence fence) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetFenceStatus", (GLADapiproc) glad_vkGetFenceStatus, 2, device, fence);
    ret = glad_vkGetFenceStatus(device, fence);
    _post_call_vulkan_callback((void*) &ret, "vkGetFenceStatus", (GLADapiproc) glad_vkGetFenceStatus, 2, device, fence);
    return ret;
}
PFN_vkGetFenceStatus glad_debug_vkGetFenceStatus = glad_debug_impl_vkGetFenceStatus;
static void GLAD_API_PTR glad_on_demand_impl_vkGetImageMemoryRequirements(VkDevice device, VkImage image, VkMemoryRequirements * pMemoryRequirements) {
    glad_vkGetImageMemoryRequirements = (PFN_vkGetImageMemoryRequirements) glad_vk_on_demand_loader("vkGetImageMemoryRequirements");
    glad_vkGetImageMemoryRequirements(device, image, pMemoryRequirements);
}
PFN_vkGetImageMemoryRequirements glad_vkGetImageMemoryRequirements = glad_on_demand_impl_vkGetImageMemoryRequirements;
static void GLAD_API_PTR glad_debug_impl_vkGetImageMemoryRequirements(VkDevice device, VkImage image, VkMemoryRequirements * pMemoryRequirements) {
    _pre_call_vulkan_callback("vkGetImageMemoryRequirements", (GLADapiproc) glad_vkGetImageMemoryRequirements, 3, device, image, pMemoryRequirements);
    glad_vkGetImageMemoryRequirements(device, image, pMemoryRequirements);
    _post_call_vulkan_callback(NULL, "vkGetImageMemoryRequirements", (GLADapiproc) glad_vkGetImageMemoryRequirements, 3, device, image, pMemoryRequirements);
    
}
PFN_vkGetImageMemoryRequirements glad_debug_vkGetImageMemoryRequirements = glad_debug_impl_vkGetImageMemoryRequirements;
static void GLAD_API_PTR glad_on_demand_impl_vkGetImageMemoryRequirements2(VkDevice device, const VkImageMemoryRequirementsInfo2 * pInfo, VkMemoryRequirements2 * pMemoryRequirements) {
    glad_vkGetImageMemoryRequirements2 = (PFN_vkGetImageMemoryRequirements2) glad_vk_on_demand_loader("vkGetImageMemoryRequirements2");
    glad_vkGetImageMemoryRequirements2(device, pInfo, pMemoryRequirements);
}
PFN_vkGetImageMemoryRequirements2 glad_vkGetImageMemoryRequirements2 = glad_on_demand_impl_vkGetImageMemoryRequirements2;
static void GLAD_API_PTR glad_debug_impl_vkGetImageMemoryRequirements2(VkDevice device, const VkImageMemoryRequirementsInfo2 * pInfo, VkMemoryRequirements2 * pMemoryRequirements) {
    _pre_call_vulkan_callback("vkGetImageMemoryRequirements2", (GLADapiproc) glad_vkGetImageMemoryRequirements2, 3, device, pInfo, pMemoryRequirements);
    glad_vkGetImageMemoryRequirements2(device, pInfo, pMemoryRequirements);
    _post_call_vulkan_callback(NULL, "vkGetImageMemoryRequirements2", (GLADapiproc) glad_vkGetImageMemoryRequirements2, 3, device, pInfo, pMemoryRequirements);
    
}
PFN_vkGetImageMemoryRequirements2 glad_debug_vkGetImageMemoryRequirements2 = glad_debug_impl_vkGetImageMemoryRequirements2;
static void GLAD_API_PTR glad_on_demand_impl_vkGetImageSparseMemoryRequirements(VkDevice device, VkImage image, uint32_t * pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements * pSparseMemoryRequirements) {
    glad_vkGetImageSparseMemoryRequirements = (PFN_vkGetImageSparseMemoryRequirements) glad_vk_on_demand_loader("vkGetImageSparseMemoryRequirements");
    glad_vkGetImageSparseMemoryRequirements(device, image, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}
PFN_vkGetImageSparseMemoryRequirements glad_vkGetImageSparseMemoryRequirements = glad_on_demand_impl_vkGetImageSparseMemoryRequirements;
static void GLAD_API_PTR glad_debug_impl_vkGetImageSparseMemoryRequirements(VkDevice device, VkImage image, uint32_t * pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements * pSparseMemoryRequirements) {
    _pre_call_vulkan_callback("vkGetImageSparseMemoryRequirements", (GLADapiproc) glad_vkGetImageSparseMemoryRequirements, 4, device, image, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    glad_vkGetImageSparseMemoryRequirements(device, image, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    _post_call_vulkan_callback(NULL, "vkGetImageSparseMemoryRequirements", (GLADapiproc) glad_vkGetImageSparseMemoryRequirements, 4, device, image, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    
}
PFN_vkGetImageSparseMemoryRequirements glad_debug_vkGetImageSparseMemoryRequirements = glad_debug_impl_vkGetImageSparseMemoryRequirements;
static void GLAD_API_PTR glad_on_demand_impl_vkGetImageSparseMemoryRequirements2(VkDevice device, const VkImageSparseMemoryRequirementsInfo2 * pInfo, uint32_t * pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2 * pSparseMemoryRequirements) {
    glad_vkGetImageSparseMemoryRequirements2 = (PFN_vkGetImageSparseMemoryRequirements2) glad_vk_on_demand_loader("vkGetImageSparseMemoryRequirements2");
    glad_vkGetImageSparseMemoryRequirements2(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}
PFN_vkGetImageSparseMemoryRequirements2 glad_vkGetImageSparseMemoryRequirements2 = glad_on_demand_impl_vkGetImageSparseMemoryRequirements2;
static void GLAD_API_PTR glad_debug_impl_vkGetImageSparseMemoryRequirements2(VkDevice device, const VkImageSparseMemoryRequirementsInfo2 * pInfo, uint32_t * pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2 * pSparseMemoryRequirements) {
    _pre_call_vulkan_callback("vkGetImageSparseMemoryRequirements2", (GLADapiproc) glad_vkGetImageSparseMemoryRequirements2, 4, device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    glad_vkGetImageSparseMemoryRequirements2(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    _post_call_vulkan_callback(NULL, "vkGetImageSparseMemoryRequirements2", (GLADapiproc) glad_vkGetImageSparseMemoryRequirements2, 4, device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    
}
PFN_vkGetImageSparseMemoryRequirements2 glad_debug_vkGetImageSparseMemoryRequirements2 = glad_debug_impl_vkGetImageSparseMemoryRequirements2;
static void GLAD_API_PTR glad_on_demand_impl_vkGetImageSubresourceLayout(VkDevice device, VkImage image, const VkImageSubresource * pSubresource, VkSubresourceLayout * pLayout) {
    glad_vkGetImageSubresourceLayout = (PFN_vkGetImageSubresourceLayout) glad_vk_on_demand_loader("vkGetImageSubresourceLayout");
    glad_vkGetImageSubresourceLayout(device, image, pSubresource, pLayout);
}
PFN_vkGetImageSubresourceLayout glad_vkGetImageSubresourceLayout = glad_on_demand_impl_vkGetImageSubresourceLayout;
static void GLAD_API_PTR glad_debug_impl_vkGetImageSubresourceLayout(VkDevice device, VkImage image, const VkImageSubresource * pSubresource, VkSubresourceLayout * pLayout) {
    _pre_call_vulkan_callback("vkGetImageSubresourceLayout", (GLADapiproc) glad_vkGetImageSubresourceLayout, 4, device, image, pSubresource, pLayout);
    glad_vkGetImageSubresourceLayout(device, image, pSubresource, pLayout);
    _post_call_vulkan_callback(NULL, "vkGetImageSubresourceLayout", (GLADapiproc) glad_vkGetImageSubresourceLayout, 4, device, image, pSubresource, pLayout);
    
}
PFN_vkGetImageSubresourceLayout glad_debug_vkGetImageSubresourceLayout = glad_debug_impl_vkGetImageSubresourceLayout;
static PFN_vkVoidFunction GLAD_API_PTR glad_on_demand_impl_vkGetInstanceProcAddr(VkInstance instance, const char * pName) {
    glad_vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr) glad_vk_on_demand_loader("vkGetInstanceProcAddr");
    return glad_vkGetInstanceProcAddr(instance, pName);
}
PFN_vkGetInstanceProcAddr glad_vkGetInstanceProcAddr = glad_on_demand_impl_vkGetInstanceProcAddr;
static PFN_vkVoidFunction GLAD_API_PTR glad_debug_impl_vkGetInstanceProcAddr(VkInstance instance, const char * pName) {
    PFN_vkVoidFunction ret;
    _pre_call_vulkan_callback("vkGetInstanceProcAddr", (GLADapiproc) glad_vkGetInstanceProcAddr, 2, instance, pName);
    ret = glad_vkGetInstanceProcAddr(instance, pName);
    _post_call_vulkan_callback((void*) &ret, "vkGetInstanceProcAddr", (GLADapiproc) glad_vkGetInstanceProcAddr, 2, instance, pName);
    return ret;
}
PFN_vkGetInstanceProcAddr glad_debug_vkGetInstanceProcAddr = glad_debug_impl_vkGetInstanceProcAddr;
static void GLAD_API_PTR glad_on_demand_impl_vkGetPhysicalDeviceExternalBufferProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalBufferInfo * pExternalBufferInfo, VkExternalBufferProperties * pExternalBufferProperties) {
    glad_vkGetPhysicalDeviceExternalBufferProperties = (PFN_vkGetPhysicalDeviceExternalBufferProperties) glad_vk_on_demand_loader("vkGetPhysicalDeviceExternalBufferProperties");
    glad_vkGetPhysicalDeviceExternalBufferProperties(physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
}
PFN_vkGetPhysicalDeviceExternalBufferProperties glad_vkGetPhysicalDeviceExternalBufferProperties = glad_on_demand_impl_vkGetPhysicalDeviceExternalBufferProperties;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceExternalBufferProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalBufferInfo * pExternalBufferInfo, VkExternalBufferProperties * pExternalBufferProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceExternalBufferProperties", (GLADapiproc) glad_vkGetPhysicalDeviceExternalBufferProperties, 3, physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
    glad_vkGetPhysicalDeviceExternalBufferProperties(physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceExternalBufferProperties", (GLADapiproc) glad_vkGetPhysicalDeviceExternalBufferProperties, 3, physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
    
}
PFN_vkGetPhysicalDeviceExternalBufferProperties glad_debug_vkGetPhysicalDeviceExternalBufferProperties = glad_debug_impl_vkGetPhysicalDeviceExternalBufferProperties;
static void GLAD_API_PTR glad_on_demand_impl_vkGetPhysicalDeviceExternalFenceProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalFenceInfo * pExternalFenceInfo, VkExternalFenceProperties * pExternalFenceProperties) {
    glad_vkGetPhysicalDeviceExternalFenceProperties = (PFN_vkGetPhysicalDeviceExternalFenceProperties) glad_vk_on_demand_loader("vkGetPhysicalDeviceExternalFenceProperties");
    glad_vkGetPhysicalDeviceExternalFenceProperties(physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
}
PFN_vkGetPhysicalDeviceExternalFenceProperties glad_vkGetPhysicalDeviceExternalFenceProperties = glad_on_demand_impl_vkGetPhysicalDeviceExternalFenceProperties;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceExternalFenceProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalFenceInfo * pExternalFenceInfo, VkExternalFenceProperties * pExternalFenceProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceExternalFenceProperties", (GLADapiproc) glad_vkGetPhysicalDeviceExternalFenceProperties, 3, physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
    glad_vkGetPhysicalDeviceExternalFenceProperties(physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceExternalFenceProperties", (GLADapiproc) glad_vkGetPhysicalDeviceExternalFenceProperties, 3, physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
    
}
PFN_vkGetPhysicalDeviceExternalFenceProperties glad_debug_vkGetPhysicalDeviceExternalFenceProperties = glad_debug_impl_vkGetPhysicalDeviceExternalFenceProperties;
static void GLAD_API_PTR glad_on_demand_impl_vkGetPhysicalDeviceExternalSemaphoreProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalSemaphoreInfo * pExternalSemaphoreInfo, VkExternalSemaphoreProperties * pExternalSemaphoreProperties) {
    glad_vkGetPhysicalDeviceExternalSemaphoreProperties = (PFN_vkGetPhysicalDeviceExternalSemaphoreProperties) glad_vk_on_demand_loader("vkGetPhysicalDeviceExternalSemaphoreProperties");
    glad_vkGetPhysicalDeviceExternalSemaphoreProperties(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
}
PFN_vkGetPhysicalDeviceExternalSemaphoreProperties glad_vkGetPhysicalDeviceExternalSemaphoreProperties = glad_on_demand_impl_vkGetPhysicalDeviceExternalSemaphoreProperties;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceExternalSemaphoreProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalSemaphoreInfo * pExternalSemaphoreInfo, VkExternalSemaphoreProperties * pExternalSemaphoreProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceExternalSemaphoreProperties", (GLADapiproc) glad_vkGetPhysicalDeviceExternalSemaphoreProperties, 3, physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
    glad_vkGetPhysicalDeviceExternalSemaphoreProperties(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceExternalSemaphoreProperties", (GLADapiproc) glad_vkGetPhysicalDeviceExternalSemaphoreProperties, 3, physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
    
}
PFN_vkGetPhysicalDeviceExternalSemaphoreProperties glad_debug_vkGetPhysicalDeviceExternalSemaphoreProperties = glad_debug_impl_vkGetPhysicalDeviceExternalSemaphoreProperties;
static void GLAD_API_PTR glad_on_demand_impl_vkGetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures * pFeatures) {
    glad_vkGetPhysicalDeviceFeatures = (PFN_vkGetPhysicalDeviceFeatures) glad_vk_on_demand_loader("vkGetPhysicalDeviceFeatures");
    glad_vkGetPhysicalDeviceFeatures(physicalDevice, pFeatures);
}
PFN_vkGetPhysicalDeviceFeatures glad_vkGetPhysicalDeviceFeatures = glad_on_demand_impl_vkGetPhysicalDeviceFeatures;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures * pFeatures) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceFeatures", (GLADapiproc) glad_vkGetPhysicalDeviceFeatures, 2, physicalDevice, pFeatures);
    glad_vkGetPhysicalDeviceFeatures(physicalDevice, pFeatures);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceFeatures", (GLADapiproc) glad_vkGetPhysicalDeviceFeatures, 2, physicalDevice, pFeatures);
    
}
PFN_vkGetPhysicalDeviceFeatures glad_debug_vkGetPhysicalDeviceFeatures = glad_debug_impl_vkGetPhysicalDeviceFeatures;
static void GLAD_API_PTR glad_on_demand_impl_vkGetPhysicalDeviceFeatures2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2 * pFeatures) {
    glad_vkGetPhysicalDeviceFeatures2 = (PFN_vkGetPhysicalDeviceFeatures2) glad_vk_on_demand_loader("vkGetPhysicalDeviceFeatures2");
    glad_vkGetPhysicalDeviceFeatures2(physicalDevice, pFeatures);
}
PFN_vkGetPhysicalDeviceFeatures2 glad_vkGetPhysicalDeviceFeatures2 = glad_on_demand_impl_vkGetPhysicalDeviceFeatures2;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceFeatures2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2 * pFeatures) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceFeatures2", (GLADapiproc) glad_vkGetPhysicalDeviceFeatures2, 2, physicalDevice, pFeatures);
    glad_vkGetPhysicalDeviceFeatures2(physicalDevice, pFeatures);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceFeatures2", (GLADapiproc) glad_vkGetPhysicalDeviceFeatures2, 2, physicalDevice, pFeatures);
    
}
PFN_vkGetPhysicalDeviceFeatures2 glad_debug_vkGetPhysicalDeviceFeatures2 = glad_debug_impl_vkGetPhysicalDeviceFeatures2;
static void GLAD_API_PTR glad_on_demand_impl_vkGetPhysicalDeviceFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties * pFormatProperties) {
    glad_vkGetPhysicalDeviceFormatProperties = (PFN_vkGetPhysicalDeviceFormatProperties) glad_vk_on_demand_loader("vkGetPhysicalDeviceFormatProperties");
    glad_vkGetPhysicalDeviceFormatProperties(physicalDevice, format, pFormatProperties);
}
PFN_vkGetPhysicalDeviceFormatProperties glad_vkGetPhysicalDeviceFormatProperties = glad_on_demand_impl_vkGetPhysicalDeviceFormatProperties;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties * pFormatProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceFormatProperties", (GLADapiproc) glad_vkGetPhysicalDeviceFormatProperties, 3, physicalDevice, format, pFormatProperties);
    glad_vkGetPhysicalDeviceFormatProperties(physicalDevice, format, pFormatProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceFormatProperties", (GLADapiproc) glad_vkGetPhysicalDeviceFormatProperties, 3, physicalDevice, format, pFormatProperties);
    
}
PFN_vkGetPhysicalDeviceFormatProperties glad_debug_vkGetPhysicalDeviceFormatProperties = glad_debug_impl_vkGetPhysicalDeviceFormatProperties;
static void GLAD_API_PTR glad_on_demand_impl_vkGetPhysicalDeviceFormatProperties2(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties2 * pFormatProperties) {
    glad_vkGetPhysicalDeviceFormatProperties2 = (PFN_vkGetPhysicalDeviceFormatProperties2) glad_vk_on_demand_loader("vkGetPhysicalDeviceFormatProperties2");
    glad_vkGetPhysicalDeviceFormatProperties2(physicalDevice, format, pFormatProperties);
}
PFN_vkGetPhysicalDeviceFormatProperties2 glad_vkGetPhysicalDeviceFormatProperties2 = glad_on_demand_impl_vkGetPhysicalDeviceFormatProperties2;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceFormatProperties2(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties2 * pFormatProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceFormatProperties2", (GLADapiproc) glad_vkGetPhysicalDeviceFormatProperties2, 3, physicalDevice, format, pFormatProperties);
    glad_vkGetPhysicalDeviceFormatProperties2(physicalDevice, format, pFormatProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceFormatProperties2", (GLADapiproc) glad_vkGetPhysicalDeviceFormatProperties2, 3, physicalDevice, format, pFormatProperties);
    
}
PFN_vkGetPhysicalDeviceFormatProperties2 glad_debug_vkGetPhysicalDeviceFormatProperties2 = glad_debug_impl_vkGetPhysicalDeviceFormatProperties2;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkGetPhysicalDeviceImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkImageFormatProperties * pImageFormatProperties) {
    glad_vkGetPhysicalDeviceImageFormatProperties = (PFN_vkGetPhysicalDeviceImageFormatProperties) glad_vk_on_demand_loader("vkGetPhysicalDeviceImageFormatProperties");
    return glad_vkGetPhysicalDeviceImageFormatProperties(physicalDevice, format, type, tiling, usage, flags, pImageFormatProperties);
}
PFN_vkGetPhysicalDeviceImageFormatProperties glad_vkGetPhysicalDeviceImageFormatProperties = glad_on_demand_impl_vkGetPhysicalDeviceImageFormatProperties;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkImageFormatProperties * pImageFormatProperties) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetPhysicalDeviceImageFormatProperties", (GLADapiproc) glad_vkGetPhysicalDeviceImageFormatProperties, 7, physicalDevice, format, type, tiling, usage, flags, pImageFormatProperties);
    ret = glad_vkGetPhysicalDeviceImageFormatProperties(physicalDevice, format, type, tiling, usage, flags, pImageFormatProperties);
    _post_call_vulkan_callback((void*) &ret, "vkGetPhysicalDeviceImageFormatProperties", (GLADapiproc) glad_vkGetPhysicalDeviceImageFormatProperties, 7, physicalDevice, format, type, tiling, usage, flags, pImageFormatProperties);
    return ret;
}
PFN_vkGetPhysicalDeviceImageFormatProperties glad_debug_vkGetPhysicalDeviceImageFormatProperties = glad_debug_impl_vkGetPhysicalDeviceImageFormatProperties;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkGetPhysicalDeviceImageFormatProperties2(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceImageFormatInfo2 * pImageFormatInfo, VkImageFormatProperties2 * pImageFormatProperties) {
    glad_vkGetPhysicalDeviceImageFormatProperties2 = (PFN_vkGetPhysicalDeviceImageFormatProperties2) glad_vk_on_demand_loader("vkGetPhysicalDeviceImageFormatProperties2");
    return glad_vkGetPhysicalDeviceImageFormatProperties2(physicalDevice, pImageFormatInfo, pImageFormatProperties);
}
PFN_vkGetPhysicalDeviceImageFormatProperties2 glad_vkGetPhysicalDeviceImageFormatProperties2 = glad_on_demand_impl_vkGetPhysicalDeviceImageFormatProperties2;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceImageFormatProperties2(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceImageFormatInfo2 * pImageFormatInfo, VkImageFormatProperties2 * pImageFormatProperties) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetPhysicalDeviceImageFormatProperties2", (GLADapiproc) glad_vkGetPhysicalDeviceImageFormatProperties2, 3, physicalDevice, pImageFormatInfo, pImageFormatProperties);
    ret = glad_vkGetPhysicalDeviceImageFormatProperties2(physicalDevice, pImageFormatInfo, pImageFormatProperties);
    _post_call_vulkan_callback((void*) &ret, "vkGetPhysicalDeviceImageFormatProperties2", (GLADapiproc) glad_vkGetPhysicalDeviceImageFormatProperties2, 3, physicalDevice, pImageFormatInfo, pImageFormatProperties);
    return ret;
}
PFN_vkGetPhysicalDeviceImageFormatProperties2 glad_debug_vkGetPhysicalDeviceImageFormatProperties2 = glad_debug_impl_vkGetPhysicalDeviceImageFormatProperties2;
static void GLAD_API_PTR glad_on_demand_impl_vkGetPhysicalDeviceMemoryProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties * pMemoryProperties) {
    glad_vkGetPhysicalDeviceMemoryProperties = (PFN_vkGetPhysicalDeviceMemoryProperties) glad_vk_on_demand_loader("vkGetPhysicalDeviceMemoryProperties");
    glad_vkGetPhysicalDeviceMemoryProperties(physicalDevice, pMemoryProperties);
}
PFN_vkGetPhysicalDeviceMemoryProperties glad_vkGetPhysicalDeviceMemoryProperties = glad_on_demand_impl_vkGetPhysicalDeviceMemoryProperties;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceMemoryProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties * pMemoryProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceMemoryProperties", (GLADapiproc) glad_vkGetPhysicalDeviceMemoryProperties, 2, physicalDevice, pMemoryProperties);
    glad_vkGetPhysicalDeviceMemoryProperties(physicalDevice, pMemoryProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceMemoryProperties", (GLADapiproc) glad_vkGetPhysicalDeviceMemoryProperties, 2, physicalDevice, pMemoryProperties);
    
}
PFN_vkGetPhysicalDeviceMemoryProperties glad_debug_vkGetPhysicalDeviceMemoryProperties = glad_debug_impl_vkGetPhysicalDeviceMemoryProperties;
static void GLAD_API_PTR glad_on_demand_impl_vkGetPhysicalDeviceMemoryProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties2 * pMemoryProperties) {
    glad_vkGetPhysicalDeviceMemoryProperties2 = (PFN_vkGetPhysicalDeviceMemoryProperties2) glad_vk_on_demand_loader("vkGetPhysicalDeviceMemoryProperties2");
    glad_vkGetPhysicalDeviceMemoryProperties2(physicalDevice, pMemoryProperties);
}
PFN_vkGetPhysicalDeviceMemoryProperties2 glad_vkGetPhysicalDeviceMemoryProperties2 = glad_on_demand_impl_vkGetPhysicalDeviceMemoryProperties2;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceMemoryProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties2 * pMemoryProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceMemoryProperties2", (GLADapiproc) glad_vkGetPhysicalDeviceMemoryProperties2, 2, physicalDevice, pMemoryProperties);
    glad_vkGetPhysicalDeviceMemoryProperties2(physicalDevice, pMemoryProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceMemoryProperties2", (GLADapiproc) glad_vkGetPhysicalDeviceMemoryProperties2, 2, physicalDevice, pMemoryProperties);
    
}
PFN_vkGetPhysicalDeviceMemoryProperties2 glad_debug_vkGetPhysicalDeviceMemoryProperties2 = glad_debug_impl_vkGetPhysicalDeviceMemoryProperties2;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkGetPhysicalDevicePresentRectanglesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t * pRectCount, VkRect2D * pRects) {
    glad_vkGetPhysicalDevicePresentRectanglesKHR = (PFN_vkGetPhysicalDevicePresentRectanglesKHR) glad_vk_on_demand_loader("vkGetPhysicalDevicePresentRectanglesKHR");
    return glad_vkGetPhysicalDevicePresentRectanglesKHR(physicalDevice, surface, pRectCount, pRects);
}
PFN_vkGetPhysicalDevicePresentRectanglesKHR glad_vkGetPhysicalDevicePresentRectanglesKHR = glad_on_demand_impl_vkGetPhysicalDevicePresentRectanglesKHR;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetPhysicalDevicePresentRectanglesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t * pRectCount, VkRect2D * pRects) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetPhysicalDevicePresentRectanglesKHR", (GLADapiproc) glad_vkGetPhysicalDevicePresentRectanglesKHR, 4, physicalDevice, surface, pRectCount, pRects);
    ret = glad_vkGetPhysicalDevicePresentRectanglesKHR(physicalDevice, surface, pRectCount, pRects);
    _post_call_vulkan_callback((void*) &ret, "vkGetPhysicalDevicePresentRectanglesKHR", (GLADapiproc) glad_vkGetPhysicalDevicePresentRectanglesKHR, 4, physicalDevice, surface, pRectCount, pRects);
    return ret;
}
PFN_vkGetPhysicalDevicePresentRectanglesKHR glad_debug_vkGetPhysicalDevicePresentRectanglesKHR = glad_debug_impl_vkGetPhysicalDevicePresentRectanglesKHR;
static void GLAD_API_PTR glad_on_demand_impl_vkGetPhysicalDeviceProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties * pProperties) {
    glad_vkGetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties) glad_vk_on_demand_loader("vkGetPhysicalDeviceProperties");
    glad_vkGetPhysicalDeviceProperties(physicalDevice, pProperties);
}
PFN_vkGetPhysicalDeviceProperties glad_vkGetPhysicalDeviceProperties = glad_on_demand_impl_vkGetPhysicalDeviceProperties;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties * pProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceProperties", (GLADapiproc) glad_vkGetPhysicalDeviceProperties, 2, physicalDevice, pProperties);
    glad_vkGetPhysicalDeviceProperties(physicalDevice, pProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceProperties", (GLADapiproc) glad_vkGetPhysicalDeviceProperties, 2, physicalDevice, pProperties);
    
}
PFN_vkGetPhysicalDeviceProperties glad_debug_vkGetPhysicalDeviceProperties = glad_debug_impl_vkGetPhysicalDeviceProperties;
static void GLAD_API_PTR glad_on_demand_impl_vkGetPhysicalDeviceProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2 * pProperties) {
    glad_vkGetPhysicalDeviceProperties2 = (PFN_vkGetPhysicalDeviceProperties2) glad_vk_on_demand_loader("vkGetPhysicalDeviceProperties2");
    glad_vkGetPhysicalDeviceProperties2(physicalDevice, pProperties);
}
PFN_vkGetPhysicalDeviceProperties2 glad_vkGetPhysicalDeviceProperties2 = glad_on_demand_impl_vkGetPhysicalDeviceProperties2;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2 * pProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceProperties2", (GLADapiproc) glad_vkGetPhysicalDeviceProperties2, 2, physicalDevice, pProperties);
    glad_vkGetPhysicalDeviceProperties2(physicalDevice, pProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceProperties2", (GLADapiproc) glad_vkGetPhysicalDeviceProperties2, 2, physicalDevice, pProperties);
    
}
PFN_vkGetPhysicalDeviceProperties2 glad_debug_vkGetPhysicalDeviceProperties2 = glad_debug_impl_vkGetPhysicalDeviceProperties2;
static void GLAD_API_PTR glad_on_demand_impl_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(VkPhysicalDevice physicalDevice, const VkQueryPoolPerformanceCreateInfoKHR * pPerformanceQueryCreateInfo, uint32_t * pNumPasses) {
    glad_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR = (PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR) glad_vk_on_demand_loader("vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR");
    glad_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(physicalDevice, pPerformanceQueryCreateInfo, pNumPasses);
}
PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR glad_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR = glad_on_demand_impl_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(VkPhysicalDevice physicalDevice, const VkQueryPoolPerformanceCreateInfoKHR * pPerformanceQueryCreateInfo, uint32_t * pNumPasses) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR", (GLADapiproc) glad_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR, 3, physicalDevice, pPerformanceQueryCreateInfo, pNumPasses);
    glad_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(physicalDevice, pPerformanceQueryCreateInfo, pNumPasses);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR", (GLADapiproc) glad_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR, 3, physicalDevice, pPerformanceQueryCreateInfo, pNumPasses);
    
}
PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR glad_debug_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR = glad_debug_impl_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR;
static void GLAD_API_PTR glad_on_demand_impl_vkGetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice, uint32_t * pQueueFamilyPropertyCount, VkQueueFamilyProperties * pQueueFamilyProperties) {
    glad_vkGetPhysicalDeviceQueueFamilyProperties = (PFN_vkGetPhysicalDeviceQueueFamilyProperties) glad_vk_on_demand_loader("vkGetPhysicalDeviceQueueFamilyProperties");
    glad_vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
}
PFN_vkGetPhysicalDeviceQueueFamilyProperties glad_vkGetPhysicalDeviceQueueFamilyProperties = glad_on_demand_impl_vkGetPhysicalDeviceQueueFamilyProperties;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice, uint32_t * pQueueFamilyPropertyCount, VkQueueFamilyProperties * pQueueFamilyProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceQueueFamilyProperties", (GLADapiproc) glad_vkGetPhysicalDeviceQueueFamilyProperties, 3, physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
    glad_vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceQueueFamilyProperties", (GLADapiproc) glad_vkGetPhysicalDeviceQueueFamilyProperties, 3, physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
    
}
PFN_vkGetPhysicalDeviceQueueFamilyProperties glad_debug_vkGetPhysicalDeviceQueueFamilyProperties = glad_debug_impl_vkGetPhysicalDeviceQueueFamilyProperties;
static void GLAD_API_PTR glad_on_demand_impl_vkGetPhysicalDeviceQueueFamilyProperties2(VkPhysicalDevice physicalDevice, uint32_t * pQueueFamilyPropertyCount, VkQueueFamilyProperties2 * pQueueFamilyProperties) {
    glad_vkGetPhysicalDeviceQueueFamilyProperties2 = (PFN_vkGetPhysicalDeviceQueueFamilyProperties2) glad_vk_on_demand_loader("vkGetPhysicalDeviceQueueFamilyProperties2");
    glad_vkGetPhysicalDeviceQueueFamilyProperties2(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
}
PFN_vkGetPhysicalDeviceQueueFamilyProperties2 glad_vkGetPhysicalDeviceQueueFamilyProperties2 = glad_on_demand_impl_vkGetPhysicalDeviceQueueFamilyProperties2;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceQueueFamilyProperties2(VkPhysicalDevice physicalDevice, uint32_t * pQueueFamilyPropertyCount, VkQueueFamilyProperties2 * pQueueFamilyProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceQueueFamilyProperties2", (GLADapiproc) glad_vkGetPhysicalDeviceQueueFamilyProperties2, 3, physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
    glad_vkGetPhysicalDeviceQueueFamilyProperties2(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceQueueFamilyProperties2", (GLADapiproc) glad_vkGetPhysicalDeviceQueueFamilyProperties2, 3, physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
    
}
PFN_vkGetPhysicalDeviceQueueFamilyProperties2 glad_debug_vkGetPhysicalDeviceQueueFamilyProperties2 = glad_debug_impl_vkGetPhysicalDeviceQueueFamilyProperties2;
static void GLAD_API_PTR glad_on_demand_impl_vkGetPhysicalDeviceSparseImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkSampleCountFlagBits samples, VkImageUsageFlags usage, VkImageTiling tiling, uint32_t * pPropertyCount, VkSparseImageFormatProperties * pProperties) {
    glad_vkGetPhysicalDeviceSparseImageFormatProperties = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties) glad_vk_on_demand_loader("vkGetPhysicalDeviceSparseImageFormatProperties");
    glad_vkGetPhysicalDeviceSparseImageFormatProperties(physicalDevice, format, type, samples, usage, tiling, pPropertyCount, pProperties);
}
PFN_vkGetPhysicalDeviceSparseImageFormatProperties glad_vkGetPhysicalDeviceSparseImageFormatProperties = glad_on_demand_impl_vkGetPhysicalDeviceSparseImageFormatProperties;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceSparseImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkSampleCountFlagBits samples, VkImageUsageFlags usage, VkImageTiling tiling, uint32_t * pPropertyCount, VkSparseImageFormatProperties * pProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceSparseImageFormatProperties", (GLADapiproc) glad_vkGetPhysicalDeviceSparseImageFormatProperties, 8, physicalDevice, format, type, samples, usage, tiling, pPropertyCount, pProperties);
    glad_vkGetPhysicalDeviceSparseImageFormatProperties(physicalDevice, format, type, samples, usage, tiling, pPropertyCount, pProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceSparseImageFormatProperties", (GLADapiproc) glad_vkGetPhysicalDeviceSparseImageFormatProperties, 8, physicalDevice, format, type, samples, usage, tiling, pPropertyCount, pProperties);
    
}
PFN_vkGetPhysicalDeviceSparseImageFormatProperties glad_debug_vkGetPhysicalDeviceSparseImageFormatProperties = glad_debug_impl_vkGetPhysicalDeviceSparseImageFormatProperties;
static void GLAD_API_PTR glad_on_demand_impl_vkGetPhysicalDeviceSparseImageFormatProperties2(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSparseImageFormatInfo2 * pFormatInfo, uint32_t * pPropertyCount, VkSparseImageFormatProperties2 * pProperties) {
    glad_vkGetPhysicalDeviceSparseImageFormatProperties2 = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties2) glad_vk_on_demand_loader("vkGetPhysicalDeviceSparseImageFormatProperties2");
    glad_vkGetPhysicalDeviceSparseImageFormatProperties2(physicalDevice, pFormatInfo, pPropertyCount, pProperties);
}
PFN_vkGetPhysicalDeviceSparseImageFormatProperties2 glad_vkGetPhysicalDeviceSparseImageFormatProperties2 = glad_on_demand_impl_vkGetPhysicalDeviceSparseImageFormatProperties2;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceSparseImageFormatProperties2(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSparseImageFormatInfo2 * pFormatInfo, uint32_t * pPropertyCount, VkSparseImageFormatProperties2 * pProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceSparseImageFormatProperties2", (GLADapiproc) glad_vkGetPhysicalDeviceSparseImageFormatProperties2, 4, physicalDevice, pFormatInfo, pPropertyCount, pProperties);
    glad_vkGetPhysicalDeviceSparseImageFormatProperties2(physicalDevice, pFormatInfo, pPropertyCount, pProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceSparseImageFormatProperties2", (GLADapiproc) glad_vkGetPhysicalDeviceSparseImageFormatProperties2, 4, physicalDevice, pFormatInfo, pPropertyCount, pProperties);
    
}
PFN_vkGetPhysicalDeviceSparseImageFormatProperties2 glad_debug_vkGetPhysicalDeviceSparseImageFormatProperties2 = glad_debug_impl_vkGetPhysicalDeviceSparseImageFormatProperties2;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkGetPhysicalDeviceSurfaceCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilitiesKHR * pSurfaceCapabilities) {
    glad_vkGetPhysicalDeviceSurfaceCapabilitiesKHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR) glad_vk_on_demand_loader("vkGetPhysicalDeviceSurfaceCapabilitiesKHR");
    return glad_vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, pSurfaceCapabilities);
}
PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR glad_vkGetPhysicalDeviceSurfaceCapabilitiesKHR = glad_on_demand_impl_vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceSurfaceCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilitiesKHR * pSurfaceCapabilities) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetPhysicalDeviceSurfaceCapabilitiesKHR", (GLADapiproc) glad_vkGetPhysicalDeviceSurfaceCapabilitiesKHR, 3, physicalDevice, surface, pSurfaceCapabilities);
    ret = glad_vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, pSurfaceCapabilities);
    _post_call_vulkan_callback((void*) &ret, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR", (GLADapiproc) glad_vkGetPhysicalDeviceSurfaceCapabilitiesKHR, 3, physicalDevice, surface, pSurfaceCapabilities);
    return ret;
}
PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR glad_debug_vkGetPhysicalDeviceSurfaceCapabilitiesKHR = glad_debug_impl_vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkGetPhysicalDeviceSurfaceFormatsKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t * pSurfaceFormatCount, VkSurfaceFormatKHR * pSurfaceFormats) {
    glad_vkGetPhysicalDeviceSurfaceFormatsKHR = (PFN_vkGetPhysicalDeviceSurfaceFormatsKHR) glad_vk_on_demand_loader("vkGetPhysicalDeviceSurfaceFormatsKHR");
    return glad_vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, pSurfaceFormatCount, pSurfaceFormats);
}
PFN_vkGetPhysicalDeviceSurfaceFormatsKHR glad_vkGetPhysicalDeviceSurfaceFormatsKHR = glad_on_demand_impl_vkGetPhysicalDeviceSurfaceFormatsKHR;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceSurfaceFormatsKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t * pSurfaceFormatCount, VkSurfaceFormatKHR * pSurfaceFormats) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetPhysicalDeviceSurfaceFormatsKHR", (GLADapiproc) glad_vkGetPhysicalDeviceSurfaceFormatsKHR, 4, physicalDevice, surface, pSurfaceFormatCount, pSurfaceFormats);
    ret = glad_vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, pSurfaceFormatCount, pSurfaceFormats);
    _post_call_vulkan_callback((void*) &ret, "vkGetPhysicalDeviceSurfaceFormatsKHR", (GLADapiproc) glad_vkGetPhysicalDeviceSurfaceFormatsKHR, 4, physicalDevice, surface, pSurfaceFormatCount, pSurfaceFormats);
    return ret;
}
PFN_vkGetPhysicalDeviceSurfaceFormatsKHR glad_debug_vkGetPhysicalDeviceSurfaceFormatsKHR = glad_debug_impl_vkGetPhysicalDeviceSurfaceFormatsKHR;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkGetPhysicalDeviceSurfacePresentModesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t * pPresentModeCount, VkPresentModeKHR * pPresentModes) {
    glad_vkGetPhysicalDeviceSurfacePresentModesKHR = (PFN_vkGetPhysicalDeviceSurfacePresentModesKHR) glad_vk_on_demand_loader("vkGetPhysicalDeviceSurfacePresentModesKHR");
    return glad_vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, pPresentModeCount, pPresentModes);
}
PFN_vkGetPhysicalDeviceSurfacePresentModesKHR glad_vkGetPhysicalDeviceSurfacePresentModesKHR = glad_on_demand_impl_vkGetPhysicalDeviceSurfacePresentModesKHR;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceSurfacePresentModesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t * pPresentModeCount, VkPresentModeKHR * pPresentModes) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetPhysicalDeviceSurfacePresentModesKHR", (GLADapiproc) glad_vkGetPhysicalDeviceSurfacePresentModesKHR, 4, physicalDevice, surface, pPresentModeCount, pPresentModes);
    ret = glad_vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, pPresentModeCount, pPresentModes);
    _post_call_vulkan_callback((void*) &ret, "vkGetPhysicalDeviceSurfacePresentModesKHR", (GLADapiproc) glad_vkGetPhysicalDeviceSurfacePresentModesKHR, 4, physicalDevice, surface, pPresentModeCount, pPresentModes);
    return ret;
}
PFN_vkGetPhysicalDeviceSurfacePresentModesKHR glad_debug_vkGetPhysicalDeviceSurfacePresentModesKHR = glad_debug_impl_vkGetPhysicalDeviceSurfacePresentModesKHR;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkGetPhysicalDeviceSurfaceSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, VkSurfaceKHR surface, VkBool32 * pSupported) {
    glad_vkGetPhysicalDeviceSurfaceSupportKHR = (PFN_vkGetPhysicalDeviceSurfaceSupportKHR) glad_vk_on_demand_loader("vkGetPhysicalDeviceSurfaceSupportKHR");
    return glad_vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queueFamilyIndex, surface, pSupported);
}
PFN_vkGetPhysicalDeviceSurfaceSupportKHR glad_vkGetPhysicalDeviceSurfaceSupportKHR = glad_on_demand_impl_vkGetPhysicalDeviceSurfaceSupportKHR;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceSurfaceSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, VkSurfaceKHR surface, VkBool32 * pSupported) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetPhysicalDeviceSurfaceSupportKHR", (GLADapiproc) glad_vkGetPhysicalDeviceSurfaceSupportKHR, 4, physicalDevice, queueFamilyIndex, surface, pSupported);
    ret = glad_vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queueFamilyIndex, surface, pSupported);
    _post_call_vulkan_callback((void*) &ret, "vkGetPhysicalDeviceSurfaceSupportKHR", (GLADapiproc) glad_vkGetPhysicalDeviceSurfaceSupportKHR, 4, physicalDevice, queueFamilyIndex, surface, pSupported);
    return ret;
}
PFN_vkGetPhysicalDeviceSurfaceSupportKHR glad_debug_vkGetPhysicalDeviceSurfaceSupportKHR = glad_debug_impl_vkGetPhysicalDeviceSurfaceSupportKHR;
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
static VkBool32 GLAD_API_PTR glad_on_demand_impl_vkGetPhysicalDeviceWaylandPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, struct wl_display * display) {
    glad_vkGetPhysicalDeviceWaylandPresentationSupportKHR = (PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR) glad_vk_on_demand_loader("vkGetPhysicalDeviceWaylandPresentationSupportKHR");
    return glad_vkGetPhysicalDeviceWaylandPresentationSupportKHR(physicalDevice, queueFamilyIndex, display);
}
PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR glad_vkGetPhysicalDeviceWaylandPresentationSupportKHR = glad_on_demand_impl_vkGetPhysicalDeviceWaylandPresentationSupportKHR;
static VkBool32 GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceWaylandPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, struct wl_display * display) {
    VkBool32 ret;
    _pre_call_vulkan_callback("vkGetPhysicalDeviceWaylandPresentationSupportKHR", (GLADapiproc) glad_vkGetPhysicalDeviceWaylandPresentationSupportKHR, 3, physicalDevice, queueFamilyIndex, display);
    ret = glad_vkGetPhysicalDeviceWaylandPresentationSupportKHR(physicalDevice, queueFamilyIndex, display);
    _post_call_vulkan_callback((void*) &ret, "vkGetPhysicalDeviceWaylandPresentationSupportKHR", (GLADapiproc) glad_vkGetPhysicalDeviceWaylandPresentationSupportKHR, 3, physicalDevice, queueFamilyIndex, display);
    return ret;
}
PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR glad_debug_vkGetPhysicalDeviceWaylandPresentationSupportKHR = glad_debug_impl_vkGetPhysicalDeviceWaylandPresentationSupportKHR;
#endif
#if defined(VK_USE_PLATFORM_WIN32_KHR)
static VkBool32 GLAD_API_PTR glad_on_demand_impl_vkGetPhysicalDeviceWin32PresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex) {
    glad_vkGetPhysicalDeviceWin32PresentationSupportKHR = (PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR) glad_vk_on_demand_loader("vkGetPhysicalDeviceWin32PresentationSupportKHR");
    return glad_vkGetPhysicalDeviceWin32PresentationSupportKHR(physicalDevice, queueFamilyIndex);
}
PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR glad_vkGetPhysicalDeviceWin32PresentationSupportKHR = glad_on_demand_impl_vkGetPhysicalDeviceWin32PresentationSupportKHR;
static VkBool32 GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceWin32PresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex) {
    VkBool32 ret;
    _pre_call_vulkan_callback("vkGetPhysicalDeviceWin32PresentationSupportKHR", (GLADapiproc) glad_vkGetPhysicalDeviceWin32PresentationSupportKHR, 2, physicalDevice, queueFamilyIndex);
    ret = glad_vkGetPhysicalDeviceWin32PresentationSupportKHR(physicalDevice, queueFamilyIndex);
    _post_call_vulkan_callback((void*) &ret, "vkGetPhysicalDeviceWin32PresentationSupportKHR", (GLADapiproc) glad_vkGetPhysicalDeviceWin32PresentationSupportKHR, 2, physicalDevice, queueFamilyIndex);
    return ret;
}
PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR glad_debug_vkGetPhysicalDeviceWin32PresentationSupportKHR = glad_debug_impl_vkGetPhysicalDeviceWin32PresentationSupportKHR;
#endif
#if defined(VK_USE_PLATFORM_XCB_KHR)
static VkBool32 GLAD_API_PTR glad_on_demand_impl_vkGetPhysicalDeviceXcbPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, xcb_connection_t * connection, xcb_visualid_t visual_id) {
    glad_vkGetPhysicalDeviceXcbPresentationSupportKHR = (PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR) glad_vk_on_demand_loader("vkGetPhysicalDeviceXcbPresentationSupportKHR");
    return glad_vkGetPhysicalDeviceXcbPresentationSupportKHR(physicalDevice, queueFamilyIndex, connection, visual_id);
}
PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR glad_vkGetPhysicalDeviceXcbPresentationSupportKHR = glad_on_demand_impl_vkGetPhysicalDeviceXcbPresentationSupportKHR;
static VkBool32 GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceXcbPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, xcb_connection_t * connection, xcb_visualid_t visual_id) {
    VkBool32 ret;
    _pre_call_vulkan_callback("vkGetPhysicalDeviceXcbPresentationSupportKHR", (GLADapiproc) glad_vkGetPhysicalDeviceXcbPresentationSupportKHR, 4, physicalDevice, queueFamilyIndex, connection, visual_id);
    ret = glad_vkGetPhysicalDeviceXcbPresentationSupportKHR(physicalDevice, queueFamilyIndex, connection, visual_id);
    _post_call_vulkan_callback((void*) &ret, "vkGetPhysicalDeviceXcbPresentationSupportKHR", (GLADapiproc) glad_vkGetPhysicalDeviceXcbPresentationSupportKHR, 4, physicalDevice, queueFamilyIndex, connection, visual_id);
    return ret;
}
PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR glad_debug_vkGetPhysicalDeviceXcbPresentationSupportKHR = glad_debug_impl_vkGetPhysicalDeviceXcbPresentationSupportKHR;
#endif
#if defined(VK_USE_PLATFORM_XLIB_KHR)
static VkBool32 GLAD_API_PTR glad_on_demand_impl_vkGetPhysicalDeviceXlibPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, Display * dpy, VisualID visualID) {
    glad_vkGetPhysicalDeviceXlibPresentationSupportKHR = (PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR) glad_vk_on_demand_loader("vkGetPhysicalDeviceXlibPresentationSupportKHR");
    return glad_vkGetPhysicalDeviceXlibPresentationSupportKHR(physicalDevice, queueFamilyIndex, dpy, visualID);
}
PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR glad_vkGetPhysicalDeviceXlibPresentationSupportKHR = glad_on_demand_impl_vkGetPhysicalDeviceXlibPresentationSupportKHR;
static VkBool32 GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceXlibPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, Display * dpy, VisualID visualID) {
    VkBool32 ret;
    _pre_call_vulkan_callback("vkGetPhysicalDeviceXlibPresentationSupportKHR", (GLADapiproc) glad_vkGetPhysicalDeviceXlibPresentationSupportKHR, 4, physicalDevice, queueFamilyIndex, dpy, visualID);
    ret = glad_vkGetPhysicalDeviceXlibPresentationSupportKHR(physicalDevice, queueFamilyIndex, dpy, visualID);
    _post_call_vulkan_callback((void*) &ret, "vkGetPhysicalDeviceXlibPresentationSupportKHR", (GLADapiproc) glad_vkGetPhysicalDeviceXlibPresentationSupportKHR, 4, physicalDevice, queueFamilyIndex, dpy, visualID);
    return ret;
}
PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR glad_debug_vkGetPhysicalDeviceXlibPresentationSupportKHR = glad_debug_impl_vkGetPhysicalDeviceXlibPresentationSupportKHR;
#endif
static VkResult GLAD_API_PTR glad_on_demand_impl_vkGetPipelineCacheData(VkDevice device, VkPipelineCache pipelineCache, size_t * pDataSize, void * pData) {
    glad_vkGetPipelineCacheData = (PFN_vkGetPipelineCacheData) glad_vk_on_demand_loader("vkGetPipelineCacheData");
    return glad_vkGetPipelineCacheData(device, pipelineCache, pDataSize, pData);
}
PFN_vkGetPipelineCacheData glad_vkGetPipelineCacheData = glad_on_demand_impl_vkGetPipelineCacheData;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetPipelineCacheData(VkDevice device, VkPipelineCache pipelineCache, size_t * pDataSize, void * pData) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetPipelineCacheData", (GLADapiproc) glad_vkGetPipelineCacheData, 4, device, pipelineCache, pDataSize, pData);
    ret = glad_vkGetPipelineCacheData(device, pipelineCache, pDataSize, pData);
    _post_call_vulkan_callback((void*) &ret, "vkGetPipelineCacheData", (GLADapiproc) glad_vkGetPipelineCacheData, 4, device, pipelineCache, pDataSize, pData);
    return ret;
}
PFN_vkGetPipelineCacheData glad_debug_vkGetPipelineCacheData = glad_debug_impl_vkGetPipelineCacheData;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkGetPipelineExecutableInternalRepresentationsKHR(VkDevice device, const VkPipelineExecutableInfoKHR * pExecutableInfo, uint32_t * pInternalRepresentationCount, VkPipelineExecutableInternalRepresentationKHR * pInternalRepresentations) {
    glad_vkGetPipelineExecutableInternalRepresentationsKHR = (PFN_vkGetPipelineExecutableInternalRepresentationsKHR) glad_vk_on_demand_loader("vkGetPipelineExecutableInternalRepresentationsKHR");
    return glad_vkGetPipelineExecutableInternalRepresentationsKHR(device, pExecutableInfo, pInternalRepresentationCount, pInternalRepresentations);
}
PFN_vkGetPipelineExecutableInternalRepresentationsKHR glad_vkGetPipelineExecutableInternalRepresentationsKHR = glad_on_demand_impl_vkGetPipelineExecutableInternalRepresentationsKHR;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetPipelineExecutableInternalRepresentationsKHR(VkDevice device, const VkPipelineExecutableInfoKHR * pExecutableInfo, uint32_t * pInternalRepresentationCount, VkPipelineExecutableInternalRepresentationKHR * pInternalRepresentations) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetPipelineExecutableInternalRepresentationsKHR", (GLADapiproc) glad_vkGetPipelineExecutableInternalRepresentationsKHR, 4, device, pExecutableInfo, pInternalRepresentationCount, pInternalRepresentations);
    ret = glad_vkGetPipelineExecutableInternalRepresentationsKHR(device, pExecutableInfo, pInternalRepresentationCount, pInternalRepresentations);
    _post_call_vulkan_callback((void*) &ret, "vkGetPipelineExecutableInternalRepresentationsKHR", (GLADapiproc) glad_vkGetPipelineExecutableInternalRepresentationsKHR, 4, device, pExecutableInfo, pInternalRepresentationCount, pInternalRepresentations);
    return ret;
}
PFN_vkGetPipelineExecutableInternalRepresentationsKHR glad_debug_vkGetPipelineExecutableInternalRepresentationsKHR = glad_debug_impl_vkGetPipelineExecutableInternalRepresentationsKHR;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkGetPipelineExecutablePropertiesKHR(VkDevice device, const VkPipelineInfoKHR * pPipelineInfo, uint32_t * pExecutableCount, VkPipelineExecutablePropertiesKHR * pProperties) {
    glad_vkGetPipelineExecutablePropertiesKHR = (PFN_vkGetPipelineExecutablePropertiesKHR) glad_vk_on_demand_loader("vkGetPipelineExecutablePropertiesKHR");
    return glad_vkGetPipelineExecutablePropertiesKHR(device, pPipelineInfo, pExecutableCount, pProperties);
}
PFN_vkGetPipelineExecutablePropertiesKHR glad_vkGetPipelineExecutablePropertiesKHR = glad_on_demand_impl_vkGetPipelineExecutablePropertiesKHR;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetPipelineExecutablePropertiesKHR(VkDevice device, const VkPipelineInfoKHR * pPipelineInfo, uint32_t * pExecutableCount, VkPipelineExecutablePropertiesKHR * pProperties) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetPipelineExecutablePropertiesKHR", (GLADapiproc) glad_vkGetPipelineExecutablePropertiesKHR, 4, device, pPipelineInfo, pExecutableCount, pProperties);
    ret = glad_vkGetPipelineExecutablePropertiesKHR(device, pPipelineInfo, pExecutableCount, pProperties);
    _post_call_vulkan_callback((void*) &ret, "vkGetPipelineExecutablePropertiesKHR", (GLADapiproc) glad_vkGetPipelineExecutablePropertiesKHR, 4, device, pPipelineInfo, pExecutableCount, pProperties);
    return ret;
}
PFN_vkGetPipelineExecutablePropertiesKHR glad_debug_vkGetPipelineExecutablePropertiesKHR = glad_debug_impl_vkGetPipelineExecutablePropertiesKHR;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkGetPipelineExecutableStatisticsKHR(VkDevice device, const VkPipelineExecutableInfoKHR * pExecutableInfo, uint32_t * pStatisticCount, VkPipelineExecutableStatisticKHR * pStatistics) {
    glad_vkGetPipelineExecutableStatisticsKHR = (PFN_vkGetPipelineExecutableStatisticsKHR) glad_vk_on_demand_loader("vkGetPipelineExecutableStatisticsKHR");
    return glad_vkGetPipelineExecutableStatisticsKHR(device, pExecutableInfo, pStatisticCount, pStatistics);
}
PFN_vkGetPipelineExecutableStatisticsKHR glad_vkGetPipelineExecutableStatisticsKHR = glad_on_demand_impl_vkGetPipelineExecutableStatisticsKHR;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetPipelineExecutableStatisticsKHR(VkDevice device, const VkPipelineExecutableInfoKHR * pExecutableInfo, uint32_t * pStatisticCount, VkPipelineExecutableStatisticKHR * pStatistics) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetPipelineExecutableStatisticsKHR", (GLADapiproc) glad_vkGetPipelineExecutableStatisticsKHR, 4, device, pExecutableInfo, pStatisticCount, pStatistics);
    ret = glad_vkGetPipelineExecutableStatisticsKHR(device, pExecutableInfo, pStatisticCount, pStatistics);
    _post_call_vulkan_callback((void*) &ret, "vkGetPipelineExecutableStatisticsKHR", (GLADapiproc) glad_vkGetPipelineExecutableStatisticsKHR, 4, device, pExecutableInfo, pStatisticCount, pStatistics);
    return ret;
}
PFN_vkGetPipelineExecutableStatisticsKHR glad_debug_vkGetPipelineExecutableStatisticsKHR = glad_debug_impl_vkGetPipelineExecutableStatisticsKHR;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkGetQueryPoolResults(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void * pData, VkDeviceSize stride, VkQueryResultFlags flags) {
    glad_vkGetQueryPoolResults = (PFN_vkGetQueryPoolResults) glad_vk_on_demand_loader("vkGetQueryPoolResults");
    return glad_vkGetQueryPoolResults(device, queryPool, firstQuery, queryCount, dataSize, pData, stride, flags);
}
PFN_vkGetQueryPoolResults glad_vkGetQueryPoolResults = glad_on_demand_impl_vkGetQueryPoolResults;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetQueryPoolResults(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void * pData, VkDeviceSize stride, VkQueryResultFlags flags) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetQueryPoolResults", (GLADapiproc) glad_vkGetQueryPoolResults, 8, device, queryPool, firstQuery, queryCount, dataSize, pData, stride, flags);
    ret = glad_vkGetQueryPoolResults(device, queryPool, firstQuery, queryCount, dataSize, pData, stride, flags);
    _post_call_vulkan_callback((void*) &ret, "vkGetQueryPoolResults", (GLADapiproc) glad_vkGetQueryPoolResults, 8, device, queryPool, firstQuery, queryCount, dataSize, pData, stride, flags);
    return ret;
}
PFN_vkGetQueryPoolResults glad_debug_vkGetQueryPoolResults = glad_debug_impl_vkGetQueryPoolResults;
static void GLAD_API_PTR glad_on_demand_impl_vkGetRenderAreaGranularity(VkDevice device, VkRenderPass renderPass, VkExtent2D * pGranularity) {
    glad_vkGetRenderAreaGranularity = (PFN_vkGetRenderAreaGranularity) glad_vk_on_demand_loader("vkGetRenderAreaGranularity");
    glad_vkGetRenderAreaGranularity(device, renderPass, pGranularity);
}
PFN_vkGetRenderAreaGranularity glad_vkGetRenderAreaGranularity = glad_on_demand_impl_vkGetRenderAreaGranularity;
static void GLAD_API_PTR glad_debug_impl_vkGetRenderAreaGranularity(VkDevice device, VkRenderPass renderPass, VkExtent2D * pGranularity) {
    _pre_call_vulkan_callback("vkGetRenderAreaGranularity", (GLADapiproc) glad_vkGetRenderAreaGranularity, 3, device, renderPass, pGranularity);
    glad_vkGetRenderAreaGranularity(device, renderPass, pGranularity);
    _post_call_vulkan_callback(NULL, "vkGetRenderAreaGranularity", (GLADapiproc) glad_vkGetRenderAreaGranularity, 3, device, renderPass, pGranularity);
    
}
PFN_vkGetRenderAreaGranularity glad_debug_vkGetRenderAreaGranularity = glad_debug_impl_vkGetRenderAreaGranularity;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkGetSemaphoreCounterValue(VkDevice device, VkSemaphore semaphore, uint64_t * pValue) {
    glad_vkGetSemaphoreCounterValue = (PFN_vkGetSemaphoreCounterValue) glad_vk_on_demand_loader("vkGetSemaphoreCounterValue");
    return glad_vkGetSemaphoreCounterValue(device, semaphore, pValue);
}
PFN_vkGetSemaphoreCounterValue glad_vkGetSemaphoreCounterValue = glad_on_demand_impl_vkGetSemaphoreCounterValue;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetSemaphoreCounterValue(VkDevice device, VkSemaphore semaphore, uint64_t * pValue) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetSemaphoreCounterValue", (GLADapiproc) glad_vkGetSemaphoreCounterValue, 3, device, semaphore, pValue);
    ret = glad_vkGetSemaphoreCounterValue(device, semaphore, pValue);
    _post_call_vulkan_callback((void*) &ret, "vkGetSemaphoreCounterValue", (GLADapiproc) glad_vkGetSemaphoreCounterValue, 3, device, semaphore, pValue);
    return ret;
}
PFN_vkGetSemaphoreCounterValue glad_debug_vkGetSemaphoreCounterValue = glad_debug_impl_vkGetSemaphoreCounterValue;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkGetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain, uint32_t * pSwapchainImageCount, VkImage * pSwapchainImages) {
    glad_vkGetSwapchainImagesKHR = (PFN_vkGetSwapchainImagesKHR) glad_vk_on_demand_loader("vkGetSwapchainImagesKHR");
    return glad_vkGetSwapchainImagesKHR(device, swapchain, pSwapchainImageCount, pSwapchainImages);
}
PFN_vkGetSwapchainImagesKHR glad_vkGetSwapchainImagesKHR = glad_on_demand_impl_vkGetSwapchainImagesKHR;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain, uint32_t * pSwapchainImageCount, VkImage * pSwapchainImages) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetSwapchainImagesKHR", (GLADapiproc) glad_vkGetSwapchainImagesKHR, 4, device, swapchain, pSwapchainImageCount, pSwapchainImages);
    ret = glad_vkGetSwapchainImagesKHR(device, swapchain, pSwapchainImageCount, pSwapchainImages);
    _post_call_vulkan_callback((void*) &ret, "vkGetSwapchainImagesKHR", (GLADapiproc) glad_vkGetSwapchainImagesKHR, 4, device, swapchain, pSwapchainImageCount, pSwapchainImages);
    return ret;
}
PFN_vkGetSwapchainImagesKHR glad_debug_vkGetSwapchainImagesKHR = glad_debug_impl_vkGetSwapchainImagesKHR;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkGetSwapchainStatusKHR(VkDevice device, VkSwapchainKHR swapchain) {
    glad_vkGetSwapchainStatusKHR = (PFN_vkGetSwapchainStatusKHR) glad_vk_on_demand_loader("vkGetSwapchainStatusKHR");
    return glad_vkGetSwapchainStatusKHR(device, swapchain);
}
PFN_vkGetSwapchainStatusKHR glad_vkGetSwapchainStatusKHR = glad_on_demand_impl_vkGetSwapchainStatusKHR;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetSwapchainStatusKHR(VkDevice device, VkSwapchainKHR swapchain) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetSwapchainStatusKHR", (GLADapiproc) glad_vkGetSwapchainStatusKHR, 2, device, swapchain);
    ret = glad_vkGetSwapchainStatusKHR(device, swapchain);
    _post_call_vulkan_callback((void*) &ret, "vkGetSwapchainStatusKHR", (GLADapiproc) glad_vkGetSwapchainStatusKHR, 2, device, swapchain);
    return ret;
}
PFN_vkGetSwapchainStatusKHR glad_debug_vkGetSwapchainStatusKHR = glad_debug_impl_vkGetSwapchainStatusKHR;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkInvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange * pMemoryRanges) {
    glad_vkInvalidateMappedMemoryRanges = (PFN_vkInvalidateMappedMemoryRanges) glad_vk_on_demand_loader("vkInvalidateMappedMemoryRanges");
    return glad_vkInvalidateMappedMemoryRanges(device, memoryRangeCount, pMemoryRanges);
}
PFN_vkInvalidateMappedMemoryRanges glad_vkInvalidateMappedMemoryRanges = glad_on_demand_impl_vkInvalidateMappedMemoryRanges;
static VkResult GLAD_API_PTR glad_debug_impl_vkInvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange * pMemoryRanges) {
    VkResult ret;
    _pre_call_vulkan_callback("vkInvalidateMappedMemoryRanges", (GLADapiproc) glad_vkInvalidateMappedMemoryRanges, 3, device, memoryRangeCount, pMemoryRanges);
    ret = glad_vkInvalidateMappedMemoryRanges(device, memoryRangeCount, pMemoryRanges);
    _post_call_vulkan_callback((void*) &ret, "vkInvalidateMappedMemoryRanges", (GLADapiproc) glad_vkInvalidateMappedMemoryRanges, 3, device, memoryRangeCount, pMemoryRanges);
    return ret;
}
PFN_vkInvalidateMappedMemoryRanges glad_debug_vkInvalidateMappedMemoryRanges = glad_debug_impl_vkInvalidateMappedMemoryRanges;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkMapMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void ** ppData) {
    glad_vkMapMemory = (PFN_vkMapMemory) glad_vk_on_demand_loader("vkMapMemory");
    return glad_vkMapMemory(device, memory, offset, size, flags, ppData);
}
PFN_vkMapMemory glad_vkMapMemory = glad_on_demand_impl_vkMapMemory;
static VkResult GLAD_API_PTR glad_debug_impl_vkMapMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void ** ppData) {
    VkResult ret;
    _pre_call_vulkan_callback("vkMapMemory", (GLADapiproc) glad_vkMapMemory, 6, device, memory, offset, size, flags, ppData);
    ret = glad_vkMapMemory(device, memory, offset, size, flags, ppData);
    _post_call_vulkan_callback((void*) &ret, "vkMapMemory", (GLADapiproc) glad_vkMapMemory, 6, device, memory, offset, size, flags, ppData);
    return ret;
}
PFN_vkMapMemory glad_debug_vkMapMemory = glad_debug_impl_vkMapMemory;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkMergePipelineCaches(VkDevice device, VkPipelineCache dstCache, uint32_t srcCacheCount, const VkPipelineCache * pSrcCaches) {
    glad_vkMergePipelineCaches = (PFN_vkMergePipelineCaches) glad_vk_on_demand_loader("vkMergePipelineCaches");
    return glad_vkMergePipelineCaches(device, dstCache, srcCacheCount, pSrcCaches);
}
PFN_vkMergePipelineCaches glad_vkMergePipelineCaches = glad_on_demand_impl_vkMergePipelineCaches;
static VkResult GLAD_API_PTR glad_debug_impl_vkMergePipelineCaches(VkDevice device, VkPipelineCache dstCache, uint32_t srcCacheCount, const VkPipelineCache * pSrcCaches) {
    VkResult ret;
    _pre_call_vulkan_callback("vkMergePipelineCaches", (GLADapiproc) glad_vkMergePipelineCaches, 4, device, dstCache, srcCacheCount, pSrcCaches);
    ret = glad_vkMergePipelineCaches(device, dstCache, srcCacheCount, pSrcCaches);
    _post_call_vulkan_callback((void*) &ret, "vkMergePipelineCaches", (GLADapiproc) glad_vkMergePipelineCaches, 4, device, dstCache, srcCacheCount, pSrcCaches);
    return ret;
}
PFN_vkMergePipelineCaches glad_debug_vkMergePipelineCaches = glad_debug_impl_vkMergePipelineCaches;
static void GLAD_API_PTR glad_on_demand_impl_vkQueueBeginDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT * pLabelInfo) {
    glad_vkQueueBeginDebugUtilsLabelEXT = (PFN_vkQueueBeginDebugUtilsLabelEXT) glad_vk_on_demand_loader("vkQueueBeginDebugUtilsLabelEXT");
    glad_vkQueueBeginDebugUtilsLabelEXT(queue, pLabelInfo);
}
PFN_vkQueueBeginDebugUtilsLabelEXT glad_vkQueueBeginDebugUtilsLabelEXT = glad_on_demand_impl_vkQueueBeginDebugUtilsLabelEXT;
static void GLAD_API_PTR glad_debug_impl_vkQueueBeginDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT * pLabelInfo) {
    _pre_call_vulkan_callback("vkQueueBeginDebugUtilsLabelEXT", (GLADapiproc) glad_vkQueueBeginDebugUtilsLabelEXT, 2, queue, pLabelInfo);
    glad_vkQueueBeginDebugUtilsLabelEXT(queue, pLabelInfo);
    _post_call_vulkan_callback(NULL, "vkQueueBeginDebugUtilsLabelEXT", (GLADapiproc) glad_vkQueueBeginDebugUtilsLabelEXT, 2, queue, pLabelInfo);
    
}
PFN_vkQueueBeginDebugUtilsLabelEXT glad_debug_vkQueueBeginDebugUtilsLabelEXT = glad_debug_impl_vkQueueBeginDebugUtilsLabelEXT;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkQueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const VkBindSparseInfo * pBindInfo, VkFence fence) {
    glad_vkQueueBindSparse = (PFN_vkQueueBindSparse) glad_vk_on_demand_loader("vkQueueBindSparse");
    return glad_vkQueueBindSparse(queue, bindInfoCount, pBindInfo, fence);
}
PFN_vkQueueBindSparse glad_vkQueueBindSparse = glad_on_demand_impl_vkQueueBindSparse;
static VkResult GLAD_API_PTR glad_debug_impl_vkQueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const VkBindSparseInfo * pBindInfo, VkFence fence) {
    VkResult ret;
    _pre_call_vulkan_callback("vkQueueBindSparse", (GLADapiproc) glad_vkQueueBindSparse, 4, queue, bindInfoCount, pBindInfo, fence);
    ret = glad_vkQueueBindSparse(queue, bindInfoCount, pBindInfo, fence);
    _post_call_vulkan_callback((void*) &ret, "vkQueueBindSparse", (GLADapiproc) glad_vkQueueBindSparse, 4, queue, bindInfoCount, pBindInfo, fence);
    return ret;
}
PFN_vkQueueBindSparse glad_debug_vkQueueBindSparse = glad_debug_impl_vkQueueBindSparse;
static void GLAD_API_PTR glad_on_demand_impl_vkQueueEndDebugUtilsLabelEXT(VkQueue queue) {
    glad_vkQueueEndDebugUtilsLabelEXT = (PFN_vkQueueEndDebugUtilsLabelEXT) glad_vk_on_demand_loader("vkQueueEndDebugUtilsLabelEXT");
    glad_vkQueueEndDebugUtilsLabelEXT(queue);
}
PFN_vkQueueEndDebugUtilsLabelEXT glad_vkQueueEndDebugUtilsLabelEXT = glad_on_demand_impl_vkQueueEndDebugUtilsLabelEXT;
static void GLAD_API_PTR glad_debug_impl_vkQueueEndDebugUtilsLabelEXT(VkQueue queue) {
    _pre_call_vulkan_callback("vkQueueEndDebugUtilsLabelEXT", (GLADapiproc) glad_vkQueueEndDebugUtilsLabelEXT, 1, queue);
    glad_vkQueueEndDebugUtilsLabelEXT(queue);
    _post_call_vulkan_callback(NULL, "vkQueueEndDebugUtilsLabelEXT", (GLADapiproc) glad_vkQueueEndDebugUtilsLabelEXT, 1, queue);
    
}
PFN_vkQueueEndDebugUtilsLabelEXT glad_debug_vkQueueEndDebugUtilsLabelEXT = glad_debug_impl_vkQueueEndDebugUtilsLabelEXT;
static void GLAD_API_PTR glad_on_demand_impl_vkQueueInsertDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT * pLabelInfo) {
    glad_vkQueueInsertDebugUtilsLabelEXT = (PFN_vkQueueInsertDebugUtilsLabelEXT) glad_vk_on_demand_loader("vkQueueInsertDebugUtilsLabelEXT");
    glad_vkQueueInsertDebugUtilsLabelEXT(queue, pLabelInfo);
}
PFN_vkQueueInsertDebugUtilsLabelEXT glad_vkQueueInsertDebugUtilsLabelEXT = glad_on_demand_impl_vkQueueInsertDebugUtilsLabelEXT;
static void GLAD_API_PTR glad_debug_impl_vkQueueInsertDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT * pLabelInfo) {
    _pre_call_vulkan_callback("vkQueueInsertDebugUtilsLabelEXT", (GLADapiproc) glad_vkQueueInsertDebugUtilsLabelEXT, 2, queue, pLabelInfo);
    glad_vkQueueInsertDebugUtilsLabelEXT(queue, pLabelInfo);
    _post_call_vulkan_callback(NULL, "vkQueueInsertDebugUtilsLabelEXT", (GLADapiproc) glad_vkQueueInsertDebugUtilsLabelEXT, 2, queue, pLabelInfo);
    
}
PFN_vkQueueInsertDebugUtilsLabelEXT glad_debug_vkQueueInsertDebugUtilsLabelEXT = glad_debug_impl_vkQueueInsertDebugUtilsLabelEXT;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkQueuePresentKHR(VkQueue queue, const VkPresentInfoKHR * pPresentInfo) {
    glad_vkQueuePresentKHR = (PFN_vkQueuePresentKHR) glad_vk_on_demand_loader("vkQueuePresentKHR");
    return glad_vkQueuePresentKHR(queue, pPresentInfo);
}
PFN_vkQueuePresentKHR glad_vkQueuePresentKHR = glad_on_demand_impl_vkQueuePresentKHR;
static VkResult GLAD_API_PTR glad_debug_impl_vkQueuePresentKHR(VkQueue queue, const VkPresentInfoKHR * pPresentInfo) {
    VkResult ret;
    _pre_call_vulkan_callback("vkQueuePresentKHR", (GLADapiproc) glad_vkQueuePresentKHR, 2, queue, pPresentInfo);
    ret = glad_vkQueuePresentKHR(queue, pPresentInfo);
    _post_call_vulkan_callback((void*) &ret, "vkQueuePresentKHR", (GLADapiproc) glad_vkQueuePresentKHR, 2, queue, pPresentInfo);
    return ret;
}
PFN_vkQueuePresentKHR glad_debug_vkQueuePresentKHR = glad_debug_impl_vkQueuePresentKHR;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkQueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo * pSubmits, VkFence fence) {
    glad_vkQueueSubmit = (PFN_vkQueueSubmit) glad_vk_on_demand_loader("vkQueueSubmit");
    return glad_vkQueueSubmit(queue, submitCount, pSubmits, fence);
}
PFN_vkQueueSubmit glad_vkQueueSubmit = glad_on_demand_impl_vkQueueSubmit;
static VkResult GLAD_API_PTR glad_debug_impl_vkQueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo * pSubmits, VkFence fence) {
    VkResult ret;
    _pre_call_vulkan_callback("vkQueueSubmit", (GLADapiproc) glad_vkQueueSubmit, 4, queue, submitCount, pSubmits, fence);
    ret = glad_vkQueueSubmit(queue, submitCount, pSubmits, fence);
    _post_call_vulkan_callback((void*) &ret, "vkQueueSubmit", (GLADapiproc) glad_vkQueueSubmit, 4, queue, submitCount, pSubmits, fence);
    return ret;
}
PFN_vkQueueSubmit glad_debug_vkQueueSubmit = glad_debug_impl_vkQueueSubmit;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkQueueWaitIdle(VkQueue queue) {
    glad_vkQueueWaitIdle = (PFN_vkQueueWaitIdle) glad_vk_on_demand_loader("vkQueueWaitIdle");
    return glad_vkQueueWaitIdle(queue);
}
PFN_vkQueueWaitIdle glad_vkQueueWaitIdle = glad_on_demand_impl_vkQueueWaitIdle;
static VkResult GLAD_API_PTR glad_debug_impl_vkQueueWaitIdle(VkQueue queue) {
    VkResult ret;
    _pre_call_vulkan_callback("vkQueueWaitIdle", (GLADapiproc) glad_vkQueueWaitIdle, 1, queue);
    ret = glad_vkQueueWaitIdle(queue);
    _post_call_vulkan_callback((void*) &ret, "vkQueueWaitIdle", (GLADapiproc) glad_vkQueueWaitIdle, 1, queue);
    return ret;
}
PFN_vkQueueWaitIdle glad_debug_vkQueueWaitIdle = glad_debug_impl_vkQueueWaitIdle;
static void GLAD_API_PTR glad_on_demand_impl_vkReleaseProfilingLockKHR(VkDevice device) {
    glad_vkReleaseProfilingLockKHR = (PFN_vkReleaseProfilingLockKHR) glad_vk_on_demand_loader("vkReleaseProfilingLockKHR");
    glad_vkReleaseProfilingLockKHR(device);
}
PFN_vkReleaseProfilingLockKHR glad_vkReleaseProfilingLockKHR = glad_on_demand_impl_vkReleaseProfilingLockKHR;
static void GLAD_API_PTR glad_debug_impl_vkReleaseProfilingLockKHR(VkDevice device) {
    _pre_call_vulkan_callback("vkReleaseProfilingLockKHR", (GLADapiproc) glad_vkReleaseProfilingLockKHR, 1, device);
    glad_vkReleaseProfilingLockKHR(device);
    _post_call_vulkan_callback(NULL, "vkReleaseProfilingLockKHR", (GLADapiproc) glad_vkReleaseProfilingLockKHR, 1, device);
    
}
PFN_vkReleaseProfilingLockKHR glad_debug_vkReleaseProfilingLockKHR = glad_debug_impl_vkReleaseProfilingLockKHR;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkResetCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferResetFlags flags) {
    glad_vkResetCommandBuffer = (PFN_vkResetCommandBuffer) glad_vk_on_demand_loader("vkResetCommandBuffer");
    return glad_vkResetCommandBuffer(commandBuffer, flags);
}
PFN_vkResetCommandBuffer glad_vkResetCommandBuffer = glad_on_demand_impl_vkResetCommandBuffer;
static VkResult GLAD_API_PTR glad_debug_impl_vkResetCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferResetFlags flags) {
    VkResult ret;
    _pre_call_vulkan_callback("vkResetCommandBuffer", (GLADapiproc) glad_vkResetCommandBuffer, 2, commandBuffer, flags);
    ret = glad_vkResetCommandBuffer(commandBuffer, flags);
    _post_call_vulkan_callback((void*) &ret, "vkResetCommandBuffer", (GLADapiproc) glad_vkResetCommandBuffer, 2, commandBuffer, flags);
    return ret;
}
PFN_vkResetCommandBuffer glad_debug_vkResetCommandBuffer = glad_debug_impl_vkResetCommandBuffer;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkResetCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags flags) {
    glad_vkResetCommandPool = (PFN_vkResetCommandPool) glad_vk_on_demand_loader("vkResetCommandPool");
    return glad_vkResetCommandPool(device, commandPool, flags);
}
PFN_vkResetCommandPool glad_vkResetCommandPool = glad_on_demand_impl_vkResetCommandPool;
static VkResult GLAD_API_PTR glad_debug_impl_vkResetCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags flags) {
    VkResult ret;
    _pre_call_vulkan_callback("vkResetCommandPool", (GLADapiproc) glad_vkResetCommandPool, 3, device, commandPool, flags);
    ret = glad_vkResetCommandPool(device, commandPool, flags);
    _post_call_vulkan_callback((void*) &ret, "vkResetCommandPool", (GLADapiproc) glad_vkResetCommandPool, 3, device, commandPool, flags);
    return ret;
}
PFN_vkResetCommandPool glad_debug_vkResetCommandPool = glad_debug_impl_vkResetCommandPool;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkResetDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorPoolResetFlags flags) {
    glad_vkResetDescriptorPool = (PFN_vkResetDescriptorPool) glad_vk_on_demand_loader("vkResetDescriptorPool");
    return glad_vkResetDescriptorPool(device, descriptorPool, flags);
}
PFN_vkResetDescriptorPool glad_vkResetDescriptorPool = glad_on_demand_impl_vkResetDescriptorPool;
static VkResult GLAD_API_PTR glad_debug_impl_vkResetDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorPoolResetFlags flags) {
    VkResult ret;
    _pre_call_vulkan_callback("vkResetDescriptorPool", (GLADapiproc) glad_vkResetDescriptorPool, 3, device, descriptorPool, flags);
    ret = glad_vkResetDescriptorPool(device, descriptorPool, flags);
    _post_call_vulkan_callback((void*) &ret, "vkResetDescriptorPool", (GLADapiproc) glad_vkResetDescriptorPool, 3, device, descriptorPool, flags);
    return ret;
}
PFN_vkResetDescriptorPool glad_debug_vkResetDescriptorPool = glad_debug_impl_vkResetDescriptorPool;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkResetEvent(VkDevice device, VkEvent event) {
    glad_vkResetEvent = (PFN_vkResetEvent) glad_vk_on_demand_loader("vkResetEvent");
    return glad_vkResetEvent(device, event);
}
PFN_vkResetEvent glad_vkResetEvent = glad_on_demand_impl_vkResetEvent;
static VkResult GLAD_API_PTR glad_debug_impl_vkResetEvent(VkDevice device, VkEvent event) {
    VkResult ret;
    _pre_call_vulkan_callback("vkResetEvent", (GLADapiproc) glad_vkResetEvent, 2, device, event);
    ret = glad_vkResetEvent(device, event);
    _post_call_vulkan_callback((void*) &ret, "vkResetEvent", (GLADapiproc) glad_vkResetEvent, 2, device, event);
    return ret;
}
PFN_vkResetEvent glad_debug_vkResetEvent = glad_debug_impl_vkResetEvent;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkResetFences(VkDevice device, uint32_t fenceCount, const VkFence * pFences) {
    glad_vkResetFences = (PFN_vkResetFences) glad_vk_on_demand_loader("vkResetFences");
    return glad_vkResetFences(device, fenceCount, pFences);
}
PFN_vkResetFences glad_vkResetFences = glad_on_demand_impl_vkResetFences;
static VkResult GLAD_API_PTR glad_debug_impl_vkResetFences(VkDevice device, uint32_t fenceCount, const VkFence * pFences) {
    VkResult ret;
    _pre_call_vulkan_callback("vkResetFences", (GLADapiproc) glad_vkResetFences, 3, device, fenceCount, pFences);
    ret = glad_vkResetFences(device, fenceCount, pFences);
    _post_call_vulkan_callback((void*) &ret, "vkResetFences", (GLADapiproc) glad_vkResetFences, 3, device, fenceCount, pFences);
    return ret;
}
PFN_vkResetFences glad_debug_vkResetFences = glad_debug_impl_vkResetFences;
static void GLAD_API_PTR glad_on_demand_impl_vkResetQueryPool(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) {
    glad_vkResetQueryPool = (PFN_vkResetQueryPool) glad_vk_on_demand_loader("vkResetQueryPool");
    glad_vkResetQueryPool(device, queryPool, firstQuery, queryCount);
}
PFN_vkResetQueryPool glad_vkResetQueryPool = glad_on_demand_impl_vkResetQueryPool;
static void GLAD_API_PTR glad_debug_impl_vkResetQueryPool(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) {
    _pre_call_vulkan_callback("vkResetQueryPool", (GLADapiproc) glad_vkResetQueryPool, 4, device, queryPool, firstQuery, queryCount);
    glad_vkResetQueryPool(device, queryPool, firstQuery, queryCount);
    _post_call_vulkan_callback(NULL, "vkResetQueryPool", (GLADapiproc) glad_vkResetQueryPool, 4, device, queryPool, firstQuery, queryCount);
    
}
PFN_vkResetQueryPool glad_debug_vkResetQueryPool = glad_debug_impl_vkResetQueryPool;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkSetDebugUtilsObjectNameEXT(VkDevice device, const VkDebugUtilsObjectNameInfoEXT * pNameInfo) {
    glad_vkSetDebugUtilsObjectNameEXT = (PFN_vkSetDebugUtilsObjectNameEXT) glad_vk_on_demand_loader("vkSetDebugUtilsObjectNameEXT");
    return glad_vkSetDebugUtilsObjectNameEXT(device, pNameInfo);
}
PFN_vkSetDebugUtilsObjectNameEXT glad_vkSetDebugUtilsObjectNameEXT = glad_on_demand_impl_vkSetDebugUtilsObjectNameEXT;
static VkResult GLAD_API_PTR glad_debug_impl_vkSetDebugUtilsObjectNameEXT(VkDevice device, const VkDebugUtilsObjectNameInfoEXT * pNameInfo) {
    VkResult ret;
    _pre_call_vulkan_callback("vkSetDebugUtilsObjectNameEXT", (GLADapiproc) glad_vkSetDebugUtilsObjectNameEXT, 2, device, pNameInfo);
    ret = glad_vkSetDebugUtilsObjectNameEXT(device, pNameInfo);
    _post_call_vulkan_callback((void*) &ret, "vkSetDebugUtilsObjectNameEXT", (GLADapiproc) glad_vkSetDebugUtilsObjectNameEXT, 2, device, pNameInfo);
    return ret;
}
PFN_vkSetDebugUtilsObjectNameEXT glad_debug_vkSetDebugUtilsObjectNameEXT = glad_debug_impl_vkSetDebugUtilsObjectNameEXT;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkSetDebugUtilsObjectTagEXT(VkDevice device, const VkDebugUtilsObjectTagInfoEXT * pTagInfo) {
    glad_vkSetDebugUtilsObjectTagEXT = (PFN_vkSetDebugUtilsObjectTagEXT) glad_vk_on_demand_loader("vkSetDebugUtilsObjectTagEXT");
    return glad_vkSetDebugUtilsObjectTagEXT(device, pTagInfo);
}
PFN_vkSetDebugUtilsObjectTagEXT glad_vkSetDebugUtilsObjectTagEXT = glad_on_demand_impl_vkSetDebugUtilsObjectTagEXT;
static VkResult GLAD_API_PTR glad_debug_impl_vkSetDebugUtilsObjectTagEXT(VkDevice device, const VkDebugUtilsObjectTagInfoEXT * pTagInfo) {
    VkResult ret;
    _pre_call_vulkan_callback("vkSetDebugUtilsObjectTagEXT", (GLADapiproc) glad_vkSetDebugUtilsObjectTagEXT, 2, device, pTagInfo);
    ret = glad_vkSetDebugUtilsObjectTagEXT(device, pTagInfo);
    _post_call_vulkan_callback((void*) &ret, "vkSetDebugUtilsObjectTagEXT", (GLADapiproc) glad_vkSetDebugUtilsObjectTagEXT, 2, device, pTagInfo);
    return ret;
}
PFN_vkSetDebugUtilsObjectTagEXT glad_debug_vkSetDebugUtilsObjectTagEXT = glad_debug_impl_vkSetDebugUtilsObjectTagEXT;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkSetEvent(VkDevice device, VkEvent event) {
    glad_vkSetEvent = (PFN_vkSetEvent) glad_vk_on_demand_loader("vkSetEvent");
    return glad_vkSetEvent(device, event);
}
PFN_vkSetEvent glad_vkSetEvent = glad_on_demand_impl_vkSetEvent;
static VkResult GLAD_API_PTR glad_debug_impl_vkSetEvent(VkDevice device, VkEvent event) {
    VkResult ret;
    _pre_call_vulkan_callback("vkSetEvent", (GLADapiproc) glad_vkSetEvent, 2, device, event);
    ret = glad_vkSetEvent(device, event);
    _post_call_vulkan_callback((void*) &ret, "vkSetEvent", (GLADapiproc) glad_vkSetEvent, 2, device, event);
    return ret;
}
PFN_vkSetEvent glad_debug_vkSetEvent = glad_debug_impl_vkSetEvent;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkSignalSemaphore(VkDevice device, const VkSemaphoreSignalInfo * pSignalInfo) {
    glad_vkSignalSemaphore = (PFN_vkSignalSemaphore) glad_vk_on_demand_loader("vkSignalSemaphore");
    return glad_vkSignalSemaphore(device, pSignalInfo);
}
PFN_vkSignalSemaphore glad_vkSignalSemaphore = glad_on_demand_impl_vkSignalSemaphore;
static VkResult GLAD_API_PTR glad_debug_impl_vkSignalSemaphore(VkDevice device, const VkSemaphoreSignalInfo * pSignalInfo) {
    VkResult ret;
    _pre_call_vulkan_callback("vkSignalSemaphore", (GLADapiproc) glad_vkSignalSemaphore, 2, device, pSignalInfo);
    ret = glad_vkSignalSemaphore(device, pSignalInfo);
    _post_call_vulkan_callback((void*) &ret, "vkSignalSemaphore", (GLADapiproc) glad_vkSignalSemaphore, 2, device, pSignalInfo);
    return ret;
}
PFN_vkSignalSemaphore glad_debug_vkSignalSemaphore = glad_debug_impl_vkSignalSemaphore;
static void GLAD_API_PTR glad_on_demand_impl_vkSubmitDebugUtilsMessageEXT(VkInstance instance, VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT * pCallbackData) {
    glad_vkSubmitDebugUtilsMessageEXT = (PFN_vkSubmitDebugUtilsMessageEXT) glad_vk_on_demand_loader("vkSubmitDebugUtilsMessageEXT");
    glad_vkSubmitDebugUtilsMessageEXT(instance, messageSeverity, messageTypes, pCallbackData);
}
PFN_vkSubmitDebugUtilsMessageEXT glad_vkSubmitDebugUtilsMessageEXT = glad_on_demand_impl_vkSubmitDebugUtilsMessageEXT;
static void GLAD_API_PTR glad_debug_impl_vkSubmitDebugUtilsMessageEXT(VkInstance instance, VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT * pCallbackData) {
    _pre_call_vulkan_callback("vkSubmitDebugUtilsMessageEXT", (GLADapiproc) glad_vkSubmitDebugUtilsMessageEXT, 4, instance, messageSeverity, messageTypes, pCallbackData);
    glad_vkSubmitDebugUtilsMessageEXT(instance, messageSeverity, messageTypes, pCallbackData);
    _post_call_vulkan_callback(NULL, "vkSubmitDebugUtilsMessageEXT", (GLADapiproc) glad_vkSubmitDebugUtilsMessageEXT, 4, instance, messageSeverity, messageTypes, pCallbackData);
    
}
PFN_vkSubmitDebugUtilsMessageEXT glad_debug_vkSubmitDebugUtilsMessageEXT = glad_debug_impl_vkSubmitDebugUtilsMessageEXT;
static void GLAD_API_PTR glad_on_demand_impl_vkTrimCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) {
    glad_vkTrimCommandPool = (PFN_vkTrimCommandPool) glad_vk_on_demand_loader("vkTrimCommandPool");
    glad_vkTrimCommandPool(device, commandPool, flags);
}
PFN_vkTrimCommandPool glad_vkTrimCommandPool = glad_on_demand_impl_vkTrimCommandPool;
static void GLAD_API_PTR glad_debug_impl_vkTrimCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) {
    _pre_call_vulkan_callback("vkTrimCommandPool", (GLADapiproc) glad_vkTrimCommandPool, 3, device, commandPool, flags);
    glad_vkTrimCommandPool(device, commandPool, flags);
    _post_call_vulkan_callback(NULL, "vkTrimCommandPool", (GLADapiproc) glad_vkTrimCommandPool, 3, device, commandPool, flags);
    
}
PFN_vkTrimCommandPool glad_debug_vkTrimCommandPool = glad_debug_impl_vkTrimCommandPool;
static void GLAD_API_PTR glad_on_demand_impl_vkUnmapMemory(VkDevice device, VkDeviceMemory memory) {
    glad_vkUnmapMemory = (PFN_vkUnmapMemory) glad_vk_on_demand_loader("vkUnmapMemory");
    glad_vkUnmapMemory(device, memory);
}
PFN_vkUnmapMemory glad_vkUnmapMemory = glad_on_demand_impl_vkUnmapMemory;
static void GLAD_API_PTR glad_debug_impl_vkUnmapMemory(VkDevice device, VkDeviceMemory memory) {
    _pre_call_vulkan_callback("vkUnmapMemory", (GLADapiproc) glad_vkUnmapMemory, 2, device, memory);
    glad_vkUnmapMemory(device, memory);
    _post_call_vulkan_callback(NULL, "vkUnmapMemory", (GLADapiproc) glad_vkUnmapMemory, 2, device, memory);
    
}
PFN_vkUnmapMemory glad_debug_vkUnmapMemory = glad_debug_impl_vkUnmapMemory;
static void GLAD_API_PTR glad_on_demand_impl_vkUpdateDescriptorSetWithTemplate(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void * pData) {
    glad_vkUpdateDescriptorSetWithTemplate = (PFN_vkUpdateDescriptorSetWithTemplate) glad_vk_on_demand_loader("vkUpdateDescriptorSetWithTemplate");
    glad_vkUpdateDescriptorSetWithTemplate(device, descriptorSet, descriptorUpdateTemplate, pData);
}
PFN_vkUpdateDescriptorSetWithTemplate glad_vkUpdateDescriptorSetWithTemplate = glad_on_demand_impl_vkUpdateDescriptorSetWithTemplate;
static void GLAD_API_PTR glad_debug_impl_vkUpdateDescriptorSetWithTemplate(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void * pData) {
    _pre_call_vulkan_callback("vkUpdateDescriptorSetWithTemplate", (GLADapiproc) glad_vkUpdateDescriptorSetWithTemplate, 4, device, descriptorSet, descriptorUpdateTemplate, pData);
    glad_vkUpdateDescriptorSetWithTemplate(device, descriptorSet, descriptorUpdateTemplate, pData);
    _post_call_vulkan_callback(NULL, "vkUpdateDescriptorSetWithTemplate", (GLADapiproc) glad_vkUpdateDescriptorSetWithTemplate, 4, device, descriptorSet, descriptorUpdateTemplate, pData);
    
}
PFN_vkUpdateDescriptorSetWithTemplate glad_debug_vkUpdateDescriptorSetWithTemplate = glad_debug_impl_vkUpdateDescriptorSetWithTemplate;
static void GLAD_API_PTR glad_on_demand_impl_vkUpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, const VkWriteDescriptorSet * pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet * pDescriptorCopies) {
    glad_vkUpdateDescriptorSets = (PFN_vkUpdateDescriptorSets) glad_vk_on_demand_loader("vkUpdateDescriptorSets");
    glad_vkUpdateDescriptorSets(device, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies);
}
PFN_vkUpdateDescriptorSets glad_vkUpdateDescriptorSets = glad_on_demand_impl_vkUpdateDescriptorSets;
static void GLAD_API_PTR glad_debug_impl_vkUpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, const VkWriteDescriptorSet * pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet * pDescriptorCopies) {
    _pre_call_vulkan_callback("vkUpdateDescriptorSets", (GLADapiproc) glad_vkUpdateDescriptorSets, 5, device, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies);
    glad_vkUpdateDescriptorSets(device, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies);
    _post_call_vulkan_callback(NULL, "vkUpdateDescriptorSets", (GLADapiproc) glad_vkUpdateDescriptorSets, 5, device, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies);
    
}
PFN_vkUpdateDescriptorSets glad_debug_vkUpdateDescriptorSets = glad_debug_impl_vkUpdateDescriptorSets;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkWaitForFences(VkDevice device, uint32_t fenceCount, const VkFence * pFences, VkBool32 waitAll, uint64_t timeout) {
    glad_vkWaitForFences = (PFN_vkWaitForFences) glad_vk_on_demand_loader("vkWaitForFences");
    return glad_vkWaitForFences(device, fenceCount, pFences, waitAll, timeout);
}
PFN_vkWaitForFences glad_vkWaitForFences = glad_on_demand_impl_vkWaitForFences;
static VkResult GLAD_API_PTR glad_debug_impl_vkWaitForFences(VkDevice device, uint32_t fenceCount, const VkFence * pFences, VkBool32 waitAll, uint64_t timeout) {
    VkResult ret;
    _pre_call_vulkan_callback("vkWaitForFences", (GLADapiproc) glad_vkWaitForFences, 5, device, fenceCount, pFences, waitAll, timeout);
    ret = glad_vkWaitForFences(device, fenceCount, pFences, waitAll, timeout);
    _post_call_vulkan_callback((void*) &ret, "vkWaitForFences", (GLADapiproc) glad_vkWaitForFences, 5, device, fenceCount, pFences, waitAll, timeout);
    return ret;
}
PFN_vkWaitForFences glad_debug_vkWaitForFences = glad_debug_impl_vkWaitForFences;
static VkResult GLAD_API_PTR glad_on_demand_impl_vkWaitSemaphores(VkDevice device, const VkSemaphoreWaitInfo * pWaitInfo, uint64_t timeout) {
    glad_vkWaitSemaphores = (PFN_vkWaitSemaphores) glad_vk_on_demand_loader("vkWaitSemaphores");
    return glad_vkWaitSemaphores(device, pWaitInfo, timeout);
}
PFN_vkWaitSemaphores glad_vkWaitSemaphores = glad_on_demand_impl_vkWaitSemaphores;
static VkResult GLAD_API_PTR glad_debug_impl_vkWaitSemaphores(VkDevice device, const VkSemaphoreWaitInfo * pWaitInfo, uint64_t timeout) {
    VkResult ret;
    _pre_call_vulkan_callback("vkWaitSemaphores", (GLADapiproc) glad_vkWaitSemaphores, 3, device, pWaitInfo, timeout);
    ret = glad_vkWaitSemaphores(device, pWaitInfo, timeout);
    _post_call_vulkan_callback((void*) &ret, "vkWaitSemaphores", (GLADapiproc) glad_vkWaitSemaphores, 3, device, pWaitInfo, timeout);
    return ret;
}
PFN_vkWaitSemaphores glad_debug_vkWaitSemaphores = glad_debug_impl_vkWaitSemaphores;


 
void gladInstallVulkanDebug() {
    glad_debug_vkAcquireNextImage2KHR = glad_debug_impl_vkAcquireNextImage2KHR;
    glad_debug_vkAcquireNextImageKHR = glad_debug_impl_vkAcquireNextImageKHR;
    glad_debug_vkAcquireProfilingLockKHR = glad_debug_impl_vkAcquireProfilingLockKHR;
    glad_debug_vkAllocateCommandBuffers = glad_debug_impl_vkAllocateCommandBuffers;
    glad_debug_vkAllocateDescriptorSets = glad_debug_impl_vkAllocateDescriptorSets;
    glad_debug_vkAllocateMemory = glad_debug_impl_vkAllocateMemory;
    glad_debug_vkBeginCommandBuffer = glad_debug_impl_vkBeginCommandBuffer;
    glad_debug_vkBindBufferMemory = glad_debug_impl_vkBindBufferMemory;
    glad_debug_vkBindBufferMemory2 = glad_debug_impl_vkBindBufferMemory2;
    glad_debug_vkBindImageMemory = glad_debug_impl_vkBindImageMemory;
    glad_debug_vkBindImageMemory2 = glad_debug_impl_vkBindImageMemory2;
    glad_debug_vkCmdBeginDebugUtilsLabelEXT = glad_debug_impl_vkCmdBeginDebugUtilsLabelEXT;
    glad_debug_vkCmdBeginQuery = glad_debug_impl_vkCmdBeginQuery;
    glad_debug_vkCmdBeginRenderPass = glad_debug_impl_vkCmdBeginRenderPass;
    glad_debug_vkCmdBeginRenderPass2 = glad_debug_impl_vkCmdBeginRenderPass2;
    glad_debug_vkCmdBindDescriptorSets = glad_debug_impl_vkCmdBindDescriptorSets;
    glad_debug_vkCmdBindIndexBuffer = glad_debug_impl_vkCmdBindIndexBuffer;
    glad_debug_vkCmdBindPipeline = glad_debug_impl_vkCmdBindPipeline;
    glad_debug_vkCmdBindVertexBuffers = glad_debug_impl_vkCmdBindVertexBuffers;
    glad_debug_vkCmdBlitImage = glad_debug_impl_vkCmdBlitImage;
    glad_debug_vkCmdClearAttachments = glad_debug_impl_vkCmdClearAttachments;
    glad_debug_vkCmdClearColorImage = glad_debug_impl_vkCmdClearColorImage;
    glad_debug_vkCmdClearDepthStencilImage = glad_debug_impl_vkCmdClearDepthStencilImage;
    glad_debug_vkCmdCopyBuffer = glad_debug_impl_vkCmdCopyBuffer;
    glad_debug_vkCmdCopyBufferToImage = glad_debug_impl_vkCmdCopyBufferToImage;
    glad_debug_vkCmdCopyImage = glad_debug_impl_vkCmdCopyImage;
    glad_debug_vkCmdCopyImageToBuffer = glad_debug_impl_vkCmdCopyImageToBuffer;
    glad_debug_vkCmdCopyQueryPoolResults = glad_debug_impl_vkCmdCopyQueryPoolResults;
    glad_debug_vkCmdDebugMarkerBeginEXT = glad_debug_impl_vkCmdDebugMarkerBeginEXT;
    glad_debug_vkCmdDebugMarkerEndEXT = glad_debug_impl_vkCmdDebugMarkerEndEXT;
    glad_debug_vkCmdDebugMarkerInsertEXT = glad_debug_impl_vkCmdDebugMarkerInsertEXT;
    glad_debug_vkCmdDispatch = glad_debug_impl_vkCmdDispatch;
    glad_debug_vkCmdDispatchBase = glad_debug_impl_vkCmdDispatchBase;
    glad_debug_vkCmdDispatchBaseKHR = glad_debug_impl_vkCmdDispatchBaseKHR;
    glad_debug_vkCmdDispatchIndirect = glad_debug_impl_vkCmdDispatchIndirect;
    glad_debug_vkCmdDraw = glad_debug_impl_vkCmdDraw;
    glad_debug_vkCmdDrawIndexed = glad_debug_impl_vkCmdDrawIndexed;
    glad_debug_vkCmdDrawIndexedIndirect = glad_debug_impl_vkCmdDrawIndexedIndirect;
    glad_debug_vkCmdDrawIndexedIndirectCount = glad_debug_impl_vkCmdDrawIndexedIndirectCount;
    glad_debug_vkCmdDrawIndirect = glad_debug_impl_vkCmdDrawIndirect;
    glad_debug_vkCmdDrawIndirectCount = glad_debug_impl_vkCmdDrawIndirectCount;
    glad_debug_vkCmdEndDebugUtilsLabelEXT = glad_debug_impl_vkCmdEndDebugUtilsLabelEXT;
    glad_debug_vkCmdEndQuery = glad_debug_impl_vkCmdEndQuery;
    glad_debug_vkCmdEndRenderPass = glad_debug_impl_vkCmdEndRenderPass;
    glad_debug_vkCmdEndRenderPass2 = glad_debug_impl_vkCmdEndRenderPass2;
    glad_debug_vkCmdExecuteCommands = glad_debug_impl_vkCmdExecuteCommands;
    glad_debug_vkCmdFillBuffer = glad_debug_impl_vkCmdFillBuffer;
    glad_debug_vkCmdInsertDebugUtilsLabelEXT = glad_debug_impl_vkCmdInsertDebugUtilsLabelEXT;
    glad_debug_vkCmdNextSubpass = glad_debug_impl_vkCmdNextSubpass;
    glad_debug_vkCmdNextSubpass2 = glad_debug_impl_vkCmdNextSubpass2;
    glad_debug_vkCmdPipelineBarrier = glad_debug_impl_vkCmdPipelineBarrier;
    glad_debug_vkCmdPushConstants = glad_debug_impl_vkCmdPushConstants;
    glad_debug_vkCmdResetEvent = glad_debug_impl_vkCmdResetEvent;
    glad_debug_vkCmdResetQueryPool = glad_debug_impl_vkCmdResetQueryPool;
    glad_debug_vkCmdResolveImage = glad_debug_impl_vkCmdResolveImage;
    glad_debug_vkCmdSetBlendConstants = glad_debug_impl_vkCmdSetBlendConstants;
    glad_debug_vkCmdSetDepthBias = glad_debug_impl_vkCmdSetDepthBias;
    glad_debug_vkCmdSetDepthBounds = glad_debug_impl_vkCmdSetDepthBounds;
    glad_debug_vkCmdSetDeviceMask = glad_debug_impl_vkCmdSetDeviceMask;
    glad_debug_vkCmdSetDeviceMaskKHR = glad_debug_impl_vkCmdSetDeviceMaskKHR;
    glad_debug_vkCmdSetEvent = glad_debug_impl_vkCmdSetEvent;
    glad_debug_vkCmdSetLineWidth = glad_debug_impl_vkCmdSetLineWidth;
    glad_debug_vkCmdSetScissor = glad_debug_impl_vkCmdSetScissor;
    glad_debug_vkCmdSetStencilCompareMask = glad_debug_impl_vkCmdSetStencilCompareMask;
    glad_debug_vkCmdSetStencilReference = glad_debug_impl_vkCmdSetStencilReference;
    glad_debug_vkCmdSetStencilWriteMask = glad_debug_impl_vkCmdSetStencilWriteMask;
    glad_debug_vkCmdSetViewport = glad_debug_impl_vkCmdSetViewport;
    glad_debug_vkCmdUpdateBuffer = glad_debug_impl_vkCmdUpdateBuffer;
    glad_debug_vkCmdWaitEvents = glad_debug_impl_vkCmdWaitEvents;
    glad_debug_vkCmdWriteTimestamp = glad_debug_impl_vkCmdWriteTimestamp;
    glad_debug_vkCreateBuffer = glad_debug_impl_vkCreateBuffer;
    glad_debug_vkCreateBufferView = glad_debug_impl_vkCreateBufferView;
    glad_debug_vkCreateCommandPool = glad_debug_impl_vkCreateCommandPool;
    glad_debug_vkCreateComputePipelines = glad_debug_impl_vkCreateComputePipelines;
    glad_debug_vkCreateDebugReportCallbackEXT = glad_debug_impl_vkCreateDebugReportCallbackEXT;
    glad_debug_vkCreateDebugUtilsMessengerEXT = glad_debug_impl_vkCreateDebugUtilsMessengerEXT;
    glad_debug_vkCreateDescriptorPool = glad_debug_impl_vkCreateDescriptorPool;
    glad_debug_vkCreateDescriptorSetLayout = glad_debug_impl_vkCreateDescriptorSetLayout;
    glad_debug_vkCreateDescriptorUpdateTemplate = glad_debug_impl_vkCreateDescriptorUpdateTemplate;
    glad_debug_vkCreateDevice = glad_debug_impl_vkCreateDevice;
    glad_debug_vkCreateEvent = glad_debug_impl_vkCreateEvent;
    glad_debug_vkCreateFence = glad_debug_impl_vkCreateFence;
    glad_debug_vkCreateFramebuffer = glad_debug_impl_vkCreateFramebuffer;
    glad_debug_vkCreateGraphicsPipelines = glad_debug_impl_vkCreateGraphicsPipelines;
    glad_debug_vkCreateImage = glad_debug_impl_vkCreateImage;
    glad_debug_vkCreateImageView = glad_debug_impl_vkCreateImageView;
    glad_debug_vkCreateInstance = glad_debug_impl_vkCreateInstance;
    glad_debug_vkCreatePipelineCache = glad_debug_impl_vkCreatePipelineCache;
    glad_debug_vkCreatePipelineLayout = glad_debug_impl_vkCreatePipelineLayout;
    glad_debug_vkCreateQueryPool = glad_debug_impl_vkCreateQueryPool;
    glad_debug_vkCreateRenderPass = glad_debug_impl_vkCreateRenderPass;
    glad_debug_vkCreateRenderPass2 = glad_debug_impl_vkCreateRenderPass2;
    glad_debug_vkCreateSampler = glad_debug_impl_vkCreateSampler;
    glad_debug_vkCreateSamplerYcbcrConversion = glad_debug_impl_vkCreateSamplerYcbcrConversion;
    glad_debug_vkCreateSemaphore = glad_debug_impl_vkCreateSemaphore;
    glad_debug_vkCreateShaderModule = glad_debug_impl_vkCreateShaderModule;
    glad_debug_vkCreateSwapchainKHR = glad_debug_impl_vkCreateSwapchainKHR;
    glad_debug_vkDebugMarkerSetObjectNameEXT = glad_debug_impl_vkDebugMarkerSetObjectNameEXT;
    glad_debug_vkDebugMarkerSetObjectTagEXT = glad_debug_impl_vkDebugMarkerSetObjectTagEXT;
    glad_debug_vkDebugReportMessageEXT = glad_debug_impl_vkDebugReportMessageEXT;
    glad_debug_vkDestroyBuffer = glad_debug_impl_vkDestroyBuffer;
    glad_debug_vkDestroyBufferView = glad_debug_impl_vkDestroyBufferView;
    glad_debug_vkDestroyCommandPool = glad_debug_impl_vkDestroyCommandPool;
    glad_debug_vkDestroyDebugReportCallbackEXT = glad_debug_impl_vkDestroyDebugReportCallbackEXT;
    glad_debug_vkDestroyDebugUtilsMessengerEXT = glad_debug_impl_vkDestroyDebugUtilsMessengerEXT;
    glad_debug_vkDestroyDescriptorPool = glad_debug_impl_vkDestroyDescriptorPool;
    glad_debug_vkDestroyDescriptorSetLayout = glad_debug_impl_vkDestroyDescriptorSetLayout;
    glad_debug_vkDestroyDescriptorUpdateTemplate = glad_debug_impl_vkDestroyDescriptorUpdateTemplate;
    glad_debug_vkDestroyDevice = glad_debug_impl_vkDestroyDevice;
    glad_debug_vkDestroyEvent = glad_debug_impl_vkDestroyEvent;
    glad_debug_vkDestroyFence = glad_debug_impl_vkDestroyFence;
    glad_debug_vkDestroyFramebuffer = glad_debug_impl_vkDestroyFramebuffer;
    glad_debug_vkDestroyImage = glad_debug_impl_vkDestroyImage;
    glad_debug_vkDestroyImageView = glad_debug_impl_vkDestroyImageView;
    glad_debug_vkDestroyInstance = glad_debug_impl_vkDestroyInstance;
    glad_debug_vkDestroyPipeline = glad_debug_impl_vkDestroyPipeline;
    glad_debug_vkDestroyPipelineCache = glad_debug_impl_vkDestroyPipelineCache;
    glad_debug_vkDestroyPipelineLayout = glad_debug_impl_vkDestroyPipelineLayout;
    glad_debug_vkDestroyQueryPool = glad_debug_impl_vkDestroyQueryPool;
    glad_debug_vkDestroyRenderPass = glad_debug_impl_vkDestroyRenderPass;
    glad_debug_vkDestroySampler = glad_debug_impl_vkDestroySampler;
    glad_debug_vkDestroySamplerYcbcrConversion = glad_debug_impl_vkDestroySamplerYcbcrConversion;
    glad_debug_vkDestroySemaphore = glad_debug_impl_vkDestroySemaphore;
    glad_debug_vkDestroyShaderModule = glad_debug_impl_vkDestroyShaderModule;
    glad_debug_vkDestroySurfaceKHR = glad_debug_impl_vkDestroySurfaceKHR;
    glad_debug_vkDestroySwapchainKHR = glad_debug_impl_vkDestroySwapchainKHR;
    glad_debug_vkDeviceWaitIdle = glad_debug_impl_vkDeviceWaitIdle;
    glad_debug_vkEndCommandBuffer = glad_debug_impl_vkEndCommandBuffer;
    glad_debug_vkEnumerateDeviceExtensionProperties = glad_debug_impl_vkEnumerateDeviceExtensionProperties;
    glad_debug_vkEnumerateDeviceLayerProperties = glad_debug_impl_vkEnumerateDeviceLayerProperties;
    glad_debug_vkEnumerateInstanceExtensionProperties = glad_debug_impl_vkEnumerateInstanceExtensionProperties;
    glad_debug_vkEnumerateInstanceLayerProperties = glad_debug_impl_vkEnumerateInstanceLayerProperties;
    glad_debug_vkEnumerateInstanceVersion = glad_debug_impl_vkEnumerateInstanceVersion;
    glad_debug_vkEnumeratePhysicalDeviceGroups = glad_debug_impl_vkEnumeratePhysicalDeviceGroups;
    glad_debug_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = glad_debug_impl_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR;
    glad_debug_vkEnumeratePhysicalDevices = glad_debug_impl_vkEnumeratePhysicalDevices;
    glad_debug_vkFlushMappedMemoryRanges = glad_debug_impl_vkFlushMappedMemoryRanges;
    glad_debug_vkFreeCommandBuffers = glad_debug_impl_vkFreeCommandBuffers;
    glad_debug_vkFreeDescriptorSets = glad_debug_impl_vkFreeDescriptorSets;
    glad_debug_vkFreeMemory = glad_debug_impl_vkFreeMemory;
    glad_debug_vkGetBufferDeviceAddress = glad_debug_impl_vkGetBufferDeviceAddress;
    glad_debug_vkGetBufferMemoryRequirements = glad_debug_impl_vkGetBufferMemoryRequirements;
    glad_debug_vkGetBufferMemoryRequirements2 = glad_debug_impl_vkGetBufferMemoryRequirements2;
    glad_debug_vkGetBufferOpaqueCaptureAddress = glad_debug_impl_vkGetBufferOpaqueCaptureAddress;
    glad_debug_vkGetDescriptorSetLayoutSupport = glad_debug_impl_vkGetDescriptorSetLayoutSupport;
    glad_debug_vkGetDeviceGroupPeerMemoryFeatures = glad_debug_impl_vkGetDeviceGroupPeerMemoryFeatures;
    glad_debug_vkGetDeviceGroupPeerMemoryFeaturesKHR = glad_debug_impl_vkGetDeviceGroupPeerMemoryFeaturesKHR;
    glad_debug_vkGetDeviceGroupPresentCapabilitiesKHR = glad_debug_impl_vkGetDeviceGroupPresentCapabilitiesKHR;
    glad_debug_vkGetDeviceGroupSurfacePresentModesKHR = glad_debug_impl_vkGetDeviceGroupSurfacePresentModesKHR;
    glad_debug_vkGetDeviceMemoryCommitment = glad_debug_impl_vkGetDeviceMemoryCommitment;
    glad_debug_vkGetDeviceMemoryOpaqueCaptureAddress = glad_debug_impl_vkGetDeviceMemoryOpaqueCaptureAddress;
    glad_debug_vkGetDeviceProcAddr = glad_debug_impl_vkGetDeviceProcAddr;
    glad_debug_vkGetDeviceQueue = glad_debug_impl_vkGetDeviceQueue;
    glad_debug_vkGetDeviceQueue2 = glad_debug_impl_vkGetDeviceQueue2;
    glad_debug_vkGetEventStatus = glad_debug_impl_vkGetEventStatus;
    glad_debug_vkGetFenceStatus = glad_debug_impl_vkGetFenceStatus;
    glad_debug_vkGetImageMemoryRequirements = glad_debug_impl_vkGetImageMemoryRequirements;
    glad_debug_vkGetImageMemoryRequirements2 = glad_debug_impl_vkGetImageMemoryRequirements2;
    glad_debug_vkGetImageSparseMemoryRequirements = glad_debug_impl_vkGetImageSparseMemoryRequirements;
    glad_debug_vkGetImageSparseMemoryRequirements2 = glad_debug_impl_vkGetImageSparseMemoryRequirements2;
    glad_debug_vkGetImageSubresourceLayout = glad_debug_impl_vkGetImageSubresourceLayout;
    glad_debug_vkGetInstanceProcAddr = glad_debug_impl_vkGetInstanceProcAddr;
    glad_debug_vkGetPhysicalDeviceExternalBufferProperties = glad_debug_impl_vkGetPhysicalDeviceExternalBufferProperties;
    glad_debug_vkGetPhysicalDeviceExternalFenceProperties = glad_debug_impl_vkGetPhysicalDeviceExternalFenceProperties;
    glad_debug_vkGetPhysicalDeviceExternalSemaphoreProperties = glad_debug_impl_vkGetPhysicalDeviceExternalSemaphoreProperties;
    glad_debug_vkGetPhysicalDeviceFeatures = glad_debug_impl_vkGetPhysicalDeviceFeatures;
    glad_debug_vkGetPhysicalDeviceFeatures2 = glad_debug_impl_vkGetPhysicalDeviceFeatures2;
    glad_debug_vkGetPhysicalDeviceFormatProperties = glad_debug_impl_vkGetPhysicalDeviceFormatProperties;
    glad_debug_vkGetPhysicalDeviceFormatProperties2 = glad_debug_impl_vkGetPhysicalDeviceFormatProperties2;
    glad_debug_vkGetPhysicalDeviceImageFormatProperties = glad_debug_impl_vkGetPhysicalDeviceImageFormatProperties;
    glad_debug_vkGetPhysicalDeviceImageFormatProperties2 = glad_debug_impl_vkGetPhysicalDeviceImageFormatProperties2;
    glad_debug_vkGetPhysicalDeviceMemoryProperties = glad_debug_impl_vkGetPhysicalDeviceMemoryProperties;
    glad_debug_vkGetPhysicalDeviceMemoryProperties2 = glad_debug_impl_vkGetPhysicalDeviceMemoryProperties2;
    glad_debug_vkGetPhysicalDevicePresentRectanglesKHR = glad_debug_impl_vkGetPhysicalDevicePresentRectanglesKHR;
    glad_debug_vkGetPhysicalDeviceProperties = glad_debug_impl_vkGetPhysicalDeviceProperties;
    glad_debug_vkGetPhysicalDeviceProperties2 = glad_debug_impl_vkGetPhysicalDeviceProperties2;
    glad_debug_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR = glad_debug_impl_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR;
    glad_debug_vkGetPhysicalDeviceQueueFamilyProperties = glad_debug_impl_vkGetPhysicalDeviceQueueFamilyProperties;
    glad_debug_vkGetPhysicalDeviceQueueFamilyProperties2 = glad_debug_impl_vkGetPhysicalDeviceQueueFamilyProperties2;
    glad_debug_vkGetPhysicalDeviceSparseImageFormatProperties = glad_debug_impl_vkGetPhysicalDeviceSparseImageFormatProperties;
    glad_debug_vkGetPhysicalDeviceSparseImageFormatProperties2 = glad_debug_impl_vkGetPhysicalDeviceSparseImageFormatProperties2;
    glad_debug_vkGetPhysicalDeviceSurfaceCapabilitiesKHR = glad_debug_impl_vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
    glad_debug_vkGetPhysicalDeviceSurfaceFormatsKHR = glad_debug_impl_vkGetPhysicalDeviceSurfaceFormatsKHR;
    glad_debug_vkGetPhysicalDeviceSurfacePresentModesKHR = glad_debug_impl_vkGetPhysicalDeviceSurfacePresentModesKHR;
    glad_debug_vkGetPhysicalDeviceSurfaceSupportKHR = glad_debug_impl_vkGetPhysicalDeviceSurfaceSupportKHR;
    glad_debug_vkGetPipelineCacheData = glad_debug_impl_vkGetPipelineCacheData;
    glad_debug_vkGetPipelineExecutableInternalRepresentationsKHR = glad_debug_impl_vkGetPipelineExecutableInternalRepresentationsKHR;
    glad_debug_vkGetPipelineExecutablePropertiesKHR = glad_debug_impl_vkGetPipelineExecutablePropertiesKHR;
    glad_debug_vkGetPipelineExecutableStatisticsKHR = glad_debug_impl_vkGetPipelineExecutableStatisticsKHR;
    glad_debug_vkGetQueryPoolResults = glad_debug_impl_vkGetQueryPoolResults;
    glad_debug_vkGetRenderAreaGranularity = glad_debug_impl_vkGetRenderAreaGranularity;
    glad_debug_vkGetSemaphoreCounterValue = glad_debug_impl_vkGetSemaphoreCounterValue;
    glad_debug_vkGetSwapchainImagesKHR = glad_debug_impl_vkGetSwapchainImagesKHR;
    glad_debug_vkGetSwapchainStatusKHR = glad_debug_impl_vkGetSwapchainStatusKHR;
    glad_debug_vkInvalidateMappedMemoryRanges = glad_debug_impl_vkInvalidateMappedMemoryRanges;
    glad_debug_vkMapMemory = glad_debug_impl_vkMapMemory;
    glad_debug_vkMergePipelineCaches = glad_debug_impl_vkMergePipelineCaches;
    glad_debug_vkQueueBeginDebugUtilsLabelEXT = glad_debug_impl_vkQueueBeginDebugUtilsLabelEXT;
    glad_debug_vkQueueBindSparse = glad_debug_impl_vkQueueBindSparse;
    glad_debug_vkQueueEndDebugUtilsLabelEXT = glad_debug_impl_vkQueueEndDebugUtilsLabelEXT;
    glad_debug_vkQueueInsertDebugUtilsLabelEXT = glad_debug_impl_vkQueueInsertDebugUtilsLabelEXT;
    glad_debug_vkQueuePresentKHR = glad_debug_impl_vkQueuePresentKHR;
    glad_debug_vkQueueSubmit = glad_debug_impl_vkQueueSubmit;
    glad_debug_vkQueueWaitIdle = glad_debug_impl_vkQueueWaitIdle;
    glad_debug_vkReleaseProfilingLockKHR = glad_debug_impl_vkReleaseProfilingLockKHR;
    glad_debug_vkResetCommandBuffer = glad_debug_impl_vkResetCommandBuffer;
    glad_debug_vkResetCommandPool = glad_debug_impl_vkResetCommandPool;
    glad_debug_vkResetDescriptorPool = glad_debug_impl_vkResetDescriptorPool;
    glad_debug_vkResetEvent = glad_debug_impl_vkResetEvent;
    glad_debug_vkResetFences = glad_debug_impl_vkResetFences;
    glad_debug_vkResetQueryPool = glad_debug_impl_vkResetQueryPool;
    glad_debug_vkSetDebugUtilsObjectNameEXT = glad_debug_impl_vkSetDebugUtilsObjectNameEXT;
    glad_debug_vkSetDebugUtilsObjectTagEXT = glad_debug_impl_vkSetDebugUtilsObjectTagEXT;
    glad_debug_vkSetEvent = glad_debug_impl_vkSetEvent;
    glad_debug_vkSignalSemaphore = glad_debug_impl_vkSignalSemaphore;
    glad_debug_vkSubmitDebugUtilsMessageEXT = glad_debug_impl_vkSubmitDebugUtilsMessageEXT;
    glad_debug_vkTrimCommandPool = glad_debug_impl_vkTrimCommandPool;
    glad_debug_vkUnmapMemory = glad_debug_impl_vkUnmapMemory;
    glad_debug_vkUpdateDescriptorSetWithTemplate = glad_debug_impl_vkUpdateDescriptorSetWithTemplate;
    glad_debug_vkUpdateDescriptorSets = glad_debug_impl_vkUpdateDescriptorSets;
    glad_debug_vkWaitForFences = glad_debug_impl_vkWaitForFences;
    glad_debug_vkWaitSemaphores = glad_debug_impl_vkWaitSemaphores;
}

void gladUninstallVulkanDebug() {
    glad_debug_vkAcquireNextImage2KHR = glad_vkAcquireNextImage2KHR;
    glad_debug_vkAcquireNextImageKHR = glad_vkAcquireNextImageKHR;
    glad_debug_vkAcquireProfilingLockKHR = glad_vkAcquireProfilingLockKHR;
    glad_debug_vkAllocateCommandBuffers = glad_vkAllocateCommandBuffers;
    glad_debug_vkAllocateDescriptorSets = glad_vkAllocateDescriptorSets;
    glad_debug_vkAllocateMemory = glad_vkAllocateMemory;
    glad_debug_vkBeginCommandBuffer = glad_vkBeginCommandBuffer;
    glad_debug_vkBindBufferMemory = glad_vkBindBufferMemory;
    glad_debug_vkBindBufferMemory2 = glad_vkBindBufferMemory2;
    glad_debug_vkBindImageMemory = glad_vkBindImageMemory;
    glad_debug_vkBindImageMemory2 = glad_vkBindImageMemory2;
    glad_debug_vkCmdBeginDebugUtilsLabelEXT = glad_vkCmdBeginDebugUtilsLabelEXT;
    glad_debug_vkCmdBeginQuery = glad_vkCmdBeginQuery;
    glad_debug_vkCmdBeginRenderPass = glad_vkCmdBeginRenderPass;
    glad_debug_vkCmdBeginRenderPass2 = glad_vkCmdBeginRenderPass2;
    glad_debug_vkCmdBindDescriptorSets = glad_vkCmdBindDescriptorSets;
    glad_debug_vkCmdBindIndexBuffer = glad_vkCmdBindIndexBuffer;
    glad_debug_vkCmdBindPipeline = glad_vkCmdBindPipeline;
    glad_debug_vkCmdBindVertexBuffers = glad_vkCmdBindVertexBuffers;
    glad_debug_vkCmdBlitImage = glad_vkCmdBlitImage;
    glad_debug_vkCmdClearAttachments = glad_vkCmdClearAttachments;
    glad_debug_vkCmdClearColorImage = glad_vkCmdClearColorImage;
    glad_debug_vkCmdClearDepthStencilImage = glad_vkCmdClearDepthStencilImage;
    glad_debug_vkCmdCopyBuffer = glad_vkCmdCopyBuffer;
    glad_debug_vkCmdCopyBufferToImage = glad_vkCmdCopyBufferToImage;
    glad_debug_vkCmdCopyImage = glad_vkCmdCopyImage;
    glad_debug_vkCmdCopyImageToBuffer = glad_vkCmdCopyImageToBuffer;
    glad_debug_vkCmdCopyQueryPoolResults = glad_vkCmdCopyQueryPoolResults;
    glad_debug_vkCmdDebugMarkerBeginEXT = glad_vkCmdDebugMarkerBeginEXT;
    glad_debug_vkCmdDebugMarkerEndEXT = glad_vkCmdDebugMarkerEndEXT;
    glad_debug_vkCmdDebugMarkerInsertEXT = glad_vkCmdDebugMarkerInsertEXT;
    glad_debug_vkCmdDispatch = glad_vkCmdDispatch;
    glad_debug_vkCmdDispatchBase = glad_vkCmdDispatchBase;
    glad_debug_vkCmdDispatchBaseKHR = glad_vkCmdDispatchBaseKHR;
    glad_debug_vkCmdDispatchIndirect = glad_vkCmdDispatchIndirect;
    glad_debug_vkCmdDraw = glad_vkCmdDraw;
    glad_debug_vkCmdDrawIndexed = glad_vkCmdDrawIndexed;
    glad_debug_vkCmdDrawIndexedIndirect = glad_vkCmdDrawIndexedIndirect;
    glad_debug_vkCmdDrawIndexedIndirectCount = glad_vkCmdDrawIndexedIndirectCount;
    glad_debug_vkCmdDrawIndirect = glad_vkCmdDrawIndirect;
    glad_debug_vkCmdDrawIndirectCount = glad_vkCmdDrawIndirectCount;
    glad_debug_vkCmdEndDebugUtilsLabelEXT = glad_vkCmdEndDebugUtilsLabelEXT;
    glad_debug_vkCmdEndQuery = glad_vkCmdEndQuery;
    glad_debug_vkCmdEndRenderPass = glad_vkCmdEndRenderPass;
    glad_debug_vkCmdEndRenderPass2 = glad_vkCmdEndRenderPass2;
    glad_debug_vkCmdExecuteCommands = glad_vkCmdExecuteCommands;
    glad_debug_vkCmdFillBuffer = glad_vkCmdFillBuffer;
    glad_debug_vkCmdInsertDebugUtilsLabelEXT = glad_vkCmdInsertDebugUtilsLabelEXT;
    glad_debug_vkCmdNextSubpass = glad_vkCmdNextSubpass;
    glad_debug_vkCmdNextSubpass2 = glad_vkCmdNextSubpass2;
    glad_debug_vkCmdPipelineBarrier = glad_vkCmdPipelineBarrier;
    glad_debug_vkCmdPushConstants = glad_vkCmdPushConstants;
    glad_debug_vkCmdResetEvent = glad_vkCmdResetEvent;
    glad_debug_vkCmdResetQueryPool = glad_vkCmdResetQueryPool;
    glad_debug_vkCmdResolveImage = glad_vkCmdResolveImage;
    glad_debug_vkCmdSetBlendConstants = glad_vkCmdSetBlendConstants;
    glad_debug_vkCmdSetDepthBias = glad_vkCmdSetDepthBias;
    glad_debug_vkCmdSetDepthBounds = glad_vkCmdSetDepthBounds;
    glad_debug_vkCmdSetDeviceMask = glad_vkCmdSetDeviceMask;
    glad_debug_vkCmdSetDeviceMaskKHR = glad_vkCmdSetDeviceMaskKHR;
    glad_debug_vkCmdSetEvent = glad_vkCmdSetEvent;
    glad_debug_vkCmdSetLineWidth = glad_vkCmdSetLineWidth;
    glad_debug_vkCmdSetScissor = glad_vkCmdSetScissor;
    glad_debug_vkCmdSetStencilCompareMask = glad_vkCmdSetStencilCompareMask;
    glad_debug_vkCmdSetStencilReference = glad_vkCmdSetStencilReference;
    glad_debug_vkCmdSetStencilWriteMask = glad_vkCmdSetStencilWriteMask;
    glad_debug_vkCmdSetViewport = glad_vkCmdSetViewport;
    glad_debug_vkCmdUpdateBuffer = glad_vkCmdUpdateBuffer;
    glad_debug_vkCmdWaitEvents = glad_vkCmdWaitEvents;
    glad_debug_vkCmdWriteTimestamp = glad_vkCmdWriteTimestamp;
    glad_debug_vkCreateBuffer = glad_vkCreateBuffer;
    glad_debug_vkCreateBufferView = glad_vkCreateBufferView;
    glad_debug_vkCreateCommandPool = glad_vkCreateCommandPool;
    glad_debug_vkCreateComputePipelines = glad_vkCreateComputePipelines;
    glad_debug_vkCreateDebugReportCallbackEXT = glad_vkCreateDebugReportCallbackEXT;
    glad_debug_vkCreateDebugUtilsMessengerEXT = glad_vkCreateDebugUtilsMessengerEXT;
    glad_debug_vkCreateDescriptorPool = glad_vkCreateDescriptorPool;
    glad_debug_vkCreateDescriptorSetLayout = glad_vkCreateDescriptorSetLayout;
    glad_debug_vkCreateDescriptorUpdateTemplate = glad_vkCreateDescriptorUpdateTemplate;
    glad_debug_vkCreateDevice = glad_vkCreateDevice;
    glad_debug_vkCreateEvent = glad_vkCreateEvent;
    glad_debug_vkCreateFence = glad_vkCreateFence;
    glad_debug_vkCreateFramebuffer = glad_vkCreateFramebuffer;
    glad_debug_vkCreateGraphicsPipelines = glad_vkCreateGraphicsPipelines;
    glad_debug_vkCreateImage = glad_vkCreateImage;
    glad_debug_vkCreateImageView = glad_vkCreateImageView;
    glad_debug_vkCreateInstance = glad_vkCreateInstance;
    glad_debug_vkCreatePipelineCache = glad_vkCreatePipelineCache;
    glad_debug_vkCreatePipelineLayout = glad_vkCreatePipelineLayout;
    glad_debug_vkCreateQueryPool = glad_vkCreateQueryPool;
    glad_debug_vkCreateRenderPass = glad_vkCreateRenderPass;
    glad_debug_vkCreateRenderPass2 = glad_vkCreateRenderPass2;
    glad_debug_vkCreateSampler = glad_vkCreateSampler;
    glad_debug_vkCreateSamplerYcbcrConversion = glad_vkCreateSamplerYcbcrConversion;
    glad_debug_vkCreateSemaphore = glad_vkCreateSemaphore;
    glad_debug_vkCreateShaderModule = glad_vkCreateShaderModule;
    glad_debug_vkCreateSwapchainKHR = glad_vkCreateSwapchainKHR;
    glad_debug_vkDebugMarkerSetObjectNameEXT = glad_vkDebugMarkerSetObjectNameEXT;
    glad_debug_vkDebugMarkerSetObjectTagEXT = glad_vkDebugMarkerSetObjectTagEXT;
    glad_debug_vkDebugReportMessageEXT = glad_vkDebugReportMessageEXT;
    glad_debug_vkDestroyBuffer = glad_vkDestroyBuffer;
    glad_debug_vkDestroyBufferView = glad_vkDestroyBufferView;
    glad_debug_vkDestroyCommandPool = glad_vkDestroyCommandPool;
    glad_debug_vkDestroyDebugReportCallbackEXT = glad_vkDestroyDebugReportCallbackEXT;
    glad_debug_vkDestroyDebugUtilsMessengerEXT = glad_vkDestroyDebugUtilsMessengerEXT;
    glad_debug_vkDestroyDescriptorPool = glad_vkDestroyDescriptorPool;
    glad_debug_vkDestroyDescriptorSetLayout = glad_vkDestroyDescriptorSetLayout;
    glad_debug_vkDestroyDescriptorUpdateTemplate = glad_vkDestroyDescriptorUpdateTemplate;
    glad_debug_vkDestroyDevice = glad_vkDestroyDevice;
    glad_debug_vkDestroyEvent = glad_vkDestroyEvent;
    glad_debug_vkDestroyFence = glad_vkDestroyFence;
    glad_debug_vkDestroyFramebuffer = glad_vkDestroyFramebuffer;
    glad_debug_vkDestroyImage = glad_vkDestroyImage;
    glad_debug_vkDestroyImageView = glad_vkDestroyImageView;
    glad_debug_vkDestroyInstance = glad_vkDestroyInstance;
    glad_debug_vkDestroyPipeline = glad_vkDestroyPipeline;
    glad_debug_vkDestroyPipelineCache = glad_vkDestroyPipelineCache;
    glad_debug_vkDestroyPipelineLayout = glad_vkDestroyPipelineLayout;
    glad_debug_vkDestroyQueryPool = glad_vkDestroyQueryPool;
    glad_debug_vkDestroyRenderPass = glad_vkDestroyRenderPass;
    glad_debug_vkDestroySampler = glad_vkDestroySampler;
    glad_debug_vkDestroySamplerYcbcrConversion = glad_vkDestroySamplerYcbcrConversion;
    glad_debug_vkDestroySemaphore = glad_vkDestroySemaphore;
    glad_debug_vkDestroyShaderModule = glad_vkDestroyShaderModule;
    glad_debug_vkDestroySurfaceKHR = glad_vkDestroySurfaceKHR;
    glad_debug_vkDestroySwapchainKHR = glad_vkDestroySwapchainKHR;
    glad_debug_vkDeviceWaitIdle = glad_vkDeviceWaitIdle;
    glad_debug_vkEndCommandBuffer = glad_vkEndCommandBuffer;
    glad_debug_vkEnumerateDeviceExtensionProperties = glad_vkEnumerateDeviceExtensionProperties;
    glad_debug_vkEnumerateDeviceLayerProperties = glad_vkEnumerateDeviceLayerProperties;
    glad_debug_vkEnumerateInstanceExtensionProperties = glad_vkEnumerateInstanceExtensionProperties;
    glad_debug_vkEnumerateInstanceLayerProperties = glad_vkEnumerateInstanceLayerProperties;
    glad_debug_vkEnumerateInstanceVersion = glad_vkEnumerateInstanceVersion;
    glad_debug_vkEnumeratePhysicalDeviceGroups = glad_vkEnumeratePhysicalDeviceGroups;
    glad_debug_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = glad_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR;
    glad_debug_vkEnumeratePhysicalDevices = glad_vkEnumeratePhysicalDevices;
    glad_debug_vkFlushMappedMemoryRanges = glad_vkFlushMappedMemoryRanges;
    glad_debug_vkFreeCommandBuffers = glad_vkFreeCommandBuffers;
    glad_debug_vkFreeDescriptorSets = glad_vkFreeDescriptorSets;
    glad_debug_vkFreeMemory = glad_vkFreeMemory;
    glad_debug_vkGetBufferDeviceAddress = glad_vkGetBufferDeviceAddress;
    glad_debug_vkGetBufferMemoryRequirements = glad_vkGetBufferMemoryRequirements;
    glad_debug_vkGetBufferMemoryRequirements2 = glad_vkGetBufferMemoryRequirements2;
    glad_debug_vkGetBufferOpaqueCaptureAddress = glad_vkGetBufferOpaqueCaptureAddress;
    glad_debug_vkGetDescriptorSetLayoutSupport = glad_vkGetDescriptorSetLayoutSupport;
    glad_debug_vkGetDeviceGroupPeerMemoryFeatures = glad_vkGetDeviceGroupPeerMemoryFeatures;
    glad_debug_vkGetDeviceGroupPeerMemoryFeaturesKHR = glad_vkGetDeviceGroupPeerMemoryFeaturesKHR;
    glad_debug_vkGetDeviceGroupPresentCapabilitiesKHR = glad_vkGetDeviceGroupPresentCapabilitiesKHR;
    glad_debug_vkGetDeviceGroupSurfacePresentModesKHR = glad_vkGetDeviceGroupSurfacePresentModesKHR;
    glad_debug_vkGetDeviceMemoryCommitment = glad_vkGetDeviceMemoryCommitment;
    glad_debug_vkGetDeviceMemoryOpaqueCaptureAddress = glad_vkGetDeviceMemoryOpaqueCaptureAddress;
    glad_debug_vkGetDeviceProcAddr = glad_vkGetDeviceProcAddr;
    glad_debug_vkGetDeviceQueue = glad_vkGetDeviceQueue;
    glad_debug_vkGetDeviceQueue2 = glad_vkGetDeviceQueue2;
    glad_debug_vkGetEventStatus = glad_vkGetEventStatus;
    glad_debug_vkGetFenceStatus = glad_vkGetFenceStatus;
    glad_debug_vkGetImageMemoryRequirements = glad_vkGetImageMemoryRequirements;
    glad_debug_vkGetImageMemoryRequirements2 = glad_vkGetImageMemoryRequirements2;
    glad_debug_vkGetImageSparseMemoryRequirements = glad_vkGetImageSparseMemoryRequirements;
    glad_debug_vkGetImageSparseMemoryRequirements2 = glad_vkGetImageSparseMemoryRequirements2;
    glad_debug_vkGetImageSubresourceLayout = glad_vkGetImageSubresourceLayout;
    glad_debug_vkGetInstanceProcAddr = glad_vkGetInstanceProcAddr;
    glad_debug_vkGetPhysicalDeviceExternalBufferProperties = glad_vkGetPhysicalDeviceExternalBufferProperties;
    glad_debug_vkGetPhysicalDeviceExternalFenceProperties = glad_vkGetPhysicalDeviceExternalFenceProperties;
    glad_debug_vkGetPhysicalDeviceExternalSemaphoreProperties = glad_vkGetPhysicalDeviceExternalSemaphoreProperties;
    glad_debug_vkGetPhysicalDeviceFeatures = glad_vkGetPhysicalDeviceFeatures;
    glad_debug_vkGetPhysicalDeviceFeatures2 = glad_vkGetPhysicalDeviceFeatures2;
    glad_debug_vkGetPhysicalDeviceFormatProperties = glad_vkGetPhysicalDeviceFormatProperties;
    glad_debug_vkGetPhysicalDeviceFormatProperties2 = glad_vkGetPhysicalDeviceFormatProperties2;
    glad_debug_vkGetPhysicalDeviceImageFormatProperties = glad_vkGetPhysicalDeviceImageFormatProperties;
    glad_debug_vkGetPhysicalDeviceImageFormatProperties2 = glad_vkGetPhysicalDeviceImageFormatProperties2;
    glad_debug_vkGetPhysicalDeviceMemoryProperties = glad_vkGetPhysicalDeviceMemoryProperties;
    glad_debug_vkGetPhysicalDeviceMemoryProperties2 = glad_vkGetPhysicalDeviceMemoryProperties2;
    glad_debug_vkGetPhysicalDevicePresentRectanglesKHR = glad_vkGetPhysicalDevicePresentRectanglesKHR;
    glad_debug_vkGetPhysicalDeviceProperties = glad_vkGetPhysicalDeviceProperties;
    glad_debug_vkGetPhysicalDeviceProperties2 = glad_vkGetPhysicalDeviceProperties2;
    glad_debug_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR = glad_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR;
    glad_debug_vkGetPhysicalDeviceQueueFamilyProperties = glad_vkGetPhysicalDeviceQueueFamilyProperties;
    glad_debug_vkGetPhysicalDeviceQueueFamilyProperties2 = glad_vkGetPhysicalDeviceQueueFamilyProperties2;
    glad_debug_vkGetPhysicalDeviceSparseImageFormatProperties = glad_vkGetPhysicalDeviceSparseImageFormatProperties;
    glad_debug_vkGetPhysicalDeviceSparseImageFormatProperties2 = glad_vkGetPhysicalDeviceSparseImageFormatProperties2;
    glad_debug_vkGetPhysicalDeviceSurfaceCapabilitiesKHR = glad_vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
    glad_debug_vkGetPhysicalDeviceSurfaceFormatsKHR = glad_vkGetPhysicalDeviceSurfaceFormatsKHR;
    glad_debug_vkGetPhysicalDeviceSurfacePresentModesKHR = glad_vkGetPhysicalDeviceSurfacePresentModesKHR;
    glad_debug_vkGetPhysicalDeviceSurfaceSupportKHR = glad_vkGetPhysicalDeviceSurfaceSupportKHR;
    glad_debug_vkGetPipelineCacheData = glad_vkGetPipelineCacheData;
    glad_debug_vkGetPipelineExecutableInternalRepresentationsKHR = glad_vkGetPipelineExecutableInternalRepresentationsKHR;
    glad_debug_vkGetPipelineExecutablePropertiesKHR = glad_vkGetPipelineExecutablePropertiesKHR;
    glad_debug_vkGetPipelineExecutableStatisticsKHR = glad_vkGetPipelineExecutableStatisticsKHR;
    glad_debug_vkGetQueryPoolResults = glad_vkGetQueryPoolResults;
    glad_debug_vkGetRenderAreaGranularity = glad_vkGetRenderAreaGranularity;
    glad_debug_vkGetSemaphoreCounterValue = glad_vkGetSemaphoreCounterValue;
    glad_debug_vkGetSwapchainImagesKHR = glad_vkGetSwapchainImagesKHR;
    glad_debug_vkGetSwapchainStatusKHR = glad_vkGetSwapchainStatusKHR;
    glad_debug_vkInvalidateMappedMemoryRanges = glad_vkInvalidateMappedMemoryRanges;
    glad_debug_vkMapMemory = glad_vkMapMemory;
    glad_debug_vkMergePipelineCaches = glad_vkMergePipelineCaches;
    glad_debug_vkQueueBeginDebugUtilsLabelEXT = glad_vkQueueBeginDebugUtilsLabelEXT;
    glad_debug_vkQueueBindSparse = glad_vkQueueBindSparse;
    glad_debug_vkQueueEndDebugUtilsLabelEXT = glad_vkQueueEndDebugUtilsLabelEXT;
    glad_debug_vkQueueInsertDebugUtilsLabelEXT = glad_vkQueueInsertDebugUtilsLabelEXT;
    glad_debug_vkQueuePresentKHR = glad_vkQueuePresentKHR;
    glad_debug_vkQueueSubmit = glad_vkQueueSubmit;
    glad_debug_vkQueueWaitIdle = glad_vkQueueWaitIdle;
    glad_debug_vkReleaseProfilingLockKHR = glad_vkReleaseProfilingLockKHR;
    glad_debug_vkResetCommandBuffer = glad_vkResetCommandBuffer;
    glad_debug_vkResetCommandPool = glad_vkResetCommandPool;
    glad_debug_vkResetDescriptorPool = glad_vkResetDescriptorPool;
    glad_debug_vkResetEvent = glad_vkResetEvent;
    glad_debug_vkResetFences = glad_vkResetFences;
    glad_debug_vkResetQueryPool = glad_vkResetQueryPool;
    glad_debug_vkSetDebugUtilsObjectNameEXT = glad_vkSetDebugUtilsObjectNameEXT;
    glad_debug_vkSetDebugUtilsObjectTagEXT = glad_vkSetDebugUtilsObjectTagEXT;
    glad_debug_vkSetEvent = glad_vkSetEvent;
    glad_debug_vkSignalSemaphore = glad_vkSignalSemaphore;
    glad_debug_vkSubmitDebugUtilsMessageEXT = glad_vkSubmitDebugUtilsMessageEXT;
    glad_debug_vkTrimCommandPool = glad_vkTrimCommandPool;
    glad_debug_vkUnmapMemory = glad_vkUnmapMemory;
    glad_debug_vkUpdateDescriptorSetWithTemplate = glad_vkUpdateDescriptorSetWithTemplate;
    glad_debug_vkUpdateDescriptorSets = glad_vkUpdateDescriptorSets;
    glad_debug_vkWaitForFences = glad_vkWaitForFences;
    glad_debug_vkWaitSemaphores = glad_vkWaitSemaphores;
}

#ifdef GLAD_VULKAN

#ifndef GLAD_LOADER_LIBRARY_C_
#define GLAD_LOADER_LIBRARY_C_

#include <stddef.h>
#include <stdlib.h>

#if GLAD_PLATFORM_WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif


static void* glad_get_dlopen_handle(const char *lib_names[], int length) {
    void *handle = NULL;
    int i;

    for (i = 0; i < length; ++i) {
#if GLAD_PLATFORM_WIN32
  #if GLAD_PLATFORM_UWP
        size_t buffer_size = (strlen(lib_names[i]) + 1) * sizeof(WCHAR);
        LPWSTR buffer = (LPWSTR) malloc(buffer_size);
        if (buffer != NULL) {
            int ret = MultiByteToWideChar(CP_ACP, 0, lib_names[i], -1, buffer, buffer_size);
            if (ret != 0) {
                handle = (void*) LoadPackagedLibrary(buffer, 0);
            }
            free((void*) buffer);
        }
  #else
        handle = (void*) LoadLibraryA(lib_names[i]);
  #endif
#else
        handle = dlopen(lib_names[i], RTLD_LAZY | RTLD_LOCAL);
#endif
        if (handle != NULL) {
            return handle;
        }
    }

    return NULL;
}

static void glad_close_dlopen_handle(void* handle) {
    if (handle != NULL) {
#if GLAD_PLATFORM_WIN32
        FreeLibrary((HMODULE) handle);
#else
        dlclose(handle);
#endif
    }
}

static GLADapiproc glad_dlsym_handle(void* handle, const char *name) {
    if (handle == NULL) {
        return NULL;
    }

#if GLAD_PLATFORM_WIN32
    return (GLADapiproc) GetProcAddress((HMODULE) handle, name);
#else
    return GLAD_GNUC_EXTENSION (GLADapiproc) dlsym(handle, name);
#endif
}

#endif /* GLAD_LOADER_LIBRARY_C_ */


static const char* DEVICE_FUNCTIONS[] = {
    "vkAcquireNextImage2KHR",
    "vkAcquireNextImageKHR",
    "vkAcquireProfilingLockKHR",
    "vkAllocateCommandBuffers",
    "vkAllocateDescriptorSets",
    "vkAllocateMemory",
    "vkBeginCommandBuffer",
    "vkBindBufferMemory",
    "vkBindBufferMemory2",
    "vkBindImageMemory",
    "vkBindImageMemory2",
    "vkCmdBeginDebugUtilsLabelEXT",
    "vkCmdBeginQuery",
    "vkCmdBeginRenderPass",
    "vkCmdBeginRenderPass2",
    "vkCmdBindDescriptorSets",
    "vkCmdBindIndexBuffer",
    "vkCmdBindPipeline",
    "vkCmdBindVertexBuffers",
    "vkCmdBlitImage",
    "vkCmdClearAttachments",
    "vkCmdClearColorImage",
    "vkCmdClearDepthStencilImage",
    "vkCmdCopyBuffer",
    "vkCmdCopyBufferToImage",
    "vkCmdCopyImage",
    "vkCmdCopyImageToBuffer",
    "vkCmdCopyQueryPoolResults",
    "vkCmdDebugMarkerBeginEXT",
    "vkCmdDebugMarkerEndEXT",
    "vkCmdDebugMarkerInsertEXT",
    "vkCmdDispatch",
    "vkCmdDispatchBase",
    "vkCmdDispatchBaseKHR",
    "vkCmdDispatchIndirect",
    "vkCmdDraw",
    "vkCmdDrawIndexed",
    "vkCmdDrawIndexedIndirect",
    "vkCmdDrawIndexedIndirectCount",
    "vkCmdDrawIndirect",
    "vkCmdDrawIndirectCount",
    "vkCmdEndDebugUtilsLabelEXT",
    "vkCmdEndQuery",
    "vkCmdEndRenderPass",
    "vkCmdEndRenderPass2",
    "vkCmdExecuteCommands",
    "vkCmdFillBuffer",
    "vkCmdInsertDebugUtilsLabelEXT",
    "vkCmdNextSubpass",
    "vkCmdNextSubpass2",
    "vkCmdPipelineBarrier",
    "vkCmdPushConstants",
    "vkCmdResetEvent",
    "vkCmdResetQueryPool",
    "vkCmdResolveImage",
    "vkCmdSetBlendConstants",
    "vkCmdSetDepthBias",
    "vkCmdSetDepthBounds",
    "vkCmdSetDeviceMask",
    "vkCmdSetDeviceMaskKHR",
    "vkCmdSetEvent",
    "vkCmdSetLineWidth",
    "vkCmdSetScissor",
    "vkCmdSetStencilCompareMask",
    "vkCmdSetStencilReference",
    "vkCmdSetStencilWriteMask",
    "vkCmdSetViewport",
    "vkCmdUpdateBuffer",
    "vkCmdWaitEvents",
    "vkCmdWriteTimestamp",
    "vkCreateBuffer",
    "vkCreateBufferView",
    "vkCreateCommandPool",
    "vkCreateComputePipelines",
    "vkCreateDescriptorPool",
    "vkCreateDescriptorSetLayout",
    "vkCreateDescriptorUpdateTemplate",
    "vkCreateEvent",
    "vkCreateFence",
    "vkCreateFramebuffer",
    "vkCreateGraphicsPipelines",
    "vkCreateImage",
    "vkCreateImageView",
    "vkCreatePipelineCache",
    "vkCreatePipelineLayout",
    "vkCreateQueryPool",
    "vkCreateRenderPass",
    "vkCreateRenderPass2",
    "vkCreateSampler",
    "vkCreateSamplerYcbcrConversion",
    "vkCreateSemaphore",
    "vkCreateShaderModule",
    "vkCreateSwapchainKHR",
    "vkDebugMarkerSetObjectNameEXT",
    "vkDebugMarkerSetObjectTagEXT",
    "vkDestroyBuffer",
    "vkDestroyBufferView",
    "vkDestroyCommandPool",
    "vkDestroyDescriptorPool",
    "vkDestroyDescriptorSetLayout",
    "vkDestroyDescriptorUpdateTemplate",
    "vkDestroyDevice",
    "vkDestroyEvent",
    "vkDestroyFence",
    "vkDestroyFramebuffer",
    "vkDestroyImage",
    "vkDestroyImageView",
    "vkDestroyPipeline",
    "vkDestroyPipelineCache",
    "vkDestroyPipelineLayout",
    "vkDestroyQueryPool",
    "vkDestroyRenderPass",
    "vkDestroySampler",
    "vkDestroySamplerYcbcrConversion",
    "vkDestroySemaphore",
    "vkDestroyShaderModule",
    "vkDestroySwapchainKHR",
    "vkDeviceWaitIdle",
    "vkEndCommandBuffer",
    "vkFlushMappedMemoryRanges",
    "vkFreeCommandBuffers",
    "vkFreeDescriptorSets",
    "vkFreeMemory",
    "vkGetBufferDeviceAddress",
    "vkGetBufferMemoryRequirements",
    "vkGetBufferMemoryRequirements2",
    "vkGetBufferOpaqueCaptureAddress",
    "vkGetDescriptorSetLayoutSupport",
    "vkGetDeviceGroupPeerMemoryFeatures",
    "vkGetDeviceGroupPeerMemoryFeaturesKHR",
    "vkGetDeviceGroupPresentCapabilitiesKHR",
    "vkGetDeviceGroupSurfacePresentModesKHR",
    "vkGetDeviceMemoryCommitment",
    "vkGetDeviceMemoryOpaqueCaptureAddress",
    "vkGetDeviceProcAddr",
    "vkGetDeviceQueue",
    "vkGetDeviceQueue2",
    "vkGetEventStatus",
    "vkGetFenceStatus",
    "vkGetImageMemoryRequirements",
    "vkGetImageMemoryRequirements2",
    "vkGetImageSparseMemoryRequirements",
    "vkGetImageSparseMemoryRequirements2",
    "vkGetImageSubresourceLayout",
    "vkGetPipelineCacheData",
    "vkGetPipelineExecutableInternalRepresentationsKHR",
    "vkGetPipelineExecutablePropertiesKHR",
    "vkGetPipelineExecutableStatisticsKHR",
    "vkGetQueryPoolResults",
    "vkGetRenderAreaGranularity",
    "vkGetSemaphoreCounterValue",
    "vkGetSwapchainImagesKHR",
    "vkGetSwapchainStatusKHR",
    "vkInvalidateMappedMemoryRanges",
    "vkMapMemory",
    "vkMergePipelineCaches",
    "vkQueueBeginDebugUtilsLabelEXT",
    "vkQueueBindSparse",
    "vkQueueEndDebugUtilsLabelEXT",
    "vkQueueInsertDebugUtilsLabelEXT",
    "vkQueuePresentKHR",
    "vkQueueSubmit",
    "vkQueueWaitIdle",
    "vkReleaseProfilingLockKHR",
    "vkResetCommandBuffer",
    "vkResetCommandPool",
    "vkResetDescriptorPool",
    "vkResetEvent",
    "vkResetFences",
    "vkResetQueryPool",
    "vkSetDebugUtilsObjectNameEXT",
    "vkSetDebugUtilsObjectTagEXT",
    "vkSetEvent",
    "vkSignalSemaphore",
    "vkTrimCommandPool",
    "vkUnmapMemory",
    "vkUpdateDescriptorSetWithTemplate",
    "vkUpdateDescriptorSets",
    "vkWaitForFences",
    "vkWaitSemaphores",
};

static int glad_vulkan_is_device_function(const char *name) {
    /* Exists as a workaround for:
     * https://github.com/KhronosGroup/Vulkan-LoaderAndValidationLayers/issues/2323
     *
     * `vkGetDeviceProcAddr` does not return NULL for non-device functions.
     */
    int i;
    int length = sizeof(DEVICE_FUNCTIONS) / sizeof(DEVICE_FUNCTIONS[0]);

    for (i=0; i < length; ++i) {
        if (strcmp(DEVICE_FUNCTIONS[i], name) == 0) {
            return 1;
        }
    }

    return 0;
}

struct _glad_vulkan_userptr {
    void *vk_handle;
    VkInstance vk_instance;
    VkDevice vk_device;
    PFN_vkGetInstanceProcAddr get_instance_proc_addr;
    PFN_vkGetDeviceProcAddr get_device_proc_addr;
};

static GLADapiproc glad_vulkan_get_proc(void *vuserptr, const char *name) {
    struct _glad_vulkan_userptr userptr = *(struct _glad_vulkan_userptr*) vuserptr;
    PFN_vkVoidFunction result = NULL;

    if (userptr.vk_device != NULL && glad_vulkan_is_device_function(name)) {
        result = userptr.get_device_proc_addr(userptr.vk_device, name);
    }

    if (result == NULL && userptr.vk_instance != NULL) {
        result = userptr.get_instance_proc_addr(userptr.vk_instance, name);
    }

    if(result == NULL) {
        result = (PFN_vkVoidFunction) glad_dlsym_handle(userptr.vk_handle, name);
    }

    return (GLADapiproc) result;
}


static void* _vulkan_handle;

static void* glad_vulkan_dlopen_handle(void) {
    static const char *NAMES[] = {
#if GLAD_PLATFORM_APPLE
        "libvulkan.1.dylib",
#elif GLAD_PLATFORM_WIN32
        "vulkan-1.dll",
        "vulkan.dll",
#else
        "libvulkan.so.1",
        "libvulkan.so",
#endif
    };

    if (_vulkan_handle == NULL) {
        _vulkan_handle = glad_get_dlopen_handle(NAMES, sizeof(NAMES) / sizeof(NAMES[0]));
    }

    return _vulkan_handle;
}

static struct _glad_vulkan_userptr glad_vulkan_build_userptr(void *handle, VkInstance instance, VkDevice device) {
    struct _glad_vulkan_userptr userptr;
    userptr.vk_handle = handle;
    userptr.vk_instance = instance;
    userptr.vk_device = device;
    userptr.get_instance_proc_addr = (PFN_vkGetInstanceProcAddr) glad_dlsym_handle(handle, "vkGetInstanceProcAddr");
    userptr.get_device_proc_addr = (PFN_vkGetDeviceProcAddr) glad_dlsym_handle(handle, "vkGetDeviceProcAddr");
    return userptr;
}


#ifdef __cplusplus
static struct _glad_vulkan_userptr glad_vulkan_internal_loader_global_userptr = {};
#else
static struct _glad_vulkan_userptr glad_vulkan_internal_loader_global_userptr = { 0 };
#endif

void gladLoaderSetVulkanInstance(VkInstance instance) {
    glad_vulkan_internal_loader_global_userptr.vk_instance = instance;
}

void gladLoaderSetVulkanDevice(VkDevice device) {
    glad_vulkan_internal_loader_global_userptr.vk_device = device;
}

static GLADapiproc glad_vulkan_internal_loader_get_proc(const char *name) {
    if (glad_vulkan_internal_loader_global_userptr.vk_handle == NULL) {
        glad_vulkan_internal_loader_global_userptr = glad_vulkan_build_userptr(glad_vulkan_dlopen_handle(), NULL, NULL);
    }

    return glad_vulkan_get_proc((void *) &glad_vulkan_internal_loader_global_userptr, name);
}


void gladLoaderUnloadVulkan(void) {
    if (_vulkan_handle != NULL) {
        glad_close_dlopen_handle(_vulkan_handle);
        _vulkan_handle = NULL;
        glad_vulkan_internal_loader_global_userptr.vk_handle = NULL;
    }
}

#endif /* GLAD_VULKAN */

#ifdef __cplusplus
}
#endif
