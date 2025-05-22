#include "HospitalManagementSystem.h"
#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;

// Helper function for date validation
bool isValidDate(const string& date) {
    if (date.length() != 8 || date[2] != '/' || date[5] != '/') {
        return false;
    }

    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 2));

    if (day < 1 || day > 31) return false;
    if (month < 1 || month > 12) return false;
    if (year < 0 || year > 2025) return false;

    return true;
}

// CREATE FUNCTIONS
void HospitalManagementSystem::createHospital() {
    string id, name, location;
    vector<string> specializations;
    string spec;
    int specCount;

    cout << "Enter Hospital ID: ";
    cin >> id;
    if (hospitalExists(id)) {
        cout << "Hospital with this ID already exists!\n";
        return;
    }

    cin.ignore();
    cout << "Enter Hospital Name: ";
    getline(cin, name);

    cout << "Enter Location: ";
    getline(cin, location);

    cout << "How many specializations does this hospital have? ";
    cin >> specCount;
    cin.ignore();

    cout << "Enter specializations (one per line):\n";
    for (int i = 0; i < specCount; ++i) {
        cout << "Specialization " << i + 1 << ": ";
        getline(cin, spec);
        specializations.push_back(spec);
    }

    hospitals.emplace_back(id, name, location, specializations);
    cout << "Hospital created successfully!\n";

    std::ostringstream details;
    details << "Name: " << name << ", Location: " << location;
    logger.log("CREATE", "HOSPITAL", id, details.str());
}

void HospitalManagementSystem::createDoctor() {
    string id, name, hospitalId, specialization;

    cout << "Enter Doctor ID: ";
    cin >> id;
    if (doctorExists(id)) {
        cout << "Doctor with this ID already exists!\n";
        return;
    }

    cin.ignore();
    cout << "Enter Doctor Name: ";
    getline(cin, name);

    cout << "Enter Hospital ID: ";
    cin >> hospitalId;
    if (!hospitalExists(hospitalId)) {
        cout << "Hospital with this ID doesn't exist!\n";
        return;
    }

    const Hospital* hospital = findHospital(hospitalId);
    cout << "Available specializations in " << hospital->getName() << ":\n";
    for (const auto& spec : hospital->getSpecializations()) {
        cout << "- " << spec << "\n";
    }

    cin.ignore();
    cout << "Enter Doctor's Specialization: ";
    getline(cin, specialization);

    if (!hospital->hasSpecialization(specialization)) {
        cout << "This specialization is not available at the selected hospital!\n";
        return;
    }

    doctors.emplace_back(id, name, hospitalId, hospital->getName(), specialization);
    cout << "Doctor created successfully!\n";

    std::ostringstream details;
    details << "Name: " << name << ", Hospital: " << hospital->getName()
            << ", Specialization: " << specialization;
    logger.log("CREATE", "DOCTOR", id, details.str());
}

void HospitalManagementSystem::createPatient() {
    string id, name, dob, hospitalId;

    cout << "Enter Patient ID: ";
    cin >> id;
    if (patientExists(id)) {
        cout << "Patient with this ID already exists!\n";
        return;
    }

    cin.ignore();
    cout << "Enter Patient Name: ";
    getline(cin, name);

    cout << "Enter Date of Birth (dd/mm/yy): ";
    getline(cin, dob);
    if (!isValidDate(dob)) {
        cout << "Invalid date format! Please use dd/mm/yy.\n";
        return;
    }

    cout << "Enter Hospital ID: ";
    cin >> hospitalId;
    if (!hospitalExists(hospitalId)) {
        cout << "Hospital with this ID doesn't exist!\n";
        return;
    }

    // Check if patient is already registered at another hospital
    for (const auto& patient : patients) {
        if (patient.getId() == id && patient.getHospitalId() != hospitalId) {
            cout << "Patient cannot be registered at more than one hospital!\n";
            return;
        }
    }

    patients.emplace_back(id, name, dob, hospitalId);
    cout << "Patient created successfully!\n";

    std::ostringstream details;
    details << "Patient: " << name << ", Hospital: " << findHospital(hospitalId)->getName()
            << ", Date: " << dob;
    logger.log("CREATE", "PATIENT", id, details.str());


}

