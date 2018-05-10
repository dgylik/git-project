#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h" //подключили код с картой
#include <sstream>

using namespace sf;

float pacmanteleporttimer = 0;
float CurrentFrame = 0;

class Entity {
protected:
	int x_0, y_0;
public:
	float dx, dy, x, y;
	int w, h, dir;
	bool life;
	Texture texture;
	Sprite sprite;
	String name;//враги могут быть разные, мы не будем делать другой класс для врага.всего лишь различим врагов по имени и дадим каждому свое действие в update в зависимости от имени
	Entity(Image &image, float X, float Y, int W, int H, String Name) {
		x = X; y = Y; w = W; h = H; name = Name;
		life = true;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
};



class Player :public Entity { // класс Игрока
public:
	int score = 0;
	int amount_of_points = 240;
	int amount_of_life = 3;
	
	
	Player(Image &image, float X, float Y, int W, int H, String Name) :Entity(image, X, Y, W, H, Name)
	{
		if (name == "pacman") {
			dir = 1;
			sprite.setTextureRect(IntRect(39, 3, w, h));
		}
	}
	
	void control(float time) 
	{
		CurrentFrame += 0.003*time;
		pacmanteleporttimer += time;
		if (life == true)
		{
			if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A))))
			{
				dir = 1;
			}
			else
			{
				if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
					dir = 2;
				}
				else
				{
					if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
						dir = 3;
					}
					else
					{
						if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
							dir = 4;
						}
					}
				}
			}
		}

		if (dir == 1) {
			if (pacmanteleporttimer > 500) { x -= 8; pacmanteleporttimer = 0; }
			if (CurrentFrame > 2) CurrentFrame -= 2;
			sprite.setTextureRect(IntRect(7 + (16 * int(CurrentFrame)), 19, 8, 8));
		}
		else {
			if (dir == 2) {
				if (pacmanteleporttimer > 500) { x += 8; pacmanteleporttimer = 0; }
				if (CurrentFrame > 2) CurrentFrame -= 2;
				sprite.setTextureRect(IntRect(7 + (16 * int(CurrentFrame)), 3, 8, 8));
			}
			else {
				if (dir == 3) {
					if (pacmanteleporttimer > 500) { y -= 8; pacmanteleporttimer = 0; }
					if (CurrentFrame > 2) CurrentFrame -= 2;
					sprite.setTextureRect(IntRect(7 + (16 * int(CurrentFrame)), 35, 8, 8));
				}
				else {
					if (dir == 4) {
						if (pacmanteleporttimer > 500) { y += 8; pacmanteleporttimer = 0; }
						if (CurrentFrame > 2) CurrentFrame -= 2;
						sprite.setTextureRect(IntRect(7 + (16 * int(CurrentFrame)), 51, 8, 8));
					}
				}
			}
		}
	}

	

	////////////////////////////////////////////////////////////////////UPDATE/////////////////////////////////////////////////////////////////////////////////////

	void update(float time,float pacmanteleporttimer) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
	{
		control(time);
		switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
		{
			case 1: dx = -1; dy = 0;   break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
			case 2: dx = 1; dy = 0;   break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
			case 3: dx = 0; dy = -1;   break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
			case 4: dx = 0; dy = 1;   break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
		}
		sprite.getPosition().x;
		sprite.getPosition().y;
	/*	if (life == false)
		{
			dir = 0;
			sprite.setTextureRect(IntRect(39 + (16 * int(CurrentFrame)), 3, 8, 8)); 
			amount_of_life--;
			life = true;
			if (CurrentFrame > 12) {
				CurrentFrame -= 12;
			}		
		}*/
		float *x_0 = &x;
		float *y_0 = &y;
		sprite.setPosition(x, y); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
		interactionWithMap();
		
	}
	

	void interactionWithMap()//ф-ция взаимодействия с картой
	{
		char a[38] = { '1', '3','4','5','6','7','8','9','q','w','e','r','t','y','u','i','o','a','s','d','f','g','h','j','k','l','z','x','c','v','n','m','.','!','@','#','$','\0'};
		for (int i = y/8; i < (y + h)/8; i++)//проходимся по тайликам, контактирующим с игроком,, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
			for (int j = x / 8; j < (x + w) / 8; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
			{
				for (int k = 0;k < 37;k++) 
				{
					if (TileMap[i][j] == a[k])//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
					{
						if (dy > 0)//если мы шли вниз,
						{
							y = i * 8 - h;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
						}
						if (dy < 0)
						{
							y = i * 8 + 8;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
						}
						if (dx > 0)
						{
							x = j * 8 - w;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
						}
						if (dx < 0)
						{
							x = j * 8 + 8;//аналогично идем влево
						}
						dir = 0;
					}

					if (TileMap[i][j] == '0')
					{ 
						score += 40;
						amount_of_points--;
						TileMap[i][j] = '2';//убираем камень, типа взяли бонус. можем и не убирать, кстати.
					}
					
					if (TileMap[i][j] == '>')
					{
						x = 8; y = 112;
					}
					if (TileMap[i][j] == 'p')
					{
						x = 168; y = 112;
					}
				}
			}
	}
	
	
};


