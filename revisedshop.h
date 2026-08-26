#pragma once
#include "itemDatabase.h"
#include "inv.h"
#include <iostream>

class revisedshop
{
private:
    static int shopItems[9]; // item id + shop instances share the same inventory data
    static int weaponItems[5]; //static is there because they are both using the same shop and they share the same inventory
    item* shopItemPtrs[9]; // pointer; item object
    item* weaponItemPtrs[5];
    itemDatabase database;
    int coins;

    inv inv2;

public:
    revisedshop();
    void OpenShop() const; // const is there if the values don't change + mainly used for getters & display!
    void OpenWeaponShop() const; // void = no need to return anything
    void BuyItem(int itemSlot); // return type  function name  parameter aka input the function needs
    void BuyWeapon(int weaponSlot);
    void AddCoins(int amount);
    void RemoveCoins(int amount);
    int GetCoins() const;
    void ShopMenu();
};
