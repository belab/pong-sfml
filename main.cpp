#include <SFML/Graphics.hpp>
#include <iostream>

void clampPaddlePosition(sf::RectangleShape& p, float bottom)
{
	const auto& pos = p.getPosition();
	const auto& height = p.getLocalBounds().height;
	if(pos.y < 0)
		p.setPosition(pos.x, 0);
	else if((pos.y+height) > bottom)
		p.setPosition(pos.x, bottom-height);
}
void reflectVertical(const sf::FloatRect& rect, float& ballSpeedY, float bottom)
{
	if (rect.top < 0 || (rect.top+rect.height) > bottom)
	{
		ballSpeedY = -ballSpeedY;
	}
}
int main()
{
	int scorePlayer1 = 0;
	int scorePlayer2 = 0;

	sf::VideoMode videomode(400, 400);
	sf::RenderWindow window(videomode, "PONG");
	sf::CircleShape ball(10.0f);
	ball.setFillColor(sf::Color::White);
	ball.setPosition(100.0f, 200.0f);

	sf::RectangleShape player1({10.0f, 50.0f});
	player1.setFillColor(sf::Color::White);
	player1.setPosition(20.0f, 200.0f);

	sf::RectangleShape player2({10.0f, 50.0f});
	player2.setFillColor(sf::Color::White);
	player2.setPosition(370.0f, 200.0f);

	sf::RectangleShape mid({1.0f, 400.0f});
	mid.setFillColor(sf::Color::White);
	mid.setPosition(200.0f, 0.0f);

	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

	sf::Text textP1("0", font);
	textP1.setPosition(100.0f, 0.0f);
	textP1.setCharacterSize(20);
	textP1.setFillColor(sf::Color::White);

	sf::Text textP2("0", font);
	textP2.setPosition(300.0f - textP2.getLocalBounds().width, 0.0f);
	textP2.setCharacterSize(20);
	textP2.setFillColor(sf::Color::White);

	sf::Vector2<float> ballSpeed(0.05f, 0.05f);

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);
		window.draw(mid);
		window.draw(ball);
		window.draw(textP1);
		window.draw(textP2);
		window.draw(player2);
		window.draw(player1);

		window.display();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			player1.move(0, -0.1f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			player1.move(0, 0.1f);
		}
		clampPaddlePosition(player1, 400.0f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			player2.move(0, -0.1f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			player2.move(0, 0.1f);
		}
		clampPaddlePosition(player2, 400.f);

		ball.move(ballSpeed.x, ballSpeed.y);
		const auto& ballRectGlobal = ball.getGlobalBounds();
		if ((ballRectGlobal.left) < 0.0f)
		{
			scorePlayer1++;
			ball.setPosition(100.0f, 200.0f);
			textP1.setString(std::to_string(scorePlayer1));
		}
		if ((ballRectGlobal.left + 20.0f) > 400.0f)
		{
			scorePlayer2++;
			textP2.setString(std::to_string(scorePlayer2));
			ball.setPosition(100.0f, 200.0f);
		}
		reflectVertical(ballRectGlobal, ballSpeed.y, 400.0f);
		if (ballRectGlobal.intersects(player1.getGlobalBounds()))
		{
			ball.setPosition(player1.getPosition().x + 10.0f, ball.getPosition().y);
			ballSpeed.x = -ballSpeed.x;
		}
		else if (ballRectGlobal.intersects(player2.getGlobalBounds()))
		{
			ball.setPosition(player2.getPosition().x -20.0f, ball.getPosition().y);
			ballSpeed.x = -ballSpeed.x;
		}
	}
}