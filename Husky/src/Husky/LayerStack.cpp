#include "LayerStack.h"

husky::LayerStack::~LayerStack()
{
	for (Layer* l : m_layers)
	{
		l->OnDetach();
		delete l;
	}
}

void husky::LayerStack::PushLayer(Layer* layer)
{
	m_layers.push_back(layer);
	layer->OnAttach();
}

void husky::LayerStack::PopLayer(Layer* layer)
{
	auto it = std::find(m_layers.begin(), m_layers.end(), layer);
	m_layers.erase(it);
	layer->OnDetach();
	delete layer;
}
