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
		Snake(Cell& initCell, const std::string& snakeName, const bool& alternativeControls);
		~Snake();

		Cell Move(Cell& nextCell, const bool& removeTail);
		void Grow(Cell& nextCell);
		
		void SetNextCellMovingDirection(const CellMovingDirection& movingDirection);
		const CellMovingDirection& GetNextCellMovingDirection();

		const std::string& GetSnakeName();
		const std::uint32_t& GetSnakeScore();

		const bool IsSelfIntersecting(Cell& nextCell);

		std::deque<Cell>& GetSnakeCells();
		Cell& GetSnakeHead();
		const bool& GetAlternativeControls();

	private:
		CellMovingDirection mNextCellMovingDirection;
		std::string mSnakeName;
		std::uint32_t mSnakeScore; // length

		std::deque<Cell> mSnakeCells;
		bool mAlternativeControls;
	};
}