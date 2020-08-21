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

struct LayerProperties{
	VkLayerProperties properties;
	std::vector<VkExtensionProperties> extensions;
};

class VulkanLayerAndExtension{
public:
	VulkanLayerAndExtension();
	~VulkanLayerAndExtension();

	/******* LAYER AND EXTENSION MEMBER FUNCTION AND VARAIBLES *******/
	
	// List of layer names requested by the application.
	// APP中所需用到的层的名称列表
	std::vector<const char *>			appRequestedLayerNames;
	
	// List of extension names requested by the application.
	// APP中需要用到的扩展的名称列表
	std::vector<const char *>			appRequestedExtensionNames;
	
	// Layers and corresponding extension list
	// 层属性和扩展属性
	std::vector<LayerProperties>		layerPropertyList;

	// Instance/global layer
	// 查询实例和全局的层数
	VkResult getInstanceLayerProperties();
	
	// Global extensions  全局扩展
	VkResult getExtensionProperties(LayerProperties &layerProps, VkPhysicalDevice* gpu = NULL);

	// Device based extensions  基于设备的扩展
	VkResult getDeviceExtensionProperties(VkPhysicalDevice* gpu);
};