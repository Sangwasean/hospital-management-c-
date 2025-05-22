#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>

class Appointment {
private:
    std::string id;
    std::string patientId;
    std::string hospitalId;
    std::string doctorId;
    std::string date;

public:
    Appointment(std::string id, std::string patientId, std::string hospitalId, std::string doctorId, std::string date);

    std::string getId() const;
    std::string getPatientId() const;
    std::string getHospitalId() const;
    std::string getDoctorId() const;
    std::string getDate() const;

    void display() const;
};

#endif // APPOINTMENT_H