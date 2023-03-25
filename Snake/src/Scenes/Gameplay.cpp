#include "Gameplay.hpp"

gm::Gameplay::Gameplay(const std::string& id, fr::Renderer& renderer, sf::Font& font)
	: IScene(id), mRenderer(&renderer), mFont(&font), mResourcesManager(), mInputManager(mRenderer->GetRenderWindow()), mBoard(*mRenderer, 20.f)
{
}

gm::Gameplay::~Gameplay()
{
}

void gm::Gameplay::Start()
{
	mBoard.GenerateBoard({ 20,20 }, { 600, 600 }, sf::Color::Black);
}

void gm::Gameplay::HandleEvents()
{
}

void gm::Gameplay::HandleInput()
{
}

void gm::Gameplay::Update()
{
	mBoard.Update();
}

void gm::Gameplay::Draw()
{
	mRenderer->GetRenderWindow().clear(sf::Color::Black);

	mBoard.Draw();
}