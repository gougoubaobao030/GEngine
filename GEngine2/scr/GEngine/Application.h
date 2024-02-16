#pragma once
#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvnet.h"
#include "LayerStack.h"

namespace GEngine {

	class WIN_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer * layer);
		void PushOverLayer(Layer * layer);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	
	private:
		std::unique_ptr<Window> m_window;
		bool isRunning = true;
		LayerStack m_layerStack;
	};

	//to be defined in CLinet;
	Application* CreateApplication();
}


