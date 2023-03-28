#pragma once
#include <SFML/Graphics.hpp>
#include <Farfocel/Utils/IScene.hpp>
#include <Farfocel/Core/Renderer.hpp>
#include <Farfocel/Utils/GUI/Widgets/Button.hpp>
#include <Farfocel/Utils/GUI/Widgets/Text.hpp>
#include <Farfocel/Managers/ResourcesManager.hpp>
#include <Farfocel/Managers/InputManager.hpp>
#include <Farfocel/Managers/EventManager.hpp>

#include <iostream>
#include <fstream>

#include "Scenes/Gameplay.hpp"
#include "Menu.hpp"

namespace gm {
	class GameOver : public fr::IScene {
	public:
		GameOver(const std::string& id, fr::Renderer& renderer, const std::uint32_t& currentScore, const std::uint32_t& topScore, const std::string& topScoreName, sf::Font& font, fr::EventManager& eventManager, fr::ScenesManager& scenesManager);
		~GameOver();

		void Start();
		void HandleEvents();
		void HandleInput();
		void Update();
		void Draw();

	private:
		fr::Renderer* mRenderer;
		fr::ResourcesManager mResourcesManager;
		fr::InputManager mInputManager;
		fr::EventManager* mEventManager;
		fr::ScenesManager* mScenesManager;

		sf::Font* mFont;

		const std::uint32_t& mCurrentScore;
		const std::uint32_t& mTopScore;
		const std::string& mTopScoreName;

		bool mDrawImgui;

		std::string mTopScoreNewName;

		frg::Text mYouDiedText;
		frg::Text mCurrentScoreText;
		frg::Text mTopScoreText;
		frg::Text mTopScoreTextNew;
		frg::Text mTopScoreTextInformative;
		frg::Text mUpoText;

		frg::Button mGoBackButton;
		frg::Button mGoBackMenuButton;

		std::fstream mScoreFile;
	};
}