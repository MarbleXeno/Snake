#pragma once
#include <SFML/Graphics.hpp>
namespace gm {
	enum class CellType {
		EMPTY = 0,
		BUFF = 1,
		SNAKE_HEAD = 2,
		SNAKE_BODY = 3,
		SNAKE_TAIL = 4
	};

	enum class CellMovingDirection {
		UP = 0,
		DOWN = 1,
		LEFT = 2,
		RIGHT = 3
	};

	class Cell : public sf::Drawable {
	public:
		Cell() 
			: mCellType(CellType::EMPTY), mCellMovingDirection(CellMovingDirection::DOWN), mCellGridPosition({0,0}), mCellRect()
		{
		
		}

		Cell(const CellType& cellType, const sf::Vector2i cellGridPosition, const sf::FloatRect& cellRect, const sf::Color& cellShapeColor)
			: mCellType(cellType), mCellMovingDirection(CellMovingDirection::DOWN), mCellGridPosition(cellGridPosition), mCellRect(cellRect), mCellShape({ cellRect.width, cellRect.height })
		{
			mCellShape.setFillColor(cellShapeColor);
			mCellShape.setOutlineColor(sf::Color::White);
			mCellShape.setOutlineThickness(1.f);
			mCellShape.setPosition({ cellRect.left, cellRect.top });
		}
		~Cell() {

		}

		void SetColor(const sf::Color& color) {
			mCellShape.setFillColor(color);
		}

		void SetCellType(const CellType& cellType) {
			mCellType = cellType;
		}

		void SetCellMovingDirection(const CellMovingDirection& cellMovingDirection) {
			mCellMovingDirection = cellMovingDirection;
		}

		void SetCellPosition(const sf::Vector2i& cellGridPosition) {
			mCellRect.left = mCellRect.width * cellGridPosition.x;
			mCellRect.top = mCellRect.height * cellGridPosition.y;
			
			mCellGridPosition = cellGridPosition;

			mCellShape.setPosition({ mCellRect.left, mCellRect.top });
		}

		const CellType& GetCellType() {
			return mCellType;
		}

		const CellMovingDirection& GetCellMovingDirection() {
			return mCellMovingDirection;
		}

		const sf::FloatRect& GetFloatRect() {
			return mCellRect;
		}

		const sf::Vector2i& GetCellGridPosition() {
			return mCellGridPosition;
		}

		void draw(sf::RenderTarget& target, sf::RenderStates states) const {
			target.draw(mCellShape);
		}

	protected:
		CellType mCellType;
		CellMovingDirection mCellMovingDirection;
		
		sf::Vector2i mCellGridPosition;
		sf::FloatRect mCellRect;
		
		sf::RectangleShape mCellShape;
	};
}