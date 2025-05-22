#include "Patient.h"
#include <iostream>

Patient::Patient(std::string id, std::string name, std::string dob, std::string hospitalId)
        : id(id), name(name), dob(dob), hospitalId(hospitalId) {}

std::string Patient::getId() const { return id; }
std::string Patient::getName() const { return name; }
std::string Patient::getDob() const { return dob; }
std::string Patient::getHospitalId() const { return hospitalId; }

void Patient::display() const {
    std::cout << "Patient ID: " << id << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Date of Birth: " << dob << "\n";
    std::cout << "Hospital ID: " << hospitalId << "\n";
}