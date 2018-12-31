//#include <iostream> 
//#include <SFML/Graphics.hpp>
//#include "map.h";
//#include "view.h";
//
//using namespace sf;//�������� ������������ ���� sf, ����� ��������� �� ������ sf::
//
//class Player { // ����� ������
//
//public:
//	float x, y, w, h, dx, dy, speed; //���������� ������ � � �, ������ ������, ��������� (�� � � �� �), ���� ��������
//	bool life, isMove, isSelect, onGround;
//	int dir; //����������� (direction) �������� ������
//	enum stateObject { left, right, up, down, jump, stay };
//	stateObject state;
//	String File; //���� � �����������
//	Image image;//���� �����������
//	Texture texture;//���� ��������
//	Sprite sprite;//���� ������
//
//	Player(String F, float X, float Y, float W, float H) { //����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������
//		life = true; isMove = false; isSelect = false; onGround = false; state = stay;
//		dx = 0; dy = 0; speed = 0; dir = 0;
//		File = F;//��� �����+����������
//		w = W; h = H;//������ � ������
//		image.loadFromFile("images/" + File);//���������� � image ���� ����������� ������ File �� ��������� ��, ��� �������� ��� �������� �������. � ����� ������ "hero.png" � ��������� ������ ���������� image.loadFromFile("images/hero/png");
//											 /*image.createMaskFromColor(Color(41, 33, 59));*///������� �������� �����-����� ����, ��� ���� ��� ���������� �� ��������.
//		texture.loadFromImage(image);//���������� ���� ����������� � ��������
//		sprite.setTexture(texture);//�������� ������ ���������
//		x = X; y = Y;//���������� ��������� �������
//		sprite.setTextureRect(IntRect(0, 0, w, h)); //������ ������� ���� ������������� ��� ������ ������ ����, � �� ���� ����� �����. IntRect - ���������� �����
//		sprite.setOrigin(w / 2, h / 2);
//	}
//	
//	void update(float time) //������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.
//	{
//		switch (state)//��� �������� ��������� �������� � ����������� �� ���������
//		{
//		case right: dx = speed; break;//��������� ���� ������
//		case left: dx = -speed; break;//��������� ���� �����
//		case up: break;//����� ��������� �������� ������ (�������� �� ��������)
//		case down: dx = 0; break;//����� ��������� �� ����� ������ ��������� (�������� �� ��������)
//		case jump: break;//����� ����� ���� ����� ��������
//		case stay: break;//� ����� ����		
//		}
//		x += dx*time;
//		checkCollisionWithMap(dx, 0);//������������ ������������ �� �
//		y += dy*time;
//		checkCollisionWithMap(0, dy);//������������ ������������ �� Y
//		if (!isMove) speed = 0;
//		sprite.setPosition(x + w / 2, y + h / 2); //������ ������� ������� � ����� ��� ������
//		if (health <= 0) { life = false; }
//		dy = dy + 0.0015*time; //������ ���������� � �����
//	
//		switch (dir)//��������� ��������� � ����������� �� �����������. (������ ����� ������������� �����������)
//		{
//		case 0: dx = speed; dy = 0; break;//�� ���� ������ ������������� ��������, �� ������ ��������. ��������, ��� �������� ���� ������ ������
//		case 1: dx = -speed; dy = 0; break;//�� ���� ������ ������������� ��������, �� ������ ��������. ����������, ��� �������� ���� ������ �����
//		case 2: dx = 0; dy = speed; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ ����
//		case 3: dx = 0; dy = -speed; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ �����
//		}
//
//		x += dx*time;//�� �������� �� �������� �����. ���� ��������� �� ����� �������� �������� ��������� � ��� ��������� ��������
//		y += dy*time;//���������� �� ������
//
//		speed = 0;//�������� ��������, ����� �������� �����������.
//		sprite.setPosition(x + w / 2, y + h / 2); //������� ������ � ������� x y , ����������. ���������� ������� � ���� �������, ����� �� ��� ������ ����� �� �����.
//		interactionWithMap();
//	}
//	float getPlayerCoordinatX() {
//		return x;
//	}
//	float getPlayerCoordinatY() {
//		return y;
//	}
//
//	void interactionWithMap()//�-��� �������������� � ������
//	{
//
//		for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������, �������������� � �������, �� ���� �� ���� ����������� ������� 32*32, ������� �� ���������� � 9 �����. ��� ������� ������� ����.
//			for (int j = x / 32; j<(x + w) / 32; j++)//��� ����� �� 32, ��� ����� �������� ����� ���������, � ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������). � j<(x + w) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
//			{
//				if (TileMap[i][j] == '0')//���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
//				{
//					if (dy>0)//���� �� ��� ����,
//					{
//						y = i * 32 - h;//�� �������� ���������� ����� ���������. ������� �������� ���������� ������ ���������� �� �����(�����) � ����� �������� �� ������ ������� ���������.
//					}
//					if (dy<0)
//					{
//						y = i * 32 + 32;//���������� � ������� �����. dy<0, ������ �� ���� ����� (���������� ���������� ������)
//					}
//					if (dx>0)
//					{
//						x = j * 32 - w;//���� ���� ������, �� ���������� � ����� ����� (������ 0) ����� ������ ���������
//					}
//					if (dx < 0)
//					{
//						x = j * 32 + 32;//���������� ���� �����
//					}
//				}
//
//				//if (TileMap[i][j] == 's') { //���� ������ ����� 's' (������)
//				//	x = 300; y = 300;//����� �� ��������... �������� ������������ �����
//				//	TileMap[i][j] = ' ';//������� ������, ���� ����� �����. ����� � �� �������, ������.
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
//			state = jump; dy = -0.5; onGround = false;//�� ��������� ����� ������,�������� � ��������, ��� �� �� �� �����
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
//	Image map_image;//������ ����������� ��� �����
//	map_image.loadFromFile("images/im2.png");//��������� ���� ��� �����
//	Texture map;//�������� �����
//	map.loadFromImage(map_image);//�������� �������� ���������
//	Sprite s_map;//������ ������ ��� �����
//	s_map.setTexture(map);//�������� �������� ��������
//
//	RenderWindow window(VideoMode(1000, 1000), "Lesson 3. kychka-pc.ru"); //��������� ��� �������� ������ ����
//	view.reset(FloatRect(0, 0, 1000, 1000));
//
//	float CurrentFrame = 0;
//	Clock clock;
//
//	Player p("im1.png", 250, 250, 32, 32);
//	//Image heroimage; //������� ������ Image (�����������)
//	//heroimage.loadFromFile("images/im1.png");//��������� � ���� ����
//
//	//Texture herotexture;//������� ������ Texture (��������)
//	//herotexture.loadFromImage(heroimage);//�������� � ���� ������ Image (�����������)
//
//	//Sprite herosprite;//������� ������ Sprite(������)
//	//herosprite.setTexture(herotexture);//������� � ���� ������ Texture (��������)
//	//herosprite.setTextureRect(IntRect(0, 0, 95, 145));//�������� ������ ��� ������������� � �����
//	//herosprite.setPosition(250, 250); //������� ������ � ������� x y 
//
//
//	//Image map_image;//������ ����������� ��� �����
//	//map_image.loadFromFile("images/im2.png");//��������� ���� ��� �����
//	//Texture map;//�������� �����
//	//map.loadFromImage(map_image);//�������� �������� ���������
//	//Sprite s_map;//������ ������ ��� �����
//	//s_map.setTexture(map);//�������� �������� ��������
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
//			p.dir = 1; p.speed = 0.1;//dir =1 - ����������� �����, speed =0.1 - �������� ��������. �������� - ����� �� ��� ����� �� �� ��� �� �������� � ����� �� ���������� ������ ���
//			CurrentFrame += 0.005*time;
//			if (CurrentFrame > 4) CurrentFrame -= 4;
//			p.sprite.setTextureRect(IntRect(128 -(32*int(CurrentFrame)), 0, -32, 32)); //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)
//			/*getPlayerCoordinateForView(p.getPlayerCoordinatX(), p.getPlayerCoordinatY());*/
//		}
//
//
//		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
//			p.dir = 0; p.speed = 0.1;//����������� ������, �� ����
//			CurrentFrame += 0.005*time;
//			if (CurrentFrame > 4) CurrentFrame -= 4;
//			p.sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 0, 32, 32)); //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)
//			/*getPlayerCoordinateForView(p.getPlayerCoordinatX(), p.getPlayerCoordinatY());*/
//		}
//
//		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
//			p.dir = 3; p.speed = 0.1;//����������� ����, �� ����
//			CurrentFrame += 0.005*time;
//			if (CurrentFrame > 1) CurrentFrame -= 1;
//			p.sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 32, 32, 32)); //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)
//			/*getPlayerCoordinateForView(p.getPlayerCoordinatX(), p.getPlayerCoordinatY());*/
//		}
//		getPlayerCoordinateForView(p.getPlayerCoordinatX(), p.getPlayerCoordinatY());
//		//if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) { //���� ������ ������� ������� ����� ��� ���� ����� �
//		//	p.dir = 2; p.speed = 0.1;//����������� �����, �� ����
//		//	CurrentFrame += 0.005*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
//		//	if (CurrentFrame > 3) CurrentFrame -= 3; //���������� �� ������ � ������� �� ������ ������������. ���� ������ � �������� ����� - ������������ �����.
//		//	p.sprite.setTextureRect(IntRect(64, 32, 32, 32)); //���������� �� ����������� �. ���������� 96,96*2,96*3 � ����� 96
//
//		
//		p.update(time);
//
//		window.setView(view);
//		window.clear();
//		for (int i = 0; i < HEIGHT_MAP; i++)
//			for (int j = 0; j < WIDTH_MAP; j++)
//			{
//				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(128, 0, 32, 32)); //���� ��������� ������ ������, �� ������ 1� ���������
//				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(0, 0, 32, 32));//���� ��������� ������ s, �� ������ 2� ���������
//				if (TileMap[i][j] == '0') s_map.setTextureRect(IntRect(192, 0, 32, 32));//���� ��������� ������ 0, �� ������ 3� ���������
//				if (TileMap[i][j] == 'n')  s_map.setTextureRect(IntRect(0, 32*7, 32, 32));
//
//				s_map.setPosition(j * 32, i * 32);//�� ���� ����������� ����������, ��������� � �����. �� ���� ������ ������� �� ��� �������. ���� ������, �� ��� ����� ���������� � ����� �������� 32*32 � �� ������ ���� �������
//
//				window.draw(s_map);//������ ���������� �� �����
//			}
//
//		window.draw(p.sprite);//������� ������ �� �����
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