void HospitalManagementSystem::createAppointment() {
    string id, patientName, doctorName, date;

    cout << "Enter Appointment ID: ";
    cin >> id;
    if (appointmentExists(id)) {
        cout << "Appointment with this ID already exists!\n";
        return;
    }

    cin.ignore();
    cout << "Enter Patient Name: ";
    getline(cin, patientName);

    Patient* patient = findPatientByName(patientName);
    if (!patient) {
        cout << "Patient not found!\n";
        return;
    }

    string hospitalId = patient->getHospitalId();
    Hospital* hospital = findHospital(hospitalId);
    if (!hospital) {
        cout << "Patient's hospital not found!\n";
        return;
    }

    cout << "Available Doctors at " << hospital->getName() << ":\n";
    bool hasDoctors = false;
    for (const auto& doctor : doctors) {
        if (doctor.getHospitalId() == hospitalId) {
            cout << "- " << doctor.getName() << " (" << doctor.getSpecialization() << ")\n";
            hasDoctors = true;
        }
    }

    if (!hasDoctors) {
        cout << "No doctors available at this hospital!\n";
        return;
    }

    cout << "Enter Doctor Name: ";
    getline(cin, doctorName);

    Doctor* doctor = findDoctorByName(doctorName);
    if (!doctor || doctor->getHospitalId() != hospitalId) {
        cout << "Doctor not found or doesn't work at patient's hospital!\n";
        return;
    }

    cout << "Enter Date (dd/mm/yy): ";
    getline(cin, date);
    if (!isValidDate(date)) {
        cout << "Invalid date format! Please use dd/mm/yy.\n";
        return;
    }

    appointments.emplace_back(id, patient->getId(), hospitalId, doctor->getId(), date);
    cout << "Appointment created successfully!\n";

    std::ostringstream details;
    details << "Patient: " << patientName << ", Doctor: " << doctorName
            << ", Date: " << date;
    logger.log("CREATE", "APPOINTMENT", id, details.str());
}

// DISPLAY FUNCTIONS
void HospitalManagementSystem::displayAllHospitals() const {
    if (hospitals.empty()) {
        cout << "No hospitals registered.\n";
        return;
    }
    cout << "===== All Hospitals =====\n";
    for (const auto& hospital : hospitals) {
        hospital.display();
        cout << "------------------------\n";
    }
}

void HospitalManagementSystem::displayAllDoctors() const {
    if (doctors.empty()) {
        cout << "No doctors registered.\n";
        return;
    }
    cout << "===== All Doctors =====\n";
    for (const auto& doctor : doctors) {
        doctor.display();
        cout << "------------------------\n";
    }
}

void HospitalManagementSystem::displayAllPatients() const {
    if (patients.empty()) {
        cout << "No patients registered.\n";
        return;
    }
    cout << "===== All Patients =====\n";
    for (const auto& patient : patients) {
        patient.display();
        cout << "------------------------\n";
    }
}

void HospitalManagementSystem::displayAllAppointments() const {
    if (appointments.empty()) {
        cout << "No appointments scheduled.\n";
        return;
    }
    cout << "===== All Appointments =====\n";
    for (const auto& appointment : appointments) {
        cout << "Appointment ID: " << appointment.getId() << "\n";

        // Find and display patient name
        for (const auto& patient : patients) {
            if (patient.getId() == appointment.getPatientId()) {
                cout << "Patient: " << patient.getName() << "\n";
                break;
            }
        }

        // Find and display hospital name
        for (const auto& hospital : hospitals) {
            if (hospital.getId() == appointment.getHospitalId()) {
                cout << "Hospital: " << hospital.getName() << "\n";
                break;
            }
        }

        // Find and display doctor name
        for (const auto& doctor : doctors) {
            if (doctor.getId() == appointment.getDoctorId()) {
                cout << "Doctor: " << doctor.getName() << "\n";
                break;
            }
        }

        cout << "Date: " << appointment.getDate() << "\n";
        cout << "------------------------\n";
    }
}

