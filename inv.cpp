#include "inv.h"
#include <iostream>

//#include <conio.h>//int input = _getch();

inv::inv() {
    for (int i = 0; i < 15;i++) {
        invitem[i] = database.getitem(i);
    }
}

//saves the number of the number base on the item database, -1 is none
int inv::invinside[16] = {7,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

void inv::OpenInv() const
{  
    for (int i = 0; i < 16; i++) {
        if (inv::invinside[i] != -1 ) {
            std::cout << i + 1<<". " << invitem[inv::invinside[i]]->getname();
        }
        else {
            std::cout << i + 1 << ". Empty";
        }
        std::cout << "         ";
        i++;
        if (inv::invinside[i] != -1) {
            std::cout << i + 1 << ". " << invitem[inv::invinside[i]]->getname()<<std::endl;
        }
        else {
            std::cout << i + 1 << ". Empty"<<std::endl;
        }
    }
}

//takes a int cuz thats how its storied, will be changed
void inv::ReceivedInv(int thing) const
{
    char changed = 'N';
    for (int i = 0; i < 16; i++) {
        if (invinside[i] == -1) {
            invinside[i] = thing;
            changed = 'Y';
            break;
        }
    }
    if (changed != 'Y') {
        std::cout << "Invantory full, cant store" << std::endl;
    }
}

item* inv::getarmorInv(int itemSlot) {
    return invitem[invinside[itemSlot]];
}

item* inv::getweaponInv(int itemSlot)
{
    return invitem[invinside[itemSlot]];
}

item* inv::geteatInv(int itemSlot)
{
    std::cout << "Ate " << invitem[invinside[itemSlot]]->getname() << std::endl;
    invinside[itemSlot] = -1;
    return invitem[invinside[itemSlot]];
}

int inv::checkingType(int itemSlot)
{
    if (invinside[itemSlot] != -1) {
        if (invitem[invinside[itemSlot]]->getitemcategory() == item::itemtype::armor) {
            return 0;
        }
        else if (invitem[invinside[itemSlot]]->getitemcategory() == item::itemtype::weapon) {
            return 1;
        }
        else if (invitem[invinside[itemSlot]]->getitemcategory() == item::itemtype::consumable) {
            std::cout << "This is a consumable, use during battle." << std::endl;
            return 2;
        }
    }
    else {//if it is emepty
        std::cout << "no item to use" << std::endl;
    }
}



//can do
//unequppingggg 
//inspect()desciptions and stuff