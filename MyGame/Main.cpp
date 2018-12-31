//#include <iostream> 
//#include <SFML/Graphics.hpp>
//#include "map.h";
//#include "view.h";
//
//using namespace sf;//включаем пространство имен sf, чтобы постоянно не писать sf::
//
//class Player { // класс Игрока
//
//public:
//	float x, y, w, h, dx, dy, speed; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
//	bool life, isMove, isSelect, onGround;
//	int dir; //направление (direction) движения игрока
//	enum stateObject { left, right, up, down, jump, stay };
//	stateObject state;
//	String File; //файл с расширением
//	Image image;//сфмл изображение
//	Texture texture;//сфмл текстура
//	Sprite sprite;//сфмл спрайт
//
//	Player(String F, float X, float Y, float W, float H) { //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
//		life = true; isMove = false; isSelect = false; onGround = false; state = stay;
//		dx = 0; dy = 0; speed = 0; dir = 0;
//		File = F;//имя файла+расширение
//		w = W; h = H;//высота и ширина
//		image.loadFromFile("images/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная image.loadFromFile("images/hero/png");
//											 /*image.createMaskFromColor(Color(41, 33, 59));*///убираем ненужный темно-синий цвет, эта тень мне показалась не красивой.
//		texture.loadFromImage(image);//закидываем наше изображение в текстуру
//		sprite.setTexture(texture);//заливаем спрайт текстурой
//		x = X; y = Y;//координата появления спрайта
//		sprite.setTextureRect(IntRect(0, 0, w, h)); //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу. IntRect - приведение типов
//		sprite.setOrigin(w / 2, h / 2);
//	}
//	
//	void update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
//	{
//		switch (state)//тут делаются различные действия в зависимости от состояния
//		{
//		case right: dx = speed; break;//состояние идти вправо
//		case left: dx = -speed; break;//состояние идти влево
//		case up: break;//будет состояние поднятия наверх (например по лестнице)
//		case down: dx = 0; break;//будет состояние во время спуска персонажа (например по лестнице)
//		case jump: break;//здесь может быть вызов анимации
//		case stay: break;//и здесь тоже		
//		}
//		x += dx*time;
//		checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
//		y += dy*time;
//		checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y
//		if (!isMove) speed = 0;
//		sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
//		if (health <= 0) { life = false; }
//		dy = dy + 0.0015*time; //делаем притяжение к земле
//	
//		switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
//		{
//		case 0: dx = speed; dy = 0; break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
//		case 1: dx = -speed; dy = 0; break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
//		case 2: dx = 0; dy = speed; break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
//		case 3: dx = 0; dy = -speed; break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
//		}
//
//		x += dx*time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
//		y += dy*time;//аналогично по игреку
//
//		speed = 0;//зануляем скорость, чтобы персонаж остановился.
//		sprite.setPosition(x + w / 2, y + h / 2); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
//		interactionWithMap();
//	}
//	float getPlayerCoordinatX() {
//		return x;
//	}
//	float getPlayerCoordinatY() {
//		return y;
//	}
//
//	void interactionWithMap()//ф-ция взаимодействия с картой
//	{
//
//		for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
//			for (int j = x / 32; j<(x + w) / 32; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
//			{
//				if (TileMap[i][j] == '0')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
//				{
//					if (dy>0)//если мы шли вниз,
//					{
//						y = i * 32 - h;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
//					}
//					if (dy<0)
//					{
//						y = i * 32 + 32;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
//					}
//					if (dx>0)
//					{
//						x = j * 32 - w;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
//					}
//					if (dx < 0)
//					{
//						x = j * 32 + 32;//аналогично идем влево
//					}
//				}
//
//				//if (TileMap[i][j] == 's') { //если символ равен 's' (камень)
//				//	x = 300; y = 300;//какое то действие... например телепортация героя
//				//	TileMap[i][j] = ' ';//убираем камень, типа взяли бонус. можем и не убирать, кстати.
//				//}
//			}
//	}
//	void control() {
//		if (Keyboard::isKeyPressed(Keyboard::Left)) {
//			state = left;
//			speed = 0.1;
//			//currentFrame += 0.005*time;
//			//if (currentFrame > 3) currentFrame -= 3;
//			//p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 135, 96, 54));
//		}
//		if (Keyboard::isKeyPressed(Keyboard::Right)) {
//			state = right;
//			speed = 0.1;
//			//	currentFrame += 0.005*time;
//			//	if (currentFrame > 3) currentFrame -= 3;
//			//	p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 232, 96, 54));
//		}
//
//		if ((Keyboard::isKeyPressed(Keyboard::Up)) && (onGround)) {
//			state = jump; dy = -0.5; onGround = false;//то состояние равно прыжок,прыгнули и сообщили, что мы не на земле
//													  //currentFrame += 0.005*time;
//													  //if (currentFrame > 3) currentFrame -= 3;
//													  //p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 307, 96, 96));
//		}
//
//		if (Keyboard::isKeyPressed(Keyboard::Down)) {
//			state = down;
//			speed = 0.1;
//
//			//currentFrame += 0.005*time;
//			//if (currentFrame > 3) currentFrame -= 3;
//			//p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 0, 96, 96));
//		}
//};
//
//int main()
//{
//	Image map_image;//объект изображения для карты
//	map_image.loadFromFile("images/im2.png");//загружаем файл для карты
//	Texture map;//текстура карты
//	map.loadFromImage(map_image);//заряжаем текстуру картинкой
//	Sprite s_map;//создаём спрайт для карты
//	s_map.setTexture(map);//заливаем текстуру спрайтом
//
//	RenderWindow window(VideoMode(1000, 1000), "Lesson 3. kychka-pc.ru"); //увеличили для удобства размер окна
//	view.reset(FloatRect(0, 0, 1000, 1000));
//
//	float CurrentFrame = 0;
//	Clock clock;
//
//	Player p("im1.png", 250, 250, 32, 32);
//	//Image heroimage; //создаем объект Image (изображение)
//	//heroimage.loadFromFile("images/im1.png");//загружаем в него файл
//
//	//Texture herotexture;//создаем объект Texture (текстура)
//	//herotexture.loadFromImage(heroimage);//передаем в него объект Image (изображения)
//
//	//Sprite herosprite;//создаем объект Sprite(спрайт)
//	//herosprite.setTexture(herotexture);//передаём в него объект Texture (текстуры)
//	//herosprite.setTextureRect(IntRect(0, 0, 95, 145));//получили нужный нам прямоугольник с котом
//	//herosprite.setPosition(250, 250); //выводим спрайт в позицию x y 
//
//
//	//Image map_image;//объект изображения для карты
//	//map_image.loadFromFile("images/im2.png");//загружаем файл для карты
//	//Texture map;//текстура карты
//	//map.loadFromImage(map_image);//заряжаем текстуру картинкой
//	//Sprite s_map;//создаём спрайт для карты
//	//s_map.setTexture(map);//заливаем текстуру спрайтом
//
//	while (window.isOpen())
//	{
//		float time = clock.getElapsedTime().asMicroseconds();
//		clock.restart();
//		time = time / 800;
//
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (Keyboard::isKeyPressed(Keyboard::Escape))
//				window.close();
//		}
//	
//		
//		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
//			p.dir = 1; p.speed = 0.1;//dir =1 - направление вверх, speed =0.1 - скорость движения. Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз
//			CurrentFrame += 0.005*time;
//			if (CurrentFrame > 4) CurrentFrame -= 4;
//			p.sprite.setTextureRect(IntRect(128 -(32*int(CurrentFrame)), 0, -32, 32)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
//			/*getPlayerCoordinateForView(p.getPlayerCoordinatX(), p.getPlayerCoordinatY());*/
//		}
//
//
//		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
//			p.dir = 0; p.speed = 0.1;//направление вправо, см выше
//			CurrentFrame += 0.005*time;
//			if (CurrentFrame > 4) CurrentFrame -= 4;
//			p.sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 0, 32, 32)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
//			/*getPlayerCoordinateForView(p.getPlayerCoordinatX(), p.getPlayerCoordinatY());*/
//		}
//
//		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
//			p.dir = 3; p.speed = 0.1;//направление вниз, см выше
//			CurrentFrame += 0.005*time;
//			if (CurrentFrame > 1) CurrentFrame -= 1;
//			p.sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 32, 32, 32)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
//			/*getPlayerCoordinateForView(p.getPlayerCoordinatX(), p.getPlayerCoordinatY());*/
//		}
//		getPlayerCoordinateForView(p.getPlayerCoordinatX(), p.getPlayerCoordinatY());
//		//if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) { //если нажата клавиша стрелка влево или англ буква А
//		//	p.dir = 2; p.speed = 0.1;//направление вверх, см выше
//		//	CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
//		//	if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
//		//	p.sprite.setTextureRect(IntRect(64, 32, 32, 32)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
//
//		
//		p.update(time);
//
//		window.setView(view);
//		window.clear();
//		for (int i = 0; i < HEIGHT_MAP; i++)
//			for (int j = 0; j < WIDTH_MAP; j++)
//			{
//				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(128, 0, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
//				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(0, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
//				if (TileMap[i][j] == '0') s_map.setTextureRect(IntRect(192, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
//				if (TileMap[i][j] == 'n')  s_map.setTextureRect(IntRect(0, 32*7, 32, 32));
//
//				s_map.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат
//
//				window.draw(s_map);//рисуем квадратики на экран
//			}
//
//		window.draw(p.sprite);//выводим спрайт на экран
//		window.display();
//	}
//
//	return 0;
//}

