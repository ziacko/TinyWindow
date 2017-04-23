//#define TW_NO_CONSOLE
#include "TinyWindow.h"

using namespace TinyWindow;

bool spacePressed = false;
void HandleKeyPresses(tWindow* window, unsigned int key, keyState_t keyState)
{
	if(keyState == keyState_t::down && key == spacebar)
	{
		printf("spacebar has been pressed \n");
		spacePressed = true;
	}

	else if (keyState == keyState_t::up && key == escape)
	{
		window->shouldClose = true;
	}
}

void HandleMouseWheel(tWindow* window, mouseScroll_t mouseScrollDirection)
{
	switch (mouseScrollDirection)
	{
		case mouseScroll_t::down:
		{
			printf("mouse wheel down \n");
			break;
		}

		case mouseScroll_t::up:
		{
			printf("mouse wheel up \n");
			break;
		}
	}
}

void PrintMonitorInfo(windowManager* manager)
{
	for (auto monitorIter : manager->GetMonitors())
	{
		printf("%s \n", monitorIter->deviceName.c_str());
		printf("%s \n", monitorIter->monitorName.c_str());
		printf("%s \n", monitorIter->displayName.c_str());
		printf("resolution:\t current width: %i | current height: %i \n", monitorIter->currentSetting->resolution.width, monitorIter->currentSetting->resolution.height);
		printf("extents:\t top: %i | left: %i | bottom: %i | right: %i \n", monitorIter->extents.top, monitorIter->extents.left, monitorIter->extents.bottom, monitorIter->extents.right);
		for (auto settingIter : monitorIter->settings)
		{
			printf("width %i | height %i | frequency %i | pixel depth: %i \n",
				settingIter->resolution.width, settingIter->resolution.height, settingIter->displayFrequency, settingIter->bitsPerPixel);
		}
		printf("\n");
	}
}

int main()
{
	std::unique_ptr<windowManager> manager(new windowManager());
	std::unique_ptr<tWindow> window(manager->AddWindow("Example"));
	PrintMonitorInfo(manager.get());

	manager->keyEvent = HandleKeyPresses;
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	while (!window->shouldClose)
	{
		manager->PollForEvents();

		if (spacePressed)
		{
			window->SetStyle(style_t::popup);
			window->SetPosition(vec2_t<int>::Zero());
			window->SetResolution(vec2_t<unsigned int>(manager->GetMonitors().back()->extents.right, manager->GetMonitors().back()->extents.bottom));
			window->ToggleFullscreen(manager->GetMonitors()[0]);
			spacePressed = false;
		}

		window->SwapDrawBuffers();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	tWindow* tempWindow = window.release();
	delete tempWindow;
	manager->ShutDown();
	return 0;
}
