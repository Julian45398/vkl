#pragma once

#include "vkl_core.h"

namespace vkl {
	inline VkFence createFence(VkDevice device, VkFenceCreateFlags flags = VKL_FLAG_NONE, const void* pNext = nullptr) {
		VkFence fence = VK_NULL_HANDLE;
		VkFenceCreateInfo info {
			VK_STRUCTURE_TYPE_FENCE_CREATE_INFO, 
			pNext, flags
		};
		VKL_RETURN(vkCreateFence(device, &info, VKL_Callbacks, &fence), fence);
	}
	inline VkSemaphore createSemaphore(VkDevice device, VkSemaphoreCreateFlags flags = VKL_FLAG_NONE, const void* pNext = nullptr) {
		VkSemaphore semaphore = VK_NULL_HANDLE;
		VkSemaphoreCreateInfo info {
			VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, 
			pNext, flags
		};
		VKL_RETURN(vkCreateSemaphore(device, &info, VKL_Callbacks, &semaphore), semaphore);
	}
}