#include <SFML/Graphics.hpp>
#include "map.h"
#include "view.h"
#include <iostream>
#include <sstream>


using namespace sf;

////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class Player {

public:
	float w, h, dx, dy, x, y, speed;
	int dir, playerScore, health;
	bool life, isMove, isSelect, onGround;//добавили переменные состояния нахождения на земле
	enum { left, right, up, down, jump, stay } state;//добавляем тип перечисления - состояние объекта
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	Player(String F, float X, float Y, float W, float H) {

		dir = 0; speed = 0; playerScore = 0; health = 100; dx = 0; dy = 0;
		life = true; isMove = false; isSelect = false; onGround = false;
		File = F;
		w = W; h = H;
		image.loadFromFile("images/" + File);
		/*image.createMaskFromColor(Color(41, 33, 59));*/
		texture.loadFromImage(image);
		sprite.setTexture(texture);

		x = X; y = Y;
		sprite.setTextureRect(IntRect(0, 0, w, h));
		sprite.setOrigin(w / 2, h / 2);
	}
	void control() {
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			state = left;
			speed = 0.1;
			//currentFrame += 0.005*time;
			//if (currentFrame > 3) currentFrame -= 3;
			//p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 135, 96, 54));
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			state = right;
			speed = 0.1;
			//	currentFrame += 0.005*time;
			//	if (currentFrame > 3) currentFrame -= 3;
			//	p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 232, 96, 54));
		}

		if ((Keyboard::isKeyPressed(Keyboard::Up)) && (onGround)) {
			state = jump; dy = -0.5; onGround = false;//то состояние равно прыжок,прыгнули и сообщили, что мы не на земле
													  //currentFrame += 0.005*time;
													  //if (currentFrame > 3) currentFrame -= 3;
													  //p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 307, 96, 96));
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			state = down;
			speed = 0.1;

			//currentFrame += 0.005*time;
			//if (currentFrame > 3) currentFrame -= 3;
			//p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 0, 96, 96));
		}
	}
	void update(float time)
	{
		control();//функция управления персонажем
		switch (state)//тут делаются различные действия в зависимости от состояния
		{
		case right: dx = speed; break;//состояние идти вправо
		case left: dx = -speed; break;//состояние идти влево
		case up: break;//будет состояние поднятия наверх (например по лестнице)
		case down: break;//будет состояние во время спуска персонажа (например по лестнице)
		case jump: break;//здесь может быть вызов анимации
		case stay: break;//и здесь тоже		
		}
		x += dx*time;
		checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
		y += dy*time;
		checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y
		if (!isMove) speed = 0;
		sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
		if (health <= 0) { life = false; }
		dy = dy + 0.0015*time;//делаем притяжение к земле
	}

	float getplayercoordinateX() {
		return x;
	}
	float getplayercoordinateY() {
		return y;
	}

	void checkCollisionWithMap(float Dx, float Dy)//ф ция проверки столкновений с картой
	{
		for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
			for (int j = x / 32; j<(x + w) / 32; j++)
			{
				if ((TileMap[i][j] == '0') || (TileMap[i][j] == 's'))//если элемент наш тайлик земли? то
				{
					if (Dy>0) { y = i * 32 - h;  dy = 0; onGround = true; }//по Y вниз=>идем в пол(стоим на месте) или падаем. В этот момент надо вытолкнуть персонажа и поставить его на землю, при этом говорим что мы на земле тем самым снова можем прыгать
					if (Dy<0) { y = i * 32 + 32;  dy = 0; }//столкновение с верхними краями карты(может и не пригодиться)
					if (Dx>0) { x = j * 32 - w; }//с правым краем карты
					if (Dx<0) { x = j * 32 + 32; }// с левым краем карты
				}
			}
	}
};

