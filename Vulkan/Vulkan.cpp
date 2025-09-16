#pragma once
#define VK_USE_PLATFORM_WIN32_KHR
#define VK_NO_PROTOTYPES
#define TW_USE_VULKAN //yaaaay! this will stop Tinywindow from creating a conflicting OpenGL context

#include "TinyWindow.h"
#include <stdio.h>
#include "vulkan.h"
#include <stdlib.h>
#include <fstream>
#include <string>
//#include "VulaknHelper.h"

using namespace TinyWindow;
PFN_vkCreateInstance vkCreateInstance = NULL;
PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = NULL;

//core vulkan extensions
PFN_vkEnumerateInstanceLayerProperties vkEnumerateInstanceLayerProperties = NULL;
PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties = NULL;
PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices = NULL;
PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties = NULL;
PFN_vkGetPhysicalDeviceQueueFamilyProperties vkGetPhysicalDeviceQueueFamilyProperties = NULL;
PFN_vkGetPhysicalDeviceSurfaceSupportKHR vkGetPhysicalDeviceSurfaceSupportKHR = NULL;
PFN_vkCreateDevice vkCreateDevice = NULL;
PFN_vkCmdPipelineBarrier vkCmdPipelineBarrier = NULL;
PFN_vkCreateCommandPool vkCreateCommandPool = NULL;
PFN_vkAllocateCommandBuffers vkAllocateCommandBuffers = NULL;
PFN_vkBeginCommandBuffer vkBeginCommandBuffer = NULL;
PFN_vkEndCommandBuffer vkEndCommandBuffer = NULL;
PFN_vkQueueSubmit vkQueueSubmit = NULL;
PFN_vkGetSwapchainImagesKHR vkGetSwapchainImagesKHR = NULL;
PFN_vkCreateFence vkCreateFence = NULL;
PFN_vkWaitForFences vkWaitForFences = NULL;
PFN_vkResetFences vkResetFences = NULL;
PFN_vkResetCommandBuffer vkResetCommandBuffer = NULL;
PFN_vkCreateImageView vkCreateImageView = NULL;
PFN_vkGetDeviceQueue vkGetDeviceQueue = NULL;
PFN_vkGetPhysicalDeviceMemoryProperties vkGetPhysicalDeviceMemoryProperties = NULL;
PFN_vkCreateImage vkCreateImage = NULL;
PFN_vkGetImageMemoryRequirements vkGetImageMemoryRequirements = NULL;
PFN_vkAllocateMemory vkAllocateMemory = NULL;
PFN_vkBindImageMemory vkBindImageMemory = NULL;
PFN_vkCreateRenderPass vkCreateRenderPass = NULL;
PFN_vkCreateFramebuffer vkCreateFramebuffer = NULL;
PFN_vkCreateBuffer vkCreateBuffer = NULL;
PFN_vkGetBufferMemoryRequirements vkGetBufferMemoryRequirements = NULL;
PFN_vkMapMemory vkMapMemory = NULL;
PFN_vkUnmapMemory vkUnmapMemory = NULL;
PFN_vkBindBufferMemory vkBindBufferMemory = NULL;
PFN_vkCreateShaderModule vkCreateShaderModule = NULL;
PFN_vkCreatePipelineLayout vkCreatePipelineLayout = NULL;
PFN_vkCreateGraphicsPipelines vkCreateGraphicsPipelines = NULL;
PFN_vkCreateSemaphore vkCreateSemaphore = NULL;
PFN_vkCmdBeginRenderPass vkCmdBeginRenderPass = NULL;
PFN_vkCmdBindPipeline vkCmdBindPipeline = NULL;
PFN_vkCmdSetViewport vkCmdSetViewport = NULL;
PFN_vkCmdSetScissor vkCmdSetScissor = NULL;
PFN_vkCmdBindVertexBuffers vkCmdBindVertexBuffers = NULL;
PFN_vkCmdDraw vkCmdDraw = NULL;
PFN_vkCmdEndRenderPass vkCmdEndRenderPass = NULL;
PFN_vkDestroyFence vkDestroyFence = NULL;
PFN_vkDestroySemaphore vkDestroySemaphore = NULL;

//vulkan EXT extensions
PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT = NULL;
PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT = NULL;
PFN_vkDebugReportMessageEXT vkDebugReportMessageEXT = NULL;

//vulkan KHR extensions
PFN_vkAcquireNextImageKHR vkAcquireNextImageKHR = NULL;
PFN_vkQueuePresentKHR vkQueuePresentKHR = NULL;
PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR vkGetPhysicalDeviceSurfaceCapabilitiesKHR = NULL;
PFN_vkGetPhysicalDeviceSurfacePresentModesKHR vkGetPhysicalDeviceSurfacePresentModesKHR = NULL;
PFN_vkCreateSwapchainKHR vkCreateSwapchainKHR = NULL;
PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR = NULL;
PFN_vkGetPhysicalDeviceSurfaceFormatsKHR vkGetPhysicalDeviceSurfaceFormatsKHR = NULL;

VKAPI_ATTR VkBool32 VKAPI_CALL DebugReportCallback(VkDebugReportFlagsEXT flags,
	VkDebugReportObjectTypeEXT objectType, uint64_t object,
	size_t location, int32_t messageCode, const char* layerPrefix,
	const char* message, void* userData)
{
	printf("%s %s \n", layerPrefix, message);
	return VK_FALSE;
}

struct vulkanContext_t
{
	uint32_t width;
	uint32_t height;

	VkInstance								vulkanInstance;
	VkDebugReportCallbackEXT				reportCallback;
	VkSurfaceKHR							surface;
	VkPhysicalDevice						physicalDevice;
	VkDevice								device;
	VkPhysicalDeviceProperties				deviceProps;
	unsigned int							queueIndex;
	VkSwapchainKHR							swapChain;
	VkCommandBuffer							setupCommandBuffer;
	VkCommandBuffer							drawCommandBuffer;
	VkImage*								presentImages;
	VkImage									depthImage;
	VkImageView								depthImageView;
	VkQueue									presentQueue;
	VkPhysicalDeviceMemoryProperties		memoryProperties;
	VkRenderPass							renderPass;
	VkFramebuffer*							framebuffers;
	VkBuffer								vertexInputBuffer;
	VkPipelineLayout						pipelineLayout;
	VkPipeline								pipeline;
	VkViewport								viewport;
	VkRect2D								scissor;

	unsigned int							desiredImageCount;
	VkFormat								colorFormat;
	VkColorSpaceKHR							colorSpace;
	VkExtent2D								surfaceResolution;
	unsigned int							imageArrayLayers;
	VkSurfaceTransformFlagBitsKHR			preTransform;
	VkPresentModeKHR						presentMode;

};

vulkanContext_t context;

//add more events i suppose

