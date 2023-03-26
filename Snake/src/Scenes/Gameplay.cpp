#include "Gameplay.hpp"

gm::Gameplay::Gameplay(const std::string& id, fr::Renderer& renderer, fr::ScenesManager& sceneManager, sf::Font& font, fr::EventManager& eventManager)
	: IScene(id), mRenderer(&renderer), mFont(&font), mResourcesManager(), mInputManager(mRenderer->GetRenderWindow()), mSceneManager(&sceneManager), mBoard(*mRenderer, 10.f, *mFont), mEventManager(eventManager)
{
}

gm::Gameplay::~Gameplay()
{
}

void gm::Gameplay::Start()
{
	mScoreFile.open("score.txt");
	std::string name = "BRAK";
	std::uint32_t score = 0;



	while (mScoreFile >> name >> score) {
		mScores[name] = score;
	}

	mBoard.GenerateBoard({ 20,20 }, { 600, 600 }, sf::Color::Black);

	mBoard.SetHighestScore(score);
}

void gm::Gameplay::HandleEvents()
{
}

void gm::Gameplay::HandleInput()
{
}

void gm::Gameplay::Update()
{
	if(!mBoard.IsOver())
		mBoard.Update();

	if (mBoard.IsOver()) {
		for (auto& score : mScores) {
			mSceneManager->Replace(new GameOver("gameover", *mRenderer, mBoard.GetCurrentScore(), score.second, score.first, *mFont, mEventManager, *mSceneManager));
		}
	}
}

void gm::Gameplay::Draw()
{
	mRenderer->GetRenderWindow().clear(sf::Color::Black);

	mBoard.Draw();
}