class SpriteManager {//это задел на следующие уроки,прошу не обращать внимания на эти изменения)
public:
	Image image;
	Texture texture;
	Sprite sprite;
	String name;
	String file;
	int widthOfSprite;
	int heightOfSprite;
	SpriteManager(String File, String Name) {
		file = File;
		name = Name;
		image.loadFromFile("images/" + file);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
};


int main()
{


	RenderWindow window(VideoMode(1000, 1000), "Lesson 20. kychka-pc.ru");
	view.reset(FloatRect(0, 0, 1000, 1000));

	/*Font font;
	font.loadFromFile("CyrilicOld.ttf");
	Text text("", font, 20);*/
	


	Image map_image;
	map_image.loadFromFile("images/im2.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	/*Image quest_image;
	quest_image.loadFromFile("images/missionbg.jpg");
	quest_image.createMaskFromColor(Color(0, 0, 0));
	Texture quest_texture;
	quest_texture.loadFromImage(quest_image);
	Sprite s_quest;
	s_quest.setTexture(quest_texture);
	s_quest.setTextureRect(IntRect(0, 0, 340, 510));
	s_quest.setScale(0.6f, 0.6f);*/

	SpriteManager playerSprite("im1.png", "Hero");//это задел на следующие уроки,прошу не обращать внимания)

	Player p("im1.png", 250, 500, 32, 32);

	float currentFrame = 0;
	Clock clock;
	float dX = 0;
	float dY = 0;
	int tempX = 0;//временная коорд Х.Снимаем ее после нажатия прав клав мыши
	int tempY = 0;//коорд Y
	float distance = 0;//это расстояние от объекта до тыка курсора
	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;

		Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
		Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)


		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
				if (event.key.code == Mouse::Left) {//а именно левая
					if (p.sprite.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
					{
						p.sprite.setColor(Color::Green);//красим спрайт в зеленый,тем самым говоря игроку,что он выбрал персонажа и может сделать ход
						p.isSelect = true;
					}
				}


			if (p.isSelect)//если выбрали объект
				if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
					if (event.key.code == Mouse::Right) {//а именно правая
						p.isMove = true;//то начинаем движение
						p.isSelect = false;//объект уже не выбран
						p.sprite.setColor(Color::White);//возвращаем обычный цвет спрайту
						tempX = pos.x;//забираем координату нажатия курсора Х
						tempY = pos.y;//и Y
						float dX = pos.x - p.x;//вектор , колинеарный прямой, которая пересекает спрайт и курсор
						float dY = pos.y - p.y;//он же, координата y
						float rotation = (atan2(dY, dX)) * 180 / 3.14159265;//получаем угол в радианах и переводим его в градусы
						std::cout << rotation << "\n";//смотрим на градусы в консольке
						p.sprite.setRotation(rotation);//поворачиваем спрайт на эти градусы	
					}
		}


		if (p.isMove) {
			distance = sqrt((tempX - p.x)*(tempX - p.x) + (tempY - p.y)*(tempY - p.y));//считаем дистанцию (расстояние от точки А до точки Б). используя формулу длины вектора

			if (distance > 2) {//этим условием убираем дергание во время конечной позиции спрайта

				p.x += 0.1*time*(tempX - p.x) / distance;//идем по иксу с помощью вектора нормали
				p.y += 0.1*time*(tempY - p.y) / distance;//идем по игреку так же
			}
			else { p.isMove = false; std::cout << "priehali\n"; }//говорим что уже никуда не идем и выводим веселое сообщение в консоль
		}







		///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
		if (p.life) {
			getPlayerCoordinateForView(p.getplayercoordinateX(), p.getplayercoordinateY());
		}


		p.update(time);


		window.setView(view);
		window.clear();


		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
			
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(128, 0, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(0, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
				if (TileMap[i][j] == '0') s_map.setTextureRect(IntRect(192, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
				if (TileMap[i][j] == 'n')  s_map.setTextureRect(IntRect(0, 32*7, 32, 32));
				s_map.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат
				window.draw(s_map);//рисуем квадратики на экран
								
				
			}
		window.draw(p.sprite);
		window.display();
	}
	return 0;
}
