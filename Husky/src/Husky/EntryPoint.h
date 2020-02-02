#pragma once

extern husky::Game* husky::CreateGame();

int main(int argc, char** argv)
{
	auto game = husky::CreateGame();

	game->Run();

	delete game;

	return 0;
}
