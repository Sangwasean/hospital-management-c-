#include "HospitalManagementSystem.h"
#include <iostream>
#include <limits>

void displayMenu() {
    std::cout << "\n===== Hospital Management System =====\n";
    std::cout << "1. Create Hospital\n";
    std::cout << "2. Create Doctor\n";
    std::cout << "3. Create Patient\n";
    std::cout << "4. Create Appointment\n";
    std::cout << "5. Display All Hospitals\n";
    std::cout << "6. Display All Doctors\n";
    std::cout << "7. Display All Patients\n";
    std::cout << "8. Display All Appointments\n";
    std::cout << "9. Display Hospital Details\n";
    std::cout << "10. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    HospitalManagementSystem hms;
    int choice;
    std::string id;

    while (true) {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: hms.createHospital(); break;
            case 2: hms.createDoctor(); break;
            case 3: hms.createPatient(); break;
            case 4: hms.createAppointment(); break;
            case 5: hms.displayAllHospitals(); break;
            case 6: hms.displayAllDoctors(); break;
            case 7: hms.displayAllPatients(); break;
            case 8: hms.displayAllAppointments(); break;
            case 9:
                std::cout << "Enter Hospital ID: ";
                std::cin >> id;
                hms.displayHospitalDetails(id);
                break;
            case 10:
                std::cout << "Exiting system...\n";
                return 0;
            default:
                std::cout << "Invalid choice! Please try again.\n";
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return 0;
}