#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>

class Doctor {
private:
    std::string id;
    std::string name;
    std::string hospitalId;
    std::string hospitalName;
    std::string specialization;

public:
    Doctor(std::string id, std::string name, std::string hospitalId, std::string hospitalName, std::string specialization);

    std::string getId() const;
    std::string getName() const;
    std::string getHospitalId() const;
    std::string getHospitalName() const;
    std::string getSpecialization() const;

    void display() const;
};

#endif // DOCTOR_H