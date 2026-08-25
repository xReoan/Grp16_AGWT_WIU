#include "dialogue.h"
#include <iostream>

dialogue::dialogue()
{}

void dialogue::introbattlediag() {
	std::cout << R"(You: Besides the fact that it was abandoned 3 years ago, there aren't any files related to this laboratory.
Whoever abandoned this place... they must've really wanted this place to be forgotten. But going here alone?
My boss really doesn't care, he’s such a bum...)" << std::endl;
	system("pause");
	std::cout << "You: Whatever… But what could this lab possibly contain, to the point where NO ONE dares to step close? It’s too suspicious." << std::endl;
	system("pause");
	std::cout << "As you entered the main lab, the eerie atmosphere sent chills down your spine," << std::endl;
	std::cout << "asbestos filling the air like snowflakes, making breathing ever so slightly difficult." << std::endl;
	system("pause");
	std::cout << "Streaks of light poured in from small crevices in the walls, giving a little bit of salvation for visibility." << std::endl;
	system("pause");
}