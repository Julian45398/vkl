#pragma once

#include <vulkan/vulkan.h>

#ifndef VKL_ENGINE_NAME
#define VKL_ENGINE_NAME "vkl"
#endif
#ifndef VKL_ENGINE_VERSION
#define VKL_ENGINE_VERSION VK_MAKE_API_VERSION(0, 0, 0, 1)
#endif
#ifndef VKL_APPLICATION_NAME
#define VKL_APPLICATION_NAME "vkl"
#endif
#ifndef VKL_APPLICATION_VERSION
#define VKL_APPLICATION_VERSION VK_MAKE_API_VERSION(0, 0, 0, 1)
#endif

#include <vector>

namespace vkl {
	inline const VkAllocationCallbacks* VKL_Callbacks = nullptr;
	inline void setAllocationCallbacks(const VkAllocationCallbacks* pCallbacks) {
		VKL_Callbacks = pCallbacks;
	}
}