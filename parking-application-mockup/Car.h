#ifndef SDDS_CAR_H__
#define SDDS_CAR_H__
#include <iostream>
#include "Vehicle.h"
namespace sdds {
	class Car : public Vehicle {
		bool m_checkWash;
	public:
		Car();
		Car(const char* licensePlate, const char* mAndM);
		Car(const Car&);
		Car& operator=(const Car&);
		virtual ~Car() {};
		std::ostream& writeType(std::ostream& ostr = std::cout) const;
		std::istream& read(std::istream& istr = std::cin);
		std::ostream& write(std::ostream& ostr = std::cout) const;
	};

}
#endif