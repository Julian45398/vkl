#pragma once

#include "vkl_core.h"

namespace vkl {
#ifdef VKL_ENABLE_VALIDATION
	inline const char* VKL_VALIDATION_LAYER_NAME = "VK_LAYER_KHRONOS_validation";
	inline VkDebugUtilsMessengerEXT createDebugUtilsMessengerEXT(const VkInstance instance, PFN_vkDebugUtilsMessengerCallbackEXT debug_callback) {
		VkDebugUtilsMessengerCreateInfoEXT create_info = {
			VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT, nullptr, 0,
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
			VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
			debug_callback, nullptr
		};
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

		VkDebugUtilsMessengerEXT messenger;
		if (func != nullptr && func(instance, &create_info, VKL_Callbacks, &messenger) == VK_SUCCESS) {
			return messenger;
		}
		else {
			return VK_NULL_HANDLE;
		}
	}
	inline void destroyDebugUtilsMessengerEXT(const VkInstance instance, VkDebugUtilsMessengerEXT messenger) {
		auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
		if (func != nullptr) {
			func(instance, messenger, VKL_Callbacks);
		}
	}
#endif
#ifdef VKL_ENABLE_VALIDATION
	inline VkInstance createInstance(uint32_t vulkan_version, uint32_t extension_count, const char* const* extensions, PFN_vkDebugUtilsMessengerCallbackEXT debug_callback) {
#else
	inline VkInstance createInstance(uint32_t vulkan_version, uint32_t extension_count, const char* const* extensions) {
#endif
		VkApplicationInfo app_info{
			VK_STRUCTURE_TYPE_APPLICATION_INFO, nullptr, VKL_APPLICATION_NAME, VKL_APPLICATION_VERSION, VKL_ENGINE_NAME, VKL_ENGINE_VERSION, vulkan_version
		};
		
		VkInstanceCreateInfo create_info{};
		create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		create_info.enabledExtensionCount = extension_count;
		create_info.ppEnabledExtensionNames = extensions;

#ifdef VKL_ENABLE_VALIDATION
		VkDebugUtilsMessengerCreateInfoEXT debug_info = {
			VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT, nullptr, 0,
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
			VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
			debug_callback, nullptr
		};

		create_info.pNext = &debug_info;
		create_info.enabledLayerCount = 1;
		create_info.ppEnabledExtensionNames = &VKL_VALIDATION_LAYER_NAME;
#else
		create_info.pNext = nullptr;
		create_info.enabledLayerCount = 0;
		create_info.ppEnabledExtensionNames = nullptr;
#endif
		VkInstance instance;
		if (vkCreateInstance(&create_info, VKL_Callbacks, &instance) != VK_SUCCESS) {
			return VK_NULL_HANDLE;
		}
		else {
			return instance;
		}
	}
	inline void destroyInstance(VkInstance instance) {
		vkDestroyInstance(instance, VKL_Callbacks);
	}
}
