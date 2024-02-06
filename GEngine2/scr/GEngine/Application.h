#pragma once
#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvnet.h"

namespace GEngine {

	class WIN_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	
	private:
		std::unique_ptr<Window> m_window;
		bool isRunning = true;
	};

	//to be defined in CLinet;
	Application* CreateApplication();
}


