#include "Board.hpp"

gm::Board::Board(fr::Renderer& renderer, const float& tickDuration)
	: mRenderer(&renderer), mInputManager(mRenderer->GetRenderWindow()), mSnakes(), mBoardCellArray(), mBoardUpdateElapsedTime(0), mTickDuration(tickDuration)
{
	srand((unsigned) time(NULL));
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


	mSnakes.push_back(Snake(mBoardCellArray[9][15], "Aspirant do 2 LO", false));
	ApplySnakeCellsToBoard();
	PlaceBuff();
}

void gm::Board::Update()
{
	ImGui::Begin("Board Controls");
	ImGui::SliderFloat("Tick Duration [ms]", &mTickDuration, 0.f, 100.f);
	
	

	for (auto& snake : mSnakes) {
		CellMovingDirection snakeMovingDirection;

		if (snake.GetAlternativeControls()) {
			if (mInputManager.IsPressed(sf::Keyboard::Up) && snake.GetSnakeHead().GetCellMovingDirection() != CellMovingDirection::DOWN)
				snakeMovingDirection = CellMovingDirection::UP;
			else if (mInputManager.IsPressed(sf::Keyboard::Down) && snake.GetSnakeHead().GetCellMovingDirection() != CellMovingDirection::UP)
				snakeMovingDirection = CellMovingDirection::DOWN;
			else if (mInputManager.IsPressed(sf::Keyboard::Left) && snake.GetSnakeHead().GetCellMovingDirection() != CellMovingDirection::RIGHT)
				snakeMovingDirection = CellMovingDirection::LEFT;
			else if (mInputManager.IsPressed(sf::Keyboard::Right) && snake.GetSnakeHead().GetCellMovingDirection() != CellMovingDirection::LEFT)
				snakeMovingDirection = CellMovingDirection::RIGHT;
			else
				snakeMovingDirection = snake.GetSnakeHead().GetCellMovingDirection();
		}
		else
		{
			if (mInputManager.IsPressed(sf::Keyboard::W) && snake.GetSnakeHead().GetCellMovingDirection() != CellMovingDirection::DOWN)
				snakeMovingDirection = CellMovingDirection::UP;
			else if (mInputManager.IsPressed(sf::Keyboard::S) && snake.GetSnakeHead().GetCellMovingDirection() != CellMovingDirection::UP)
				snakeMovingDirection = CellMovingDirection::DOWN;
			else if (mInputManager.IsPressed(sf::Keyboard::A) && snake.GetSnakeHead().GetCellMovingDirection() != CellMovingDirection::RIGHT)
				snakeMovingDirection = CellMovingDirection::LEFT;
			else if (mInputManager.IsPressed(sf::Keyboard::D) && snake.GetSnakeHead().GetCellMovingDirection() != CellMovingDirection::LEFT)
				snakeMovingDirection = CellMovingDirection::RIGHT;
			else
				snakeMovingDirection = snake.GetSnakeHead().GetCellMovingDirection();
		}

		snake.GetSnakeHead().SetCellMovingDirection(snakeMovingDirection);
		snake.SetNextCellMovingDirection(snakeMovingDirection);
	
		if (ImGui::Button("Grow Snake")) {
			Cell& nextMovingCell = GetNextCell(snake.GetSnakeHead(), snake.GetNextCellMovingDirection());
			snake.Grow(nextMovingCell);
		}
	}

	mBoardUpdateElapsedTime += mRenderer->GetDeltaTimeFloat();

	if (mBoardUpdateElapsedTime > mTickDuration * mRenderer->GetDeltaTimeFloat()) {
		for (auto& snake : mSnakes) {
			Cell& nextMovingCell = GetNextCell(snake.GetSnakeHead(), snake.GetNextCellMovingDirection());
			
			if (snake.IsSelfIntersecting(nextMovingCell)) {
				ImGui::End();
				mRenderer->GetRenderWindow().close();
				return;
				// execute like a crazy thing here you know
			}

			if (nextMovingCell.GetCellType() == CellType::BUFF) {
				snake.Grow(nextMovingCell);
				if(mTickDuration > 2)
					mTickDuration--;
				PlaceBuff();
			}

			if (nextMovingCell.GetCellType() == CellType::EMPTY) {
				Cell oldTailCell = snake.Move(nextMovingCell, true);
				mBoardCellArray[oldTailCell.GetCellGridPosition().x][oldTailCell.GetCellGridPosition().y] = oldTailCell;
			}
		
			ApplySnakeCellsToBoard();
			
		}
		mBoardUpdateElapsedTime = 0.f;
	}
	ImGui::End();
}

