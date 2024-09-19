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
	inline VkDeviceMemory allocateAndBind(VkDevice device, VkPhysicalDevice physicalDevice, uint32_t bufferCount, const VkBuffer* buffers, uint32_t imageCount, const VkImage* images, VkMemoryPropertyFlags properties) {
		VkMemoryRequirements mem_req{};
		std::vector<VkDeviceSize> offsets(bufferCount + imageCount);
		for (uint32_t i = 0; i < imageCount; ++i) {
			VkMemoryRequirements req = getImageMemoryRequirements(device, images[i]);
			if (mem_req.alignment < req.alignment) {
				mem_req.alignment = req.alignment;
			} 
			VkDeviceSize t = mem_req.size % req.alignment;
			if (t != 0) {
				offsets[i] = mem_req.size + req.alignment - t;
			}
			else {
				offsets[i] = mem_req.size;
			}
			mem_req.size = offsets[i] + req.size;
		}
		for (uint32_t i = 0; i < bufferCount; ++i) {
			VkMemoryRequirements req = getBufferMemoryRequirements(device, buffers[i]);
			if (mem_req.alignment < req.alignment) {
				mem_req.alignment = req.alignment;
			} 
			VkDeviceSize t = mem_req.size % req.alignment;
			if (t != 0) {
				offsets[imageCount + i] = mem_req.size + req.alignment - t;
			}
			else {
				offsets[imageCount + i] = mem_req.size;
			}
			mem_req.size = offsets[imageCount + i] + req.size;
		}
		VkDeviceSize t = mem_req.size % mem_req.alignment;
		if (t != 0) {
			mem_req.size += mem_req.alignment - t;
		}
		VkDeviceMemory memory = allocateMemory(device, physicalDevice, mem_req, properties);
		if (!memory) {
			return VK_NULL_HANDLE;
		}
		for (uint32_t i = 0; i < imageCount; ++i) {
			vkBindImageMemory(device, images[i], memory, offsets[i]);
		}
		for (uint32_t i = 0; i < bufferCount; ++i) {
			vkBindBufferMemory(device, buffers[i], memory, offsets[i + imageCount]);
		}
		return memory;
	}
	inline void freeMemory(VkDevice device, VkDeviceMemory memory) {
		vkFreeMemory(device, memory, VKL_Callbacks);
	}
}