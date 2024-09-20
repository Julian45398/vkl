#pragma once

#include "vkl_core.h"

namespace vkl {
	inline VkImageCreateInfo createImageInfo(VkImageType imageType, VkFormat format, VkExtent3D extent, uint32_t mipLevels, uint32_t arrayLayers, VkSampleCountFlags samples, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags = VKL_FLAG_NONE, const void* pNext = nullptr) {
		return {
			VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO, pNext,
			flags, imageType, format, extent, mipLevels, arrayLayers, (VkSampleCountFlagBits)samples, tiling, usage
		};
	}
	inline VkImageViewCreateInfo createImageViewInfo(VkImage image, VkImageViewType viewType, VkFormat format, VkComponentMapping components, VkImageSubresourceRange subresourceRange, VkImageViewCreateFlags flags = VKL_FLAG_NONE, const void* pNext = nullptr) {
		return {
			VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO, pNext, flags, image, viewType, format, components, subresourceRange
		};
	}
	inline VkImageView createImageView(VkDevice device, const VkImageViewCreateInfo& info) {
		VkImageView view = VK_NULL_HANDLE;
		VKL_RETURN(vkCreateImageView(device, &info, VKL_Callbacks, &view), view);
	}
	inline VkImageView createImageView(VkDevice device, VkImage image, VkImageViewType viewType, VkFormat format, VkComponentMapping components, VkImageSubresourceRange subresourceRange, VkImageViewCreateFlags flags = VKL_FLAG_NONE, const void* pNext = nullptr) {
		VkImageViewCreateInfo info = createImageViewInfo(image, viewType, format, components, subresourceRange, flags, pNext);
		VkImageView view = VK_NULL_HANDLE;
		VKL_RETURN(vkCreateImageView(device, &info, VKL_Callbacks, &view), view);
	}
	inline VkImage createImage(VkDevice device, const VkImageCreateInfo& info) {
		VkImage image = VK_NULL_HANDLE;
		VKL_RETURN(vkCreateImage(device, &info, VKL_Callbacks, &image), image);
	}
	inline VkImage createImage(VkDevice device, VkImageType imageType, VkFormat format, VkExtent3D extent, uint32_t mipLevels, uint32_t arrayLayers, VkSampleCountFlags samples, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags = VKL_FLAG_NONE, const void* pNext = nullptr) {
		VkImageCreateInfo info = createImageInfo(imageType, format, extent, mipLevels, arrayLayers, samples, tiling, usage, flags, pNext);
		VkImage image = VK_NULL_HANDLE;
		VKL_RETURN(vkCreateImage(device, &info, VKL_Callbacks, &image), image);
	}
	inline void destroyImage(VkDevice device, VkImage image) {
		vkDestroyImage(device, image, VKL_Callbacks);
	}
}