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

	


	Image map_image;
	map_image.loadFromFile("images/im2.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	

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
