#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;

View view;

void getPlayerCoordinateForView(float x, float y) {
	float tempX = x; float tempY = y;//считываем коорд игрока и проверяем их, чтобы убрать края

	if (x < 500) tempX = 500;//убираем из вида левую сторону
	if (y < 500) tempY = 500;//верхнюю сторону
	if (y > 500) tempY = 500;//нижнюю сторону
	if (x > 780) tempX = 780;

	view.setCenter(tempX, tempY); 
	
}
