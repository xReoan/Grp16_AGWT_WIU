#pragma once
#include "itemDatabase.h"
#include <iostream>

class shop
{
private:
    static int shopItems[4];
    static int weaponItems[5];
    item* shopItemPtrs[4];
    item* weaponItemPtrs[6];
    itemDatabase database;
    int coins;

public:
    shop();
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
