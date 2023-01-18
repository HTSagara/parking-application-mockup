#ifndef SDDS_READWRITABLE_H__
#define SDDS_READWRITABLE_H__

#include <iostream>
#include <string.h>
#include <iomanip>
#include "Utils.h"

namespace sdds
{
    class ReadWritable
    {
        bool m_commaSep; // bool flag --> keep the stat of reading or writing the object in Comma Separated mode or not

    public:
        ReadWritable(); //no-argument constructor that sets the Comma Separated Values flag to false.
        virtual ~ReadWritable() {};    //empty virtual destructor
        bool isCsv() const; // This query returns the Comma Separated Values flag
        void setCsv(bool value); // set the Comma Separated Values flag to the incoming bool value
        virtual std::istream& read(std::istream& is = std::cin) = 0;
        virtual std::ostream& write(std::ostream& os = std::cout) const = 0;
    };
    std::istream& operator>>(std::istream&, ReadWritable&);
    std::ostream& operator<<(std::ostream&, const ReadWritable&);
}

#endif