#include "Hospital.h"
#include <iostream>
#include <algorithm>

Hospital::Hospital(std::string id, std::string name, std::string location, std::vector<std::string> specializations)
        : id(id), name(name), location(location), specializations(specializations) {}

std::string Hospital::getId() const { return id; }
std::string Hospital::getName() const { return name; }
std::string Hospital::getLocation() const { return location; }
std::vector<std::string> Hospital::getSpecializations() const { return specializations; }

bool Hospital::hasSpecialization(const std::string& specialization) const {
    return std::find(specializations.begin(), specializations.end(), specialization) != specializations.end();
}

void Hospital::display() const {
    std::cout << "Hospital ID: " << id << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Location: " << location << "\n";
    std::cout << "Specializations: ";
    for (const auto& spec : specializations) {
        std::cout << spec << ", ";
    }
    std::cout << "\n";
}