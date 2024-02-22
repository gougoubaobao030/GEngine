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
		//���Ǻ������Ϊ��callback���񣬢���application��windowҪ����һ��instance,��window��openglҲҪ
		//һ��instance ���instance����m_WindowData
		glfwSetWindowUserPointer(m_gWindow, &m_WindowData);


		//callback������init�����ԭ�����ǳ�ʼ����ʱ��ͽ���(bind)��ʲô�ĺ������ã����á����ǵ��ã������ǻص���
		glfwSetWindowSizeCallback(m_gWindow, [](GLFWwindow* window, int width, int height) {

			//�²⣬���userPointer����һ���ɽ�ȥ���Եף�����ÿ��ƴ��ڵľ�������������ַ��䶯����...
			// ����ֱ��return��????(��������???)
			//��&˵�����ֵ�Ѿ����ڣ������µ�ֵ
			WindowDate& wd = *(WindowDate*)glfwGetWindowUserPointer(window);
			wd.width = width;
			wd.height = height;

			WindowResizeEvnet e(width, height);

			//�����wd���� ǰ��setwindowuserpointer���m_windowData
			//eventCallback�Ѿ����ó�application::onevent���pointer;
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