////////////////////////////////////////////////////����� ������////////////////////////
class Player {

public:
	float w, h, dx, dy, x, y, speed;
	int dir, playerScore, health;
	bool life, isMove, isSelect, onGround;//�������� ���������� ��������� ���������� �� �����
	enum { left, right, up, down, jump, stay } state;//��������� ��� ������������ - ��������� �������
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
			state = jump; dy = -0.5; onGround = false;//�� ��������� ����� ������,�������� � ��������, ��� �� �� �� �����
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
		control();//������� ���������� ����������
		switch (state)//��� �������� ��������� �������� � ����������� �� ���������
		{
		case right: dx = speed; break;//��������� ���� ������
		case left: dx = -speed; break;//��������� ���� �����
		case up: break;//����� ��������� �������� ������ (�������� �� ��������)
		case down: break;//����� ��������� �� ����� ������ ��������� (�������� �� ��������)
		case jump: break;//����� ����� ���� ����� ��������
		case stay: break;//� ����� ����		
		}
		x += dx*time;
		checkCollisionWithMap(dx, 0);//������������ ������������ �� �
		y += dy*time;
		checkCollisionWithMap(0, dy);//������������ ������������ �� Y
		if (!isMove) speed = 0;
		sprite.setPosition(x + w / 2, y + h / 2); //������ ������� ������� � ����� ��� ������
		if (health <= 0) { life = false; }
		dy = dy + 0.0015*time;//������ ���������� � �����
	}

	float getplayercoordinateX() {
		return x;
	}
	float getplayercoordinateY() {
		return y;
	}

	void checkCollisionWithMap(float Dx, float Dy)//� ��� �������� ������������ � ������
	{
		for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������� �����
			for (int j = x / 32; j<(x + w) / 32; j++)
			{
				if ((TileMap[i][j] == '0') || (TileMap[i][j] == 's'))//���� ������� ��� ������ �����? ��
				{
					if (Dy>0) { y = i * 32 - h;  dy = 0; onGround = true; }//�� Y ����=>���� � ���(����� �� �����) ��� ������. � ���� ������ ���� ���������� ��������� � ��������� ��� �� �����, ��� ���� ������� ��� �� �� ����� ��� ����� ����� ����� �������
					if (Dy<0) { y = i * 32 + 32;  dy = 0; }//������������ � �������� ������ �����(����� � �� �����������)
					if (Dx>0) { x = j * 32 - w; }//� ������ ����� �����
					if (Dx<0) { x = j * 32 + 32; }// � ����� ����� �����
				}
			}
	}
};

