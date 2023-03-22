#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

namespace frg {
	class Text : public sf::Drawable{
	public:
		Text() {}
		Text(const sf::Vector2f& position, const std::string& textString, const std::uint16_t& characterSize, const std::uint16_t& outlineSize, const sf::Color& fillColor, const sf::Font& font);
		~Text() {}

		void SetString(const std::string& textString);
		void SetFillColor(const sf::Color& color);

		const sf::Vector2f& GetTextSize() { return { mText.getGlobalBounds().width, mText.getGlobalBounds().height }; }

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	private:
		std::string mString;
		sf::Text mText;
		
		const sf::Font* mFont = nullptr;
	};
}