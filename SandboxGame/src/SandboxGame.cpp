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
	}

	void OnDetach() override
	{
		HS_LOG(std::cout, "Detaching example layer");
		delete m_heart;
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
			m_running = false;
			return true;
		}

		return false;
	}

	bool OnUpdate(float dt) override
	{
		return m_running;
	}

	void OnRender() override
	{
		husky::Renderer::DrawTexture(m_heart, 30, 40, 10);
	}

private:
	husky::Texture* m_heart = nullptr;
	bool m_running = true;
};

husky::Game* husky::CreateGame()
{
	SandboxGame* example = new SandboxGame();
	if (example->Construct(640, 480, false))
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