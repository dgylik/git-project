#include <SFML/Graphics.hpp> // прописываем библиотеку SFML
#include <iostream>
sf::RenderWindow window; //создаем окно с названием window
//sf::CircleShape circle(70,4); //создаем круг, 70 - радиус, 4 - кол-во углов
//sf::RectangleShape rectangle(sf::Vector2f(150, 5)); // создаем прямоугольник длиной 150 и высотой 5
sf::Image image;
sf::Texture texture;
sf::Sprite sprite; // прямоугольник, выводящий фигуру из image на экран(сдесь его создание)
int speed=5; //скорость движения
float CurrentFrame = 0; 


sf::Clock cloak; // время



int main() 
{
	
	window.create(sf::VideoMode(300, 300), "Test"); //параметры окна: размер 640/480 + имя
	window.setFramerateLimit(60);  //ограничение 60 фпс

	image.loadFromFile("1.png"); // загружаем картинку
	texture.loadFromImage(image);    // загружаем текстуру из картинки
	sprite.setTexture(texture);      // вносим тестуру в прямоугольник
	sprite.setPosition(240, 200);      // место на экране

	sprite.setTextureRect(sf::IntRect(0, 0, 17, 15));
	
	/*Круг
	circle.setFillColor(sf::Color::Yellow); // цвет круга 
	circle.setOutlineColor(sf::Color::Red);	// линия вокруг круга
	circle.setOutlineThickness(5);			// ширина линии вокруг круга
	circle.setPosition(250, 170);			// позиция круга
	circle.rotate(45);						// разворачивает фигуру на n(45) - градусов */

	/*Прямоугольник
	rectangle.setFillColor(sf::Color::Cyan);// задаем голубой цвет прямоугольника
	rectangle.setPosition(250, 220);        // позиция прямоугольника */

	while (window.isOpen()) //Не дает окну закрыться (пока окно открыто)
	{
		float time = cloak.getElapsedTime().asMicroseconds(); //функция, создает зависимость от времени
		cloak.restart();
		time = time / 800;
		
		


		sf::Event event;   //Создание события
		while (window.pollEvent(event)) //Уточнаем что за событие, запрашиваем событие
		{
			if (event.type == sf::Event::Closed) //Когда нажимаем на крестик окно закрывается
			{
				window.close();
			}
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))   // Движение персонажа
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
		



		window.clear(sf::Color::Black); //задний фон черный 
		//window.draw(circle);   // рисуем круг
		//window.draw(rectangle);// рисуем прямоугольник
		window.draw(sprite);
		window.display();

	}
	
	return 0;
}



