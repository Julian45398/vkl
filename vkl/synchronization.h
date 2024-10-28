#pragma once

#include "vkl_core.h"

namespace vkl {
	inline VkFence createFence(VkDevice device, VkFenceCreateFlags flags = VKL_FLAG_NONE, const void* pNext = nullptr) {
		VkFence fence;
		VkFenceCreateInfo info {
			VK_STRUCTURE_TYPE_FENCE_CREATE_INFO, 
			pNext, flags
		};
		VKL_CHECK(vkCreateFence(device, &info, VKL_Callbacks, &fence), VKL_ERROR_FENCE_CREATION_FAILED);
		return fence;
	}
	inline VkSemaphore createSemaphore(VkDevice device, VkSemaphoreCreateFlags flags = VKL_FLAG_NONE, const void* pNext = nullptr) {
		VkSemaphore semaphore;
		VkSemaphoreCreateInfo info {
			VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, 
			pNext, flags
		};
		VKL_CHECK(vkCreateSemaphore(device, &info, VKL_Callbacks, &semaphore), VKL_ERROR_SEMAPHORE_CREATION_FAILED);
		return semaphore;
	}
}