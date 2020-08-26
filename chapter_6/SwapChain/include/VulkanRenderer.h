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
#include "VulkanSwapChain.h"

// Number of samples needs to be the same at image creation
// Used at renderpass creation (in attachment) and pipeline creation
#define NUM_SAMPLES VK_SAMPLE_COUNT_1_BIT

// The Vulkan Renderer is custom class, it is not a Vulkan specific class.
// It works as a presentation manager.
// It manages the presentation windows and drawing surfaces.
class VulkanRenderer
{
public:
	VulkanRenderer(VulkanApplication* app, VulkanDevice* deviceObject);
	~VulkanRenderer();

public:
	//Simple life cycle
	void initialize();
	bool render();

	// Create an empty window
	// 创建空白窗口
	void createPresentationWindow(const int& windowWidth = 500, const int& windowHeight = 500);
	void setImageLayout(VkImage image, VkImageAspectFlags aspectMask, VkImageLayout oldImageLayout, VkImageLayout newImageLayout, VkAccessFlagBits srcAccessMask, const VkCommandBuffer& cmdBuf);

	//! Windows procedure method for handling events.
	// 处理窗口事件的windows回调函数
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// Destroy the presentation window
	void destroyPresentationWindow();

	// Getter functions for member variable specific to classes.
	inline VulkanApplication* getApplication()		{ return application; }
	inline VulkanDevice*  getDevice()				{ return deviceObj; }
	inline VulkanSwapChain*  getSwapChain() 		{ return swapChainObj; }

	// 创建Command Pool
	void createCommandPool();							// Create command pool
	// 创建swapchain颜色和深度图
	void buildSwapChainAndDepthImage();					// Create swapchain color image and depth image
	// 创建深度图
	void createDepthImage();							// Create depth image

	void destroyCommandBuffer();
	void destroyCommandPool();
	void destroyDepthBuffer();

public:
#ifdef _WIN32
#define APP_NAME_STR_LEN 80
	// hInstance - Windows 实例
	HINSTANCE					connection;				// hInstance - Windows Instance
	// name - 窗口显示的应用程序名称
	char						name[APP_NAME_STR_LEN]; // name - App name appearing on the window
	// hWnd - 窗口的句柄
	HWND						window;					// hWnd - the window handle
#else
	xcb_connection_t*			connection;
	xcb_screen_t*				screen;
	xcb_window_t				window;
	xcb_intern_atom_reply_t*	reply;
#endif

	// 深度图像的数据结构
	struct{
		VkFormat		format;
		VkImage			image;
		VkDeviceMemory	mem;
		VkImageView		view;
	}Depth;

	// 深度图的 command buffer
	VkCommandBuffer		cmdDepthImage;	// Command buffer for depth image layout
	// command pool
	VkCommandPool		cmdPool;		// Command pool

	// 窗口宽度和高度
	int					width, height;

private:
	VulkanApplication* application;
	// The device object associated with this Presentation layer.
	VulkanDevice*	   deviceObj;
	VulkanSwapChain*   swapChainObj;
};