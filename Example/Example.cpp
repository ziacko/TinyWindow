#include "TinyWindow.h"

using namespace TinyWindow;
void HandleKeyPresses(tWindow* window, int key, keyState_t keyState)
{
	if (keyState == keyState_t::down)
	{
		printf("%c \n", key);
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
	std::unique_ptr<tWindow> window(manager->AddWindow("Example", nullptr, 
		TinyWindow::vec2_t<unsigned int>(defaultWindowWidth, defaultWindowHeight), 4, 5, profile_t::core));

	manager->keyEvent = HandleKeyPresses;
	manager->mouseWheelEvent = HandleMouseWheel;
	manager->SetWindowSwapInterval(window.get(), 1);
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	while (!window->shouldClose)
	{
		manager->PollForEvents();

		window->SwapDrawBuffers();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	manager->ShutDown();
	return 0;
}
