#include "TinyWindow.h"
//#include "TutorialConfig.h"
void handleKeyPresses(unsigned int key, TinyWindow::keyState_t keyState)
{
	if(keyState == TinyWindow::keyState_t::down)
	{
		printf("%c \t", key);
	}
}

int main()
{
	TinyWindow::windowManager::Initialize();

	TinyWindow::windowManager::AddWindow("Example");
	TinyWindow::windowManager::SetWindowOnKeyEventByName("Example", handleKeyPresses);

	while (!TinyWindow::windowManager::GetWindowShouldCloseByIndex(0))
	{
		glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
		TinyWindow::windowManager::PollForEvents();// or WaitForEvents
		
		TinyWindow::windowManager::MakeWindowCurrentContextByIndex(0);
		TinyWindow::windowManager::WindowSwapBuffersByIndex(0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	TinyWindow::windowManager::ShutDown();
	return 0;
}
