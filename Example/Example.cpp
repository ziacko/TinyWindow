#include "TenyWindow.hpp"

int main()
{
	std::unique_ptr<TinyWindow::windowManager> manager = TinyWindow::windowManager::New();

	struct ExampleWindow : TinyWindow::tWindow
	{
		void onEvent_KeyEvent(TinyWindow::key_t key, TinyWindow::keyState_t keyState) override
		{
			if (keyState == TinyWindow::keyState_t::down && key == TinyWindow::key_t::spacebar)
			{
				printf("spacebar has been pressed \n");
			}
		}

		void onEvent_MouseWheel(TinyWindow::mouseScroll_t mouseScrollDirection) override
		{
			switch (mouseScrollDirection)
			{
			case TinyWindow::mouseScroll_t::down:
			{
				printf("mouse wheel down \n");
				break;
			}

			case TinyWindow::mouseScroll_t::up:
			{
				printf("mouse wheel up \n");
				break;
			}
			}
		}
	};

	auto window = manager->AddWindow<ExampleWindow>();

	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	while (!window->shouldClose)
	{
		manager->PollForEvents();

		window->SwapDrawBuffers();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}


	return 0;
}
