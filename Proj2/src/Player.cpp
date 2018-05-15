#include "Player.h"

Player::Player(string name)
{
	this->name = name;
	this->elapsedTime = 0;
	this->hints = 0;
}

void Player::incrementHint(){
	this->hints++;
	return;
}
