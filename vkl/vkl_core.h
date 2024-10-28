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
#ifndef VKL_FAILED
#error it is required to define the procedure on failure if success checks are enabled!
#define VKL_FAILED(ERROR_MSG)
#endif
#define VKL_CHECK(X, ERROR_MSG) do {if (X != VK_SUCCESS) { VKL_FAILED(ERROR_MSG); } } while (0)
#else
#define VKL_CHECK(X, ERROR_MSG) do { X; } while (0)
#endif

#define VKL_FLAG_NONE 0

namespace vkl {
#ifdef VKL_ENABLE_VALIDATION
	inline const char* VKL_VALIDATION_LAYER_NAME = "VK_LAYER_KHRONOS_validation";
#endif
	inline const VkAllocationCallbacks* VKL_Callbacks = nullptr;
	inline void setAllocationCallbacks(const VkAllocationCallbacks* pCallbacks) {
		VKL_Callbacks = pCallbacks;
	}
}

#include "vkl_error_codes.h"

