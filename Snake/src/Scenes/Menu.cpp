#include "Menu.hpp"

gm::Menu::Menu(const std::string& id, fr::Renderer& renderer, fr::ScenesManager& scenesManager, sf::Font& font, fr::EventManager& eventManager)
	: IScene(id), mRenderer(&renderer), mScenesManager(&scenesManager), mFont(&font), mResourcesManager(), mInputManager(mRenderer->GetRenderWindow()), mEventManager(eventManager)
{
}

gm::Menu::~Menu()
{
}

void gm::Menu::Start()
{
    mSnakeText = frg::Text({ mRenderer->GetRenderWindow().getSize().x / 2.f, mRenderer->GetRenderWindow().getSize().y / 2.f - 100.f }, "Wonz", 100, 2, sf::Color::White, *mFont);

	mStartButton = frg::Button({ mRenderer->GetRenderWindow().getSize().x/2.f, mRenderer->GetRenderWindow().getSize().y / 2.f + 200.f}, "START", 50, sf::Color(0,0,0,0), sf::Color::White, *mFont);
	
	mCreditsText = frg::Text({ mRenderer->GetRenderWindow().getSize().x / 2.f, mRenderer->GetRenderWindow().getSize().y / 2.f + 300.f }, "Farfocel � 2 LO Raciborz - 2m", 20, 2, sf::Color::White, *mFont);
	mCreditsTextTwo = frg::Text({ mRenderer->GetRenderWindow().getSize().x / 2.f, mRenderer->GetRenderWindow().getSize().y / 2.f + 322.f }, "Papaj / Grzes / Heino", 20, 2, sf::Color::White, *mFont);
	
	mResourcesManager.LoadTexture("background", "res/menu_background.png");
	mBackgroundSprite.setTexture(*mResourcesManager.GetTexture("background"));
}

void gm::Menu::HandleEvents()
{
}

void gm::Menu::HandleInput()
{
}

void gm::Menu::Update()
{
	mInputManager.UpdateKeyboard();
	mInputManager.UpdateMouse();

	if (mStartButton.GetBoundingBoxSize().contains(mInputManager.GetMouseRelativeCoords())) {
		mStartButton.SetTextFillColor(sf::Color::Yellow);

		if (mInputManager.IsPressed(sf::Mouse::Left)) {
			mScenesManager->Replace(new gm::Gameplay("gameplay", *mRenderer, *mScenesManager, *mFont, mEventManager));
		}
	}
	else {
		mStartButton.SetTextFillColor(sf::Color::White);
	}

}

void gm::Menu::Draw()
{
	mRenderer->GetRenderWindow().clear(sf::Color::Black);
	mRenderer->GetRenderWindow().draw(mBackgroundSprite);
	mRenderer->GetRenderWindow().draw(mSnakeText);
	mRenderer->GetRenderWindow().draw(mStartButton);
	mRenderer->GetRenderWindow().draw(mCreditsText);
	mRenderer->GetRenderWindow().draw(mCreditsTextTwo);
}
