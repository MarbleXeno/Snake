#pragma once
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <Farfocel/Core/Renderer.hpp>

#include "Cell.hpp"
#include "Snake.hpp"

namespace gm {
	class Board {
	public:
		Board(fr::Renderer& renderer);
		~Board();

				//each cell size will be calculated automatically
		void GenerateBoard(const sf::Vector2i& cellCount, const sf::Vector2f& gridSize, const sf::Color& emptyCellColor);
		void Update(const float& tickSpeed);
		void PlaceBuff();

		void Draw();
	private:
		fr::Renderer* mRenderer;
		sf::Vector2i mCellCount;
		sf::Vector2f mCellSize;

		Snake mSnake;

		Cell** mBoardCellArray;
	};
}