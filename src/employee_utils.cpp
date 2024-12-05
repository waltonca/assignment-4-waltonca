//
// Created by Walton Zhang on 2024-12-05.
//

#include "employee_utils.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

// Reads a file and returns a list of employee information
std::vector<Employee> readEmployeesFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    std::vector<Employee> employees;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        Employee emp;

        std::getline(lineStream, emp.id, '\t');
        std::getline(lineStream, emp.lastName, '\t');
        std::getline(lineStream, emp.firstName, '\t');
        std::getline(lineStream, emp.address, '\t');
        std::getline(lineStream, emp.city, '\t');
        std::getline(lineStream, emp.province, '\t');
        std::getline(lineStream, emp.postalCode, '\t');
        std::getline(lineStream, emp.phone, '\t');
        lineStream >> emp.gender;
        lineStream.ignore(1, '\t');
        lineStream >> emp.age;
        lineStream.ignore(1, '\t');
        lineStream >> emp.numDependents;
        lineStream.ignore(1, '\t');
        std::getline(lineStream, emp.department, '\t');
        lineStream >> emp.unionMember;
        lineStream.ignore(1, '\t');
        lineStream >> emp.hourlyRate;

        employees.push_back(emp);
    }

    return employees;
}

// Save employees to file
void saveEmployeeToFile(const std::vector<Employee>& employees) {
    std::ofstream outFile("../output/employees.txt", std::ios::trunc);
    if (outFile.is_open()) {
        for (const auto& emp : employees) {
            outFile << std::left << std::setw(10) << emp.id
                    << std::setw(15) << emp.lastName
                    << std::setw(15) << emp.firstName
                    << std::setw(30) << emp.address
                    << std::setw(20) << emp.city
                    << std::setw(5) << emp.province
                    << std::setw(10) << emp.postalCode
                    << std::setw(15) << emp.phone
                    << std::setw(5) << emp.gender
                    << std::setw(5) << emp.age
                    << std::setw(5) << emp.numDependents
                    << std::setw(10) << emp.department
                    << std::setw(5) << emp.unionMember
                    << std::setw(5) << emp.hourlyRate
                    << "\n";
        }
        outFile.close();
    } else {
        std::cerr << "Unable to open file for writing\n";
    }
}