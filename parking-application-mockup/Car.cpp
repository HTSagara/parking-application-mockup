#include "Car.h"

using namespace std;
namespace sdds {
	Car::Car() {
		setEmpty();
		this->m_checkWash = false;
	}
	Car::Car(const char* licensePlate, const char* mAndM) : Vehicle(licensePlate, mAndM) {
		this->m_checkWash = false;
	}
	Car::Car(const Car& value) {
		setEmpty();
		*this = value;
	}
	Car& Car::operator=(const Car& value) {
		(Vehicle&)*this = value;
		this->m_checkWash = value.m_checkWash;
		return *this;
	}
	ostream& Car::writeType(ostream& ostr) const {
		if (!isCsv()) {
			ostr << "Vehicle type: Car" << endl;
		}
		else {
			ostr << "C,";
		}
		return ostr;
	}
	istream& Car::read(istream& istr) {
		string answerCarWash;
		if (!isCsv()) {
			cout << endl;
			cout << "Car information entry" << endl;
			//It will read the Base class.
			Vehicle::read(istr);
			cout << "Carwash while parked? (Y)es/(N)o: ";
			do {
				getline(istr, answerCarWash, '\n');
				if (!(answerCarWash.length() == 1 && (tolower(answerCarWash[0]) == 'y' || tolower(answerCarWash[0]) == 'n'))) {
					istr.clear();
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				}
			} while (!(answerCarWash.length() == 1 && (tolower(answerCarWash[0]) == 'y' || tolower(answerCarWash[0]) == 'n')));
			if (tolower(answerCarWash[0]) == 'y') {
				this->m_checkWash = true;
			}
			else if (tolower(answerCarWash[0]) == 'n') {
				this->m_checkWash = false;
			}
		}
		else {
			Vehicle::read(istr);
			istr >> this->m_checkWash;
			istr.ignore(1000, '\n');
		}
		return istr;
	}
	ostream& Car::write(ostream& ostr) const {
		if (!isEmpty()) {
			Vehicle::write(ostr);
			if (isCsv()) {
				ostr << this->m_checkWash << endl;
			}
			else {
				if (this->m_checkWash) {
					ostr << "With Carwash" << endl;
				}
				else {
					ostr << "Without Carwash" << endl;
				}
			}
		}
		else {
			ostr << "Invalid Car Object" << endl;
		}
		return ostr;
	}
}