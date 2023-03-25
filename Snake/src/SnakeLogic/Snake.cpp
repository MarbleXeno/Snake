#include "Snake.hpp"

gm::Snake::Snake()
	: mAlternativeControls(false), mSnakeName("Snake"), mSnakeScore(0), mNextCellMovingDirection(CellMovingDirection::UP)
{
}

gm::Snake::Snake(Cell& initCell, const std::string& snakeName, const bool& alternativeControls)
	: mAlternativeControls(alternativeControls), mSnakeName(snakeName), mSnakeScore(0), mNextCellMovingDirection(CellMovingDirection::UP)
{
	mSnakeCells.push_back(Cell(CellType::SNAKE_HEAD, { initCell.GetCellGridPosition().x, initCell.GetCellGridPosition().y }, {initCell.GetFloatRect().left, initCell.GetFloatRect().height * (initCell.GetCellGridPosition().y), initCell.GetFloatRect().width, initCell.GetFloatRect().height}, sf::Color::Yellow));
	mSnakeCells.back().SetCellMovingDirection(CellMovingDirection::UP);

	mSnakeCells.push_back(Cell(CellType::SNAKE_BODY, { initCell.GetCellGridPosition().x, initCell.GetCellGridPosition().y + 1 }, { initCell.GetFloatRect().left, initCell.GetFloatRect().height * (initCell.GetCellGridPosition().y + 1), initCell.GetFloatRect().width, initCell.GetFloatRect().height }, sf::Color::White));
	mSnakeCells.back().SetCellMovingDirection(CellMovingDirection::UP);

	mSnakeCells.push_back(Cell(CellType::SNAKE_TAIL, { initCell.GetCellGridPosition().x, initCell.GetCellGridPosition().y + 2}, { initCell.GetFloatRect().left, initCell.GetFloatRect().height * (initCell.GetCellGridPosition().y + 2), initCell.GetFloatRect().width, initCell.GetFloatRect().height }, sf::Color::Blue));
	mSnakeCells.back().SetCellMovingDirection(CellMovingDirection::UP);

}

gm::Snake::~Snake()
{

}

gm::Cell gm::Snake::Move(Cell& nextCell, const bool& removeTail)
{
	// set old snake head as a normal body part
	mSnakeCells.front().SetCellType(CellType::SNAKE_BODY);
	mSnakeCells.front().SetColor(sf::Color::White);

	// set next cell as snake's current head
	mSnakeCells.push_front(nextCell);
	mSnakeCells.front().SetCellType(CellType::SNAKE_HEAD);
	mSnakeCells.front().SetColor(sf::Color::Yellow);

	// remove old tail from the snake
	Cell oldTail = mSnakeCells.back();
	if (removeTail) {
		mSnakeCells.pop_back();
	}

	// set the last snake cell as the current tail
	mSnakeCells.back().SetCellType(CellType::SNAKE_TAIL);
	mSnakeCells.back().SetColor(sf::Color::Blue);

	// return the old snake tail so that it can be applied to the board as just a normal cell
	if (removeTail) {
		oldTail.SetCellType(CellType::EMPTY);
		oldTail.SetColor(sf::Color::Black);
	}
	return oldTail;
}

void gm::Snake::Grow(Cell& nextCell)
{
	Move(nextCell, false);
	mSnakeScore++;
}

void gm::Snake::SetNextCellMovingDirection(const CellMovingDirection& movingDirection)
{
	mNextCellMovingDirection = movingDirection;
}

const gm::CellMovingDirection& gm::Snake::GetNextCellMovingDirection()
{
	return mNextCellMovingDirection;
}

const std::string& gm::Snake::GetSnakeName()
{
	return mSnakeName;
}

const std::uint32_t& gm::Snake::GetSnakeScore()
{
	return mSnakeScore;
}

const bool gm::Snake::IsSelfIntersecting(Cell& nextCell)
{
	for (auto& cell : mSnakeCells) {
		if (nextCell.GetCellGridPosition() == cell.GetCellGridPosition()) {
			return true;
		}
	}

	return false;
}

std::deque<gm::Cell>& gm::Snake::GetSnakeCells()
{
	return mSnakeCells;
}

gm::Cell& gm::Snake::GetSnakeHead()
{
	return mSnakeCells.front();
}

const bool& gm::Snake::GetAlternativeControls()
{
	return mAlternativeControls;
}
