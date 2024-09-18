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

#ifdef VKL_CHECK_SUCCESS
#define VKL_RETURN(X, Y) do {if (X != VK_SUCCESS) {return VK_NULL_HANDLE;} else {return Y;} } while (0)
#else
#define VKL_RETURN(X, Y) do { X; return Y; } while (0)
#endif

namespace vkl {
#ifdef VKL_ENABLE_VALIDATION
	inline const char* VKL_VALIDATION_LAYER_NAME = "VK_LAYER_KHRONOS_validation";
#endif
	inline const VkAllocationCallbacks* VKL_Callbacks = nullptr;
	inline void setAllocationCallbacks(const VkAllocationCallbacks* pCallbacks) {
		VKL_Callbacks = pCallbacks;
	}
}