#include "gepch.h"
#include "Application.h"
#include "Events/MouseEvent.h"
#include "glad/glad.h"
//#include "GLFW/glfw3.h"
#include "imgui.h"

namespace GEngine {
	Application * Application::s_instance = nullptr;

	Application::Application() {
		m_window = std::unique_ptr<Window> (Window::Create());
		m_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		s_instance = this;
	}

	Application::~Application() {

	}

	void Application::Run() {
	
		while (isRunning) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);


			for (Layer* layer : m_layerStack) {
				layer->OnUpdate();
			}

			m_window->OnUpdate();


		}

	}
	void Application::OnEvent(Event& e)
	{
		GE_CORE_TRACE(e);
		EvnetDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		  
		/*
		完全可以用lambda来实现，下面是一个陈宫的实现例
		dispatcher.Dispatch<WindowCloseEvent>([=](WindowCloseEvent& e)->bool {
			isRunning = false;
			return true;
			});
		*/
		for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
		{
			//GE_CORE_ERROR("e OK");
			(*(--it))->OnEvent(e);
			//GE_CORE_ERROR("e1 OK");

			if (e.m_Handle) break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverLayer(Layer* layer) {
		m_layerStack.PushOverLayer(layer);
		layer->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		isRunning = false;
		return true;
	}
}
