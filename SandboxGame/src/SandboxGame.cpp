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
		HS_LOG(std::cout, "Hello from client");
		return true;
	}
private:

};

class ExampleLayer : public husky::Layer
{
public:
	void OnAttach() override
	{
		HS_LOG(std::cout, "Attaching example layer");
		m_heart = husky::Renderer::LoadTextureFromBMP("80s_heart.bmp", "sprites");
		m_font = husky::Renderer::LoadFontFromTTF("aesymatt.ttf", 30, "fonts");
	}

	void OnDetach() override
	{
		HS_LOG(std::cout, "Detaching example layer");
		delete m_heart;
		delete m_font;
		delete m_text;
	}

	bool OnEvent(SDL_Event& e) override
	{
		if (e.type == SDL_KEYDOWN)
		{
			HS_LOG(std::cout, "Keydown event");
			return true;
		}

		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			HS_LOG(std::cout, "Mousedown event");
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
		m_text = husky::Renderer::RenderText(m_message, m_font, husky::Color(0, 0, 0, 255), husky::TextRenderMode::Solid, husky::Color(255, 255, 255, 255));
		husky::Renderer::DrawTexture(m_text, m_text_pos);
	}

	void OnImGuiRender() override
	{
		bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

private:
	husky::Texture* m_heart = nullptr;
	husky::Texture* m_text = nullptr;
	husky::Font* m_font = nullptr;
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