void HospitalManagementSystem::displayHospitalDetails(const string& id) const {
    const Hospital* hospital = findHospital(id);
    if (!hospital) {
        cout << "Hospital not found!\n";
        return;
    }

    cout << "===== Hospital Details =====\n";
    hospital->display();

    cout << "\n===== Doctors =====\n";
    bool hasDoctors = false;
    for (const auto& doctor : doctors) {
        if (doctor.getHospitalId() == id) {
            doctor.display();
            cout << "------------------------\n";
            hasDoctors = true;
        }
    }
    if (!hasDoctors) {
        cout << "No doctors registered at this hospital.\n";
    }

    cout << "\n===== Patients =====\n";
    bool hasPatients = false;
    for (const auto& patient : patients) {
        if (patient.getHospitalId() == id) {
            patient.display();
            cout << "------------------------\n";
            hasPatients = true;
        }
    }
    if (!hasPatients) {
        cout << "No patients registered at this hospital.\n";
    }

    cout << "\n===== Appointments =====\n";
    bool hasAppointments = false;
    for (const auto& appointment : appointments) {
        if (appointment.getHospitalId() == id) {
            appointment.display();
            cout << "------------------------\n";
            hasAppointments = true;
        }
    }
    if (!hasAppointments) {
        cout << "No appointments scheduled at this hospital.\n";
    }
}

Hospital* HospitalManagementSystem::findHospitalByName(const string& name) {
    for (auto& hospital : hospitals) {
        if (hospital.getName() == name) {
            return &hospital;
        }
    }
    return nullptr;
}

Doctor* HospitalManagementSystem::findDoctorByName(const string& name) {
    for (auto& doctor : doctors) {
        if (doctor.getName() == name) {
            return &doctor;
        }
    }
    return nullptr;
}

Patient* HospitalManagementSystem::findPatientByName(const string& name) {
    for (auto& patient : patients) {
        if (patient.getName() == name) {
            return &patient;
        }
    }
    return nullptr;
}

bool HospitalManagementSystem::hospitalExists(const string &id) const {
    for (const auto& hospital : hospitals) {
        if (hospital.getId() == id) {
            return true;
        }
    }
    return false;
}

bool HospitalManagementSystem::doctorExists(const string &id) const {
    for (const auto& doctor : doctors) {
        if (doctor.getId() == id) {
            return true;
        }
    }
    return false;
}

bool HospitalManagementSystem::patientExists(const string &id) const {
    for (const auto& patient : patients) {
        if (patient.getId() == id) {
            return true;
        }
    }
    return false;
}

bool HospitalManagementSystem::appointmentExists(const string &id) const {
    for (const auto& appointment : appointments) {
        if (appointment.getId() == id) {
            return true;
        }
    }
    return false;
}

Hospital* HospitalManagementSystem::findHospital(const string& id) {
    for (auto& hospital : hospitals) {
        if (hospital.getId() == id) {
            return &hospital;  // Return pointer to found hospital
        }
    }
    return nullptr;  // Return null if not found
}

Doctor* HospitalManagementSystem::findDoctor(const string& id) {
    for (auto& doctor : doctors) {
        if (doctor.getId() == id) {
            return &doctor;  // Return pointer to found doctor
        }
    }
    return nullptr;  // Return null if not found
}

Patient* HospitalManagementSystem::findPatient(const string& id) {
    for (auto& patient : patients) {
        if (patient.getId() == id) {
            return &patient;  // Return pointer to found patient
        }
    }
    return nullptr;  // Return null if not found
}

const Hospital* HospitalManagementSystem::findHospital(const string& id) const {
    for (const auto& hospital : hospitals) {
        if (hospital.getId() == id) {
            return &hospital;  // Return const pointer to found hospital
        }
    }
    return nullptr;  // Return null if not found
}
