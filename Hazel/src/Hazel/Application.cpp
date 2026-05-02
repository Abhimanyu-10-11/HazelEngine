#include"hzpch.h"
#include "Application.h"
namespace Hazel
{

#define HZ_BIND_FU(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(HZ_BIND_FU(OnClick));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{


		while (m_IsRunning)
		{
			m_Window->OnUpdate();
			
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

		}
	}

	void Application::OnClick(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(HZ_BIND_FU(OnWindowClosed));

		HZ_CORE_TRACE(e.ToString());

		for (auto it = m_LayerStack.end();it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.handled)
				break;
		}

	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_IsRunning = false;
		return true;

	}
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}
	void Application::PopLayer(Layer* layer)
	{
		m_LayerStack.PopLayer(layer);
	}
}
