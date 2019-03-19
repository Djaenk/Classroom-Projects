#ifndef ITEM_TO_PURCHASE_H
#define ITEM_TO_PURCHASE_H

#include <string>

class ItemToPurchase {
	public:
		ItemToPurchase();
		void SetName(std::string name);
		std::string GetName();
		void SetPrice(int price);
		int GetPrice();
		void SetQuantity(int quantity);
		int GetQuantity();
	private:
		std::string itemName;
		int itemPrice;
		int itemQuantity;
};

#endif