class Enemy :public Entity {
public:
	Enemy(Image &image, float X, float Y, int W, int H, String Name) :Entity(image, X, Y, W, H, Name) {
		if (name == "red") {
			
			sprite.setTextureRect(IntRect(103, 68, w, h));
		}
		if (name == "pink") {
			sprite.setTextureRect(IntRect(103, 84, w, h));
		}
		if (name == "blue") {
			sprite.setTextureRect(IntRect(103, 100, w, h));
		}
		if (name == "orange") {
			sprite.setTextureRect(IntRect(103, 116, w, h));
		}
	}

	void control(float time)
	{
		pacmanteleporttimer += time;
		

		if (dir == 1) {
			if (pacmanteleporttimer > 500) { x -= 8; pacmanteleporttimer = 0; }
			if (CurrentFrame > 2) CurrentFrame -= 2;
			sprite.setTextureRect(IntRect(39 + (16 * int(CurrentFrame)), 68, 8, 8));
		}
		else {
			if (dir == 2) {
				if (pacmanteleporttimer > 500) { x += 8; pacmanteleporttimer = 0; }
				if (CurrentFrame > 2) CurrentFrame -= 2;
				sprite.setTextureRect(IntRect(7 + (16 * int(CurrentFrame)), 68, 8, 8));
			}
			else {
				if (dir == 3) {
					if (pacmanteleporttimer > 500) { y -= 8; pacmanteleporttimer = 0; }
					if (CurrentFrame > 2) CurrentFrame -= 2;
					sprite.setTextureRect(IntRect(71 + (16 * int(CurrentFrame)), 68, 8, 8));
				}
				else {
					if (dir == 4) {
						if (pacmanteleporttimer > 500) { y += 8; pacmanteleporttimer = 0; }
						if (CurrentFrame > 2) CurrentFrame -= 2;
						sprite.setTextureRect(IntRect(103 + (16 * int(CurrentFrame)), 68, 8, 8));
					}
				}
			}
		}
	}

