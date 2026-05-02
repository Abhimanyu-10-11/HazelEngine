#pragma once
#include"Core.h"
#include"Window.h"
#include"Events/ApplicationEvent.h"
#include"Hazel/Layer.h"
#include"Hazel/LayerStack.h"
namespace Hazel
{

	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnClick(Event& e);
		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
	private:
		bool OnWindowClosed(WindowCloseEvent& e);
		bool m_IsRunning = true;
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;

	};
	Application* CreateApplication();
}
