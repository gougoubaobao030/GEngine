#include "Application.h"
#include "Events/MouseEvent.h"
#include "Log.h"

namespace GEngine {
	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {

		MouseButtonPressedEvent e(3);
		GEngine_TRACE(e);
		if (e.IsInCategory(EventCategoryInput))
		{
			GEngine_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryApplication)) {

			GEngine_TRACE(e);
		}
	

		while (true);

	}
}
