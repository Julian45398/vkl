#pragma once

#include "vkl_core.h"

namespace vkl {
	inline VkMemoryRequirements getBufferMemoryRequirements(VkDevice device, VkBuffer buffer) {
		assert(device != VK_NULL_HANDLE);
		assert(buffer != VK_NULL_HANDLE);
		VkMemoryRequirements req;
		VKL_RETURN(vkGetBufferMemoryRequirements(device, buffer, &req), req);
	}
	inline VkMemoryRequirements getImageMemoryRequirements(VkDevice device, VkImage image) {
		assert(device != VK_NULL_HANDLE);
		assert(image != VK_NULL_HANDLE);
		VkMemoryRequirements req;
		VKL_RETURN(vkGetImageMemoryRequirements(device, image, &req), req);
	}
	inline uint32_t findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties)
	{
		assert(physicalDevice != VK_NULL_HANDLE);
		VkPhysicalDeviceMemoryProperties mem_properties;
		vkGetPhysicalDeviceMemoryProperties(physicalDevice, &mem_properties);

		for (uint32_t i = 0; i < mem_properties.memoryTypeCount; i++) {
			if ((typeFilter & (1 << i)) && (mem_properties.memoryTypes[i].propertyFlags & properties) == properties) {
				return i;
			}
		}
		return UINT32_MAX;
	}
	inline VkMemoryAllocateInfo createMemoryAllocateInfo(VkDeviceSize allocationSize, uint32_t memoryTypeIndex, const void* pNext = nullptr) {
		return {
			VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, pNext, allocationSize, memoryTypeIndex
		};
	}
	inline VkDeviceMemory allocateMemory(VkDevice device, const VkMemoryAllocateInfo& info) {
		VkDeviceMemory memory = VK_NULL_HANDLE;
		VKL_RETURN(vkAllocateMemory(device, &info, VKL_Callbacks, &memory), memory);
	}
	inline VkDeviceMemory allocateMemory(VkDevice device, VkDeviceSize allocationSize, uint32_t memoryTypeIndex, const void* pNext = nullptr) {
		VkMemoryAllocateInfo info = createMemoryAllocateInfo(allocationSize, memoryTypeIndex, pNext);
		VkDeviceMemory memory = VK_NULL_HANDLE;
		VKL_RETURN(vkAllocateMemory(device, &info, VKL_Callbacks, &memory), memory);
	}
	inline VkDeviceMemory allocateMemory(VkDevice device, VkPhysicalDevice physicalDevice, const VkMemoryRequirements& memoryRequirements, VkMemoryPropertyFlags properties) {
		return allocateMemory(device, memoryRequirements.size, findMemoryType(physicalDevice, memoryRequirements.memoryTypeBits, properties));
	}
	inline VkDeviceMemory allocateForBuffer(VkDevice device, VkPhysicalDevice physicalDevice, VkBuffer buffer, VkMemoryPropertyFlags properties) {
		return allocateMemory(device, physicalDevice, vkl::getBufferMemoryRequirements(device, buffer), properties);
	}
	inline VkDeviceMemory allocateForImage(VkDevice device, VkPhysicalDevice physicalDevice, VkImage image, VkMemoryPropertyFlags properties) {
		return allocateMemory(device, physicalDevice, getImageMemoryRequirements(device, image), properties);
	}
	inline void freeMemory(VkDevice device, VkDeviceMemory memory) {
		vkFreeMemory(device, memory, VKL_Callbacks);
	}
}