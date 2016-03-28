#include "TinyWindow.h"

using namespace TinyWindow;
void handleKeyPresses(unsigned int key, keyState_t keyState)
{
	if(keyState == keyState_t::down && key == escape)
	{
#if defined(TW_WINDOWS)
		PostQuitMessage(0);
#endif
	}
}

int main()
{
	std::unique_ptr<windowManager> manager(new windowManager());
	std::unique_ptr<tWindow> window(manager->AddWindow("Example"));

	window->keyEvent = handleKeyPresses;

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