//window resized
void HandleWindowResize(TinyWindow::vec2_t<unsigned int> dimensions)
{
	context.width = dimensions.width;
	context.height = dimensions.height;

	//generate fresh setup command buffer object
	//setup swap chain(leave as is?)

	//make image view a global or context member
	//make image a global or context member
	//i wich vulkan had more documentation
	//free device memory?
	//regen depth stencil buffer
	//make framebuffer global or context member
	//make every freaking object in the tutorial a context member
	//you know what? I'm going to turn this into a full blown framework tomorrow and add it to my portfolio. tomorrow :)



	context.surfaceResolution.width = dimensions.width;
	context.surfaceResolution.height = dimensions.height;

	VkSwapchainCreateInfoKHR swapChainCreateInfo = {};
	swapChainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapChainCreateInfo.surface = context.surface;
	swapChainCreateInfo.minImageCount = context.desiredImageCount;
	swapChainCreateInfo.imageFormat = context.colorFormat;
	swapChainCreateInfo.imageColorSpace = context.colorSpace;
	swapChainCreateInfo.imageExtent = context.surfaceResolution;
	swapChainCreateInfo.imageArrayLayers = 1;
	swapChainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	swapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	swapChainCreateInfo.preTransform = context.preTransform;
	swapChainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swapChainCreateInfo.presentMode = context.presentMode;
	swapChainCreateInfo.clipped = true;
	swapChainCreateInfo.oldSwapchain = NULL;

/*
	VkResult result = vkCreateSwapchainKHR(context.device, &swapChainCreateInfo,
		NULL, &context.swapChain);

	if (result != VK_SUCCESS)
	{
		printf("poop \n");
	}*/

	//update vertex buffer?
}
//window maximized



std::string ReadTextFile(const char* fileName)
{
	std::string fileBuffer;
	std::ifstream fileStream(fileName, std::ios::in);
	if (!fileStream.is_open())
	{
		printf("File %s not found", fileName);
		return "";
	}

	std::string currentLine = "";
	while (!fileStream.eof())
	{
		getline(fileStream, currentLine);
		fileBuffer.append(currentLine + "\n");
	}

	fileStream.close();
	return fileBuffer;
}

//load binary file into char buffer (SPIR-V)
char* ReadBinaryFile(const char* fileName, size_t& bufferSize)
{
	long int size;
	size_t returnVal;
	void* shaderBuffer;

	FILE* file = fopen(fileName, "rb");
	if (!file)
	{
		return nullptr;
	}

	fseek(file, 0, SEEK_END); // put file cursor at end of stream
	size = ftell(file); //see how far the cursor traveled (how large the file is)

	fseek(file, 0, SEEK_SET); // put cursor back at beginning

	shaderBuffer = malloc(size); //allocate shaderBuffer a chunk of memory the size of the file
	returnVal = fread(shaderBuffer, size, 1, file); // read the contents of the file from current cursor position (should be beginning) to end

	bufferSize = size;

	return (char*)shaderBuffer;
}

void InitVulkan()
{
	HMODULE vulkanModule = LoadLibrary("vulkan-1.dll");
	if (vulkanModule == nullptr)
	{
		printf("Failed to load vulkan module.");
		return;
	}
	vkCreateInstance = (PFN_vkCreateInstance)GetProcAddress(vulkanModule, "vkCreateInstance");
	vkEnumerateInstanceLayerProperties = (PFN_vkEnumerateInstanceLayerProperties)GetProcAddress(vulkanModule, "vkEnumerateInstanceLayerProperties");
	vkEnumerateInstanceExtensionProperties = (PFN_vkEnumerateInstanceExtensionProperties)GetProcAddress(vulkanModule, "vkEnumerateInstanceExtensionProperties");
	vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)GetProcAddress(vulkanModule, "vkGetInstanceProcAddr");
}