	void interactionWithMap()//ф-ция взаимодействия с картой
	{
		int temp = 1;
		for (int i = y / 8; i < (y + h) / 8; i++)//проходимся по тайликам, контактирующим с игроком,, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
			for (int j = x / 8; j < (x + w) / 8; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
			{
				if (TileMap2[i][j] == '1')//если наш квадратик соответствует символу 1 (стена), то проверяем "направление скорости" персонажа:
				{
					if (dy > 0)//если мы шли вниз,
					{
						y = i * 8 - h;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
					}
					if (dy < 0)
					{
						y = i * 8 + 8;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
					}
					if (dx > 0)
					{
						x = j * 8 - w;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
					}
					if (dx < 0)
					{
						x = j * 8 + 8;//аналогично идем влево
					}
				//	temp = TileMap2[i][j];
				//	dir++;
				}
				if (TileMap2[i][j] == '2') 
				{
					int a, q = 4;
					int mas_dir[4] = {'1', '2', '3', '4'};
					

					if (TileMap2[i][j - 1] == '1')
					{
						mas_dir[0] = 0;q--;
					}
					if (TileMap2[i][j + 1] == '1') 
					{
						mas_dir[1] = 0;q--;
					}
					if (TileMap2[i - 1][j] == '1')
					{
						mas_dir[2] = 0;q--;
					}
					if (TileMap2[i + 1][j] == '1')
					{
						mas_dir[3] = 0;q--;
					}
							
					int *mas = new int[q];
					for (int d = 0;d < 4;d++) {
						if ((mas_dir[d] != 0)) {
							mas[d] = mas_dir[d];
						}
						a = rand() % q;
						dir = mas[a];
					}

				}
			}
	}

	void update(float time)
	{
		control(time);
		switch (dir)
		{
		case 1: dx = -1; dy = 0;   break;
		case 2: dx = 1; dy = 0;   break;
		case 3: dx = 0; dy = -1;   break;
		case 4: dx = 0; dy = 1;   break;
		}
		if (name == "red") {
			dir = 2;
			sprite.getPosition().x;
			sprite.getPosition().y;
			std::cout << "dir = " << dir<<'\n';
		}
		sprite.setPosition(x, y);
		interactionWithMap();
	}
};
////////////////////////////////////////////////////////////////////MAIN//////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	RenderWindow window(sf::VideoMode(224, 270), "PACMAN");
	Clock clock;

	Image map_image;//объект изображения для карты
	map_image.loadFromFile("images/Sprites.png");//загружаем файл для карты
	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом

	Image win_image;
	win_image.loadFromFile("images/win.png");
	Texture win;
	win.loadFromImage(win_image);
	Sprite s_win;
	s_win.setTexture(win);//заливаем текстуру спрайтом
	s_win.setTextureRect(IntRect(0, 0, 224, 270));
	
	Image pacmanImage;
	pacmanImage.loadFromFile("images/8.png");

	Image enemyImage;
	enemyImage.loadFromFile("images/8.png");

