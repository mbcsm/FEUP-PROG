#pragma once
#include "proj.h"
#include <iostream>
#include <vector>

class Player
{
	private:
		string name;
		int elapsedTime;
		int hints;
	public:
		Player(string name);
		void incrementHint();
};
