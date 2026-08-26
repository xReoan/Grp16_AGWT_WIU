#include "SurvivorPuzzle.h"
#include <iostream>

SurvivorPuzzle::SurvivorPuzzle(int startX, int startY) : Puzzle(startX, startY, 21, 5) {
	stage = 1;
	selectedChoice = 1;
	wrongChoice = false;
}

SurvivorPuzzle::~SurvivorPuzzle() {}

//ANSWER IS 223
bool SurvivorPuzzle::checkSolution() {
	if (selectedChoice == 2 && stage == 1) {
		return true;
	}

	else if (selectedChoice == 2 && stage == 2) {
		return true;
	}

	else if (selectedChoice == 3 && stage == 3) {
		return true;
	}

	return false;
}

void SurvivorPuzzle::draw() {
    std::cout << "+----------------------------------------------------------+" << std::endl;
    std::cout << "|                   SURVIVOR'S MEMORY                      |" << std::endl;
    std::cout << "|                                                          |" << std::endl;

    //==============
    //STAGE 1
    //==============
    if (stage == 1) {
        std::cout << "|                                                          |" << std::endl;
        std::cout << "| The chamber door opens.                                  |" << std::endl;
        std::cout << "| You hear the scientists approaching.                     |" << std::endl;
        std::cout << "| You've seen what happens when they take a subject.       |" << std::endl;
        std::cout << "|                                                          |" << std::endl;
        std::cout << "| What do you do?                                          |" << std::endl;
        std::cout << "|                                                          |" << std::endl;
        std::cout << "|                                                          |" << std::endl;

        if (selectedChoice == 1)
        {
            std::cout << "| [1] Beg them to stop  <                                   |" << std::endl;
            std::cout << "| [2] Build a trap                                          |" << std::endl;
            std::cout << "| [3] Hide                                                  |" << std::endl;
        }
        else if (selectedChoice == 2)
        {
            std::cout << "| [1] Beg them to stop                                      |" << std::endl;
            std::cout << "| [2] Build a trap  <                                       |" << std::endl;
            std::cout << "| [3] Hide                                                  |" << std::endl;
        }
        else
        {
            std::cout << "| [1] Beg them to stop                                      |" << std::endl;
            std::cout << "| [2] Build a trap                                          |" << std::endl;
            std::cout << "| [3] Hide  <                                               |" << std::endl;
        }

        if (wrongChoice == true) {
            if (selectedChoice == 1) {
                std::cout << "| They never listened.                                     |" << std::endl;
            }
            else if (selectedChoice == 3) {
                std::cout << "| Hiding only delayed the inevitable.                      |" << std::endl;
            }
        }
        else {
            std::cout << "|                                                          |" << std::endl;
        }
    }

        //==============
        //STAGE 2
        //==============
    else if (stage == 2)
    {
        std::cout << "|                                                          |" << std::endl;
        std::cout << "| Another subject is taken for testing.                    |" << std::endl;
        std::cout << "| You've seen this experiment before.                      |" << std::endl;
        std::cout << "| You know they won't survive.                             |" << std::endl;
        std::cout << "| Their restraints are within reach.                       |" << std::endl;
        std::cout << "|                                                          |" << std::endl;
        std::cout << "| What do you do?                                          |" << std::endl;
        std::cout << "|                                                          |" << std::endl;

        if (selectedChoice == 1){
            std::cout << "| [1] Look away  <                                         |" << std::endl;
            std::cout << "| [2] Try to free them                                     |" << std::endl;
            std::cout << "| [3] Save yourself                                        |" << std::endl;
        }
        else if (selectedChoice == 2) {
            std::cout << "| [1] Look away                                            |" << std::endl;
            std::cout << "| [2] Try to free them  <                                  |" << std::endl;
            std::cout << "| [3] Save yourself                                        |" << std::endl;
        }
        else {
            std::cout << "| [1] Look away                                            |" << std::endl;
            std::cout << "| [2] Try to free them                                     |" << std::endl;
            std::cout << "| [3] Save yourself  <                                     |" << std::endl;
        }

        if (wrongChoice == true) {
            if (selectedChoice == 1) {
                std::cout << "| Their screams... I'm so sorry                             |" << std::endl;
            }

            else if (selectedChoice == 3) {
                std::cout << "| I've betrayed them.                                       |" << std::endl;
            }
        }
        else {
            std::cout << "|                                                          |" << std::endl;
        }
    }

    //==============
    //STAGE 3
    //==============
    else if (stage == 3)
    {
        std::cout << "|                                                          |" << std::endl;
        std::cout << "| The alarm sounds.                                        |" << std::endl;
        std::cout << "| You pull at the restraints.                              |" << std::endl;
        std::cout << "| The scientists drag you away.                            |" << std::endl;
        std::cout << "| The other subject is left behind.                        |" << std::endl;
        std::cout << "|                                                          |" << std::endl;
        std::cout << "| SUBJECT STATUS: DECEASED                                 |" << std::endl;
        std::cout << "|                                                          |" << std::endl;
        std::cout << "| Later, the room is empty.                                |" << std::endl;
        std::cout << "| Some equipment has been left behind.                     |" << std::endl;
        std::cout << "|                                                          |" << std::endl;
        std::cout << "| What do you do?                                          |" << std::endl;
        std::cout << "|                                                          |" << std::endl;

        if (selectedChoice == 1) {
            std::cout << "| [1] Leave it and hide  <                                 |" << std::endl;
            std::cout << "| [2] Wait for the scientists to return                    |" << std::endl;
            std::cout << "| [3] Take the equipment and prepare yourself              |" << std::endl;
        }
        else if (selectedChoice == 2) {
            std::cout << "| [1] Leave it and hide                                    |" << std::endl;
            std::cout << "| [2] Wait for the scientists to return  <                 |" << std::endl;
            std::cout << "| [3] Take the equipment and prepare yourself              |" << std::endl;
        }
        else {
            std::cout << "| [1] Leave it and hide                                    |" << std::endl;
            std::cout << "| [2] Wait for the scientists to return                    |" << std::endl;
            std::cout << "| [3] Take the equipment and prepare yourself  <           |" << std::endl;
        }

        if (wrongChoice == true) {
            if (selectedChoice == 1) {
                std::cout << "| They will soon find me                                    |" << std::endl;
            }

            else if (selectedChoice == 2) {
                std::cout << "| Can't let them hurt me no more                            |" << std::endl;
            }
        }
        else {
            std::cout << "|                                                          |" << std::endl;
        }
    }
    
    else if (stage == 4)
    {
        std::cout << "|                    MEMORY COMPLETE                       |" << std::endl;
        std::cout << "|                                                          |" << std::endl;
        std::cout << "| You take everything you can carry.                       |" << std::endl;
        std::cout << "| Tools. Weapons. Scraps of equipment.                     |" << std::endl;
        std::cout << "|                                                          |" << std::endl;
        std::cout << "| Days pass.                                               |" << std::endl;
        std::cout << "| Then months.                                             |" << std::endl;
        std::cout << "| Then years.                                              |" << std::endl;
        std::cout << "|                                                          |" << std::endl;
        std::cout << "| The scientists never return.                             |" << std::endl;
        std::cout << "|                                                          |" << std::endl;
        std::cout << "| But you keep preparing.                                  |" << std::endl;
        std::cout << "| You set traps throughout the laboratory.                 |" << std::endl;
        std::cout << "| You survive with whatever you can find.                  |" << std::endl;
        std::cout << "|                                                          |" << std::endl;
        std::cout << "| Every unfamiliar sound means one thing...                |" << std::endl;
        std::cout << "|                                                          |" << std::endl;
        std::cout << "| They've come back.                                       |" << std::endl;
        std::cout << "|                                                          |" << std::endl;
        std::cout << "| I survived when the others couldn't.                     |" << std::endl;
        std::cout << "| I will never let them take me again.                     |" << std::endl;
        std::cout << "|                                                          |" << std::endl;
    }

    if (stage < 4) {
        std::cout << "|                                                          |" << std::endl;
        std::cout << "|             A/D Select     E Confirm     Q Back          |" << std::endl;
        std::cout << "+----------------------------------------------------------+" << std::endl;
    }

    std::cout << "+----------------------------------------------------------+" << std::endl;
}

void SurvivorPuzzle::handleInput(char input) {
    // Puzzle already completed
    if (getSolved() == true)
    {
        setExitRequested(true);
        return;
    }

    //W = move up
    if (input == 'W' || input == 'w') {
        selectedChoice--;
        if (selectedChoice < 1) {
            selectedChoice = 3;
        }

        wrongChoice = false;
    }

    //S = move down
    else if (input == 'S' || input == 's') {
        selectedChoice++;
        if (selectedChoice > 3) {
            selectedChoice = 1;
        }

        wrongChoice = false;
    }

    // E = confirm
    else if (input == 'E' || input == 'e'){
        
        // Aftermath
        if (stage == 4)
        {
            if (input == 'E' || input == 'e')
            {
                setSolved(true);
            }

            return;
        }

        if (checkSolution() == true){ 
            if (stage < 3){
                stage++;
                selectedChoice = 1;
                wrongChoice = false;
            }
            else if (stage == 3){
                stage = 4;
                wrongChoice = false;
            }
        }
        else{
            wrongChoice = true;
        }
    }

    // Q = leave
    else if (input == 'Q' || input == 'q')
    {
        setExitRequested(true);
    }
}