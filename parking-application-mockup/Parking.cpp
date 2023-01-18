#define _CRT_SECURE_NO_WARNINGS
#include "Parking.h"

using namespace std;
namespace sdds {
	//********************
	//Private Members
	//********************
	void Parking::cancelledParking()const {
		cout << "Parking cancelled" << endl;
	}
	void Parking::returningVehicle() {
		char input[1000];
		bool find = false;

		cout << "Return Vehicle" << endl;
		cout << "Enter License Plate Number: ";
		do {
			cin >> input;
			if (strlen(input) < 1 || strlen(input) > MAX_PLATE) {
				cout << "Invalid License Plate, try again: ";
				cin.clear();
			}
		} while (strlen(input) < 1 || strlen(input) > MAX_PLATE);
		cin.ignore(1000, '\n');

		for (int i = 0; i < strlen(input) + 1; i++) {
			input[i] = toupper(input[i]);
		}

		for (int i = 0; i < this->parkedVehicles + this->numOfSpots && !find; i++) {
			if (this->parkingSpots[i] != nullptr) {
				if (*this->parkingSpots[i] == input) {
					cout << endl;
					cout << "Returning:" << endl;
					this->parkingSpots[i]->setCsv(false);
					this->parkingSpots[i]->write();
					cout << endl;
					cout << "Press <ENTER> to continue....";
					delete this->parkingSpots[i];
					this->parkingSpots[i] = nullptr;

					cout << endl;
					find = true;
					this->numOfSpots++;
					this->parkedVehicles--;
				}
			}
		}
		if (!find) {
			cout << endl;
			cout << "License plate " << input << " Not found" << endl;
			cout << endl;
			cout << "Press <ENTER> to continue...." << endl;
		}
	}
	void Parking::listingVehicles() {
		cout << "*** List of parked vehicles ***" << endl;
		for (int i = 0; i < this->parkedVehicles + this->numOfSpots; i++) {
			if (this->parkingSpots[i] != nullptr) {
				this->parkingSpots[i]->setCsv(false);
				this->parkingSpots[i]->write();
				cout << "-------------------------------" << endl;
			}
		}
		cout << "Press <ENTER> to continue...." << endl;
	}
	void Parking::findingVehicle() {
		char input[MAX_PLATE + 1];
		bool find = false;
		cout << "Vehicle Search" << endl;
		cout << "Enter Licence Plate Number: ";
		do
		{
			cin >> input;
			if (strlen(input) < 1 || strlen(input) > MAX_PLATE) {
				cout << "Invalid Licence Plate, try again: ";
				cin.clear();
			}
		} while (strlen(input) < 1 || strlen(input) > MAX_PLATE);
		cin.ignore(1000, '\n');

		for (int i = 0; i < strlen(input) + 1; i++) {
			input[i] = toupper(input[i]);
		}

		for (int i = 0; i <= this->parkedVehicles + this->numOfSpots && !find; i++) {
			if (this->parkingSpots[i] != nullptr) {
				if (*this->parkingSpots[i] == input) {
					cout << endl;
					cout << "Vehicle found:" << endl;
					this->parkingSpots[i]->setCsv(false);
					this->parkingSpots[i]->write();
					cout << endl;
					find = true;
				}
			}
		}

		if (!find) {
			cout << endl;
			cout << "License plate " << input << " Not found" << endl << endl;
		}
		cout << "Press <ENTER> to continue...." << endl;

	}
	bool Parking::isEmpty()const {
		if (this->fileName == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}
	void Parking::parkingStatus()const {
		cout << "****** Valet Parking ******" << endl;
		cout << "*****  Available spots: ";
		cout.width(5);
		cout.setf(ios::left);
		cout << this->numOfSpots << "*****" << endl;
	}
	void Parking::parkVehicle() {
		int input = this->vehicleSelection.run();
		Vehicle* value = nullptr;
		bool checkAssign = true;
		if (input == 1) {
			value = new Car();
			value->setCsv(false);
			value->read();
		}
		else if (input == 2) {
			value = new Motorcycle();
			value->setCsv(false);
			value->read();
		}
		else if (input == 3) {
			this->cancelledParking();
		}
		for (int i = 0; i < this->numOfSpots + this->parkedVehicles && checkAssign; i++) {
			if (this->parkingSpots[i] == nullptr) {
				checkAssign = false;
				this->parkingSpots[i] = value;
				this->parkingSpots[i]->setParkingSpot(i + 1);
				cout << endl;
				cout << "Parking Ticket" << endl;
				this->parkingSpots[i]->write();
				cout << endl;
				this->numOfSpots--;
				this->parkedVehicles++;
				cout << "Press <ENTER> to continue...." << endl;
			}
		}
	}
	bool Parking::closeParking() {
		char answer;
		bool closePark = false;

		if (this->parkedVehicles == 0) {
			cout << "Closing Parking" << endl;
			closePark = true;
		}
		else {
			cout << "This will This will Remove and tow all remaining vehicles from the parking!!" << endl;
			cout << "Are you sure? (Y)es/(N)o: ";
			do {
				cin >> answer;
				answer = tolower(answer);
				if (answer == 'y') {
					cout << "Closing Parking" << endl;
					for (int i = 0; i <= this->numOfSpots + this->parkedVehicles;i++) {
						if (this->parkingSpots[i] != nullptr) {
							cout << endl;
							cout << "Towing request" << endl;
							cout << "*********************" << endl;
							this->parkingSpots[i]->setCsv(false);
							this->parkingSpots[i]->write();
							delete this->parkingSpots[i];
							this->parkingSpots[i] = nullptr;
						}
					}
					closePark = true;
				}
				else if (answer == 'n') {
					closePark = false;
				}
				else {
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				}
			} while (answer != 'y' && answer != 'n');
			cin.clear();
		}
		return closePark;
	}
	bool Parking::exitProgram()const {
		char answer;
		bool checkAnswer;
		cout << "This will terminate the program!" << endl;
		cout << "Are you sure? (Y)es/(N)o: ";
		do {
			cin >> answer;
			if (answer == 'Y' || answer == 'y') {
				cout << "Exiting program!" << endl;
				checkAnswer = true;
			}
			else if (answer == 'N' || answer == 'n') {
				checkAnswer =  false;
			}
			else {
				cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				cin.clear();
				cin.ignore(1000, '\n');
			}
			cin.clear();
			cin.ignore(1000, '\n');
		} while (answer != 'y' && answer != 'n');
		return checkAnswer;
	}

	bool Parking::loadFile() {
		ifstream myFile;
		bool checkLoaded = true;
		int i = 0;
		char firstChar = 'X';
		Vehicle* value = nullptr;
		
		if (!this->isEmpty()) {
			myFile.open(this->fileName);
		}
		if (!myFile) {
			checkLoaded = true;
		}
		else {
			while (i < this->numOfSpots && checkLoaded && myFile) {
				myFile.get(firstChar);
				myFile.ignore();
				if (firstChar) {
					switch (firstChar) {
					case 'M':
						value = new Motorcycle();
						break;
					case 'C':
						value = new Car();
						break;
					}

					if (value != nullptr) {		//If either of the two Vehicles is allocated
						value->setCsv(true);	//set the Vehicle to Comma Separate Value mode
						myFile >> *value;		//extract its values from the data file
						if (myFile) {
							this->parkingSpots[value->getParkingSpot() - 1] = value;
							this->parkedVehicles++;
						}
						else if (!myFile) {
							delete value;
						}
						checkLoaded = true;
					}
					i++;
				}
				else {
					checkLoaded = false;
				}
			}
			myFile.clear();
			myFile.close();
			this->numOfSpots -= this->parkedVehicles;
		}
		return checkLoaded;
	}
	void Parking::saveFile() {
		ofstream myFile;
		if (!this->isEmpty()) {
			myFile.open(this->fileName);
		}
		if (myFile) {
			for (int i = 0; i < this->parkedVehicles + this->numOfSpots; i++) {
				if (this->parkingSpots[i] != nullptr) {
					this->parkingSpots[i]->setCsv(true);
					myFile << *this->parkingSpots[i];
				}
			}
		}
		myFile.close();
	}
	void Parking::setEmpty() {
		delete[] this->fileName;
		this->fileName = nullptr;
	}
	//********************
	//Constructors
	//********************
	Parking::Parking(const char* temp, int noOfSpots) : parkingMenu("Parking Menu, select an action:", 0), vehicleSelection("Select type of the vehicle:", 1) {
		this->numOfSpots = 0;
		this->parkedVehicles = 0;

		if (temp == nullptr || temp[0] == '\0') {
			this->fileName = nullptr;
			if (noOfSpots < 10 || noOfSpots > MAX_PARKING_SPOTS) {
				this->numOfSpots = 0;
			}
		}
		else {
			this->fileName = new char[strlen(temp) + 1];
			strcpy(this->fileName, temp);
			this->numOfSpots = noOfSpots;
		}
		if (!this->loadFile()) {
			cout << "Error in data file" << endl;
		}
		this->parkingMenu.add("Park Vehicle");
		this->parkingMenu.add("Return Vehicle");
		this->parkingMenu.add("List Parked Vehicles");
		this->parkingMenu.add("Find Vehicle");
		this->parkingMenu.add("Close Parking (End of day)");
		this->parkingMenu.add("Exit Program");
		this->vehicleSelection << "Car" << "Motorcycle" << "Cancel";
	}
	Parking::~Parking() {
		this->saveFile();
		delete[] this->fileName;
		this->fileName = nullptr;
		for (int i = 0; i < this->parkedVehicles + this->numOfSpots; i++) {
			if (this->parkingSpots[i] != nullptr) {
				delete this->parkingSpots[i];
				this->parkingSpots[i] = nullptr;
			}			
		}
	}
	int Parking::run() {
		int answer1;
		bool quit = false;
		if (!isEmpty()) {
			do
			{
				parkingStatus();
				answer1 = this->parkingMenu;
				switch (answer1) {
				case 1:
					this->parkVehicle();
					break;
				case 2:
					this->returningVehicle();
					break;
				case 3:
					this->listingVehicles();
					break;
				case 4:
					this->findingVehicle();
					break;
				case 5:
					quit = this->closeParking();
					break;
				case 6:
					quit = this->exitProgram();
					break;
				}
			} while (quit == false);
			return 0;
		}
		else {
			return 1;
		}
	}
}