void LoadVulkanExtensions(vulkanContext_t& context)
{
	//load core extensions
	vkEnumeratePhysicalDevices = (PFN_vkEnumeratePhysicalDevices)vkGetInstanceProcAddr(context.vulkanInstance, "vkEnumeratePhysicalDevices");
	vkGetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties)vkGetInstanceProcAddr(context.vulkanInstance, "vkGetPhysicalDeviceProperties");
	vkGetPhysicalDeviceQueueFamilyProperties = (PFN_vkGetPhysicalDeviceQueueFamilyProperties)vkGetInstanceProcAddr(context.vulkanInstance, "vkGetPhysicalDeviceQueueFamilyProperties");
	vkCreateDevice = (PFN_vkCreateDevice)vkGetInstanceProcAddr(context.vulkanInstance, "vkCreateDevice");
	vkCmdPipelineBarrier = (PFN_vkCmdPipelineBarrier)vkGetInstanceProcAddr(context.vulkanInstance, "vkCmdPipelineBarrier");
	vkCreateCommandPool = (PFN_vkCreateCommandPool)vkGetInstanceProcAddr(context.vulkanInstance, "vkCreateCommandPool");
	vkAllocateCommandBuffers = (PFN_vkAllocateCommandBuffers)vkGetInstanceProcAddr(context.vulkanInstance, "vkAllocateCommandBuffers");
	vkBeginCommandBuffer = (PFN_vkBeginCommandBuffer)vkGetInstanceProcAddr(context.vulkanInstance, "vkBeginCommandBuffer");
	vkEndCommandBuffer = (PFN_vkEndCommandBuffer)vkGetInstanceProcAddr(context.vulkanInstance, "vkEndCommandBuffer");
	vkQueueSubmit = (PFN_vkQueueSubmit)vkGetInstanceProcAddr(context.vulkanInstance, "vkQueueSubmit");
	vkCreateFence = (PFN_vkCreateFence)vkGetInstanceProcAddr(context.vulkanInstance, "vkCreateFence");
	vkWaitForFences = (PFN_vkWaitForFences)vkGetInstanceProcAddr(context.vulkanInstance, "vkWaitForFences");
	vkResetFences = (PFN_vkResetFences)vkGetInstanceProcAddr(context.vulkanInstance, "vkResetFences");
	vkResetCommandBuffer = (PFN_vkResetCommandBuffer)vkGetInstanceProcAddr(context.vulkanInstance, "vkResetCommandBuffer");
	vkCreateImageView = (PFN_vkCreateImageView)vkGetInstanceProcAddr(context.vulkanInstance, "vkCreateImageView");
	vkGetDeviceQueue = (PFN_vkGetDeviceQueue)vkGetInstanceProcAddr(context.vulkanInstance, "vkGetDeviceQueue");
	vkGetPhysicalDeviceMemoryProperties = (PFN_vkGetPhysicalDeviceMemoryProperties)vkGetInstanceProcAddr(context.vulkanInstance, "vkGetPhysicalDeviceMemoryProperties");
	vkCreateImage = (PFN_vkCreateImage)vkGetInstanceProcAddr(context.vulkanInstance, "vkCreateImage");
	vkGetImageMemoryRequirements = (PFN_vkGetImageMemoryRequirements)vkGetInstanceProcAddr(context.vulkanInstance, "vkGetImageMemoryRequirements");
	vkAllocateMemory = (PFN_vkAllocateMemory)vkGetInstanceProcAddr(context.vulkanInstance, "vkAllocateMemory");
	vkBindImageMemory = (PFN_vkBindImageMemory)vkGetInstanceProcAddr(context.vulkanInstance, "vkBindImageMemory");
	vkCreateRenderPass = (PFN_vkCreateRenderPass)vkGetInstanceProcAddr(context.vulkanInstance, "vkCreateRenderPass");
	vkCreateFramebuffer = (PFN_vkCreateFramebuffer)vkGetInstanceProcAddr(context.vulkanInstance, "vkCreateFramebuffer");
	vkCreateBuffer = (PFN_vkCreateBuffer)vkGetInstanceProcAddr(context.vulkanInstance, "vkCreateBuffer");
	vkGetBufferMemoryRequirements = (PFN_vkGetBufferMemoryRequirements)vkGetInstanceProcAddr(context.vulkanInstance, "vkGetBufferMemoryRequirements");
	vkMapMemory = (PFN_vkMapMemory)vkGetInstanceProcAddr(context.vulkanInstance, "vkMapMemory");
	vkUnmapMemory = (PFN_vkUnmapMemory)vkGetInstanceProcAddr(context.vulkanInstance, "vkUnmapMemory");
	vkBindBufferMemory = (PFN_vkBindBufferMemory)vkGetInstanceProcAddr(context.vulkanInstance, "vkBindBufferMemory");
	vkCreateShaderModule = (PFN_vkCreateShaderModule)vkGetInstanceProcAddr(context.vulkanInstance, "vkCreateShaderModule");
	vkCreatePipelineLayout = (PFN_vkCreatePipelineLayout)vkGetInstanceProcAddr(context.vulkanInstance, "vkCreatePipelineLayout");
	vkCreateGraphicsPipelines = (PFN_vkCreateGraphicsPipelines)vkGetInstanceProcAddr(context.vulkanInstance, "vkCreateGraphicsPipelines");
	vkCreateSemaphore = (PFN_vkCreateSemaphore)vkGetInstanceProcAddr(context.vulkanInstance, "vkCreateSemaphore");
	vkCmdBeginRenderPass = (PFN_vkCmdBeginRenderPass)vkGetInstanceProcAddr(context.vulkanInstance, "vkCmdBeginRenderPass");
	vkCmdBindPipeline = (PFN_vkCmdBindPipeline)vkGetInstanceProcAddr(context.vulkanInstance, "vkCmdBindPipeline");
	vkCmdSetViewport = (PFN_vkCmdSetViewport)vkGetInstanceProcAddr(context.vulkanInstance, "vkCmdSetViewport");
	vkCmdSetScissor = (PFN_vkCmdSetScissor)vkGetInstanceProcAddr(context.vulkanInstance, "vkCmdSetScissor");
	vkCmdBindVertexBuffers = (PFN_vkCmdBindVertexBuffers)vkGetInstanceProcAddr(context.vulkanInstance, "vkCmdBindVertexBuffers");
	vkCmdDraw = (PFN_vkCmdDraw)vkGetInstanceProcAddr(context.vulkanInstance, "vkCmdDraw");
	vkCmdEndRenderPass = (PFN_vkCmdEndRenderPass)vkGetInstanceProcAddr(context.vulkanInstance, "vkCmdEndRenderPass");
	vkDestroyFence = (PFN_vkDestroyFence)vkGetInstanceProcAddr(context.vulkanInstance, "vkDestroyFence");
	vkDestroySemaphore = (PFN_vkDestroySemaphore)vkGetInstanceProcAddr(context.vulkanInstance, "vkDestroySemaphore");

	//load EXT extensions
	vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(context.vulkanInstance, "vkCreateDebugReportCallbackEXT");
	vkDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(context.vulkanInstance, "vkDestroyDebugReportCallbackEXT");
	vkDebugReportMessageEXT = (PFN_vkDebugReportMessageEXT)vkGetInstanceProcAddr(context.vulkanInstance, "vkDebugReportMessageEXT");

	//load KHR extensions
	vkCreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddr(context.vulkanInstance, "vkCreateWin32SurfaceKHR");
	vkGetPhysicalDeviceSurfaceSupportKHR = (PFN_vkGetPhysicalDeviceSurfaceSupportKHR)vkGetInstanceProcAddr(context.vulkanInstance, "vkGetPhysicalDeviceSurfaceSupportKHR");
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR)vkGetInstanceProcAddr(context.vulkanInstance, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR");
	vkGetPhysicalDeviceSurfacePresentModesKHR = (PFN_vkGetPhysicalDeviceSurfacePresentModesKHR)vkGetInstanceProcAddr(context.vulkanInstance, "vkGetPhysicalDeviceSurfacePresentModesKHR");
	vkCreateSwapchainKHR = (PFN_vkCreateSwapchainKHR)vkGetInstanceProcAddr(context.vulkanInstance, "vkCreateSwapchainKHR");
	vkGetSwapchainImagesKHR = (PFN_vkGetSwapchainImagesKHR)vkGetInstanceProcAddr(context.vulkanInstance, "vkGetSwapchainImagesKHR");
	vkAcquireNextImageKHR = (PFN_vkAcquireNextImageKHR)vkGetInstanceProcAddr(context.vulkanInstance, "vkAcquireNextImageKHR");
	vkQueuePresentKHR = (PFN_vkQueuePresentKHR)vkGetInstanceProcAddr(context.vulkanInstance, "vkQueuePresentKHR");
	vkGetPhysicalDeviceSurfaceFormatsKHR = (PFN_vkGetPhysicalDeviceSurfaceFormatsKHR)vkGetInstanceProcAddr(context.vulkanInstance, "vkGetPhysicalDeviceSurfaceFormatsKHR");
}

void draw()
{
	VkSemaphore presentCompleteSemaphore, renderingCompleteSemaphore;
	VkSemaphoreCreateInfo semaphoreCreateInfo =
	{
		VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, 0, 0
	};
	vkCreateSemaphore(context.device, &semaphoreCreateInfo,
		NULL, &presentCompleteSemaphore);

	vkCreateSemaphore(context.device, &semaphoreCreateInfo,
		NULL, &renderingCompleteSemaphore);

	unsigned int nextImageIndex;
	vkAcquireNextImageKHR(context.device,
		context.swapChain, UINT64_MAX,
		presentCompleteSemaphore, VK_NULL_HANDLE, &nextImageIndex);

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	vkBeginCommandBuffer(context.drawCommandBuffer, &beginInfo);


	VkImageMemoryBarrier layoutTransitionBarrier = {};
	layoutTransitionBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	layoutTransitionBarrier.srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
	layoutTransitionBarrier.dstAccessMask =
		VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	layoutTransitionBarrier.oldLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	layoutTransitionBarrier.newLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
	layoutTransitionBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	layoutTransitionBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	layoutTransitionBarrier.image = context.presentImages[nextImageIndex];

	VkImageSubresourceRange resourceRange =
	{
		VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1
	};
	layoutTransitionBarrier.subresourceRange = resourceRange;

	vkCmdPipelineBarrier(context.drawCommandBuffer,
		VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
		VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
		0, 0, NULL, 0, NULL, 1,
		&layoutTransitionBarrier);

	VkClearValue clearValue[] =
	{
		{0.25f, 0.25f, 0.25f, 1.0f},
		{1.0f, 0.0f}
	};

	VkRenderPassBeginInfo renderPassBeginInfo = {};
	renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassBeginInfo.renderPass = context.renderPass;
	renderPassBeginInfo.framebuffer = context.framebuffers[nextImageIndex];
	renderPassBeginInfo.renderArea = { 0, 0, context.width, context.height };
	renderPassBeginInfo.clearValueCount = 2;
	renderPassBeginInfo.pClearValues = clearValue;
	vkCmdBeginRenderPass(context.drawCommandBuffer, &renderPassBeginInfo,
		VK_SUBPASS_CONTENTS_INLINE);

	vkCmdBindPipeline(context.drawCommandBuffer,
		VK_PIPELINE_BIND_POINT_GRAPHICS,
		context.pipeline);

	context.viewport = { 0, 0, context.width, context.height, 0, 1};	
	vkCmdSetViewport(context.drawCommandBuffer, 0, 1, &context.viewport);

	context.scissor = { 0, 0, context.width, context.height };
	vkCmdSetScissor(context.drawCommandBuffer, 0, 1, &context.scissor);

	VkDeviceSize offsets = {};
	vkCmdBindVertexBuffers(context.drawCommandBuffer, 0,
		1, &context.vertexInputBuffer, &offsets);
	vkCmdDraw(context.drawCommandBuffer, 6, 1, 0, 0);
	//PFN_vkCmdDrawIndexed// for index buffers?
	vkCmdEndRenderPass(context.drawCommandBuffer);

	VkImageMemoryBarrier prePresentBarrier = {};
	prePresentBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	prePresentBarrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	prePresentBarrier.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
	prePresentBarrier.oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
	prePresentBarrier.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	prePresentBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	prePresentBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	prePresentBarrier.subresourceRange =
	{
		VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1
	};
	prePresentBarrier.image = context.presentImages[nextImageIndex];

	vkCmdPipelineBarrier(context.drawCommandBuffer,
		VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
		VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
		0, 0, NULL, 0, NULL, 1,
		&prePresentBarrier);
	vkEndCommandBuffer(context.drawCommandBuffer);


	VkFence renderFence;
	VkFenceCreateInfo fenceCreateInfo = {};
	fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	vkCreateFence(context.device, &fenceCreateInfo,
		NULL, &renderFence);

	VkPipelineStageFlags waitStageMasks =
	{
		VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT
	};
	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = &presentCompleteSemaphore;
	submitInfo.pWaitDstStageMask = &waitStageMasks;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &context.drawCommandBuffer;
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = &renderingCompleteSemaphore;
	vkQueueSubmit(context.presentQueue, 1, &submitInfo, renderFence);

	vkWaitForFences(context.device, 1, &renderFence, VK_TRUE, UINT64_MAX);
	vkDestroyFence(context.device, renderFence, NULL);

	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.pNext = NULL;
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = &renderingCompleteSemaphore;
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = &context.swapChain;
	presentInfo.pImageIndices = &nextImageIndex;
	presentInfo.pResults = NULL;

	vkQueuePresentKHR(context.presentQueue, &presentInfo);

	vkDestroySemaphore(context.device, presentCompleteSemaphore, NULL);
	vkDestroySemaphore(context.device, renderingCompleteSemaphore, NULL);


}



