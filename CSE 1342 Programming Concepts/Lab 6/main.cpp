#include <iostream>
#include "ItemToPurchase.h"

using namespace std;//though namespaces are specified here,
					//using namespace is necessary because
					//grading is based on unit tests that don't

int main() {
	std::string item_name;
	int price;
	int quantity;

	ItemToPurchase item;
	std::cout << "Item 1" << std::endl;
	std::cout << "Enter the item name:" << std::endl;
	std::getline(std::cin, item_name);
	item.SetName(item_name);
	std::cout << "Enter the item price:" << std::endl;
	std::cin >> price;
	item.SetPrice(price);
	std::cout << "Enter the item quantity:" << std::endl;
	std::cin >> quantity;
	item.SetQuantity(quantity);
	std::cout << std::endl;

	ItemToPurchase item_2;
	std::cout << "Item 2" << std::endl;
	std::cout << "Enter the item name:" << std::endl;
	std::cin.ignore();
	std::getline(std::cin, item_name);
	item_2.SetName(item_name);
	std::cout << "Enter the item price:" << std::endl;
	std::cin >> price;
	item_2.SetPrice(price);
	std::cout << "Enter the item quantity:" << std::endl;
	std::cin >> quantity;
	std::cin.ignore();
	item_2.SetQuantity(quantity);
	std::cout << std::endl;

	std::cout << "TOTAL COST" << std::endl;
	std::cout << item.GetName() << " " << item.GetQuantity() << " @ $" << item.GetPrice() << " = $" << item.GetPrice() * item.GetQuantity() << std::endl;
	std::cout << item_2.GetName() << " " << item_2.GetQuantity() << " @ $" << item_2.GetPrice() << " = $" << item_2.GetPrice() * item_2.GetQuantity() << std::endl;
	std::cout << std::endl << "Total: $" << (item.GetPrice() * item.GetQuantity()) + (item_2.GetPrice() * item_2.GetQuantity()) << std::endl;
	return 0;
}