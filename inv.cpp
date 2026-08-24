#include "inv.h"
#include "item.h"
#include "itemDatabase.h"
#include <iostream>

//#include <conio.h>//int input = _getch();

inv::inv() {
    for (int i = 0; i < 15;i++) {
        invitem[i] = database.getitem(i);
    }
}

//saves the number of the number base on the item database, -1 is none
int inv::invinside[16] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

void inv::OpenInv() const
{

    for (int i = 0; i < 16; i++) {
        if (inv::invinside[i] != -1 ) {
            std::cout << i + 1<<". " << invitem[inv::invinside[i]]->getname() << std::endl;
        }
        else {
            std::cout << i + 1 << ". Empty" << std::endl;
        }
    }
}

//takes a int cuz thats how its storied, will be changed
void inv::RecivedInv(int thing) const
{
    char changed = 'N';
    for (int i = 0; i < 16; i++) {
        if (invinside[i] == -1) {
            invinside[i] = thing;
            changed = 'Y';
            return;
        }
    }
    if (changed != 'Y') {
        std::cout << "Invantory full, cant store" << std::endl;
    }
}

//like which of the 16 items slot is the item they used is from, can be changed
void inv::UsedInv(int itemSlot) const
{
    if (invinside[itemSlot] != -1) {
        std::cout << "Used " << invitem[invinside[itemSlot]]->getname() << std::endl;;
        invinside[itemSlot] = -1;
    }
    else {//if it is emepty
        std::cout << "no item to use"<<std::endl;
    }
}
