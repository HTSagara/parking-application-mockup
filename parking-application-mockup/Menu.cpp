/*
* Student Name: Henrique Toshio Sagara
* Student ID: 170954218
* Email: hsagara@myseneca.ca
*/
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "Menu.h"
#include "Utils.h"

using namespace std;
namespace sdds {
    //*******************************************************************
    // Menu Item Class
    //*******************************************************************
    void MenuItem::setEmpty() {
        this->mItems = nullptr;
    }
    MenuItem::MenuItem() {
        setEmpty();
    }
    MenuItem::MenuItem(const char* content) {
        if (content && content[0]) {
            this->mItems = new char[strlen(content) + 1];
            strcpy(this->mItems, content);
        }
        else {
            setEmpty();
        }
    }
    MenuItem::~MenuItem() {
        delete[] this->mItems;
    }
    MenuItem::operator bool() const {
        return (this->mItems && this->mItems[0]);
    };
    MenuItem::operator const char* () const {
        return this->mItems;
    }
    std::ostream& MenuItem::displayItems(std::ostream& ostr)const {
        if (*this) {
            ostr << this->mItems;
        }
        return ostr;
    }

    //*******************************************************************
    // Menu Class
    //*******************************************************************
    Menu::Menu() {
        this->count = 0;
    };
    Menu::Menu(const char* content, int value) {
        if (content) {
            strcpy(this->title, content, MAX_MENU_ITEMS);
            this->identIndex = value;
        }
        else {
            this->title[0] = '\0';
            this->identIndex = 0;
        }
    }
    Menu::operator bool()const {
        if (!isEmpty()) {
            return true;
        }
        else {
            return false;
        }
    }
    bool Menu::isEmpty()const {
        return this->title[0] == '\0';
    }
    std::ostream& Menu::display(std::ostream& ostr)const {
        if (*this) {
            this->identention(ostr);
            ostr << this->title << endl;
            for (int i = 0; i < this->count; i++) {
                this->identention(ostr);
                ostr << i + 1 << "- ";
                this->items[i].displayItems(ostr);
                ostr << endl;
            }
            if (this->count > 0) {
                this->identention(ostr);
                ostr << "> ";
            }

        }
        else if (this->count <= 0) {
            ostr << "Invalid Menu!" << endl;
        }
        return ostr;
    }
    std::ostream& Menu::identention(std::ostream& ostr)const {
        int i;
        for (i = 0; i < this->identIndex; i++) {
            ostr << "    ";
        }
        return ostr;
    }
    Menu& Menu::operator=(const char* content) {
        strcpy(this->title, content, MAX_MENU_ITEMS);
        return *this;
    }
    int Menu::run()const {
        int input;
        bool checkInput;
        this->display();
        if (!this->isEmpty()) {
            if (this->count <= 0) {
                std::cout << "No Items to display!" << endl;
                return 0;
            }
            else {
                do {
                    cin >> input;
                    if (std::cin.fail() || (input <= 0 || input > this->count)) {
                        checkInput = false;
                        if (std::cin.fail()) {
                            std::cout << "Invalid Integer, try again: ";
                            std::cin.clear();
                            std::cin.ignore(1000, '\n');
                        }
                        else if (input <= 0 || input > this->count) {
                            std::cout << "Invalid selection, try again: ";
                            std::cin.clear();
                            std::cin.ignore(1000, '\n');
                        }

                    }
                    else {
                        checkInput = true;
                        std::cin.ignore(1000, '\n');
                    }
                } while (checkInput == false);
                return input;
            }
        }
        return 0;
    }
    void Menu::clear() {
        this->title[0] = '\0';
        this->identIndex = 0;
        this->count = 0;
    }
    void Menu::add(const char* content) {
        if (!(this->isEmpty()) && this->count < MAX_NO_OF_ITEMS && content != nullptr) {
            this->items[count].mItems = new char[strlen(content) + 1];
            std::strcpy(this->items[count].mItems, content);
            this->count++;
        }
        else {
            this->setEmpty();
        }
    }
    Menu& Menu::operator<<(const char* content) {
        if (count < MAX_MENU_ITEMS)
        {
            add(content);
        }
        return *this;
    }
    void Menu::setEmpty() {
        this->count = 0;
        this->identIndex = 0;
        this->title[0] = '\0';

    }
    Menu::operator int()const {
        return this->run();
    }
    //*******************************************************************
    // Helper Function
    //*******************************************************************
    std::ostream& operator<<(std::ostream& ostr, Menu& menu) {
        return (menu.display(ostr));
    }
}