	Font font;//шрифт 
	font.loadFromFile("font/namco.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 8);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)

	Player pacman(pacmanImage, 104, 184, 8, 8,"pacman");//создаем объект pacman класса player,задаем "1.png" как имя файла+расширение, далее координата Х,У, ширина, высота.
	Enemy red(enemyImage, 16, 8, 8, 8, "red");
	//Enemy pink(enemyImage, 8, 8, 8, 8, "pink");
	//Enemy blue(enemyImage, 8, 8, 8, 8, "blue");
	//Enemy orange(enemyImage, 8, 8, 8, 8, "orange");

	while (window.isOpen())
	{
		
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time/800;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		pacman.update(time, pacmanteleporttimer);
		red.update(time);
		//////////////////////////////////////////////////////WIN//////////////////////////////////////////////////////////////////////////////////////////////////
		
			window.clear();

			for (int i = 0; i < HEIGHT_MAP; i++)
				for (int j = 0; j < WIDTH_MAP; j++)
				{
					if (TileMap[i][j] == '0')  s_map.setTextureRect(IntRect(8, 8, 8, 8));
					if (TileMap[i][j] == '1')  s_map.setTextureRect(IntRect(0, 0, 8, 8));
					if (TileMap[i][j] == '2')  s_map.setTextureRect(IntRect(24, 24, 8, 8));
					if (TileMap[i][j] == '3')  s_map.setTextureRect(IntRect(8, 0, 8, 8));
					if (TileMap[i][j] == '4')  s_map.setTextureRect(IntRect(104, 0, 8, 8));
					if (TileMap[i][j] == '5')  s_map.setTextureRect(IntRect(112, 0, 8, 8));
					if (TileMap[i][j] == '6')  s_map.setTextureRect(IntRect(216, 0, 8, 8));
					if (TileMap[i][j] == '7')  s_map.setTextureRect(IntRect(0, 8, 8, 8));
					if (TileMap[i][j] == '8')  s_map.setTextureRect(IntRect(104, 8, 8, 8));
					if (TileMap[i][j] == '9')  s_map.setTextureRect(IntRect(112, 8, 8, 8));
					if (TileMap[i][j] == 'q')  s_map.setTextureRect(IntRect(216, 8, 8, 8));
					if (TileMap[i][j] == 'w')  s_map.setTextureRect(IntRect(16, 16, 8, 8));
					if (TileMap[i][j] == 'e')  s_map.setTextureRect(IntRect(24, 16, 8, 8));
					if (TileMap[i][j] == 'r')  s_map.setTextureRect(IntRect(40, 16, 8, 8));
					if (TileMap[i][j] == 'b')  s_map.setTextureRect(IntRect(8, 24, 8, 8));
					if (TileMap[i][j] == 't')  s_map.setTextureRect(IntRect(16, 24, 8, 8));
					if (TileMap[i][j] == 'y')  s_map.setTextureRect(IntRect(40, 24, 8, 8));
					if (TileMap[i][j] == 'u')  s_map.setTextureRect(IntRect(16, 32, 8, 8));
					if (TileMap[i][j] == 'i')  s_map.setTextureRect(IntRect(24, 32, 8, 8));
					if (TileMap[i][j] == 'o')  s_map.setTextureRect(IntRect(40, 32, 8, 8));
					if (TileMap[i][j] == 'p')  s_map.setTextureRect(IntRect(24, 24, 8, 8));
					if (TileMap[i][j] == 'a')  s_map.setTextureRect(IntRect(0, 72, 8, 8));
					if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(8, 72, 8, 8));
					if (TileMap[i][j] == 'd')  s_map.setTextureRect(IntRect(216, 72, 8, 8));
					if (TileMap[i][j] == 'f')  s_map.setTextureRect(IntRect(40, 80, 8, 8));
					if (TileMap[i][j] == 'g')  s_map.setTextureRect(IntRect(176, 80, 8, 8));
					if (TileMap[i][j] == 'h')  s_map.setTextureRect(IntRect(80, 96, 8, 8));
					if (TileMap[i][j] == 'j')  s_map.setTextureRect(IntRect(88, 96, 8, 8));
					if (TileMap[i][j] == 'k')  s_map.setTextureRect(IntRect(104, 96, 8, 8));
					if (TileMap[i][j] == 'l')  s_map.setTextureRect(IntRect(120, 96, 8, 8));
					if (TileMap[i][j] == 'z')  s_map.setTextureRect(IntRect(136, 96, 8, 8));
					if (TileMap[i][j] == 'x')  s_map.setTextureRect(IntRect(80, 104, 8, 8));
					if (TileMap[i][j] == 'c')  s_map.setTextureRect(IntRect(136, 104, 8, 8));
					if (TileMap[i][j] == 'v')  s_map.setTextureRect(IntRect(0, 120, 8, 8));
					if (TileMap[i][j] == 'n')  s_map.setTextureRect(IntRect(80, 128, 8, 8));
					if (TileMap[i][j] == 'm')  s_map.setTextureRect(IntRect(88, 128, 8, 8));
					if (TileMap[i][j] == '.')  s_map.setTextureRect(IntRect(136, 128, 8, 8));
					if (TileMap[i][j] == '!')  s_map.setTextureRect(IntRect(0, 192, 8, 8));
					if (TileMap[i][j] == '@')  s_map.setTextureRect(IntRect(0, 200, 8, 8));
					if (TileMap[i][j] == '#')  s_map.setTextureRect(IntRect(216, 192, 8, 8));
					if (TileMap[i][j] == '$')  s_map.setTextureRect(IntRect(216, 200, 8, 8));


					s_map.setPosition(j * 8, i * 8);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

					window.draw(s_map);//рисуем квадратики на экран
				}

			std::ostringstream playerScore;    // объявили переменную
			playerScore << pacman.score;		//занесли в нее число очков, то есть формируем строку
			text.setString("score " + playerScore.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
			text.setPosition(5, 253);//задаем позицию текста, центр камеры
			window.draw(text);//рисую этот текст

			window.draw(pacman.sprite);//рисуем спрайт объекта p класса player
			window.draw(red.sprite);

			if (pacman.amount_of_points == 0)
			{
				pacman.dir = 0;
				window.draw(s_win);//рисуем спрайт объекта p класса player
			}
			window.display();
		}
	

	return 0;
}