#include "Doctor.h"
#include <iostream>

Doctor::Doctor(std::string id, std::string name, std::string hospitalId, std::string hospitalName, std::string specialization)
        : id(id), name(name), hospitalId(hospitalId), hospitalName(hospitalName), specialization(specialization) {}

std::string Doctor::getId() const { return id; }
std::string Doctor::getName() const { return name; }
std::string Doctor::getHospitalId() const { return hospitalId; }
std::string Doctor::getHospitalName() const { return hospitalName; }
std::string Doctor::getSpecialization() const { return specialization; }

void Doctor::display() const {
    std::cout << "Doctor ID: " << id << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Hospital: " << hospitalName << " (ID: " << hospitalId << ")\n";
    std::cout << "Specialization: " << specialization << "\n";
}