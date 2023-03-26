#pragma once
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Farfocel/Utils/IScene.hpp>
#include <Farfocel/Core/Renderer.hpp>
#include <Farfocel/Utils/GUI/Widgets/Button.hpp>
#include <Farfocel/Managers/ResourcesManager.hpp>
#include <Farfocel/Managers/InputManager.hpp>

#include "SnakeLogic/Board.hpp"
#include "Scenes/GameOver.hpp"

namespace gm {
	class Gameplay : public fr::IScene {
	public:
		Gameplay(const std::string& id, fr::Renderer& renderer, fr::ScenesManager& sceneManager, sf::Font& font, fr::EventManager& eventManager);
		~Gameplay();

		void Start();
		void HandleEvents();
		void HandleInput();
		void Update();
		void Draw();

	private:
		fr::Renderer* mRenderer;
		fr::ResourcesManager mResourcesManager;
		fr::InputManager mInputManager;
		fr::ScenesManager* mSceneManager;
		fr::EventManager& mEventManager;

		sf::Font* mFont;
		
		Board mBoard;

		std::fstream mScoreFile;

		std::map<std::string, std::uint32_t> mScores;
	};
}