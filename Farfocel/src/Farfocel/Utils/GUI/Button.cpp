#include "Farfocel/Utils/GUI/Widgets/Button.hpp"

frg::Button::Button()
{
}

frg::Button::Button(const sf::Vector2f& position, const std::string& textString, const std::uint16_t& characterSize, const sf::Color& backgroundColor, const sf::Color& textColor, const sf::Font& font)
{
	mText = frg::Text(position, textString, characterSize, 2, textColor, font);
	
	mBackground.setFillColor(backgroundColor);
	mBackground.setSize({ mText.GetTextSize().x + 20.f, mText.GetTextSize().y + 20.f });

	mBackground.setOrigin((mBackground.getLocalBounds().left + mBackground.getLocalBounds().width) / 2.f, (mBackground.getLocalBounds().top + mBackground.getLocalBounds().height) / 2.f);

	mBackground.setPosition(position);
}

frg::Button::~Button()
{
}

void frg::Button::SetString(const std::string& textString)
{
}

void frg::Button::SetTextFillColor(const sf::Color& color)
{
	mText.SetFillColor(color);
}

const sf::FloatRect frg::Button::GetBoundingBoxSize()
{
	return mBackground.getGlobalBounds();
}

void frg::Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mBackground);
	target.draw(mText);

}