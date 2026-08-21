#include "shop.h"
#include "item.h"
#include "itemDatabase.h"
#include "inv.h"
#include <iostream>
#include <cstdlib>

int shop::shopItems[4] = { 6, 7, 8, 9 };
int shop::weaponItems[5] = { 1, 2, 3, 4, 5 };

shop::shop() : coins()
{
    for (int i = 0; i < 10; i++) {
        if (shopItems[i] != -1) {
            shopItemPtrs[i] = database.getitem(shopItems[i]);
        }
        else {
            shopItemPtrs[i] = nullptr;
        }
    }

    for (int i = 0; i < 10; i++) {
        if (weaponItems[i] != -1) {
            weaponItemPtrs[i] = database.getitem(weaponItems[i]);
        }
        else {
            weaponItemPtrs[i] = nullptr;
        }
    }
}

void shop::ShopMenu()
{
    char choice;
    int slotChoice;

    while (true) {
        system("cls");
        std::cout << "            What would you like to buy?" << std::endl;
        std::cout << "----------------------------------------------------" << std::endl;
        std::cout << "|       [I] Items        |       [W] Weapons       |" << std::endl;
        std::cout << "----------------------------------------------------" << std::endl;     
        std::cout << "[C] Check Coins                        [E] Exit Shop" << std::endl;
        std::cout << "                Press Enter to refresh" << std::endl;

        std::cin >> choice;

        // Convert to uppercase automatically
        choice = toupper(choice);

        switch (choice) {
        case 'I': {
            OpenShop();
            std::cout << "\nEnter slot number to buy (1-10) or 0 to cancel: ";
            std::cin >> slotChoice;
            if (slotChoice > 0 && slotChoice <= 10) {
                BuyItem(slotChoice - 1);
            }
            std::cin.ignore();
            std::cin.get();
            break;
        }

        case 'W': {
            OpenWeaponShop();
            std::cout << "\nEnter slot number to buy (1-10) or 0 to cancel: ";
            std::cin >> slotChoice;
            if (slotChoice > 0 && slotChoice <= 10) {
                BuyWeapon(slotChoice - 1);
            }
            std::cin.ignore();
            std::cin.get();
            break;
        }

        case 'C': {
            std::cout << "Amount of coins you own: " << coins << std::endl;
            std::cin.ignore();
            std::cin.get();
            break;
        }

        case 'E': {
            std::cout << "Thanks for visiting the shop!" << std::endl;
            return;
        }

        default: {
            std::cout << "Invalid choice! Please enter I, W, C, or E." << std::endl;
            std::cin.ignore();
            std::cin.get();     
            break;
        }
        }
    }
}

void shop::OpenShop() const
{
    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << "                    ITEMS FOR SALE                  " << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;

    for (int i = 0; i < 4; i++) {
        if (shopItems[i] != -1 && shopItemPtrs[i] != nullptr) {
            std::cout << " [" << i + 1 << "] " << shopItemPtrs[i]->getname()
                << " - " << shopItemPtrs[i]->getprice() << " coins" << std::endl;
        }
        else {
            std::cout << " [" << i + 1 << "] Empty slot" << std::endl;
        }
    }
    std::cout << "----------------------------------------------------" << std::endl;
}

void shop::OpenWeaponShop() const
{
    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << "                   WEAPONS FOR SALE                 " << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;

    for (int i = 0; i < 5; i++) {
        if (weaponItems[i] != -1 && weaponItemPtrs[i] != nullptr) {
            std::cout << " [" << i + 1 << "] " << weaponItemPtrs[i]->getname()
                << " - " << weaponItemPtrs[i]->getprice() << " coins" << std::endl;
        }
        else {
            std::cout << " [" << i + 1 << "] Empty slot" << std::endl;
        }
    }
    std::cout << "----------------------------------------------------" << std::endl;
}

void shop::BuyItem(int itemSlot) const
{
    if (itemSlot < 0 || itemSlot >= 10) {
        std::cout << "Invalid slot number!" << std::endl;
        return;
    }

    if (shopItems[itemSlot] == -1) {
        std::cout << "No item in that slot!" << std::endl;
        return;
    }

    item* selectedItem = shopItemPtrs[itemSlot];
    int price = selectedItem->getprice();

    if (coins < price) {
        std::cout << "Not enough coins! You need " << price - coins << " more coins." << std::endl;
        return;
    }

    std::cout << "You bought " << selectedItem->getname() << " for " << price << " coins!" << std::endl;
    inv2.RecivedInv(shopItems[itemSlot]);
}

void shop::BuyWeapon(int weaponSlot) const
{
    if (weaponSlot < 0 || weaponSlot >= 10) {
        std::cout << "Invalid weapon slot number!" << std::endl;
        return;
    }

    if (weaponItems[weaponSlot] == -1) {
        std::cout << "No weapon in that slot!" << std::endl;
        return;
    }

    item* selectedWeapon = weaponItemPtrs[weaponSlot];
    int price = selectedWeapon->getprice();

    if (coins < price) {
        std::cout << "Not enough coins! You need " << price - coins << " more coins." << std::endl;
        return;
    }

    std::cout << "You bought " << selectedWeapon->getname() << " for " << price << " coins!" << std::endl;
    inv2.RecivedInv(weaponItems[weaponSlot]);
}

void shop::AddCoins(int amount)
{
    if (amount > 0) {
        coins += amount;
        std::cout << "Added " << amount << " coins. Total: " << coins << std::endl;
    }
}

int shop::GetCoins() const
{
    return coins;
}

bool shop::IsItemAvailable(int itemSlot) const
{
    if (itemSlot >= 0 && itemSlot < 10) {
        return shopItems[itemSlot] != -1;
    }
    return false;
}

bool shop::IsWeaponAvailable(int weaponSlot) const
{
    if (weaponSlot >= 0 && weaponSlot < 10) {
        return weaponItems[weaponSlot] != -1;
    }
    return false;
}
