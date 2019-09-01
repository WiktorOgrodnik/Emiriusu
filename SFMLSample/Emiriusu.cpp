#include "pch.h" 

int main()
{
	setlocale(LC_ALL, "");
	Log::newLog("Uruchamainie silnika");
	Engine::getInstance().startGame();
	return 0;
}
