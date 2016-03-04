#include "TinyWindow.h"
//#include "TutorialConfig.h"
void handleKeyPresses(unsigned int key, tinyWindowKeyState_t keyState)
{
	if(keyState == tinyWindowKeyState_t::DOWN)
	{
		printf("%c \t", key);
	}
}

int main()
{
	windowManager::Initialize();

	windowManager::AddWindow("Example");
	windowManager::SetWindowOnKeyEventByName("Example", handleKeyPresses);

	while (!windowManager::GetWindowShouldCloseByIndex(0))
	{
		glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
		windowManager::PollForEvents();// or WaitForEvents
		
		windowManager::MakeWindowCurrentContextByIndex(0);
		windowManager::WindowSwapBuffersByIndex(0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	windowManager::ShutDown();
	return 0;
}
