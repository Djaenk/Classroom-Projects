#include <iostream>
#include <string>
#include "ItemToPurchase.h"

using namespace std;//though namespaces are specified here,
					//using namespace is necessary because
					//grading is based on unit tests that don't
					
ItemToPurchase::ItemToPurchase(){
	itemName = "none";
	itemPrice = 0;
	itemQuantity = 0;
}

void ItemToPurchase::SetName(std::string name){
	itemName = name;
}

std::string ItemToPurchase::GetName(){
	return itemName;
}

void ItemToPurchase::SetPrice(int price){
	itemPrice = price;
}

int ItemToPurchase::GetPrice(){
	return itemPrice;
}

void ItemToPurchase::SetQuantity(int quantity){
	itemQuantity = quantity;
}

int ItemToPurchase::GetQuantity(){
	return itemQuantity;
}