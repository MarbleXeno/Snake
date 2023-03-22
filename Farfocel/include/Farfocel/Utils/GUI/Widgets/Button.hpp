#pragma once
#include <SFML/Graphics.hpp>

#include "Farfocel/Utils/GUI/Widgets/Text.hpp"

namespace frg {
	class Button : public sf::Drawable{
	public:
		Button();
		Button(const sf::Vector2f& position, const std::string& textString, const std::uint16_t& characterSize, const sf::Color& backgroundColor, const sf::Color& textColor, const sf::Font& font);
		~Button();

		void SetString(const std::string& textString);
		void SetTextFillColor(const sf::Color& color);

		const sf::FloatRect GetBoundingBoxSize();

	private:
		frg::Text mText;
		sf::RectangleShape mBackground;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}