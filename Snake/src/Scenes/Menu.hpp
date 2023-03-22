#pragma once
#include <SFML/Graphics.hpp>
#include <Farfocel/Utils/IScene.hpp>
#include <Farfocel/Core/Renderer.hpp>
#include <Farfocel/Utils/GUI/Widgets/Button.hpp>
#include <Farfocel/Managers/ResourcesManager.hpp>
#include <Farfocel/Managers/InputManager.hpp>

#include "Gameplay.hpp"

namespace gm {
	class Menu : public fr::IScene {
	public:
		Menu(const std::string& id, fr::Renderer& renderer, fr::ScenesManager& scenesManager, sf::Font& font);
		~Menu();

		void Start();
		void HandleEvents();
		void HandleInput();
		void Update();
		void Draw();

	private:
		fr::Renderer* mRenderer;
		fr::ScenesManager* mScenesManager;
		fr::ResourcesManager mResourcesManager;
		fr::InputManager mInputManager;
		
		sf::Font* mFont;
		
		sf::Sprite mBackgroundSprite;
		
		frg::Text mSnakeText;
		frg::Button mStartButton;
		frg::Text mCreditsText;

	};
}