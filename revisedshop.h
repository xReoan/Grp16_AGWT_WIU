#pragma once
#include "itemDatabase.h"
#include "inv.h"
#include <iostream>

class revisedshop
{
private:
    static int shopItems[9];
    static int weaponItems[5];
    item* shopItemPtrs[9];
    item* weaponItemPtrs[5];
    itemDatabase database;
    int coins;

    inv inv2;

public:
    revisedshop();
    void OpenShop() const;
    void OpenWeaponShop() const;
    void BuyItem(int itemSlot) const;
    void BuyWeapon(int weaponSlot) const;
    void AddCoins(int amount);
    int GetCoins() const;
    bool IsItemAvailable(int itemSlot) const;
    bool IsWeaponAvailable(int weaponSlot) const;
    void ShopMenu();
};