int main()
{
	windowManager* manager = new windowManager();
	tWindow* window = manager->AddWindow("Example");

	context.width = 1280;
	context.height = 720;

	InitVulkan();

	unsigned int layerCount = 0;
	vkEnumerateInstanceLayerProperties(&layerCount, NULL);
	VkLayerProperties* layersAvailable = new VkLayerProperties[layerCount];
	vkEnumerateInstanceLayerProperties(&layerCount, layersAvailable);

	bool foundValidation = false;
	for (unsigned int iter = 0; iter < layerCount; iter++)
	{
		if (!strcmp(layersAvailable[iter].layerName, "VK_LAYER_LUNARG_standard_validation"))
		{
			foundValidation = true;
		}
	}

	if (!foundValidation)
	{
		printf("could not find validation \n");
	}

	const char* layers[] = { "VK_LAYER_LUNARG_standard_validation" };

	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, NULL);
	VkExtensionProperties* availableExtensions = new VkExtensionProperties[extensionCount];
	vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, availableExtensions);

	const char* extensions[] = {
		"VK_KHR_surface",
		"VK_KHR_win32_surface",
		"VK_EXT_debug_report" };
	unsigned int numRequiredExtensions = sizeof(extensions) / sizeof(char*);
	unsigned int foundExtensions = 0;
	for (unsigned int iter = 0; iter < extensionCount; iter++)
	{
		for (unsigned int nestIter = 0; nestIter < numRequiredExtensions; nestIter++)
		{
			if (!strcmp(availableExtensions[iter].extensionName, extensions[nestIter]))
			{
				foundExtensions++;
			}
		}
	}

	if (foundExtensions != numRequiredExtensions)
	{
		printf("Could not find debug extension \n");
	}

	VkApplicationInfo appInfo;
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Vulkan Test";
	appInfo.engineVersion = 1;
	appInfo.apiVersion = VK_MAKE_VERSION(1, 0, 0);

	VkInstanceCreateInfo instanceInfo = {};
	instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceInfo.pApplicationInfo = &appInfo;
	instanceInfo.enabledLayerCount = 1;
	instanceInfo.ppEnabledLayerNames = layers;
	instanceInfo.enabledExtensionCount = 3;
	instanceInfo.ppEnabledExtensionNames = extensions;

	VkResult result = vkCreateInstance(&instanceInfo,
		NULL, &context.vulkanInstance);

	if (result != VK_SUCCESS)
	{
		printf("Failed to create Vulkan instance \n");
	}
	//setup callbacks
	window->resizeEvent = HandleWindowResize;



	VkDebugReportCallbackCreateInfoEXT callbackCreateInfo = {};
	callbackCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
	callbackCreateInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
	callbackCreateInfo.pfnCallback = &DebugReportCallback;
	callbackCreateInfo.pUserData = NULL;

	LoadVulkanExtensions(context);

	result = vkCreateDebugReportCallbackEXT(context.vulkanInstance,
		&callbackCreateInfo, NULL, &context.reportCallback);

	if (result != VK_SUCCESS)
	{
		printf("failed to create debug report callback");
	}

	VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {};
	surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surfaceCreateInfo.hinstance = window->GetWindowClassInstance();
	surfaceCreateInfo.hwnd = window->GetWindowHandle();

	result = vkCreateWin32SurfaceKHR(context.vulkanInstance,
		&surfaceCreateInfo, NULL, &context.surface);

	if (result != VK_SUCCESS)
	{
		printf("could not create surface \n");
	}

	//uhh what a mess
	uint32_t physicalDeviceCount = 0;
	vkEnumeratePhysicalDevices(context.vulkanInstance, &physicalDeviceCount, NULL);
	VkPhysicalDevice* devices = new VkPhysicalDevice[physicalDeviceCount];
	vkEnumeratePhysicalDevices(context.vulkanInstance, &physicalDeviceCount, devices);

	for (unsigned int deviceIter = 0; deviceIter < physicalDeviceCount; deviceIter++)
	{
		VkPhysicalDeviceProperties deviceProps = {};
		vkGetPhysicalDeviceProperties(devices[deviceIter], &deviceProps);

		unsigned int queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(devices[deviceIter],
			&queueFamilyCount, NULL);
		VkQueueFamilyProperties* queueFamilyProperties = new VkQueueFamilyProperties[queueFamilyCount];
		vkGetPhysicalDeviceQueueFamilyProperties(devices[deviceIter],
			&queueFamilyCount, queueFamilyProperties);

		for (unsigned int queueIter = 0; queueIter < queueFamilyCount; queueIter++)
		{
			VkBool32 supportsPresent;
			vkGetPhysicalDeviceSurfaceSupportKHR(devices[queueIter], queueIter, context.surface,
				&supportsPresent);

			if (supportsPresent &&
				queueFamilyProperties[queueIter].queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				context.physicalDevice = devices[deviceIter];
				context.deviceProps = deviceProps;
				context.queueIndex = queueIter;
				break;
			}
		}
		delete[] queueFamilyProperties;

		if (context.physicalDevice)
		{
			break;
		}
	}

	delete[] devices;

	if (!context.physicalDevice)
	{
		printf("no physical device that can render \n");
	}

	VkDeviceQueueCreateInfo queueCreateInfo = {};
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = context.queueIndex;
	queueCreateInfo.queueCount = 1;
	float queueProperties[] = { 1.0f };
	queueCreateInfo.pQueuePriorities = queueProperties;

	VkDeviceCreateInfo deviceInfo = {};
	deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceInfo.queueCreateInfoCount = 1;
	deviceInfo.pQueueCreateInfos = &queueCreateInfo;
	deviceInfo.enabledLayerCount = 1;
	deviceInfo.ppEnabledLayerNames = layers;

	const char* deviceExtensions[] = { "VK_KHR_swapchain" };
	deviceInfo.enabledExtensionCount = 1;
	deviceInfo.ppEnabledExtensionNames = deviceExtensions;

	VkPhysicalDeviceFeatures features = {};
	features.shaderClipDistance = VK_TRUE;
	deviceInfo.pEnabledFeatures = &features;

	result = vkCreateDevice(context.physicalDevice, &deviceInfo,
		NULL, &context.device);
	if (result != VK_SUCCESS)
	{
		printf("failed to create logical device \n");
	}

	vkGetDeviceQueue(context.device, context.queueIndex, 0, &context.presentQueue);

	uint32_t formatCount = 0;

	vkGetPhysicalDeviceSurfaceFormatsKHR(
		context.physicalDevice, context.surface,
		&formatCount, NULL);

	VkSurfaceFormatKHR* surfaceFormats = new VkSurfaceFormatKHR[formatCount];
	vkGetPhysicalDeviceSurfaceFormatsKHR(
		context.physicalDevice, context.surface,
		&formatCount, surfaceFormats);

	context.colorFormat;
	if (formatCount == 1 && surfaceFormats[0].format == VK_FORMAT_UNDEFINED)
	{
		context.colorFormat = VK_FORMAT_B8G8R8_UNORM;
	}

	else
	{
		context.colorFormat = surfaceFormats[0].format;
	}

	VkColorSpaceKHR colorSpace;
	colorSpace = surfaceFormats[0].colorSpace;
	delete[] surfaceFormats;

	VkSurfaceCapabilitiesKHR surfaceCapabilities = {};
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(context.physicalDevice,
		context.surface, &surfaceCapabilities);

	context.desiredImageCount = 2;
	if (context.desiredImageCount < surfaceCapabilities.minImageCount)
	{
		context.desiredImageCount = surfaceCapabilities.minImageCount;
	}

	else if (surfaceCapabilities.maxImageCount != 0 &&
		context.desiredImageCount > surfaceCapabilities.maxImageCount)
	{
		context.desiredImageCount = surfaceCapabilities.maxImageCount;
	}

	context.surfaceResolution = surfaceCapabilities.currentExtent;
	if (context.surfaceResolution.width == -1)
	{
		context.surfaceResolution.width = context.width;
		context.surfaceResolution.height = context.height;
	}

	else
	{
		context.width = context.surfaceResolution.width;
		context.height = context.surfaceResolution.height;
	}

	context.preTransform = surfaceCapabilities.currentTransform;
	if (surfaceCapabilities.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR)
	{
		context.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	}

	unsigned int presentModeCount = 0;
	vkGetPhysicalDeviceSurfacePresentModesKHR(context.physicalDevice,
		context.surface, &presentModeCount, NULL);
	VkPresentModeKHR* presentModes = new VkPresentModeKHR[presentModeCount];
	vkGetPhysicalDeviceSurfacePresentModesKHR(context.physicalDevice,
		context.surface, &presentModeCount, presentModes);

	context.presentMode = VK_PRESENT_MODE_FIFO_KHR; //FIFO = first in first out?
	for (unsigned int presentIter = 0; presentIter < presentModeCount; presentIter++)
	{
		if (presentModes[presentIter] == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			context.presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
			break;
		}
	}
	delete[] presentModes;

	//is swap chain another name for draw buffers? (double/triple buffering / vsync?)
	VkSwapchainCreateInfoKHR swapChainCreateInfo = {};
	swapChainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapChainCreateInfo.surface = context.surface;
	swapChainCreateInfo.minImageCount = context.desiredImageCount;
	swapChainCreateInfo.imageFormat = context.colorFormat;
	swapChainCreateInfo.imageColorSpace = context.colorSpace;
	swapChainCreateInfo.imageExtent = context.surfaceResolution;
	swapChainCreateInfo.imageArrayLayers = 1;
	swapChainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	swapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	swapChainCreateInfo.preTransform = context.preTransform;
	swapChainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swapChainCreateInfo.presentMode = context.presentMode;
	swapChainCreateInfo.clipped = true;
	swapChainCreateInfo.oldSwapchain = NULL;

	result = vkCreateSwapchainKHR(context.device, &swapChainCreateInfo,
		NULL, &context.swapChain);
	if (result != VK_SUCCESS)
	{
		printf("failed to crate swapChain \n");
	}

	VkCommandPoolCreateInfo commandPoolCreateInfo = {};
	commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	commandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	commandPoolCreateInfo.queueFamilyIndex = context.queueIndex;

	VkCommandPool commandPool;
	result = vkCreateCommandPool(context.device,
		&commandPoolCreateInfo, NULL, &commandPool);

	if (result != VK_SUCCESS)
	{
		printf("failed to create command pool \n");
	}

	VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
	commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	commandBufferAllocateInfo.commandPool = commandPool;
	commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	commandBufferAllocateInfo.commandBufferCount = 1;

	result = vkAllocateCommandBuffers(context.device, &commandBufferAllocateInfo,
		&context.setupCommandBuffer);

	if (result != VK_SUCCESS)
	{
		printf("failed to allocate setup command buffer \n");
	}

	result = vkAllocateCommandBuffers(context.device, &commandBufferAllocateInfo,
		&context.drawCommandBuffer);

	if (result != VK_SUCCESS)
	{
		printf("failed to allocate draw command buffer \n");
	}

	unsigned int imageCount = 0;
	vkGetSwapchainImagesKHR(context.device,
		context.swapChain, &imageCount, NULL);
	context.presentImages = new VkImage[imageCount];
	vkGetSwapchainImagesKHR(context.device,
		context.swapChain, &imageCount, context.presentImages);

	VkImageViewCreateInfo presentImagesViewCreateInfo = {};
	presentImagesViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	presentImagesViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	presentImagesViewCreateInfo.format = context.colorFormat;
	presentImagesViewCreateInfo.components =
	{
		VK_COMPONENT_SWIZZLE_R,
		VK_COMPONENT_SWIZZLE_G,
		VK_COMPONENT_SWIZZLE_B,
		VK_COMPONENT_SWIZZLE_A
	};
	presentImagesViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	presentImagesViewCreateInfo.subresourceRange.baseMipLevel = 0;
	presentImagesViewCreateInfo.subresourceRange.levelCount = 1;
	presentImagesViewCreateInfo.subresourceRange.baseArrayLayer = 0;
	presentImagesViewCreateInfo.subresourceRange.layerCount = 1;
	//context.presentImages[0] = presentImagesViewCreateInfo.image;

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	VkFenceCreateInfo fenceCreateInfo = {};
	fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	VkFence submitFence;
	vkCreateFence(context.device, &fenceCreateInfo, NULL, &submitFence);

	VkImageView* presentImageViews = new VkImageView[imageCount];
	for (unsigned int imageIter = 0; imageIter < imageCount; imageIter++)
	{
		presentImagesViewCreateInfo.image = context.presentImages[imageIter];
		vkBeginCommandBuffer(context.setupCommandBuffer, &beginInfo);

		VkImageMemoryBarrier layoutTransitionBarrier = {};
		layoutTransitionBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		layoutTransitionBarrier.srcAccessMask = 0;
		layoutTransitionBarrier.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
		layoutTransitionBarrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		layoutTransitionBarrier.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		layoutTransitionBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		layoutTransitionBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		layoutTransitionBarrier.image = context.presentImages[imageIter];
		VkImageSubresourceRange resourceRange =
		{
			VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1
		};

		layoutTransitionBarrier.subresourceRange = resourceRange;

		vkCmdPipelineBarrier(context.setupCommandBuffer,
			VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
			VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
			0, 0, NULL,
			0, NULL, 1,
			&layoutTransitionBarrier);

		vkEndCommandBuffer(context.setupCommandBuffer);

		VkPipelineStageFlags waitStageMasks[] =
		{
			VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT
		};
		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.waitSemaphoreCount = 0;
		submitInfo.pWaitSemaphores = NULL;
		submitInfo.pWaitDstStageMask = waitStageMasks;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &context.setupCommandBuffer;
		submitInfo.signalSemaphoreCount = 0;
		submitInfo.pSignalSemaphores = NULL;
		result = vkQueueSubmit(context.presentQueue, 1, &submitInfo, submitFence);

		vkWaitForFences(context.device, 1, &submitFence, VK_TRUE, UINT64_MAX);
		vkResetFences(context.device, 1, &submitFence);
		vkResetCommandBuffer(context.setupCommandBuffer, 0);

		result = vkCreateImageView(context.device, &presentImagesViewCreateInfo,
			NULL, &presentImageViews[imageIter]);

		if (result != VK_SUCCESS)
		{
			printf("could not create imageView \n");
		}
	}

	vkGetPhysicalDeviceMemoryProperties(context.physicalDevice, &context.memoryProperties);

	VkImageCreateInfo imageCreateInfo = {};
	imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
	imageCreateInfo.format = VK_FORMAT_D16_UNORM;
	imageCreateInfo.extent = { context.width, context.height, 1 };
	imageCreateInfo.mipLevels = 1;
	imageCreateInfo.arrayLayers = 1;
	imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	imageCreateInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
	imageCreateInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
	imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	imageCreateInfo.queueFamilyIndexCount = 0;
	imageCreateInfo.pQueueFamilyIndices = NULL;
	imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

	result = vkCreateImage(context.device, &imageCreateInfo, NULL, &context.depthImage);

	VkMemoryRequirements memoryRequirements = {};
	vkGetImageMemoryRequirements(context.device, context.depthImage, &memoryRequirements);

	VkMemoryAllocateInfo imageAllocateInfo = {};
	imageAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	imageAllocateInfo.allocationSize = memoryRequirements.size;

	unsigned int memoryTypeBits = memoryRequirements.memoryTypeBits;
	VkMemoryPropertyFlags desiredMemoryFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
	for (unsigned int memoryIter = 0; memoryIter < 32; memoryIter++)
	{
		VkMemoryType memoryType = context.memoryProperties.memoryTypes[memoryIter];
		if (memoryTypeBits & 1)
		{
			if ((memoryType.propertyFlags & desiredMemoryFlags) == desiredMemoryFlags)
			{
				imageAllocateInfo.memoryTypeIndex = memoryIter;
				break;
			}
		}
		memoryTypeBits = memoryTypeBits >> 1;
	}

	VkDeviceMemory imageMemory = {};
	result = vkAllocateMemory(context.device, &imageAllocateInfo, NULL, &imageMemory);
	if (result != VK_SUCCESS)
	{
		printf("failed to allocate device memory \n");
	}

	result = vkBindImageMemory(context.device, context.depthImage,
		imageMemory, 0);

	if (result != VK_SUCCESS)
	{
		printf("failed to bind image memory \n");
	}

	VkCommandBufferBeginInfo commandBufferBeginInfo = {};
	commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	commandBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(context.setupCommandBuffer, &commandBufferBeginInfo);

	VkImageMemoryBarrier layoutTransitionBarrier = {};
	layoutTransitionBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	layoutTransitionBarrier.srcAccessMask = 0;
	layoutTransitionBarrier.dstAccessMask =
		VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT |
		VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
	layoutTransitionBarrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	layoutTransitionBarrier.newLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
	layoutTransitionBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	layoutTransitionBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	layoutTransitionBarrier.image = context.depthImage;
	VkImageSubresourceRange resourceRange =
	{
		VK_IMAGE_ASPECT_DEPTH_BIT, 0, 1, 0, 1
	};

	layoutTransitionBarrier.subresourceRange = resourceRange;

	vkCmdPipelineBarrier(context.setupCommandBuffer,
		VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
		VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
		0, 0, NULL, 0, NULL, 1,
		&layoutTransitionBarrier);

	vkEndCommandBuffer(context.setupCommandBuffer);

	VkPipelineStageFlags waitStageMasks[] =
	{
		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT
	};
	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.waitSemaphoreCount = 0;
	submitInfo.pWaitSemaphores = NULL;
	submitInfo.pWaitDstStageMask = waitStageMasks;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &context.setupCommandBuffer;
	submitInfo.signalSemaphoreCount = 0;
	submitInfo.pSignalSemaphores = NULL;
	result = vkQueueSubmit(context.presentQueue, 1,
		&submitInfo, submitFence);

	vkWaitForFences(context.device, 1, &submitFence,
		VK_TRUE, UINT64_MAX);
	vkResetFences(context.device, 1, &submitFence);
	vkResetCommandBuffer(context.setupCommandBuffer, 0);

	VkImageAspectFlags aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
	VkImageViewCreateInfo imageViewCreateInfo = {};
	imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageViewCreateInfo.image = context.depthImage;
	imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	imageViewCreateInfo.format = imageCreateInfo.format;
	imageViewCreateInfo.components =
	{
		VK_COMPONENT_SWIZZLE_IDENTITY,
		VK_COMPONENT_SWIZZLE_IDENTITY,

		VK_COMPONENT_SWIZZLE_IDENTITY,
		VK_COMPONENT_SWIZZLE_IDENTITY
	};

	imageViewCreateInfo.subresourceRange.aspectMask = aspectMask;
	imageViewCreateInfo.subresourceRange.levelCount = 1;
	imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
	imageViewCreateInfo.subresourceRange.layerCount = 1;

	result = vkCreateImageView(context.device,
		&imageViewCreateInfo, NULL, &context.depthImageView);

	if (result != VK_SUCCESS)
	{
		printf("failed to create depth image view \n");
	}

	VkAttachmentDescription passAttachments[2] = {};
	passAttachments[0].format = context.colorFormat;
	passAttachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
	passAttachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	passAttachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	passAttachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	passAttachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	passAttachments[0].initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
	passAttachments[0].finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	passAttachments[1].format = VK_FORMAT_D16_UNORM;
	passAttachments[1].samples = VK_SAMPLE_COUNT_1_BIT;
	passAttachments[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	passAttachments[1].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	passAttachments[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	passAttachments[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	passAttachments[1].initialLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
	passAttachments[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	VkAttachmentReference colorAttachmentReference = {};
	colorAttachmentReference.attachment = 0;
	colorAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkAttachmentReference depthAttachmentsReference = {};
	depthAttachmentsReference.attachment = 1;
	depthAttachmentsReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass = {};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentReference;
	subpass.pDepthStencilAttachment = &depthAttachmentsReference;

	VkRenderPassCreateInfo renderPassCreateInfo = {};
	renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassCreateInfo.attachmentCount = 2;
	renderPassCreateInfo.pAttachments = passAttachments;
	renderPassCreateInfo.subpassCount = 1;
	renderPassCreateInfo.pSubpasses = &subpass;

	result = vkCreateRenderPass(context.device,
		&renderPassCreateInfo, NULL, &context.renderPass);

	if (result != VK_SUCCESS)
	{
		printf(" failed to create renderPass \n");
	}

	VkImageView frameBufferAttachments[2];
	frameBufferAttachments[1] = context.depthImageView;
	VkFramebufferCreateInfo framebufferCreateInfo = {};
	framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	framebufferCreateInfo.renderPass = context.renderPass;
	framebufferCreateInfo.attachmentCount = 2;
	framebufferCreateInfo.pAttachments = frameBufferAttachments;
	framebufferCreateInfo.width = context.width;
	framebufferCreateInfo.height = context.height;
	framebufferCreateInfo.layers = 1;

	context.framebuffers = new VkFramebuffer[imageCount];
	for (unsigned int imageIter = 0; imageIter < imageCount; imageIter++)
	{
		frameBufferAttachments[0] = presentImageViews[imageIter];
		result = vkCreateFramebuffer(context.device, &framebufferCreateInfo,
			NULL, &context.framebuffers[imageIter]);

		if (result != VK_SUCCESS)
		{
			printf("failed to create framebuffer \n");
		}
	}

	struct vertex
	{
		float c, y, z, w;
	};

	VkBufferCreateInfo vertexInputBufferInfo = {};
	vertexInputBufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	vertexInputBufferInfo.size = sizeof(vertex) * 6;
	vertexInputBufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	vertexInputBufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	result = vkCreateBuffer(context.device, &vertexInputBufferInfo,
		NULL, &context.vertexInputBuffer);

	if (result != VK_SUCCESS)
	{
		printf("failed to create vertex input buffer \n");
	}

	VkMemoryRequirements vertexBufferMemoryRequirements = {};
	vkGetBufferMemoryRequirements(context.device, context.vertexInputBuffer,
		&vertexBufferMemoryRequirements);

	VkMemoryAllocateInfo bufferAllocateInfo = {};
	bufferAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	bufferAllocateInfo.allocationSize = vertexBufferMemoryRequirements.size;

	unsigned int vertexMemotyTypeBits = vertexBufferMemoryRequirements.memoryTypeBits;
	VkMemoryPropertyFlags vertexDesiredMemoryFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;

	for (unsigned int memoryIter = 0; memoryIter < 32; memoryIter++)
	{
		VkMemoryType memoryType = context.memoryProperties.memoryTypes[memoryIter];
		if (vertexMemotyTypeBits & 1)
		{
			if ((memoryType.propertyFlags * vertexDesiredMemoryFlags) == vertexDesiredMemoryFlags)
			{
				bufferAllocateInfo.memoryTypeIndex = 1;
				break;
			}
		}
		vertexMemotyTypeBits = vertexMemotyTypeBits >> 1;
	}

	VkDeviceMemory vertexBufferMemory;
	result = vkAllocateMemory(context.device, &bufferAllocateInfo,
		NULL, &vertexBufferMemory);
	if (result != VK_SUCCESS)
	{
		printf("failed to allocate buffer memory \n");
	}

	void* mapped;
	result = vkMapMemory(context.device,
		vertexBufferMemory, 0, VK_WHOLE_SIZE, 0, &mapped);
	if (result != VK_SUCCESS)
	{
		printf("failed to map buffer memory \n");
	}

	vertex* quad = (vertex*)mapped;
	vertex v1 = { -1.0f, -1.0f, 0.0f, 1.0f }; // top left
	vertex v2 = { 1.0f, -1.0f, 0.0f, 1.0f }; // top right
	vertex v3 = { 1.0f, 1.0f, 0.0f, 1.0f }; // bottom right

	vertex v4 = { 1.0f, 1.0f, 0.0f, 1.0f }; // bottom right 
	vertex v5 = { -1.0f, 1.0f, 0.0f, 1.0f }; //bottom left
	vertex v6 = { -1.0f, -1.0f, 0.0f, 1.0f }; // top left
	
	quad[0] = v1;
	quad[1] = v2;
	quad[2] = v3;
	quad[3] = v4;
	quad[4] = v5;
	quad[5] = v6;

	vkUnmapMemory(context.device, vertexBufferMemory);

	result = vkBindBufferMemory(context.device,
		context.vertexInputBuffer, vertexBufferMemory, 0);

	if (result != VK_SUCCESS)
	{
		printf("failed to bind buffer memory \n");
	}

	unsigned int codeSize;
	std::string code;
	HANDLE fileHandle = 0;
	code = ReadTextFile("vert.spv");

	if (fileHandle == INVALID_HANDLE_VALUE)
	{
		printf("failed to open shader file \n");
	}

	VkShaderModuleCreateInfo vertexShaderCreationInfo = {};
	vertexShaderCreationInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	vertexShaderCreationInfo.codeSize = code.size();
	vertexShaderCreationInfo.pCode = (unsigned int*)code.c_str();

	
	/*
	vertexShaderCreationInfo.codeSize = (3 * sizeof(unsigned int)) + code.size();
	vertexShaderCreationInfo.pCode = (unsigned int*)malloc(vertexShaderCreationInfo.codeSize);

	((unsigned int*)vertexShaderCreationInfo.pCode)[0] = 0x07230203;
	((unsigned int*)vertexShaderCreationInfo.pCode)[1] = 0;
	((unsigned int*)vertexShaderCreationInfo.pCode)[2] = VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT;
	memcpy(((unsigned int*)vertexShaderCreationInfo.pCode + 3), code.c_str(), code.size());*/

	VkShaderModule vertexShaderModule;
	result = vkCreateShaderModule(context.device,
		&vertexShaderCreationInfo, NULL, &vertexShaderModule);

	if (result != VK_SUCCESS)
	{
		printf("failed to open shader file \n");
	}

	code = ReadTextFile("frag.spv");

	VkShaderModuleCreateInfo fragmentShaderCreationInfo = {};
	fragmentShaderCreationInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	fragmentShaderCreationInfo.codeSize = code.size();
	fragmentShaderCreationInfo.pCode = (unsigned int*)code.c_str();
	/*fragmentShaderCreationInfo.codeSize = (3 * sizeof(unsigned int)) + code.size();
	fragmentShaderCreationInfo.pCode = (unsigned int*)malloc(vertexShaderCreationInfo.codeSize);

	((unsigned int*)fragmentShaderCreationInfo.pCode)[0] = 0x07230203;
	((unsigned int*)fragmentShaderCreationInfo.pCode)[1] = 0;
	((unsigned int*)fragmentShaderCreationInfo.pCode)[2] = VkShaderStageFlagBits::VK_SHADER_STAGE_FRAGMENT_BIT;
	memcpy(((unsigned int*)fragmentShaderCreationInfo.pCode + 3), code.c_str(), code.size());*/

	VkShaderModule fragmentShaderModule;
	result = vkCreateShaderModule(context.device, &fragmentShaderCreationInfo,
		NULL, &fragmentShaderModule);

	if (result != VK_SUCCESS)
	{
		printf("failed to create fragment shader module \n");
	}

	VkPipelineLayoutCreateInfo layoutCreateInfo = {};
	layoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	layoutCreateInfo.setLayoutCount = 0;
	layoutCreateInfo.pSetLayouts = NULL;
	layoutCreateInfo.pushConstantRangeCount = 0;
	layoutCreateInfo.pPushConstantRanges = NULL;

	result = vkCreatePipelineLayout(context.device,
		&layoutCreateInfo, NULL, &context.pipelineLayout);

	if (result != VK_SUCCESS)
	{
		printf("failed to create pipeline layout \n");
	}

	VkPipelineShaderStageCreateInfo shaderStageCreateInfo[2] = {};
	shaderStageCreateInfo[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	shaderStageCreateInfo[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
	shaderStageCreateInfo[0].module = vertexShaderModule;
	shaderStageCreateInfo[0].pName = "main";
	shaderStageCreateInfo[0].pSpecializationInfo = NULL;

	shaderStageCreateInfo[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	shaderStageCreateInfo[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	shaderStageCreateInfo[1].module = fragmentShaderModule;
	shaderStageCreateInfo[1].pName = "main";
	shaderStageCreateInfo[1].pSpecializationInfo = NULL;

	VkVertexInputBindingDescription vertexBindingDescription = {};
	vertexBindingDescription.binding = 0;
	vertexBindingDescription.stride = sizeof(vertex);
	vertexBindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

	VkVertexInputAttributeDescription vertexInputAttributeDescription = {};
	vertexInputAttributeDescription.location = 0;
	vertexInputAttributeDescription.binding = 0;
	vertexInputAttributeDescription.format = VK_FORMAT_R32G32B32A32_SFLOAT;
	vertexInputAttributeDescription.offset = 0;

	VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo = {};
	vertexInputStateCreateInfo = {};
	vertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInputStateCreateInfo.vertexBindingDescriptionCount = 1;
	vertexInputStateCreateInfo.pVertexBindingDescriptions = &vertexBindingDescription;
	vertexInputStateCreateInfo.vertexAttributeDescriptionCount = 1;
	vertexInputStateCreateInfo.pVertexAttributeDescriptions = &vertexInputAttributeDescription;

	VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo = {};
	inputAssemblyStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssemblyStateCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST; // no quads?
	inputAssemblyStateCreateInfo.primitiveRestartEnable = VK_FALSE;

	VkViewport viewport = {};
	viewport.x = 0;
	viewport.y = 0;
	viewport.width = (float)context.width;
	viewport.height = (float)context.height;
	viewport.minDepth = 0;
	viewport.maxDepth = 1;

	VkRect2D scissors = {};
	scissors.offset = { 0, 0 };
	scissors.extent = { context.width, context.height };

	VkPipelineViewportStateCreateInfo viewportState = {};
	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	viewportState.viewportCount = 1;
	viewportState.pViewports = &viewport;
	viewportState.scissorCount = 1;
	viewportState.pScissors = &scissors;

	VkPipelineRasterizationStateCreateInfo rasterizationState = {};
	rasterizationState.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizationState.depthClampEnable = VK_FALSE;
	rasterizationState.rasterizerDiscardEnable = VK_FALSE;
	rasterizationState.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizationState.cullMode = VK_CULL_MODE_NONE;
	rasterizationState.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
	rasterizationState.depthBiasEnable = VK_FALSE;
	rasterizationState.depthBiasConstantFactor = 0;
	rasterizationState.depthBiasClamp = 0;
	rasterizationState.depthBiasSlopeFactor = 0;
	rasterizationState.lineWidth = 1;

	VkPipelineMultisampleStateCreateInfo multisampleState = {};
	multisampleState.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampleState.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	multisampleState.sampleShadingEnable = VK_FALSE;
	multisampleState.minSampleShading = 0;
	multisampleState.pSampleMask = NULL;
	multisampleState.alphaToCoverageEnable = VK_FALSE;
	multisampleState.alphaToOneEnable = VK_FALSE;

	VkStencilOpState stencilOPState = {};
	stencilOPState.failOp = VK_STENCIL_OP_KEEP;
	stencilOPState.passOp = VK_STENCIL_OP_KEEP;
	stencilOPState.depthFailOp = VK_STENCIL_OP_KEEP;
	stencilOPState.compareOp = VK_COMPARE_OP_ALWAYS;
	stencilOPState.compareMask = 0;
	stencilOPState.writeMask = 0;
	stencilOPState.reference = 0;

	VkPipelineDepthStencilStateCreateInfo depthStencilState = {};
	depthStencilState.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	depthStencilState.depthTestEnable = VK_TRUE;
	depthStencilState.depthWriteEnable = VK_TRUE;
	depthStencilState.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
	depthStencilState.depthBoundsTestEnable = VK_FALSE;
	depthStencilState.stencilTestEnable = VK_FALSE;
	depthStencilState.front = stencilOPState;
	depthStencilState.back = stencilOPState;
	depthStencilState.minDepthBounds = 0;
	depthStencilState.maxDepthBounds = 0;

	VkPipelineColorBlendAttachmentState colorBlendAttachmentState = {};
	colorBlendAttachmentState.blendEnable = VK_FALSE;
	colorBlendAttachmentState.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_COLOR;
	colorBlendAttachmentState.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR;
	colorBlendAttachmentState.colorBlendOp = VK_BLEND_OP_ADD;
	colorBlendAttachmentState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	colorBlendAttachmentState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	colorBlendAttachmentState.alphaBlendOp = VK_BLEND_OP_ADD;
	colorBlendAttachmentState.colorWriteMask = 0xf;

	VkPipelineColorBlendStateCreateInfo colorBlendState = {};
	colorBlendState.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlendState.logicOpEnable = VK_FALSE;
	colorBlendState.logicOp = VK_LOGIC_OP_CLEAR;
	colorBlendState.attachmentCount = 1;
	colorBlendState.pAttachments = &colorBlendAttachmentState;
	colorBlendState.blendConstants[0] = 0.0f;
	colorBlendState.blendConstants[1] = 0.0f;
	colorBlendState.blendConstants[2] = 0.0f;
	colorBlendState.blendConstants[3] = 0.0f;

	VkDynamicState dynamicState[2] =
	{
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR
	};
	VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo = {};
	dynamicStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamicStateCreateInfo.dynamicStateCount = 2;
	dynamicStateCreateInfo.pDynamicStates = dynamicState;

	VkGraphicsPipelineCreateInfo pipelineCreateInfo = {};
	pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineCreateInfo.stageCount = 2;
	pipelineCreateInfo.pStages = shaderStageCreateInfo;
	pipelineCreateInfo.pVertexInputState = &vertexInputStateCreateInfo;
	pipelineCreateInfo.pInputAssemblyState = &inputAssemblyStateCreateInfo;
	pipelineCreateInfo.pTessellationState = NULL;
	pipelineCreateInfo.pViewportState = &viewportState;
	pipelineCreateInfo.pRasterizationState = &rasterizationState;
	pipelineCreateInfo.pMultisampleState = &multisampleState;
	pipelineCreateInfo.pDepthStencilState = &depthStencilState;
	pipelineCreateInfo.pColorBlendState = &colorBlendState;
	pipelineCreateInfo.pDynamicState = &dynamicStateCreateInfo;
	pipelineCreateInfo.layout = context.pipelineLayout;
	pipelineCreateInfo.renderPass = context.renderPass;
	pipelineCreateInfo.subpass = 0;
	pipelineCreateInfo.basePipelineHandle = NULL;
	pipelineCreateInfo.basePipelineIndex = 0;

	result = vkCreateGraphicsPipelines(context.device,
		VK_NULL_HANDLE, 1, &pipelineCreateInfo, NULL,
		&context.pipeline);

	if (result != VK_SUCCESS)
	{
		printf("could not create graphics pipeline \n");
	}

	while (!window->shouldClose)
	{
		manager->PollForEvents();
		draw();
	}

	manager->ShutDown();
	return 0;
}