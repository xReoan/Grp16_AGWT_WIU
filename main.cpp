#include "Game.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

int main()
{
    // Gives rand() a different seed
    // based on the current time.
    srand(static_cast<unsigned int>(time(nullptr)));

    //start screen
    std::cout << R"(
 _______    _______  _______  __   __  _______    _     _  ___   _______  __   __ 
|   _   |  |       ||   _   ||  |_|  ||       |  | | _ | ||   | |       ||  | |  |
|  |_|  |  |    ___||  |_|  ||       ||    ___|  | || || ||   | |_     _||  |_|  |
|       |  |   | __ |       ||       ||   |___   |       ||   |   |   |  |       |
|       |  |   ||  ||       ||       ||    ___|  |       ||   |   |   |  |       |
|   _   |  |   |_| ||   _   || ||_|| ||   |___   |   _   ||   |   |   |  |   _   |
|__| |__|  |_______||__| |__||_|   |_||_______|  |__| |__||___|   |___|  |__| |__|

                                        
              mmmmmmmm  mm    mm  mmmmmmmm  mmm  mmm 
              """##"""  ##    ##  ##""""""  ###  ### 
                 ##     ##    ##  ##        ######## 
                 ##     ########  #######   ## ## ## 
                 ##     ##    ##  ##        ## "" ## 
                 ##     ##    ##  ##mmmmmm  ##    ##  ##
                 ""     ""    ""  """"""""  ""    ""  ""
	)" << std::endl;;
    system("pause");
    system("cls");

    Game game;

    game.run();

    return 0;
}
