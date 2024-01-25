#pragma once
#ifdef GE_PLATFORM_WINDOWS
#include "Application.h"

//extern GEngine::Application * GEngine::CreateApplication();

int main(int agrv, char** agrc) {

	std::cout << "GOUGOU Engine WElCOME" << std::endl; //include iostream in gengine.h
	std::cout << "GOUGOU Engine WElCOME Say Dont need extern" << std::endl; //include iostream in gengine.h
	auto app = GEngine::CreateApplication();
	app->Run();
	delete app;
}


#else
#error shabi
#endif