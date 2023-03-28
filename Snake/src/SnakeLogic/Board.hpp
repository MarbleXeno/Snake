#pragma once
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <Farfocel/Core/Renderer.hpp>
#include <Farfocel/Managers/InputManager.hpp>

#include <Farfocel/Managers/ResourcesManager.hpp>

#include <Farfocel/Utils/GUI/Widgets/Text.hpp>

#include <imgui.h>
#include <imgui-SFML.h>

#include "Cell.hpp"
#include "Snake.hpp"

namespace gm {
	class Board {
	public:
		Board(fr::Renderer& renderer, const float& tickDuration, const sf::Font& font);
		~Board();

				//each cell size will be calculated automatically
		void GenerateBoard(const sf::Vector2i& cellCount, const sf::Vector2f& gridSize, const sf::Color& emptyCellColor);
		
		void PlaceBuff();
		
		Cell GetNextCell(Cell& snakeHeadCell, const CellMovingDirection& currentMovingDirection);
		void ApplySnakeCellsToBoard();
		const bool CheckForBoardBoundary(const sf::Vector2i index);
		
		void SetHighestScore(const std::uint32_t& score);

		const std::uint32_t& GetCurrentScore();
		const bool& IsOver();

		void Update();

		void Draw();
	private:
		fr::Renderer* mRenderer;
		fr::InputManager mInputManager;
		fr::ResourcesManager mResourcesManager;
		sf::Vector2i mCellCount;
		sf::Vector2f mCellSize;

		std::vector<Snake> mSnakes;
		float mTickDuration;
		float mBoardUpdateElapsedTime;

		Cell** mBoardCellArray;

		bool mIsOver;

		// Scoreboard
		const sf::Font* mFont;
		frg::Text mCurrentScore;
		frg::Text mHighestScore;

	};
}