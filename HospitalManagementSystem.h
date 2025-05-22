#ifndef HOSPITAL_MANAGEMENT_SYSTEM_H
#define HOSPITAL_MANAGEMENT_SYSTEM_H

#include "Hospital.h"
#include "Doctor.h"
#include "Patient.h"
#include "Appointment.h"
#include "Logger.h"
#include <vector>

class HospitalManagementSystem {
private:
    std::vector<Hospital> hospitals;
    std::vector<Doctor> doctors;
    std::vector<Patient> patients;
    std::vector<Appointment> appointments;
    Logger logger;

    bool hospitalExists(const std::string& id) const;
    bool doctorExists(const std::string& id) const;
    bool patientExists(const std::string& id) const;
    bool appointmentExists(const std::string& id) const;

    Hospital* findHospital(const std::string& id);
    const Hospital* findHospital(const std::string& id) const;
    Doctor* findDoctor(const std::string& id);
    Patient* findPatient(const std::string& id);

public:
    void createHospital();
    void createDoctor();
    void createPatient();
    void createAppointment();

    void displayAllHospitals() const;
    void displayAllDoctors() const;
    void displayAllPatients() const;
    void displayAllAppointments() const;
    void displayHospitalDetails(const std::string& id) const;

    Hospital* findHospitalByName(const std::string& name);
    Doctor* findDoctorByName(const std::string& name);
    Patient* findPatientByName(const std::string& name);
    HospitalManagementSystem() : logger("hospital_log.csv") {}
};

#endif