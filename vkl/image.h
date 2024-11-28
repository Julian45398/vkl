#pragma once

#include "vkl_core.h"

namespace vkl {
	inline VkSamplerCreateInfo createSamplerInfo(VkFilter magFilter, VkFilter minFilter, VkSamplerMipmapMode mipmapMode, VkSamplerAddressMode addressModeU, VkSamplerAddressMode addressModeV,
		VkSamplerAddressMode addressModeW, float mipLodBias, VkBool32 anisotropyEnable, float maxAnisotropy, VkBool32 compareEnable, VkCompareOp compareOp, float minLod, float maxLod,
		VkBorderColor borderColor, VkBool32 unnormalizedCoordinates, VkSamplerCreateFlags flags = VKL_FLAG_NONE, const void* pNext = nullptr) {
		return {
			VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO, pNext, flags,
			magFilter, minFilter,
			mipmapMode, addressModeU, addressModeV, addressModeW, mipLodBias,
			anisotropyEnable, maxAnisotropy, compareEnable,
			compareOp, minLod, maxLod, borderColor, unnormalizedCoordinates,
		};
	}
	inline VkSamplerCreateInfo createSamplerInfo(VkFilter filterType, VkSamplerMipmapMode mipmapMode, VkSamplerAddressMode addressMode, 
		float mipLodBias = 0.0f, VkBool32 anisotropyEnable = VK_FALSE, float maxAnisotropy = 0.0f, VkBool32 compareEnable = VK_FALSE, VkCompareOp compareOp = VK_COMPARE_OP_ALWAYS, float minLod = 0.0f, float maxLod = 0.0f, VkBorderColor borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK, VkBool32 unnormalizedCoordinates = VK_FALSE,
		VkSamplerCreateFlags flags = VKL_FLAG_NONE, const void* pNext = nullptr) {
		return createSamplerInfo(filterType, filterType, mipmapMode, addressMode, addressMode, addressMode, mipLodBias, anisotropyEnable, maxAnisotropy, compareEnable, compareOp, minLod, maxLod, borderColor, unnormalizedCoordinates, flags, pNext);
	}
	inline VkSampler createSampler(VkDevice device, const VkSamplerCreateInfo& info) {
		VkSampler sampler;
		VKL_CHECK(vkCreateSampler(device, &info, VKL_Callbacks, &sampler), VKL_ERROR_SAMPLER_CREATION_FAILED);
		return sampler;
	}
	inline VkSampler createSampler(VkDevice device, VkFilter filterType, VkSamplerMipmapMode mipmapMode, VkSamplerAddressMode addressMode,
		float mipLodBias = 0.0f, VkBool32 anisotropyEnable = VK_FALSE, float maxAnisotropy = 0.0f, VkBool32 compareEnable = VK_FALSE, VkCompareOp compareOp = VK_COMPARE_OP_ALWAYS, float minLod = 0.0f, float maxLod = 0.0f, VkBorderColor borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK, VkBool32 unnormalizedCoordinates = VK_FALSE,
		VkSamplerCreateFlags flags = VKL_FLAG_NONE, const void* pNext = nullptr) {
		VkSamplerCreateInfo info = createSamplerInfo(filterType, mipmapMode, addressMode, mipLodBias, anisotropyEnable, maxAnisotropy, compareEnable, compareOp, minLod, maxLod, borderColor, unnormalizedCoordinates, flags, pNext);
		return createSampler(device, info);
	}
	inline VkSampler createSampler(VkDevice device, VkFilter magFilter, VkFilter minFilter, VkSamplerMipmapMode mipmapMode, VkSamplerAddressMode addressModeU, VkSamplerAddressMode addressModeV,
		VkSamplerAddressMode addressModeW, float mipLodBias, VkBool32 anisotropyEnable, float maxAnisotropy, VkBool32 compareEnable, VkCompareOp compareOp, float minLod, float maxLod,
		VkBorderColor borderColor, VkBool32 unnormalizedCoordinates, VkSamplerCreateFlags flags = VKL_FLAG_NONE, const void* pNext = nullptr) {
		VkSamplerCreateInfo info = createSamplerInfo(magFilter, minFilter, mipmapMode, addressModeU, addressModeV, addressModeW, mipLodBias,
			anisotropyEnable, maxAnisotropy, compareEnable, compareOp, minLod, maxLod, borderColor, unnormalizedCoordinates, flags, pNext);
		return createSampler(device, info);
	}
	inline void destroySampler(VkDevice device, VkSampler sampler) {
		VKL_CHECK(vkDestroySampler(device, sampler, VKL_Callbacks), VKL_ERROR_SAMPLER_DESTRUCTION_FAILED);
	}
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
		VkImageView view;
		VKL_CHECK(vkCreateImageView(device, &info, VKL_Callbacks, &view), VKL_ERROR_IMAGE_VIEW_CREATION_FAILED);
		return view;
	}
	inline VkImageView createImageView(VkDevice device, VkImage image, VkImageViewType viewType, VkFormat format, VkComponentMapping components, VkImageSubresourceRange subresourceRange, VkImageViewCreateFlags flags = VKL_FLAG_NONE, const void* pNext = nullptr) {
		VkImageViewCreateInfo info = createImageViewInfo(image, viewType, format, components, subresourceRange, flags, pNext);
		VkImageView view;
		VKL_CHECK(vkCreateImageView(device, &info, VKL_Callbacks, &view), VKL_ERROR_IMAGE_VIEW_CREATION_FAILED);
		return view;
	}
	inline VkImageView createImageView(VkDevice device, VkImage image, VkFormat format = VK_FORMAT_R8G8B8A8_SRGB, VkImageAspectFlags imageAspect = VK_IMAGE_ASPECT_COLOR_BIT, uint32_t mipLevel = 0, uint32_t levelCount = 1, uint32_t arrayLayer = 0, uint32_t layerCount = 1, VkImageViewType viewType = VK_IMAGE_VIEW_TYPE_2D) {
		return vkl::createImageView(device, image, viewType, format, { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY }, { imageAspect, mipLevel, levelCount, arrayLayer, layerCount });
	}
	inline VkImageView createImageView(VkDevice device, VkImage image, VkFormat format, const VkImageSubresourceRange& subresourceRange, VkImageViewType viewType = VK_IMAGE_VIEW_TYPE_2D) {
		return vkl::createImageView(device, image, viewType, format, { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY }, subresourceRange);
	}
	inline VkImage createImage(VkDevice device, const VkImageCreateInfo& info) {
		VkImage image;
		VKL_CHECK(vkCreateImage(device, &info, VKL_Callbacks, &image), VKL_ERROR_IMAGE_CREATION_FAILED);
		return image;
	}
	inline VkImage createImage(VkDevice device, VkImageType imageType, VkFormat format, const VkExtent3D& extent, VkImageUsageFlags usage, uint32_t mipLevels = 1, uint32_t arrayLayers = 1, VkSampleCountFlags samples = VK_SAMPLE_COUNT_1_BIT, VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL, VkImageCreateFlags flags = VKL_FLAG_NONE, const void* pNext = nullptr) {
		VkImageCreateInfo info = createImageInfo(imageType, format, extent, mipLevels, arrayLayers, samples, tiling, usage, flags, pNext);
		VkImage image;
		VKL_CHECK(vkCreateImage(device, &info, VKL_Callbacks, &image), VKL_ERROR_IMAGE_CREATION_FAILED);
		return image;
	}
	inline VkImage createImage2D(VkDevice device, VkFormat format, uint32_t width, uint32_t height, VkImageUsageFlags usage, uint32_t mipLevels = 1, uint32_t arrayLayers = 1, VkSampleCountFlags samples = VK_SAMPLE_COUNT_1_BIT, VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL, VkImageCreateFlags flags = VKL_FLAG_NONE, const void* pNext = nullptr) {
		return createImage(device, VK_IMAGE_TYPE_2D, format, { width, height, 1 }, usage, mipLevels, arrayLayers, samples, tiling, flags, pNext);
	}
	inline void destroyImage(VkDevice device, VkImage image) {
		vkDestroyImage(device, image, VKL_Callbacks);
	}
	inline void destroyImageView(VkDevice device, VkImageView imageView) {
		vkDestroyImageView(device, imageView, VKL_Callbacks);
	}
}