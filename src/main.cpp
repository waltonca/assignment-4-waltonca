#include <iostream>
#include <string>
#include "employee_utils.h"
#include "merge_sort.h"

int main(int argc, char* argv[]) {
    // Receives a file path as an argument
    if (argc != 3) {
        std::cerr << "Usage: mergesort <path/to/employees.txt> -field=<column_index>\n";
        return 1;
    }

    std::string filePath = argv[1];
    std::string fieldStr = argv[2];

    // Parsing Field Indexes
    int field_index = -1;
    if (fieldStr.find("-field=") == 0) {
        field_index = std::stoi(fieldStr.substr(7));  // Extracting field index
    }

    if (field_index == -1) {
        std::cerr << "Invalid field index.\n";
        return 1;
    }

    try {
        auto employees = readEmployeesFromFile(filePath);
        merge_sort(employees, field_index);  // Perform merge sort
        saveEmployeeToFile(employees);  // Save sorted data to file
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}