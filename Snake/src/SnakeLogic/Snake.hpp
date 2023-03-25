#pragma once
#include <Farfocel/Managers/InputManager.hpp>
#include <iostream>
#include <deque>

#include "Cell.hpp"
namespace gm {
	enum class SnakeMovingDirection {
		UP = 0,
		DOWN,
		LEFT,
		RIGHT
	};

	class Snake {
	public:
		Snake();
		Snake(Cell& initCell, const bool& alternativeControls);
		~Snake();

		Cell Move(Cell& nextCell);
		void Grow(Cell& nextCell);
		
		void SetNextCellMovingDirection(const CellMovingDirection& movingDirection);
		const CellMovingDirection& GetNextCellMovingDirection();

		std::deque<Cell>& GetSnakeCells();
		Cell& GetSnakeHead();
		const bool& GetAlternativeControls();

	private:
		CellMovingDirection mNextCellMovingDirection;

		std::deque<Cell> mSnakeCells;
		bool mAlternativeControls;
	};
}