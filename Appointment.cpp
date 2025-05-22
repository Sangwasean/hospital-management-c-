#include "Appointment.h"
#include <iostream>

Appointment::Appointment(std::string id, std::string patientId, std::string hospitalId, std::string doctorId, std::string date)
        : id(id), patientId(patientId), hospitalId(hospitalId), doctorId(doctorId), date(date) {}

std::string Appointment::getId() const { return id; }
std::string Appointment::getPatientId() const { return patientId; }
std::string Appointment::getHospitalId() const { return hospitalId; }
std::string Appointment::getDoctorId() const { return doctorId; }
std::string Appointment::getDate() const { return date; }

void Appointment::display() const {
    std::cout << "Appointment ID: " << id << "\n";
    std::cout << "Patient ID: " << patientId << "\n";
    std::cout << "Hospital ID: " << hospitalId << "\n";
    std::cout << "Doctor ID: " << doctorId << "\n";
    std::cout << "Date: " << date << "\n";
}