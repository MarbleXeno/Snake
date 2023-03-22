#pragma once
#include <SFML/Graphics.hpp>
#include <Farfocel/Utils/IScene.hpp>
#include <Farfocel/Core/Renderer.hpp>
#include <Farfocel/Utils/GUI/Widgets/Button.hpp>
#include <Farfocel/Managers/ResourcesManager.hpp>
#include <Farfocel/Managers/InputManager.hpp>

#include "SnakeLogic/Board.hpp"

namespace gm {
	class Gameplay : public fr::IScene {
	public:
		Gameplay(const std::string& id, fr::Renderer& renderer, sf::Font& font);
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
		
		sf::Font* mFont;
		
		Board mBoard;
	};
}