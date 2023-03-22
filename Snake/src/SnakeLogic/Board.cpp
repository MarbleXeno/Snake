#include "Board.hpp"

gm::Board::Board(fr::Renderer& renderer)
	: mRenderer(&renderer)
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

	mSnake = Snake(mBoardCellArray, { 2,2 });
	mSnake.Move({ 2,3 });
}

void gm::Board::Update(const float& tickSpeed)
{

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
