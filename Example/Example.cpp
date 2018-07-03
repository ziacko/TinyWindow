//#define TW_NO_CONSOLE
#include "TinyWindow.h"

using namespace TinyWindow;

bool spacePressed = false;
void HandleKeyPresses(tWindow* window, unsigned int key, keyState_t keyState)
{
	if(keyState == keyState_t::down && key == spacebar)
	{
		printf("Window: %s | spacebar has been pressed \n", window->name);
		spacePressed = true;
	}

	else if (keyState == keyState_t::up && key == escape)
	{
		window->shouldClose = true;
	}

	else if(keyState == keyState_t::down)
	{
		printf("Window: %s | %c | down\n", window->name, key);
	}

	else if (keyState == keyState_t::up)
	{
		printf("Window: %s | %c | up\n", window->name, key);
	}
}

void HandleMouseClick(tWindow* window, mouseButton_t button, buttonState_t state)
{
	switch (button)
	{
	case mouseButton_t::left:
	{
		if (state == buttonState_t::down)
		{
			printf("Window: %s | left button down \n", window->name);
		}
		break;
	}

	case mouseButton_t::middle:
	{
		if (state == buttonState_t::down)
		{
			printf("Window: %s | middle button down \n", window->name);
		}
		break;
	}

	case mouseButton_t::right:
	{
		if (state == buttonState_t::down)
		{
			printf("Window: %s | right button down \n", window->name);
		}
		break;
	}

	default:
	{
		break;
	}
	}
}

void HandleMouseWheel(tWindow* window, mouseScroll_t mouseScrollDirection)
{
	switch (mouseScrollDirection)
	{
		case mouseScroll_t::down:
		{
			printf("Window: %s | mouse wheel down \n", window->name);
			break;
		}

		case mouseScroll_t::up:
		{
			printf("Window: %s | mouse wheel up \n", window->name);
			break;
		}
	}
}

void HandleShutdown(tWindow* window)
{
	printf("window: %s has closed \n", window->name);
}

void HandleMaximized(tWindow* window)
{
	printf("Window: %s | has been maximized \n", window->name);
}

void HandleMinimized(tWindow* window)
{
	printf("Window: %s | has been minimized \n", window->name);
}

void HandleFocus(tWindow* window, bool isFocused)
{
	isFocused ? printf("Window: %s | is now in focus\n", window->name) : printf("Window: %s | is out of focus\n", window->name);
}

void HandleMovement(tWindow* window, const vec2_t<int>& windowPosition)
{
	printf("Window: %s | new position X: %i Y:%i\n", window->name, windowPosition.x, windowPosition.y);
}

void HandleResize(tWindow* window, const vec2_t<unsigned int>& windowSize)
{
	printf("Window: %s | new position X: %i Y:%i\n", window->name, windowSize.width, windowSize.height);
}

void HandleMouseMovement(tWindow* window, const vec2_t<int>& windowMousePosition, const vec2_t<int>& screenMousePosition)
{
	printf("Window: %s | window position X: %i Y: %i | screen position X: %i Y: %i \n", window->name,
		windowMousePosition.x, windowMousePosition.y, screenMousePosition.x, screenMousePosition.y);
}

void HandleFileDrop(tWindow* window, const std::vector<std::string>& files, const vec2_t<int>& windowMousePosition)
{
	printf("Window: %s files dropped | \n", window->name);
	for (const auto& iter : files)
	{
		printf("\t %s \n", iter.c_str());
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
	//manager->mouseButtonEvent = HandleMouseClick;
	//manager->mouseWheelEvent = HandleMouseWheel;
	//manager->destroyedEvent = HandleShutdown;
	//manager->maximizedEvent = HandleMaximized;
	//manager->minimizedEvent = HandleMinimized;
	//manager->focusEvent = HandleFocus;
	//manager->movedEvent = HandleMovement;
	//manager->resizeEvent = HandleResize;
	//manager->fileDropEvent = HandleFileDrop;
	//manager->mouseMoveEvent = HandleMouseMovement;
	
	
	while (!window->shouldClose)
	{
		manager->PollForEvents();
		if (spacePressed)
		{
			window->SetStyle(style_t::popup);
			window->SetPosition(vec2_t<int>::Zero());
			window->SetResolution(vec2_t<unsigned int>(manager->GetMonitors().back()->resolution.width, manager->GetMonitors().back()->resolution.height));
			window->ToggleFullscreen(manager->GetMonitors()[0]);
			spacePressed = false;
		}

		glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
		window->SwapDrawBuffers();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	manager->ShutDown();
	tWindow* tempWindow = window.release();
	delete tempWindow;
	
	return 0;
}
