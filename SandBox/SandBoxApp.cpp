#include "gengine.h"

class SandBox : public GEngine::Application {
public:
	SandBox() {

	}

	~SandBox() {

	}
};

GEngine::Application* GEngine::CreateApplication() {
	return new SandBox;
}