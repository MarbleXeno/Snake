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

	class Cell : public sf::Drawable {
	public:
		Cell() 
			: mCellType(CellType::EMPTY), mCellGridPosition({0,0}), mCellRect(), mDrawSprite(false)
		{
		
		}

		Cell(const CellType& cellType, const sf::Vector2i cellGridPosition, const sf::FloatRect& cellRect, const sf::Color& cellShapeColor)
			: mCellType(cellType), mCellGridPosition(cellGridPosition), mCellRect(cellRect), mCellSprite(), mDrawSprite(false), mCellShape({ cellRect.width, cellRect.height })
		{
			mCellShape.setFillColor(cellShapeColor);
			mCellShape.setOutlineColor(sf::Color::White);
			mCellShape.setOutlineThickness(2.f);
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

		const CellType& GetCellType() {
			return mCellType;
		}

		const sf::FloatRect& GetFloatRect() {
			return mCellRect;
		}

		const sf::Vector2i& GetCellGridPosition() {
			return mCellGridPosition;
		}

		void SetCellTexture(const sf::Texture& texture) {
			mCellSprite.setTexture(texture);
			mDrawSprite = true;
		}

		void draw(sf::RenderTarget& target, sf::RenderStates states) const {
			target.draw(mCellShape);
			if (mDrawSprite)
				target.draw(mCellSprite);
		}

	protected:
		CellType mCellType;
		sf::Vector2i mCellGridPosition;
		sf::FloatRect mCellRect;
		
		bool mDrawSprite;
		sf::RectangleShape mCellShape;
		sf::Sprite mCellSprite;
	};
}