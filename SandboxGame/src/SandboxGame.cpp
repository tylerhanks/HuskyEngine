#include "Husky.h"
#include <iostream>

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

	bool OnUpdate(float dt) override
	{
		//HS_LOG(std::cout, "Frame time: " + std::to_string(dt));
		return true;
	}
private:

};

husky::Game* husky::CreateGame()
{
	return new SandboxGame();
}