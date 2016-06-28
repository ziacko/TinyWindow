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

	else if (keyState == keyState_t::up && key == spacebar)
	{
		spacePressed = false;
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

int main()
{
	std::unique_ptr<windowManager> manager(new windowManager());
	std::unique_ptr<tWindow> window(manager->AddWindow("Example"));

	window->keyEvent = HandleKeyPresses;
	window->mouseWheelEvent = HandleMouseWheel;
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	while (!window->shouldClose)
	{
		manager->PollForEvents();

		if (spacePressed)
		{
			window->ToggleFullscreen(0);
		}

		window->SwapDrawBuffers();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	window.release();
	manager->ShutDown();
	return 0;
}
