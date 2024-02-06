#pragma once

#include "GLFW/glfw3.h"
#include "GEngine/Window.h"

namespace GEngine {

	class WindowsWindow :public Window
	{
	private:
		GLFWwindow* m_gWindow;

		//caz we need to pass para to glfw(glfwgetuserpointer..), callback, so we use this struct
		//and do not need pass all class, 
		struct WindowDate
		{
			std::string title;
			unsigned int width;
			unsigned int height;

			bool VSync;

			EventCallbackFn eventCallback;
		};

		WindowDate m_WindowData;
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const { return m_WindowData.width; }
		inline unsigned int GetHeight() const { return m_WindowData.height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_WindowData.eventCallback = callback; }
		void SetVSync(bool isEnable) override;
		bool IsVSync() const override;

	private:
		void Init(const WindowProps& props);
		void Shutdown();
	};
}

