#pragma once
#include "itemDatabase.h"
#include "inv.h"
#include <iostream>

class revisedshop
{
private:
    int shopItems[9]; // item id
    int weaponItems[5]; 
    item* shopItemPtrs[9]; // pointer; item object
    item* weaponItemPtrs[5];
    itemDatabase database;
    int coins;

    inv inv2;

public:
    revisedshop();
    void OpenShop() const; // const is there if the values don't change + mainly used for getters & display!
    void OpenWeaponShop() const; // void = no need to return anything
    void BuyItem(int itemSlot);
    void BuyWeapon(int weaponSlot);
    void AddCoins(int amount);
    int GetCoins() const;
    bool IsItemAvailable(int itemSlot) const;
    bool IsWeaponAvailable(int weaponSlot) const;
    void ShopMenu();
};
