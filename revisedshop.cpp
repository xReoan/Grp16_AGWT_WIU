#include "revisedshop.h"
#include "item.h"
#include "itemDatabase.h"
#include "inv.h"
#include <iostream>
#include <cstdlib>

// initialize the arrays + they are using the same array so static would make sense here
int revisedshop::shopItems[9] = { 6, 7, 8, 9, 10, 11, 12, 13, 14 };
int revisedshop::weaponItems[5] = { 1, 2, 3, 4, 5 };

revisedshop::revisedshop() : coins()
{
    for (int i = 0; i < 10; i++) { // for each index in the shopItems + shopItemPtrs arrays
        if (shopItems[i] != -1) { // check value at i in shopItems is NOT -1 = " slot is empty ", have "-1" there because all valid items start from 0, therefore "-1" cannot refer to any valid items, considering it a "item invalid/empty"
            shopItemPtrs[i] = database.getitem(shopItems[i]); 
        }
        else {
            shopItemPtrs[i] = nullptr; // to say "don't add item/don't use it"
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

void revisedshop::ShopMenu()
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
				BuyItem(slotChoice - 1); // do a "- 1" so that the user can input 1-10, but the array is 0-9
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

// shop items displayed after "I"
void revisedshop::OpenShop() const // const so it doesnt change any data
{
    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << "                    ITEMS FOR SALE                  " << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;

    for (int i = 0; i < 9; i++) {
        if (shopItems[i] != -1 && shopItemPtrs[i] != nullptr) { // if the item is NOT -1 and NOT nullptr=meaaning it exists in memory
            std::cout << " [" << i + 1 << "] " << shopItemPtrs[i]->getname() // use nullptr as a checker/a sential value as it'll mean nothing is there, this also prevents crashes
                << " - " << shopItemPtrs[i]->getprice() << " coins" << std::endl; // nullptr instead of 0 because 0 can be mistaken as an integer but nullptr refers to only a pointer.
			std::cout << "     " << shopItemPtrs[i]->getdescription() << std::endl;
            if (shopItemPtrs[i]->getdefensevalue() != 0) {
				// if the item has defense value
                std::cout << "    Defense Value: " << shopItemPtrs[i]->getdefensevalue() << std::endl;
            }
            if (shopItemPtrs[i]->gethealvalue() != 0) {
                // if item has health value
                std::cout << "    Health Value: " << shopItemPtrs[i]->gethealvalue() << std::endl;
            }
			if (shopItemPtrs[i]->getduration() != 0) {
                // if item has a duration
					std::cout << "    Duration: " << shopItemPtrs[i]->getduration() << " turns" << std::endl;
				
			}
        }
        else {
            std::cout << " [" << i + 1 << "] Empty slot" << std::endl;
        }
    }
    std::cout << "----------------------------------------------------" << std::endl;
}

// weapon items displayed after "W"
void revisedshop::OpenWeaponShop() const
{
    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << "                   WEAPONS FOR SALE                 " << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;

    for (int i = 0; i < 5; i++) {
        if (weaponItems[i] != -1 && weaponItemPtrs[i] != nullptr) {
            std::cout << " [" << i + 1 << "] " << weaponItemPtrs[i]->getname()
                << " - " << weaponItemPtrs[i]->getprice() << " coins" << std::endl;
            std::cout << "    " << weaponItemPtrs[i]->getdescription() << std::endl;
            // if weapon has attack value
            if (weaponItemPtrs[i]->getattackvalue() != 0) {
                std::cout << "    Attack Value: " << weaponItemPtrs[i]->getattackvalue() << std::endl;
            }
        }
        else {
            std::cout << " [" << i + 1 << "] Empty slot" << std::endl;
        }
    }
    std::cout << "----------------------------------------------------" << std::endl;
}

void revisedshop::BuyItem(int itemSlot)
{
    if (itemSlot < 0 || itemSlot >= 10) { // not in list
        std::cout << "Invalid slot number!" << std::endl;
        return;
    }

	if (shopItems[itemSlot] == -1) { // if the item is -1, it doesn't exist 
        std::cout << "No item in that slot!" << std::endl;
        return;
    }

	// if the player has enough coins to buy the item
    item* selectedItem = shopItemPtrs[itemSlot];
    int price = selectedItem->getprice();

    if (coins < price) {
        std::cout << "Not enough coins! You need " << price - coins << " more coins." << std::endl;
        return;
    }

    std::cout << "You bought " << selectedItem->getname() << " for " << price << " coins!" << std::endl;
    inv2.ReceivedInv(shopItems[itemSlot]);
}

void revisedshop::BuyWeapon(int weaponSlot)
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
    inv2.ReceivedInv(weaponItems[weaponSlot]);
}

// CURRENCY ---------------
void revisedshop::AddCoins(int amount)
{
    if (amount > 0) {
        coins += amount; // add amount added to coins
        std::cout << "Added " << amount << " coins. Total: " << coins << std::endl;
    }
}

// returns current coin total of the shop
int revisedshop::GetCoins() const // const=ensure func no change the shop's data aka does nnt modify any variables
{
    return coins; // sends back the coin value if called by diff func
}

// check if item available
bool revisedshop::IsItemAvailable(int itemSlot) const
{
    if (itemSlot >= 0 && itemSlot < 10) {
        return shopItems[itemSlot] != -1; // return true/false based on slot
    }
    return false;
}

//check if weapon available
bool revisedshop::IsWeaponAvailable(int weaponSlot) const
{
    if (weaponSlot >= 0 && weaponSlot < 10) {
        return weaponItems[weaponSlot] != -1;
    }
    return false;
}
