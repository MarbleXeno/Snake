#include "Snake.hpp"

gm::Snake::Snake(Cell** boardCells, const sf::Vector2i startingPosition)
	: mBoardCells(boardCells)
{
	mHeadCell = Cell(CellType::SNAKE_HEAD, startingPosition, mBoardCells[startingPosition.x][startingPosition.y].GetFloatRect(), sf::Color::Red);
	mBodyCells.push_back(Cell(CellType::SNAKE_BODY, { startingPosition.x, startingPosition.y + 1 }, mBoardCells[startingPosition.x][startingPosition.y + 1].GetFloatRect(), sf::Color::Blue));
	mBodyCells.push_back(Cell(CellType::SNAKE_TAIL, { startingPosition.x, startingPosition.y + 2 }, mBoardCells[startingPosition.x][startingPosition.y+2].GetFloatRect(), sf::Color::Yellow));


}

gm::Snake::~Snake()
{
}

void gm::Snake::Move(const sf::Vector2i nextPosition)
{

}

void gm::Snake::ApplySnakeCells()
{
}
