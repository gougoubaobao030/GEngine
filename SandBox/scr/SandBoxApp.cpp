#include "gengine.h"

class SampleLayer : public GEngine::Layer {
public:
	SampleLayer(): Layer("SampleLayer") {}
	~SampleLayer(){}

	void OnEvent(GEngine::Event & e) override {
		GE_TRACE(e);

	}

	void OnUpdate() override {
		GE_INFO("SampleLayer: updated");
	}
};


class SandBox : public GEngine::Application {
public:
	SandBox() {
		PushLayer(new SampleLayer);
	}

	~SandBox() {

	}
};

GEngine::Application* GEngine::CreateApplication() {
	return new SandBox;
}