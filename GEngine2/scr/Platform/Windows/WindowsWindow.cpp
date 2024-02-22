#include "gepch.h"
#include "WindowsWindow.h"
#include "GEngine/Events/ApplicationEvnet.h"
#include "GEngine/Events/KeyEvent.h"
#include "GEngine/Events/MouseEvent.h"


namespace GEngine {

	//not belong to windows window ,but glfw only once;

	static bool s_isGLFWInitialized = false;

	static void ErrorCallbackFn(int error, const char* description) {
		GE_CORE_ERROR("GLFW ERROR: { 0 }: { 1 }", error, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {
		Init(props);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props) {
		m_WindowData.title = props.title;
		m_WindowData.width = props.width;
		m_WindowData.height = props.height;

		GE_CORE_INFO("Create WindowsWindow {0}, ({1}, {2})",
			m_WindowData.title, m_WindowData.width, m_WindowData.height);

		//init glfw only once
		if (!s_isGLFWInitialized) {

			int success = glfwInit();

			//need something to do
			GE_CORE_ASSERT(success, "Could not initialize GLFW")
			glfwSetErrorCallback(ErrorCallbackFn);
			s_isGLFWInitialized = true;
		}

		m_gWindow = glfwCreateWindow(m_WindowData.width, m_WindowData.height, m_WindowData.title.c_str(), NULL, NULL);
		glfwMakeContextCurrent(m_gWindow);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GE_CORE_ASSERT(status, "Glad is failed in initialize --gougou");
		//①是好像就是为了callback服务，②是application到window要生成一个instance,那window到opengl也要
		//一个instance 这个instance就是m_WindowData
		glfwSetWindowUserPointer(m_gWindow, &m_WindowData);


		//callback设置在init里面的原因大概是初始化的时候就进行(bind)啊什么的函数设置，设置。不是调用，调用是回调。
		glfwSetWindowSizeCallback(m_gWindow, [](GLFWwindow* window, int width, int height) {

			//猜测，这个userPointer就是一个派进去的卧底，来获得控制窗口的句柄？而且这个地址会变动所以...
			// 不能直接return啊????(是这样吗???)
			//用&说明这个值已经存在，不是新的值
			WindowDate& wd = *(WindowDate*)glfwGetWindowUserPointer(window);
			wd.width = width;
			wd.height = height;

			WindowResizeEvnet e(width, height);

			//这里的wd就是 前面setwindowuserpointer里的m_windowData
			//eventCallback已经设置成application::onevent这个pointer;
			wd.eventCallback(e);
			});

		glfwSetWindowCloseCallback(m_gWindow, [](GLFWwindow* window) {
			WindowDate& wd = *(WindowDate*)glfwGetWindowUserPointer(window);

			WindowCloseEvent e;
			wd.eventCallback(e);
			});

		glfwSetKeyCallback(m_gWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {

			WindowDate& wd = *(WindowDate*)glfwGetWindowUserPointer(window);
			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressEvented e(key, 0);
				wd.eventCallback(e);
				break;
			}

			case GLFW_RELEASE:
			{
				KeyReleasedEvent e(key);
				wd.eventCallback(e);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressEvented e(key, 1);
				wd.eventCallback(e);
				break;
			}
			}
			});

		glfwSetMouseButtonCallback(m_gWindow, [](GLFWwindow* window, int button, int action, int mods) {
			WindowDate& wd = *(WindowDate*)glfwGetWindowUserPointer(window);

			switch (action)

			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent e(button);
				wd.eventCallback(e);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent e(button);
				wd.eventCallback(e);
				break;
			}
			}
			});

		glfwSetCursorPosCallback(m_gWindow, [](GLFWwindow* window, double xpos, double ypos) {
			WindowDate& wd = *(WindowDate*)glfwGetWindowUserPointer(window);
			MouseMovedEvent e((float)xpos, (float)ypos);
			wd.eventCallback(e);
			});

		glfwSetScrollCallback(m_gWindow, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowDate& wd = *(WindowDate*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent e((float)xoffset, (float)yoffset);
			wd.eventCallback(e);

			});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_gWindow);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_gWindow);
	}

	void WindowsWindow::SetVSync(bool isEnable) {
		if (isEnable == true) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}

		m_WindowData.VSync = isEnable;
	}

	bool WindowsWindow::IsVSync() const {
		return m_WindowData.VSync;
	}

}