/*
* Student Name: Henrique Toshio Sagara
* Student ID: 170954218
* Email: hsagara@myseneca.ca
*/
#ifndef SDDS_MENU_H_
#define SDDS_MENU_H
#include <iostream>
#include "Utils.h"
#include "Vehicle.h"

namespace sdds {
	const int MAX_MENU_ITEMS = 50;
	const int MAX_NO_OF_ITEMS = 10;
	class Menu;

	class MenuItem {
		friend class Menu;
		char* mItems{};
		void setEmpty();
		MenuItem();
		MenuItem(const char* content);
		~MenuItem();
		MenuItem(const MenuItem&) = delete;
		void operator=(const MenuItem) = delete;
		operator bool() const;
		operator const char* () const;
		std::ostream& displayItems(std::ostream& ostr = std::cout)const;
	};

	class Menu {
		char title[MAX_MENU_ITEMS + 1]{};
		MenuItem items[MAX_NO_OF_ITEMS];
		int identIndex = 0;
		int count = 0;
	public:
		Menu();
		Menu(const char*, int value = 0);
		void operator=(const Menu&) = delete;
		operator bool()const;
		bool isEmpty()const;
		std::ostream& display(std::ostream& ostr = std::cout)const;
		std::ostream& identention(std::ostream& ostr = std::cout)const;
		int run()const;
		Menu& operator=(const char* content);
		void clear();
		void add(const char*);
		Menu& operator<<(const char* content);
		void setEmpty();
		operator int()const;
	};

}
#endif