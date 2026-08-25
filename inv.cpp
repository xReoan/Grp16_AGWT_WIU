#include "inv.h"
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

void inv::inspecting(int itemSlot)
{
    if (invinside[itemSlot] != -1) {
        std::cout << "Name: " << invitem[invinside[itemSlot]]->getname() << std::endl;
        std::cout << "description: " << invitem[invinside[itemSlot]]->getdescription() << std::endl;

        //item type
        if (invitem[invinside[itemSlot]]->getitemcategory() == item::itemtype::weapon) {
            std::cout << "Item type: weapon"<< "      ";
        }
        else if (invitem[invinside[itemSlot]]->getitemcategory() == item::itemtype::armor) {
            std::cout << "Item type: armor" << "      ";
        }
        else if (invitem[invinside[itemSlot]]->getitemcategory() == item::itemtype::consumable) {
            std::cout << "Item type: consumable" << "      ";
        }

        //combat type
        if (invitem[invinside[itemSlot]]->getcombatcategory() == item::combattype::none) {
            std::cout << "Combat type: none" << "      ";
        }
        else if (invitem[invinside[itemSlot]]->getcombatcategory() == item::combattype::melee) {
            std::cout << "Combat type: melee" << "      ";
        }
        else if (invitem[invinside[itemSlot]]->getcombatcategory() == item::combattype::projectile) {
            std::cout << "Combat type: projectile" << "      ";
        }

        //Tier
        if (invitem[invinside[itemSlot]]->getequipmenttier() == item::equipment::basic) {
            std::cout << "Tier: basic" << "      ";
        }
        else if (invitem[invinside[itemSlot]]->getequipmenttier() == item::equipment::advanced) {
            std::cout << "Tier type: advanced" << "      ";
        }
        else if (invitem[invinside[itemSlot]]->getequipmenttier() == item::equipment::none) {
            std::cout << "Tier type: none" << "      ";
        }

        //std::cout << "Name: " << invitem[invinside[itemSlot]]->getpassiveeffect() << std::endl; according to item.h but theres none
        if (invitem[invinside[itemSlot]]->getattackvalue() != 0) {
            std::cout << "Attack: " << invitem[invinside[itemSlot]]->getattackvalue() << std::endl;
        }
        
        
        if (invitem[invinside[itemSlot]]->getdefensevalue() != 0) {
            std::cout << "Defense: " << invitem[invinside[itemSlot]]->getdefensevalue() << std::endl;
        }


        if (invitem[invinside[itemSlot]]->gethealvalue() != 0) {
            std::cout << "Healing: " << invitem[invinside[itemSlot]]->gethealvalue() << std::endl;
        }
        

        if (invitem[invinside[itemSlot]]->getduration() != 0) {
            std::cout << "Duration: " << invitem[invinside[itemSlot]]->getduration() << std::endl;
        }
    }
    else {
        std::cout << "theres nothing to inspect" << std::endl;
    }
}

//can do
//inspect()desciptions and stuff