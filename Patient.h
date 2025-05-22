#ifndef PATIENT_H
#define PATIENT_H

#include <string>

class Patient {
private:
    std::string id;
    std::string name;
    std::string dob;
    std::string hospitalId;

public:
    Patient(std::string id, std::string name, std::string dob, std::string hospitalId);

    std::string getId() const;
    std::string getName() const;
    std::string getDob() const;
    std::string getHospitalId() const;

    void display() const;
};

#endif // PATIENT_H