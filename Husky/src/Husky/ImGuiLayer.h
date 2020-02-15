#pragma once
#include "Layer.h"

namespace husky {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;

		bool OnEvent(SDL_Event& e) override;

		bool OnUpdate(float dt) override;

		void Begin();
		void End();
	private:
		void ImGui_ImplSDL2_UpdateMousePosAndButtons();
		void ImGui_ImplSDL2_UpdateMouseCursor();
		void ImGui_ImplSDL2_NewFrame();
	};

}
