#include "ReadWritable.h"

using namespace std;

namespace sdds
{
    ReadWritable::ReadWritable()
    {
        this->m_commaSep = false;
    }

    bool ReadWritable::isCsv() const
    {
        return this->m_commaSep;
    }

    void ReadWritable::setCsv(bool value)
    {
        this->m_commaSep = value;
    }

    std::istream& operator>>(std::istream& is, ReadWritable& r)
    {
        r.read(is);
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const ReadWritable& r)
    {
        r.write(os);
        return os;
    }
}
