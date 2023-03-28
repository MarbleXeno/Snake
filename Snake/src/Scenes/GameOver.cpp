#include "GameOver.hpp"

gm::GameOver::GameOver(const std::string& id, fr::Renderer& renderer, const std::uint32_t& currentScore, const std::uint32_t& topScore, const std::string& topScoreName, sf::Font& font, fr::EventManager& eventManager, fr::ScenesManager& scenesManager)
	: IScene(id), mRenderer(&renderer), mFont(&font), mResourcesManager(), mInputManager(mRenderer->GetRenderWindow()), mCurrentScore(currentScore), mTopScore(topScore), mTopScoreName(topScoreName), mEventManager(&eventManager), mScenesManager(&scenesManager), mDrawImgui(false)
{
	mYouDiedText = frg::Text({ 600 / 2, 700 / 4 }, "Nie zyjesz", 80, 2, sf::Color::Red, *mFont);
	mCurrentScoreText = frg::Text({ 600 / 2, 700 / 3 }, "Twoj wynik: " + std::to_string(mCurrentScore), 20, 1, sf::Color::White, *mFont);
	mTopScoreText = frg::Text({ 600 / 2,700 / 2.8 }, "Najwiekszy wynik: " + std::to_string(mTopScore) + ", przez " + mTopScoreName, 20, 1, sf::Color::White, *mFont);

	if (currentScore > topScore) {
		mTopScoreTextNew = frg::Text({ 600 / 2,700 / 2.4 }, "Wow, udalo ci sie pobic rekord!", 20, 1, sf::Color::Green, *mFont);
		mTopScoreTextInformative = frg::Text({ 600 / 2,700 / 2.2 }, "Wpisz swoj nick: ", 20, 1, sf::Color::White, *mFont);
	}
	else {
		mUpoText = frg::Text({ 600 / 2,700 / 2.4 }, "Do pobicia rekordu brakuje ci: " + std::to_string(mTopScore - mCurrentScore), 20, 1, sf::Color::White, *mFont);
	}

	mGoBackButton = frg::Button({ 600 / 2,700 / 1.5 }, "ZAGRAJ PONOWNIE", 35, sf::Color::Color(0, 0, 0, 0), sf::Color::White, *mFont);
	mGoBackMenuButton = frg::Button({ 600 / 2,700 / 1.2 }, "WROC DO MENU", 35, sf::Color::Color(0, 0, 0, 0), sf::Color::White, *mFont);
}

gm::GameOver::~GameOver()
{

}

void gm::GameOver::Start()
{

	mEventManager->AddBinding(sf::Event::TextEntered, true, [=]() {
		if (mRenderer->GetWindowEvent().text.unicode == '\b') {
			if (!mTopScoreNewName.empty())
				mTopScoreNewName.erase(mTopScoreNewName.size() - 1, 1);
		}
		else if (mRenderer->GetWindowEvent().text.unicode < 128) {
			mTopScoreNewName += mRenderer->GetWindowEvent().text.unicode;
		}
		});
}

void gm::GameOver::HandleEvents()
{

}

void gm::GameOver::HandleInput()
{

}

void gm::GameOver::Update()
{
	if (mCurrentScore > mTopScore) {
		mTopScoreTextInformative.SetString("Wpisz swoj nick: " + mTopScoreNewName);
		mTopScoreTextInformative.SetTextPosition({ 600 / 2,700 / 2.2 });
	}

	if (mGoBackButton.GetBoundingBoxSize().contains(mInputManager.GetMouseRelativeCoords())) {
		mGoBackButton.SetTextFillColor(sf::Color::Yellow);

		if (mInputManager.IsPressed(sf::Mouse::Left)) {
			if (mCurrentScore > mTopScore) {
				std::string score = mTopScoreNewName + " " + std::to_string(mCurrentScore);
				mScoreFile.open("score.txt", std::ofstream::out | std::ofstream::trunc);
				mScoreFile << score;
				mScoreFile.close();
			}
			mScenesManager->Replace(new gm::Gameplay("gameplay", *mRenderer, *mScenesManager, *mFont, *mEventManager));
		}
	}
	else {
		mGoBackButton.SetTextFillColor(sf::Color::White);
	}

	if (mGoBackMenuButton.GetBoundingBoxSize().contains(mInputManager.GetMouseRelativeCoords())) {
		mGoBackMenuButton.SetTextFillColor(sf::Color::Yellow);

		if (mInputManager.IsPressed(sf::Mouse::Left)) {
			if (mCurrentScore > mTopScore) {
				std::string score = mTopScoreNewName + " " + std::to_string(mCurrentScore);
				mScoreFile.open("score.txt", std::ofstream::out | std::ofstream::trunc);
				mScoreFile << score;
				mScoreFile.close();
			}
			mScenesManager->Replace(new gm::Menu("gameplay", *mRenderer, *mScenesManager, *mFont, *mEventManager));
		}
	}
	else {
		mGoBackMenuButton.SetTextFillColor(sf::Color::White);
	}
}

void gm::GameOver::Draw()
{
	mRenderer->GetRenderWindow().clear(sf::Color::Black);
	mRenderer->GetRenderWindow().draw(mYouDiedText);
	mRenderer->GetRenderWindow().draw(mCurrentScoreText);
	mRenderer->GetRenderWindow().draw(mTopScoreText);

	if (mCurrentScore > mTopScore) {
		mRenderer->GetRenderWindow().draw(mTopScoreTextNew);
		mRenderer->GetRenderWindow().draw(mTopScoreTextInformative);

	}
	else {
		mRenderer->GetRenderWindow().draw(mUpoText);
	}

	mRenderer->GetRenderWindow().draw(mGoBackButton);
	mRenderer->GetRenderWindow().draw(mGoBackMenuButton);
}
