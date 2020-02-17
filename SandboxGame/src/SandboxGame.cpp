#include "Husky.h"

class SandboxGame : public husky::Game
{
public:
	SandboxGame()
	{
	}

protected:
	bool OnCreate() override
	{
		HS_LOG("Hello from client");
		return true;
	}
private:

};

class ExampleLayer : public husky::Layer
{
public:
	void OnAttach() override
	{
		HS_LOG("Attaching example layer");
		m_heart = husky::Renderer::LoadTextureFromBMP("80s_heart.bmp", "sprites", husky::colors::Black);
		m_font = husky::Renderer::LoadFontFromTTF("aesymatt.ttf", 30, "fonts");
	}

	void OnDetach() override
	{
		HS_LOG("Detaching example layer");
	}

	bool OnEvent(SDL_Event& e) override
	{
		if (e.type == SDL_KEYDOWN)
		{
			HS_LOG("Keydown event");
			return true;
		}

		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			HS_LOG("Mousedown event");
			//m_running = false;
			return true;
		}

		return false;
	}

	bool OnUpdate(float dt) override
	{
		//m_heart_pos += m_heart_vel * dt;
		m_counter++;
		m_message = "Hello! This is a variable: " + std::to_string(m_counter);

		return m_running;
	}

	void OnRender() override
	{
		husky::Renderer::DrawTexture(m_heart, m_heart_pos, 10);
		m_text = husky::Renderer::RenderTextSolid(m_message, m_font, husky::colors::Purple);
		auto text_shaded = husky::Renderer::RenderTextShaded("Shaded text", m_font, husky::colors::Blue, husky::colors::Maroon);
		auto text_blended = husky::Renderer::RenderTextBlended("Blended text", m_font, husky::colors::Black);
		husky::Renderer::DrawTexture(m_text, m_text_pos);
		husky::Renderer::DrawTexture(text_shaded, m_text_pos + husky::Vec2f(0.0f, 100.0f));
		husky::Renderer::DrawTexture(text_blended, m_text_pos + husky::Vec2f(0.0f, 200.0f));
	}

	void OnImGuiRender() override
	{
		bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

private:
	husky::ref<husky::Texture> m_heart = nullptr;
	husky::ref<husky::Texture> m_text = nullptr;
	husky::ref<husky::Font> m_font = nullptr;
	husky::Vec2f m_text_pos = { 100.0f, 200.0f };
	husky::Vec2f m_heart_pos = { 0.0f, 0.0f };
	husky::Vec2f m_heart_vel = { 100.0f, 0.0f };
	int m_counter = 0;
	std::string m_message = "";
	bool m_running = true;
};

husky::Game* husky::CreateGame()
{
	SandboxGame* example = new SandboxGame();
	if (example->Construct(1920, 1080, false))
	{
		example->SetAssetPath("SandboxGame", "assets");
		example->PushLayer(new ExampleLayer());
		return example;
	}

	else
	{
		return nullptr;
	}
}