#ifndef SDDS_PARKING_H__
#define SDDS_PARKING_H__
#include <iostream>
#include <fstream>
#include <cstring>
#include "Menu.h"
#include "Utils.h"
#include "Motorcycle.h"
#include "Car.h"
#include "Vehicle.h"

namespace sdds {
	const int MAX_PARKING_SPOTS = 100;
	class Parking : public Menu{
		char* fileName{};								//Filename: C-style string with an unknown size to hold the data path and file name of the application.
		Menu parkingMenu;								//Parking has a Menu object for the main menu of the application.
		Menu vehicleSelection;							//a Menu object for the Vehicle selection menu that is displayed as a submenu when option one of the Parking Menu is selected.
		int numOfSpots;
		int parkedVehicles;
		Vehicle* parkingSpots[MAX_PARKING_SPOTS]{};
		
		Parking(const Parking&) = delete;				//Copy and Assignment
		void operator=(const Parking) = delete;			//Copy and Assignment
		void cancelledParking()const;					//Park Vehicle / Cancel:
		void returningVehicle();						//Return Vehicle:
		void listingVehicles();							//List Parked Vehicles:
		void findingVehicle();							//Find Vehicle
		bool isEmpty()const;							//function that returns true if the Parking is in an invalid empty State or false if the parking is valid and usable.
		void parkingStatus()const;						//This function does not receive or return anything and at this stage only prints
		void parkVehicle();								//The function displays the Vehicle Selection sub-menu.
		bool closeParking();							//Close Parking function
		bool exitProgram()const;						//Exit Parking App Function
		bool loadFile();								//Load Data File function
		void saveFile();								//Save Data File function
	public:
		void setEmpty();
		Parking(const char*, int);						//Constructor
		virtual ~Parking();										//Deconstructor
		int run();

	};
}

#endif