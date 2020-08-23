/*
* Learning Vulkan - ISBN: 9781786469809
*
* Author: Parminder Singh, parminder.vulkan@gmail.com
* Linkedin: https://www.linkedin.com/in/parmindersingh18
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include "Headers.h"
class VulkanInstance;
class VulkanDevice;
class VulkanRenderer;
class VulkanApplication;
/*
* Keep each of our swap chain buffers' image, command buffer and view in one spot
*/
struct SwapChainBuffer{
	VkImage image;
	VkImageView view;
};

struct SwapChainPrivateVariables
{
	// Store the image surface capabilities
	// 保存image surface属性
	VkSurfaceCapabilitiesKHR	surfCapabilities;				

	// Stores the number of present mode support by the implementation
	// 保存了 present mode number
	uint32_t					presentModeCount;

	// Arrays for retrived present modes
	// present modes array
	std::vector<VkPresentModeKHR> presentModes;

	// Size of the swap chain color images
	// swap chain color image 的大小
	VkExtent2D					swapChainExtent;

	// Number of color images supported by the implementation
	// 可用的 color image 的数量
	uint32_t					desiredNumberOfSwapChainImages;

	VkSurfaceTransformFlagBitsKHR preTransform;

	// Stores present mode bitwise flag for the creation of swap chain
	// 保存了swap chain创建对应的present mode
	VkPresentModeKHR			swapchainPresentMode;

	// The retrived drawing color swap chain images
	// 获取到的swap chain images
	std::vector<VkImage>		swapchainImages;

	std::vector<VkSurfaceFormatKHR> surfFormats;
};

struct SwapChainPublicVariables
{
	// The logical platform dependent surface object
	// 系统平台相关的surface object
	VkSurfaceKHR surface;

	// Number of buffer image used for swap chain
	// swap chain 用到的 buffer image 的数量
	uint32_t swapchainImageCount;

	// Swap chain object
	// swap chain 对象
	VkSwapchainKHR swapChain;

	// List of color swap chain images
	// swap chain 对象列表
	std::vector<SwapChainBuffer> colorBuffer;

	// Semaphore for sync purpose
	// 同步对象的信号
	VkSemaphore presentCompleteSemaphore;

	// Current drawing surface index in use
	// 当前使用的drawing surface 索引
	uint32_t currentColorBuffer;

	// Format of the image 
	// image的format
	VkFormat format;
};

class VulkanSwapChain{

// Public member function
public:
	VulkanSwapChain(VulkanRenderer* renderer);
	~VulkanSwapChain();
	void intializeSwapChain();
	void createSwapChain(const VkCommandBuffer& cmd);
	void destroySwapChain();


// Private member variables
private:
	VkResult createSwapChainExtensions();
	void getSupportedFormats();
	VkResult createSurface();
	uint32_t getGraphicsQueueWithPresentationSupport();
	void getSurfaceCapabilitiesAndPresentMode();
	void managePresentMode();
	void createSwapChainColorImages();
	void createColorImageView(const VkCommandBuffer& cmd);

// Public member variables
public:
	// User define structure containing public variables used 
	// by the swap chain private and public functions.
	SwapChainPublicVariables	scPublicVars;
	PFN_vkQueuePresentKHR		fpQueuePresentKHR;
	PFN_vkAcquireNextImageKHR	fpAcquireNextImageKHR;

	// Private member variables
private:
	PFN_vkGetPhysicalDeviceSurfaceSupportKHR		fpGetPhysicalDeviceSurfaceSupportKHR;
	PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR	fpGetPhysicalDeviceSurfaceCapabilitiesKHR;
	PFN_vkGetPhysicalDeviceSurfaceFormatsKHR		fpGetPhysicalDeviceSurfaceFormatsKHR;
	PFN_vkGetPhysicalDeviceSurfacePresentModesKHR	fpGetPhysicalDeviceSurfacePresentModesKHR;
	PFN_vkDestroySurfaceKHR							fpDestroySurfaceKHR;

	// Layer Extensions Debugging
	PFN_vkCreateSwapchainKHR	fpCreateSwapchainKHR;
	PFN_vkDestroySwapchainKHR	fpDestroySwapchainKHR;
	PFN_vkGetSwapchainImagesKHR fpGetSwapchainImagesKHR;

	// User define structure containing private variables used 
	// by the swap chain private and public functions.
	SwapChainPrivateVariables	scPrivateVars;
	VulkanRenderer*				rendererObj;	// parent
	VulkanApplication*			appObj;
};
