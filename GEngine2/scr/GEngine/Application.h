#pragma once
#include "Core.h"
namespace GEngine {

	class WIN_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	//to be defined in CLinet;
	Application* CreateApplication();
}

