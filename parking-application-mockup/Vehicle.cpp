#include "Vehicle.h"

using namespace std;

namespace sdds
{
    Vehicle::Vehicle()
    {
        setEmpty();
    }

    Vehicle::Vehicle(const char* lPlate, const char* mModel)
    {
        setEmpty();
        if (lPlate != nullptr && lPlate[0] != '\0' && mModel != nullptr && mModel[0] != '\0' && strlen(lPlate) <= 8 && strlen(mModel) >= 2 && strlen(mModel) <= MAX_READ_CHAR)
        {
            strcpy(this->m_licensePlate, lPlate, MAX_PLATE);
            this->m_licensePlate[MAX_PLATE] = '\0';
            this->m_makeAndModel = new char[strlen(mModel) + 1];
            strcpy(this->m_makeAndModel, mModel, strlen(mModel) + 1);
            this->m_pSpotNumber = 0;
        }
    }

    Vehicle::~Vehicle()
    {
        delete[] this->m_makeAndModel;
    }

    Vehicle::Vehicle(const Vehicle& value)
    {
        setEmpty();
        *this = value;
    }

    Vehicle& Vehicle::operator=(const Vehicle& value)
    {
        if (this != &value)
        {
            if (this->m_makeAndModel != nullptr)
            {
                delete[] this->m_makeAndModel;
                this->m_makeAndModel = nullptr;
            }
            strcpy(this->m_licensePlate, value.m_licensePlate, MAX_PLATE);
            this->m_licensePlate[MAX_PLATE] = '\0';
            if (value.m_makeAndModel != nullptr)
            {
                this->m_makeAndModel = new char[strlen(value.m_makeAndModel) + 1];
                strcpy(this->m_makeAndModel, value.m_makeAndModel, strlen(value.m_makeAndModel) + 1);
            }
            this->m_pSpotNumber = value.m_pSpotNumber;
            this->setCsv(value.isCsv());
        }
        return *this;
    }

    const char* Vehicle::getLicensePlate() const
    {
        return this->m_licensePlate;
    }

    const char* Vehicle::getMakeModel() const
    {
        return this->m_makeAndModel;
    }

    void Vehicle::setMakeModel(const char* mModel)
    {
        if (mModel != nullptr && mModel[0] != '\0')
        {
            if (this->m_makeAndModel != nullptr)
            {
                delete[] this->m_makeAndModel;
                this->m_makeAndModel = nullptr;
            }
            this->m_makeAndModel = new char[strlen(mModel) + 1];
            strcpy(this->m_makeAndModel, mModel);
        }
    }

    int Vehicle::getParkingSpot() const
    {
        return this->m_pSpotNumber;
    }

    void Vehicle::setParkingSpot(int value)
    {
        if (value >= 0)
        {
            this->m_pSpotNumber = value;
        }
        else
        {
            setEmpty();
        }
    }

    bool Vehicle::operator==(const char* licensePlate) const
    {
        bool result = false;
        if ((licensePlate) && licensePlate[0] != '\0' && (this->m_licensePlate) && this->m_licensePlate[0] != '\0')
        {
            char* licensePlateTmp = alcpy(licensePlate);
            for (int i = 0; licensePlateTmp[i] != '\0'; i++)
            {
                licensePlateTmp[i] = tolower(licensePlateTmp[i]);
            }
            char* temp = alcpy(this->m_licensePlate);
            for (int i = 0; temp[i] != '\0'; i++)
            {
                temp[i] = tolower(temp[i]);
            }
            bool result = (strcmp(licensePlateTmp, temp) == 0);
            delete[] licensePlateTmp;
            delete[] temp;
            return result;
        }
        return result;
    }

    bool Vehicle::operator==(const Vehicle& value) const
    {
        return bool(value.getLicensePlate());
    }

    istream& Vehicle::read(istream& is)
    {
        if (isCsv())
        {
            is >> this->m_pSpotNumber;
            is.ignore();
            is.getline(this->m_licensePlate, 9, ',');
            for (int i = 0; this->m_licensePlate[i] != '\0' && i < 9; i++)
            {
                this->m_licensePlate[i] = toupper(this->m_licensePlate[i]);
            }
            char tempMakeModel[MAX_READ_CHAR + 1];
            is.getline(tempMakeModel, MAX_READ_CHAR + 1, ',');
            setMakeModel(tempMakeModel);
        }
        else
        {

            this->m_pSpotNumber = 0;
            cout << "Enter License Plate Number: ";
            string tempLicensePlate;
            getline(is, tempLicensePlate);
            while (tempLicensePlate.length() > 8)
            {
                cout << "Invalid License Plate, try again: ";
                getline(is, tempLicensePlate);
            }
            for (int i = 0; tempLicensePlate[i] != '\0' && i < 8; i++)
            {
                tempLicensePlate[i] = toupper(tempLicensePlate[i]);
            }
            strcpy(this->m_licensePlate, tempLicensePlate.c_str(), strlen(tempLicensePlate.c_str()) + 1);
            cout << "Enter Make and Model: ";
            string tempMakeModel;
            getline(is, tempMakeModel);
            while (tempMakeModel.length() < 2 || tempMakeModel.length() > 60)
            {
                cout << "Invalid Make and model, try again: ";
                getline(is, tempMakeModel);
            }
            setMakeModel(tempMakeModel.c_str());
        }

        if (is.fail())
        {
            setEmpty();
        }
        return is;
    }

    ostream& Vehicle::write(ostream& os) const
    {
        if (this->isEmpty())
        {
            os << "Invalid Vehicle Object" << endl;
        }
        else
        {
            writeType(os);
            if (isCsv())
            {
                os << this->m_pSpotNumber << "," << m_licensePlate << "," << this->m_makeAndModel << ",";
            }
            else
            {
                os << "Parking Spot Number: ";
                if (this->m_pSpotNumber == 0)
                {
                    os << "N/A" << endl;
                }
                else
                {
                    os << this->m_pSpotNumber << endl;
                }
                os << "License Plate: " << this->m_licensePlate << endl;
                os << "Make and Model: " << this->m_makeAndModel << endl;
            }
        }
        return os;
    }
    void Vehicle::setEmpty()
    {
        m_licensePlate[0] = '\0';
        if (this->m_makeAndModel != nullptr)
        {
            delete[] this->m_makeAndModel;
            this->m_makeAndModel = nullptr;
        }
        this->m_pSpotNumber = 0;
    }

    bool Vehicle::isEmpty() const
    {
        return this->m_licensePlate[0] == '\0' && this->m_makeAndModel == nullptr && this->m_pSpotNumber == 0;
    }
}
