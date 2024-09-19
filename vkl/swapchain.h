#pragma once

#include "vkl_core.h"

namespace vkl {
	inline VkSwapchainKHR createSwapchain(VkDevice device, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkExtent2D extent, uint32_t presentQueueFamilyIndex, uint32_t graphicsQueueFamilyIndex, uint32_t presentModeCount, const VkPresentModeKHR* presentModes, VkSwapchainKHR oldSwapchain = VK_NULL_HANDLE) {
		VkSwapchainCreateInfoKHR create_info{};
		create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		create_info.oldSwapchain = oldSwapchain;
		VkSurfaceCapabilitiesKHR capabilities;
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &capabilities);

		VkPresentModeKHR present_mode = VK_PRESENT_MODE_MAX_ENUM_KHR;
		{
			uint32_t present_mode_count;
			vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &present_mode_count, nullptr);
			std::vector<VkPresentModeKHR> present_modes(present_mode_count);
			if (present_mode_count != 0) {
				vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &present_mode_count, present_modes.data());
			}
			else {
				return VK_NULL_HANDLE;
			}

			for (uint32_t i = 0; i < presentModeCount; ++i) {
				bool present_mode_found = false;
				for (const auto& available_present_mode : present_modes) {
					if (available_present_mode == presentModes[i]) {
						present_mode = available_present_mode;
						present_mode_found = true;
						break;
					}
				}
				if (present_mode_found) {
					break;
				}
			}
			if (present_mode == VK_PRESENT_MODE_MAX_ENUM_KHR) {
				return VK_NULL_HANDLE;
			}
		}
		uint32_t image_count = capabilities.minImageCount + 1;
		if (capabilities.maxImageCount > 0 && image_count > capabilities.maxImageCount) {
			image_count = capabilities.maxImageCount;
		}

		VkSurfaceFormatKHR surface_format;
		{
			uint32_t format_count;
			vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &format_count, nullptr);
			std::vector<VkSurfaceFormatKHR> surface_formats;
			if (format_count != 0) {
				surface_formats.resize(format_count);
				vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &format_count, surface_formats.data());
			}
			else {
				return VK_NULL_HANDLE;
			}
			surface_format = surface_formats[0];
			for (const auto& available_format : surface_formats) {
				if (available_format.format == VK_FORMAT_B8G8R8A8_SRGB && available_format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
				{
					surface_format = available_format;
				}
			}
		}
		VkSwapchainCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = surface;
		createInfo.minImageCount = image_count;
		createInfo.imageFormat = surface_format.format;
		createInfo.imageColorSpace = surface_format.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		if (presentQueueFamilyIndex != graphicsQueueFamilyIndex) {
			uint32_t queueFamilyIndices[] = { graphicsQueueFamilyIndex, presentQueueFamilyIndex };
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else {
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		}

		createInfo.preTransform = capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = present_mode;
		createInfo.clipped = VK_TRUE;

		VkSwapchainKHR swapchain = VK_NULL_HANDLE;
		VKL_RETURN(vkCreateSwapchainKHR(device, &createInfo, VKL_Callbacks, &swapchain), swapchain);
	}
	inline void destroySwapchain(VkDevice device, VkSwapchainKHR swapchain) {
		vkDestroySwapchainKHR(device, swapchain, VKL_Callbacks);
	}
}