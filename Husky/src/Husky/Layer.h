#pragma once
#include <SDL.h>

namespace husky {

	class Layer
	{
	public:
		Layer() = default;
		virtual ~Layer() = default;

		//Called once when the layer is pushed.
		virtual void OnAttach() {}
		//Called once when the layer is popped.
		virtual void OnDetach() {}

		//Called every frame. Return false to indicate the layer should be popped.
		virtual bool OnUpdate(float delta_time) { return false; }

		//Called every frame. Place calls to Renderer here.
		virtual void OnRender() {}

		//Called on an event.
		//Return true to indicate the event has been handled or false to indicate that it should continue being propogated.
		virtual bool OnEvent(SDL_Event& e) { return false; }
	};

}