class SpriteManager {//��� ����� �� ��������� �����,����� �� �������� �������� �� ��� ���������)
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

	SpriteManager playerSprite("im1.png", "Hero");//��� ����� �� ��������� �����,����� �� �������� ��������)

	Player p("im1.png", 250, 500, 32, 32);

	float currentFrame = 0;
	Clock clock;
	float dX = 0;
	float dY = 0;
	int tempX = 0;//��������� ����� �.������� �� ����� ������� ���� ���� ����
	int tempY = 0;//����� Y
	float distance = 0;//��� ���������� �� ������� �� ���� �������
	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;

		Vector2i pixelPos = Mouse::getPosition(window);//�������� ����� �������
		Vector2f pos = window.mapPixelToCoords(pixelPos);//��������� �� � ������� (������ �� ����� ����)


		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)//���� ������ ������� ����
				if (event.key.code == Mouse::Left) {//� ������ �����
					if (p.sprite.getGlobalBounds().contains(pos.x, pos.y))//� ��� ���� ���������� ������� �������� � ������
					{
						p.sprite.setColor(Color::Green);//������ ������ � �������,��� ����� ������ ������,��� �� ������ ��������� � ����� ������� ���
						p.isSelect = true;
					}
				}


			if (p.isSelect)//���� ������� ������
				if (event.type == Event::MouseButtonPressed)//���� ������ ������� ����
					if (event.key.code == Mouse::Right) {//� ������ ������
						p.isMove = true;//�� �������� ��������
						p.isSelect = false;//������ ��� �� ������
						p.sprite.setColor(Color::White);//���������� ������� ���� �������
						tempX = pos.x;//�������� ���������� ������� ������� �
						tempY = pos.y;//� Y
						float dX = pos.x - p.x;//������ , ����������� ������, ������� ���������� ������ � ������
						float dY = pos.y - p.y;//�� ��, ���������� y
						float rotation = (atan2(dY, dX)) * 180 / 3.14159265;//�������� ���� � �������� � ��������� ��� � �������
						std::cout << rotation << "\n";//������� �� ������� � ���������
						p.sprite.setRotation(rotation);//������������ ������ �� ��� �������	
					}
		}


		if (p.isMove) {
			distance = sqrt((tempX - p.x)*(tempX - p.x) + (tempY - p.y)*(tempY - p.y));//������� ��������� (���������� �� ����� � �� ����� �). ��������� ������� ����� �������

			if (distance > 2) {//���� �������� ������� �������� �� ����� �������� ������� �������

				p.x += 0.1*time*(tempX - p.x) / distance;//���� �� ���� � ������� ������� �������
				p.y += 0.1*time*(tempY - p.y) / distance;//���� �� ������ ��� ��
			}
			else { p.isMove = false; std::cout << "priehali\n"; }//������� ��� ��� ������ �� ���� � ������� ������� ��������� � �������
		}







		///////////////////////////////////////////���������� ���������� � ���������////////////////////////////////////////////////////////////////////////
		if (p.life) {
			getPlayerCoordinateForView(p.getplayercoordinateX(), p.getplayercoordinateY());
		}


		p.update(time);


		window.setView(view);
		window.clear();


		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
			
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(128, 0, 32, 32)); //���� ��������� ������ ������, �� ������ 1� ���������
				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(0, 0, 32, 32));//���� ��������� ������ s, �� ������ 2� ���������
				if (TileMap[i][j] == '0') s_map.setTextureRect(IntRect(192, 0, 32, 32));//���� ��������� ������ 0, �� ������ 3� ���������
				if (TileMap[i][j] == 'n')  s_map.setTextureRect(IntRect(0, 32*7, 32, 32));
				s_map.setPosition(j * 32, i * 32);//�� ���� ����������� ����������, ��������� � �����. �� ���� ������ ������� �� ��� �������. ���� ������, �� ��� ����� ���������� � ����� �������� 32*32 � �� ������ ���� �������
				window.draw(s_map);//������ ���������� �� �����
								
				
			}
		window.draw(p.sprite);
		window.display();
	}
	return 0;
}
