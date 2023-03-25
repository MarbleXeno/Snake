#pragma once
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <Farfocel/Core/Renderer.hpp>
#include <Farfocel/Managers/InputManager.hpp>


#include "Cell.hpp"
#include "Snake.hpp"

namespace gm {
	class Board {
	public:
		Board(fr::Renderer& renderer);
		~Board();

				//each cell size will be calculated automatically
		void GenerateBoard(const sf::Vector2i& cellCount, const sf::Vector2f& gridSize, const sf::Color& emptyCellColor);
		void PlaceBuff();
		
		Cell GetNextCell(Cell& snakeHeadCell, const CellMovingDirection& currentMovingDirection);
		void ApplySnakeCellsToBoard();
		
		void Update(const float& tickSpeed);

		void Draw();
	private:
		fr::Renderer* mRenderer;
		fr::InputManager mInputManager;

		sf::Vector2i mCellCount;
		sf::Vector2f mCellSize;

		std::vector<Snake> mSnakes;

		float mBoardUpdateElapsedTime;

		Cell** mBoardCellArray;
	};
}