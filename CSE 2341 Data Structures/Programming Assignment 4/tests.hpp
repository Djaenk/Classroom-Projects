#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include "linkedlist.h"
#include "stack.h"
#include <iostream>

TEST_CASE("Linked list and stack tests"){
	LinkedList<int> list;
	Stack<int> stack;

	SECTION("Default constructor and size function"){
		REQUIRE(list.size() == 0);
	}
	
	SECTION("Indexing"){
		list.insert(1, 0);
		list.insert(2, 0);
		list.insert(3, 0);
		list.insert(4, 0);
		list.insert(5, 0);
		REQUIRE(list[0] == 5);
		REQUIRE(list[2] == 3);
		REQUIRE(list[4] == 1);
	}

	SECTION("Appending"){
		list.append(10);
		list.append(20);
		list.append(30);
		REQUIRE(list[0] == 10);
		REQUIRE(list[1] == 20);
		REQUIRE(list[2] == 30);
	}

	SECTION("Prepending"){
		list.prepend(10);
		list.prepend(20);
		list.prepend(30);
		REQUIRE(list[0] == 30);
		REQUIRE(list[1] == 20);
		REQUIRE(list[2] == 10);
	}

	SECTION("Erasing"){
		list.insert(1, 0);
		list.insert(2, 0);
		list.insert(3, 0);
		list.insert(4, 0);
		list.insert(5, 0);
		list.erase(0);
		list.erase(1);
		REQUIRE(list[0] == 4);
		REQUIRE(list[2] == 1);
	}

	SECTION("pushing and popping"){
		stack.push(1);
		stack.push(2);
		stack.push(3);
		REQUIRE(stack.pop() == 3);
		REQUIRE(stack.pop() == 2);
		REQUIRE(stack.pop() == 1);
	}
}