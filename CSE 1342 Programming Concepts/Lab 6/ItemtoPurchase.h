#ifndef ITEM_TO_PURCHASE_H
#define ITEM_TO_PURCHASE_H

#include <string>

using namespace std;//though namespaces are specified here,
					//using namespace is necessary because
					//grading is based on unit tests that don't

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