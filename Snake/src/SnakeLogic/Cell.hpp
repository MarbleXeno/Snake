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
			: mCellType(CellType::EMPTY), mCellMovingDirection(CellMovingDirection::DOWN), mCellGridPosition({0,0}), mCellRect(), mDraw(false)
		{
		
		}

		Cell(const CellType& cellType, const sf::Vector2i cellGridPosition, const sf::FloatRect& cellRect, const sf::Color& cellShapeColor)
			: mCellType(cellType), mCellMovingDirection(CellMovingDirection::DOWN), mCellGridPosition(cellGridPosition), mCellRect(cellRect), mCellShape({ cellRect.width, cellRect.height }), mDraw(false)
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
			if (mCellType == CellType::EMPTY) { mDraw = false; }
		}

		void SetCellMovingDirection(const CellMovingDirection& cellMovingDirection) {
			mCellMovingDirection = cellMovingDirection;

			switch (mCellMovingDirection)
			{
			case gm::CellMovingDirection::UP:
				mSprite.setRotation(-90);
				mSprite.setScale(1.f, 1.f);

				break;
			case gm::CellMovingDirection::DOWN:
				mSprite.setRotation(90);
				mSprite.setScale(1.f, 1.f);

				break;
			case gm::CellMovingDirection::LEFT:
				mSprite.setRotation(0);
				mSprite.setScale(-1.f, 1.f);
				break;
			case gm::CellMovingDirection::RIGHT:
				mSprite.setRotation(0);
				mSprite.setScale(1.f, 1.f);
				break;
			default:
				break;
			}
		}

		void SetCellPosition(const sf::Vector2i& cellGridPosition) {
			mCellRect.left = mCellRect.width * cellGridPosition.x;
			mCellRect.top = mCellRect.height * cellGridPosition.y;
			
			mCellGridPosition = cellGridPosition;
		}

		void SetTexture(sf::Texture& texture) {
			mSprite.setTexture(texture);
			mSprite.setOrigin(mSprite.getGlobalBounds().width / 2, mSprite.getGlobalBounds().height / 2);
			mSprite.setPosition(mCellShape.getPosition().x + mCellShape.getSize().x / 2, mCellShape.getPosition().y + mCellShape.getSize().y / 2);

			mDraw = true;
		}

		void CanDraw(const bool& canDraw) { mDraw = canDraw; }

		const CellType& GetCellType() {
			return mCellType;
		}

		const CellMovingDirection& GetCellMovingDirection() {
			return mCellMovingDirection;
		}

		const sf::FloatRect& GetFloatRect() {
			return mCellRect;
		}

		const sf::Vector2f GetCellPosition() {
			return mCellShape.getPosition();
		}

		const sf::Vector2i& GetCellGridPosition() {
			return mCellGridPosition;
		}

		void draw(sf::RenderTarget& target, sf::RenderStates states) const {
			target.draw(mCellShape);
			if(mDraw)
				target.draw(mSprite);
		}

	protected:
		CellType mCellType;
		CellMovingDirection mCellMovingDirection;
		
		sf::Vector2i mCellGridPosition;
		sf::FloatRect mCellRect;

		bool mDraw;
		sf::Sprite mSprite;

		sf::RectangleShape mCellShape;
	};
}