#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;

View view;

void getPlayerCoordinateForView(float x, float y) {
	float tempX = x; float tempY = y;//��������� ����� ������ � ��������� ��, ����� ������ ����

	if (x < 500) tempX = 500;//������� �� ���� ����� �������
	if (y < 500) tempY = 500;//������� �������
	if (y > 500) tempY = 500;//������ �������
	if (x > 780) tempX = 780;

	view.setCenter(tempX, tempY); 
	
}
