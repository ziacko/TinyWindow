#include "TinyWindow.h"
//#include "TutorialConfig.h"

void blarg(GLuint Key, GLboolean KeyState)
{
	//do something here
}

int main()
{
	windowManager::Initialize();

	windowManager::AddWindow("Example");

	windowManager::SetWindowOnKeyEventByIndex(0, blarg);

	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	while (!windowManager::GetWindowShouldCloseByIndex(0))
	{
		windowManager::PollForEvents();// or WaitForEvents
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		windowManager::MakeWindowCurrentContextByIndex(0);
		windowManager::WindowSwapBuffersByIndex(0);
	}

	windowManager::ShutDown();
	return 0;
}