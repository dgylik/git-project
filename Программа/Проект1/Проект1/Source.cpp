#include <SFML/Graphics.hpp> // ����������� ���������� SFML
#include <iostream>
sf::RenderWindow window; //������� ���� � ��������� window
//sf::CircleShape circle(70,4); //������� ����, 70 - ������, 4 - ���-�� �����
//sf::RectangleShape rectangle(sf::Vector2f(150, 5)); // ������� ������������� ������ 150 � ������� 5
sf::Image image;
sf::Texture texture;
sf::Sprite sprite; // �������������, ��������� ������ �� image �� �����(����� ��� ��������)
int speed=5; //�������� ��������
float CurrentFrame = 0; 


sf::Clock cloak; // �����



int main() 
{
	
	window.create(sf::VideoMode(300, 300), "Test"); //��������� ����: ������ 640/480 + ���
	window.setFramerateLimit(60);  //����������� 60 ���

	image.loadFromFile("1.png"); // ��������� ��������
	texture.loadFromImage(image);    // ��������� �������� �� ��������
	sprite.setTexture(texture);      // ������ ������� � �������������
	sprite.setPosition(240, 200);      // ����� �� ������

	sprite.setTextureRect(sf::IntRect(0, 0, 17, 15));
	
	/*����
	circle.setFillColor(sf::Color::Yellow); // ���� ����� 
	circle.setOutlineColor(sf::Color::Red);	// ����� ������ �����
	circle.setOutlineThickness(5);			// ������ ����� ������ �����
	circle.setPosition(250, 170);			// ������� �����
	circle.rotate(45);						// ������������� ������ �� n(45) - �������� */

	/*�������������
	rectangle.setFillColor(sf::Color::Cyan);// ������ ������� ���� ��������������
	rectangle.setPosition(250, 220);        // ������� �������������� */

	while (window.isOpen()) //�� ���� ���� ��������� (���� ���� �������)
	{
		float time = cloak.getElapsedTime().asMicroseconds(); //�������, ������� ����������� �� �������
		cloak.restart();
		time = time / 800;
		
		


		sf::Event event;   //�������� �������
		while (window.pollEvent(event)) //�������� ��� �� �������, ����������� �������
		{
			if (event.type == sf::Event::Closed) //����� �������� �� ������� ���� �����������
			{
				window.close();
			}
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))   // �������� ���������
		{	
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 2) CurrentFrame -= 2;
			sprite.setTextureRect(sf::IntRect(3+int(CurrentFrame)*15, 33, 16, 15));  // 1)19 33  2)34  47
			sprite.move(0, -speed/time);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 2) CurrentFrame -= 2;
			sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*18, 48, 17, 13));     //1) 19 47   2)33 15
			sprite.move(0, +speed/time);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 2) CurrentFrame -= 2;
			sprite.setTextureRect(sf::IntRect(int(CurrentFrame)*17, 0, 17, 15));
			sprite.move(+speed/time, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 2) CurrentFrame -= 2;
			sprite.setTextureRect(sf::IntRect(4+int(CurrentFrame)*14, 15, 16, 18));  //1) 18 16   2)34 30
			sprite.move(-speed/time, 0);
		}
		



		window.clear(sf::Color::Black); //������ ��� ������ 
		//window.draw(circle);   // ������ ����
		//window.draw(rectangle);// ������ �������������
		window.draw(sprite);
		window.display();

	}
	
	return 0;
}