gm::Cell gm::Board::GetNextCell(Cell& snakeHeadCell, const CellMovingDirection& currentMovingDirection)
{
	Cell nextCell;
	sf::Vector2i nextCellIndex;
	switch (currentMovingDirection)
	{
	case CellMovingDirection::UP:
		nextCellIndex.x = snakeHeadCell.GetCellGridPosition().x;
		nextCellIndex.y = snakeHeadCell.GetCellGridPosition().y - 1;

		if (CheckForBoardBoundary(nextCellIndex)) {
			nextCell = mBoardCellArray[nextCellIndex.x][nextCellIndex.y];
			nextCell.SetCellMovingDirection(currentMovingDirection);
		}
		else
		{
			// execute YOU LOOSE SCREEN
			mRenderer->GetRenderWindow().close();
		}
		break;
	case CellMovingDirection::DOWN:
		nextCellIndex.x = snakeHeadCell.GetCellGridPosition().x;
		nextCellIndex.y = snakeHeadCell.GetCellGridPosition().y + 1;

		if (CheckForBoardBoundary(nextCellIndex)) {
			nextCell = mBoardCellArray[nextCellIndex.x][nextCellIndex.y];
			nextCell.SetCellMovingDirection(currentMovingDirection);
		}
		else
		{
			// execute YOU LOOSE SCREEN
			mRenderer->GetRenderWindow().close();
		}

		break;
	case CellMovingDirection::LEFT:
		nextCellIndex.x = snakeHeadCell.GetCellGridPosition().x - 1;
		nextCellIndex.y = snakeHeadCell.GetCellGridPosition().y;

		if (CheckForBoardBoundary(nextCellIndex)) {
			nextCell = mBoardCellArray[nextCellIndex.x][nextCellIndex.y];
			nextCell.SetCellMovingDirection(currentMovingDirection);
		}
		else
		{
			// execute YOU LOOSE SCREEN
			mRenderer->GetRenderWindow().close();
		}

		break;
	case CellMovingDirection::RIGHT:
		nextCellIndex.x = snakeHeadCell.GetCellGridPosition().x + 1;
		nextCellIndex.y = snakeHeadCell.GetCellGridPosition().y;

		if (CheckForBoardBoundary(nextCellIndex)) {
			nextCell = mBoardCellArray[nextCellIndex.x][nextCellIndex.y];
			nextCell.SetCellMovingDirection(currentMovingDirection);
		}
		else
		{

			// execute YOU LOOSE SCREEN
			mRenderer->GetRenderWindow().close();

		}

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

const bool gm::Board::CheckForBoardBoundary(const sf::Vector2i index)
{
	if (index.x < 0 || index.y < 0) { return false; }
	else if (index.x >= mCellCount.x || index.y >= mCellCount.y) { return false; }
	else { return true; }


}

void gm::Board::PlaceBuff()
{
	sf::Vector2i buffCellIndex;
	buffCellIndex.x = rand() % mCellCount.x;
	buffCellIndex.y = rand() % mCellCount.y;

	Cell& buffCell = mBoardCellArray[buffCellIndex.x][buffCellIndex.y];

	if (buffCell.GetCellType() != CellType::EMPTY) { PlaceBuff(); }

	buffCell.SetCellType(CellType::BUFF);
	buffCell.SetColor(sf::Color::Cyan);
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
