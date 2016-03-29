#include "TinyWindow.h"

using namespace TinyWindow;
void HandleKeyPresses(unsigned int key, keyState_t keyState)
{
	if(keyState == keyState_t::down && key == escape)
	{
#if defined(TW_WINDOWS)
		PostQuitMessage(0);
#endif
	}
}

void HandleMouseWheel(mouseScroll_t mouseScrollDirection)
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

	while (!window->shouldClose)
	{
		glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
		manager->PollForEvents();// or WaitForEvents
		
		//manager->MakeWindowCurrentContext(window);
		window->SwapDrawBuffers();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	window.release();
	manager->ShutDown();
	return 0;
}
