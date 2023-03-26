#include "Farfocel/Utils/GUI/Widgets/Text.hpp"

frg::Text::Text(const sf::Vector2f& position, const std::string& textString, const std::uint16_t& characterSize, const std::uint16_t& outlineSize, const sf::Color& fillColor, const sf::Font& font)
	: mString(textString), mText(), mFont(&font)
{
	mText.setFont(*mFont);
	mText.setString(mString);
	mText.setCharacterSize(characterSize);
	mText.setOutlineThickness(outlineSize);
	mText.setFillColor(fillColor);

	mText.setOrigin((mText.getLocalBounds().left + mText.getLocalBounds().width) / 2.f, (mText.getLocalBounds().top + mText.getLocalBounds().height) / 2.f);

	mText.setPosition(position);

}

void frg::Text::SetString(const std::string& textString)
{
	mString = textString;
	mText.setString(mString);
}

void frg::Text::SetFillColor(const sf::Color& color)
{
	mText.setFillColor(color);
}

void frg::Text::SetTextPosition(const sf::Vector2f& position)
{
	mText.setOrigin((mText.getLocalBounds().left + mText.getLocalBounds().width) / 2.f, (mText.getLocalBounds().top + mText.getLocalBounds().height) / 2.f);
	mText.setPosition(position);
}

void frg::Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mText);
}
