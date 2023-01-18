#include "Motorcycle.h"

using namespace std;
namespace sdds {
	Motorcycle::Motorcycle() {
		setEmpty();
		this->m_checkSideCar = false;
	}
	Motorcycle::Motorcycle(const char* licensePlate, const char* mAndM) : Vehicle(licensePlate, mAndM) {
		this->m_checkSideCar = false;
	}
	Motorcycle::Motorcycle(const Motorcycle& value) {
		setEmpty();
		*this = value;
	}
	Motorcycle& Motorcycle::operator=(const Motorcycle& value) {
		if (this != &value) {
			(Vehicle&)*this = value;
			this->m_checkSideCar = value.m_checkSideCar;
		}
		return *this;
	}
	ostream& Motorcycle::writeType(ostream& ostr) const {
		if (!isCsv()) {
			ostr << "Vehicle type: Motorcycle" << endl;
		}
		else {
			ostr << "M,";
		}
		return ostr;
	}
	istream& Motorcycle::read(istream& istr) {
		string hasSideCar;
		if (!isCsv()) {
			cout << endl;
			cout << "Motorcycle information entry" << endl;
			//It will read the Base class.
			Vehicle::read(istr);
			cout << "Does the Motorcycle have a side car? (Y)es/(N)o: ";
			do {
				getline(istr, hasSideCar, '\n');
				if (!(hasSideCar.length() == 1 && (tolower(hasSideCar[0]) == 'y' || tolower(hasSideCar[0]) == 'n'))) {
					istr.clear();
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				}
			} while (!(hasSideCar.length() == 1 && (tolower(hasSideCar[0]) == 'y' || tolower(hasSideCar[0]) == 'n')));
			if (tolower(hasSideCar[0]) == 'y') {
				this->m_checkSideCar = true;
			}
			else if (tolower(hasSideCar[0]) == 'n') {
				this->m_checkSideCar = false;
			}
		}
		else {
			Vehicle::read(istr);
			istr >> this->m_checkSideCar;
			istr.ignore(10000, '\n');
		}
		return istr;
	}
	ostream& Motorcycle::write(ostream& ostr) const {
		if (!isEmpty()) {
			Vehicle::write(ostr);
			if (isCsv()) {
				ostr << this->m_checkSideCar << endl;
			}
			else if (this->m_checkSideCar) {
				ostr << "With Sidecar" << endl;
			}
		}
		else {
			ostr << "Invalid Motorcycle Object" << endl;
		}
		return ostr;
	}
}
