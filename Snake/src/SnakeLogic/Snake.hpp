#pragma once
#include <Farfocel/Managers/InputManager.hpp>
#include <iostream>

#include "Cell.hpp"
namespace gm {
	class Snake {
	public:
		Snake() {}
		Snake(Cell** boardCells, const sf::Vector2i startingPosition);
		~Snake();

		void Move(const sf::Vector2i nextPosition);
		void ApplySnakeCells();

	private:
		Cell** mBoardCells;

		Cell mHeadCell;
		Cell mTailCell;
		std::vector<Cell> mBodyCells;
	};
}