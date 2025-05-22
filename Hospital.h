#ifndef HOSPITAL_H
#define HOSPITAL_H
#include <string>
#include <vector>

class Hospital {
private:
    std::string id;
    std::string name;
    std::string location;
    std::vector<std::string> specializations;

public:
    Hospital(std::string id, std::string name, std::string location, std::vector<std::string> specializations);

    std::string getId() const;
    std::string getName() const;
    std::string getLocation() const;
    std::vector<std::string> getSpecializations() const;

    bool hasSpecialization(const std::string& specialization) const;
    void display() const;
};

#endif