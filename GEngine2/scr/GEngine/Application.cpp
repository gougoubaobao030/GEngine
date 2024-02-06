#include "gepch.h"
#include "Application.h"
#include "Events/MouseEvent.h"
#include "GLFW/glfw3.h"

namespace GEngine {
	Application::Application() {
		m_window = std::unique_ptr<Window> (Window::Create());
		m_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	Application::~Application() {

	}

	void Application::Run() {
	
		while (isRunning) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_window->OnUpdate();
		}

	}
	void Application::OnEvent(Event& e)
	{
		GEngine_CORE_TRACE(e);
		EvnetDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		  
		/*
		��ȫ������lambda��ʵ�֣�������һ���¹���ʵ����
		dispatcher.Dispatch<WindowCloseEvent>([=](WindowCloseEvent& e)->bool {
			isRunning = false;
			return true;
			});
		*/
	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		isRunning = false;
		return true;
	}
}
