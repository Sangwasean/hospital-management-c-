cmake_minimum_required(VERSION 3.26)
project(hospital_management_system)

set(CMAKE_CXX_STANDARD 17)

add_executable(hospital_management_system main.cpp
        Appointment.cpp
        Appointment.h
        Patient.cpp
        Patient.h
        Doctor.cpp
        Doctor.h
        Hospital.h
        Hospital.cpp
        HospitalManagementSystem.cpp
        HospitalManagementSystem.h)
