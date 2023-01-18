#ifndef SDDS_MOTORCYCLE_H__
#define SDDS_MOTORCYCLE_H__
#include <iostream>
#include "Vehicle.h"
namespace sdds {
	class Motorcycle : public Vehicle {
		bool m_checkSideCar;
	public:
		Motorcycle();
		Motorcycle(const char* licensePlate, const char* mAndM);
		Motorcycle(const Motorcycle&);
		Motorcycle& operator=(const Motorcycle& value);
		virtual ~Motorcycle() {};
		std::ostream& writeType(std::ostream& ostr = std::cout) const;
		std::istream& read(std::istream& istr = std::cin);
		std::ostream& write(std::ostream& ostr) const;
	};
}
#endif