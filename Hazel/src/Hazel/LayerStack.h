#pragma once
#include"Layer.h"
namespace Hazel
{

	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();
		void PushLayer(Layer* layer);
		void PushOverlay(Layer * overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer * overlay);
		
		inline std::vector<Layer*>::iterator begin() { return m_Layer.begin(); }
		inline std::vector<Layer*>::iterator end() { return m_Layer.end(); }
	private:
		std::vector<Layer*> m_Layer;
		std::vector<Layer*>::iterator m_LayerInsert;

	};
}
