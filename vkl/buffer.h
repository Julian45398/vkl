#pragma once

#include "vkl_core.h"

namespace vkl {
	inline VkBufferCreateInfo createBufferInfo(VkBufferCreateFlags flags, VkDeviceSize size, VkBufferUsageFlags usage, VkSharingMode sharingMode, uint32_t queueFamilyIndexCount, const uint32_t* pQueueFamilyIndices, const void* pNext = nullptr) {
		return {
			VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO, pNext, flags, size, usage, sharingMode, queueFamilyIndexCount, pQueueFamilyIndices 
		};
	}
	inline VkBuffer createBuffer(VkDevice device, const VkBufferCreateInfo& createInfo) {
		VkBuffer buffer = VK_NULL_HANDLE;
		VKL_RETURN(vkCreateBuffer(device, &createInfo, VKL_Callbacks, &buffer), buffer);
		return buffer;
	}
	inline VkBuffer createBufferInfo(VkDevice device, VkBufferCreateFlags flags, VkDeviceSize size, VkBufferUsageFlags usage, VkSharingMode sharingMode, uint32_t queueFamilyIndexCount, const uint32_t* pQueueFamilyIndices, const void* pNext = nullptr) {
		VkBufferCreateInfo info = createBufferInfo(flags, size, usage, sharingMode, queueFamilyIndexCount, pQueueFamilyIndices, pNext);
		VkBuffer buffer = VK_NULL_HANDLE;
		VKL_RETURN(vkCreateBuffer(device, &info, VKL_Callbacks, &buffer), buffer);
	}
	inline void destroyBuffer(VkDevice device, VkBuffer buffer) {
		vkDestroyBuffer(device, buffer, VKL_Callbacks);
	}
}