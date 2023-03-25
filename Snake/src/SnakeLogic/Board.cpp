#include "Board.hpp"

gm::Board::Board(fr::Renderer& renderer)
	: mRenderer(&renderer), mInputManager(mRenderer->GetRenderWindow()), mSnakes(), mBoardCellArray(), mBoardUpdateElapsedTime(0)
{
	srand(time(NULL));

}

gm::Board::~Board()
{
}

void gm::Board::GenerateBoard(const sf::Vector2i& cellCount, const sf::Vector2f& gridSize, const sf::Color& emptyCellColor)
{
	mCellCount = cellCount;

	//Calculating each cell's size
	mCellSize.x = gridSize.x / mCellCount.x;
	mCellSize.y = gridSize.y / mCellCount.y;

	// allocating 2 dimensional array
								// row
	mBoardCellArray = new Cell*[mCellCount.x];
	for (int row = 0; row < mCellCount.x; row++) {
								// column
		mBoardCellArray[row] = new Cell[mCellCount.y];
	}

	for (int row = 0; row < mCellCount.x; row++)
	{
		for (int column = 0; column < mCellCount.y; column++) {
			
			mBoardCellArray[row][column] = Cell(CellType::EMPTY, {row, column}, { row * mCellSize.x, column * mCellSize.y, mCellSize.x, mCellSize.y}, emptyCellColor);
		}
	}


	mSnakes.push_back(Snake(mBoardCellArray[9][8], false));
	mSnakes.push_back(Snake(mBoardCellArray[3][3], true));
	ApplySnakeCellsToBoard();
}

void gm::Board::Update(const float& tickSpeed)
{
	for (auto& snake : mSnakes) {
		CellMovingDirection snakeMovingDirection;

		if (snake.GetAlternativeControls()) {
			if (mInputManager.IsPressed(sf::Keyboard::Up))
				snakeMovingDirection = CellMovingDirection::UP;
			else if (mInputManager.IsPressed(sf::Keyboard::Down))
				snakeMovingDirection = CellMovingDirection::DOWN;
			else if (mInputManager.IsPressed(sf::Keyboard::Left))
				snakeMovingDirection = CellMovingDirection::LEFT;
			else if (mInputManager.IsPressed(sf::Keyboard::Right))
				snakeMovingDirection = CellMovingDirection::RIGHT;
			else
				snakeMovingDirection = snake.GetSnakeHead().GetCellMovingDirection();
		}
		else
		{
			if (mInputManager.IsPressed(sf::Keyboard::W))
				snakeMovingDirection = CellMovingDirection::UP;
			else if (mInputManager.IsPressed(sf::Keyboard::S))
				snakeMovingDirection = CellMovingDirection::DOWN;
			else if (mInputManager.IsPressed(sf::Keyboard::A))
				snakeMovingDirection = CellMovingDirection::LEFT;
			else if (mInputManager.IsPressed(sf::Keyboard::D))
				snakeMovingDirection = CellMovingDirection::RIGHT;
			else
				snakeMovingDirection = snake.GetSnakeHead().GetCellMovingDirection();
		}

		snake.GetSnakeHead().SetCellMovingDirection(snakeMovingDirection);
		snake.SetNextCellMovingDirection(snakeMovingDirection);
	}

	mBoardUpdateElapsedTime += mRenderer->GetDeltaTimeFloat();

	if (mBoardUpdateElapsedTime > tickSpeed * mRenderer->GetDeltaTimeFloat()) {
		for (auto& snake : mSnakes) {
			Cell nextMovingCell = GetNextCell(snake.GetSnakeHead(), snake.GetNextCellMovingDirection());
			Cell oldTailCell = snake.Move(nextMovingCell);
			mBoardCellArray[oldTailCell.GetCellGridPosition().x][oldTailCell.GetCellGridPosition().y] = oldTailCell;
		}
		ApplySnakeCellsToBoard();

		mBoardUpdateElapsedTime = 0.f;
	}
}

gm::Cell gm::Board::GetNextCell(Cell& snakeHeadCell, const CellMovingDirection& currentMovingDirection)
{
	Cell nextCell;

	switch (currentMovingDirection)
	{
	case CellMovingDirection::UP:
		nextCell = mBoardCellArray[snakeHeadCell.GetCellGridPosition().x][snakeHeadCell.GetCellGridPosition().y - 1];
		nextCell.SetCellMovingDirection(currentMovingDirection);
		break;
	case CellMovingDirection::DOWN:
		nextCell = mBoardCellArray[snakeHeadCell.GetCellGridPosition().x][snakeHeadCell.GetCellGridPosition().y + 1];
		nextCell.SetCellMovingDirection(currentMovingDirection);
		break;
	case CellMovingDirection::LEFT:
		nextCell = mBoardCellArray[snakeHeadCell.GetCellGridPosition().x - 1][snakeHeadCell.GetCellGridPosition().y];
		nextCell.SetCellMovingDirection(currentMovingDirection);
		break;
	case CellMovingDirection::RIGHT:
		nextCell = mBoardCellArray[snakeHeadCell.GetCellGridPosition().x + 1][snakeHeadCell.GetCellGridPosition().y];
		nextCell.SetCellMovingDirection(currentMovingDirection);
		break;
	default:
		break;
	}

	return nextCell;
}

void gm::Board::ApplySnakeCellsToBoard()
{
	for (auto& snake : mSnakes) {
		for (auto& cell : snake.GetSnakeCells()) {
			mBoardCellArray[cell.GetCellGridPosition().x][cell.GetCellGridPosition().y] = cell;
		}
	}
}

void gm::Board::PlaceBuff()
{

}

void gm::Board::Draw()
{
	for (int row = 0; row < mCellCount.x; row++)
	{
		for (int column = 0; column < mCellCount.y; column++) {
			mRenderer->GetRenderWindow().draw(mBoardCellArray[row][column]);
		}
	}
}
