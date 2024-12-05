#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>

struct Employee {
  std::string id;
  std::string lastName;
  std::string firstName;
  std::string address;
  std::string city;
  std::string province;
  std::string postalCode;
  std::string phone;
  char gender;
  int age;
  int numDependents;
  std::string department;
  char unionMember;
  double hourlyRate;
};

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

// mergesort function
template <typename T>
void merge_sort(std::vector<T>& vec, int field_index) {
    if (vec.size() <= 1) return;

    std::vector<T> left(vec.begin(), vec.begin() + vec.size() / 2);
    std::vector<T> right(vec.begin() + vec.size() / 2, vec.end());

    merge_sort(left, field_index);
    merge_sort(right, field_index);

    size_t i = 0, j = 0, k = 0;
    while (i < left.size() && j < right.size()) {
        bool condition = false;
        // According to the field index, decide the basis for sorting
        if (field_index == 13) { // Sort by HourlyRate, numerically
            condition = left[i].hourlyRate < right[j].hourlyRate;
        } else if (field_index == 0) { // Sort by EmployeeID, alphanumerically
            condition = left[i].id < right[j].id;
        } else if (field_index == 9) { // Sort by Age, numerically
            condition = left[i].age < right[j].age;
        } else if (field_index == 11) { // Sort by Department alphabetically
            condition = left[i].department < right[j].department;
        } else if (field_index == 1) { // Sort by Last Name alphabetically
            condition = left[i].lastName < right[j].lastName;
        } else if (field_index == 2) { // Sort by First Name alphabetically
            condition = left[i].firstName < right[j].firstName;
        } else if (field_index == 3) { // Sort by Address alphabetically
            condition = left[i].address < right[j].address;
        } else if (field_index == 4) { // Sort by City alphabetically
            condition = left[i].city < right[j].city;
        } else if (field_index == 5) { // Sort by Province alphabetically
            condition = left[i].province < right[j].province;
        } else if (field_index == 6) { // Sort by PostalCode alphabetically
            condition = left[i].postalCode < right[j].postalCode;
        } else if (field_index == 7) { // Sort by Phone number alphabetically
            condition = left[i].phone < right[j].phone;
        } else if (field_index == 8) { // Sort by Gender alphabetically
            condition = left[i].gender < right[j].gender;
        } else if (field_index == 10) { // Sort by Number of Dependents numerically
            condition = left[i].numDependents < right[j].numDependents;
        } else if (field_index == 12) { // Sort by Union Member alphabetically
            condition = left[i].unionMember < right[j].unionMember;
        }

        if (condition) {
            vec[k++] = left[i++];
        } else {
            vec[k++] = right[j++];
        }
    }

    while (i < left.size()) vec[k++] = left[i++];
    while (j < right.size()) vec[k++] = right[j++];
}

// Print employees
void printEmployees(const std::vector<Employee>& employees) {
    for (const auto& emp : employees) {
        std::cout << std::left << std::setw(10) << emp.id
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
}

// save file
void saveEmployeeToFile(const std::vector<Employee>& employees) {
    // Open the output file output/employees.txt (if the file does not exist it will be created)
    std::ofstream outFile("../output/employees.txt", std::ios::trunc); // Empty files on each run

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

        // Close the file after successful file write
        outFile.close();
    } else {
        std::cerr << "Unable to open file for writing\n";
    }
}

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
        field_index = std::stoi(fieldStr.substr(7)); // Extracting field indexes
    }

    if (field_index == -1) {
        std::cerr << "Invalid field index.\n";
        return 1;
    }

    try {
        auto employees = readEmployeesFromFile(filePath);

        //std::cout << "Unsorted Employee Data:\n";
        //printEmployees(employees);

        // perform merge sort
        merge_sort(employees, field_index);

        //std::cout << "Sorted Employee Data (Field " << field_index << "):\n";
        //printEmployees(employees);
        saveEmployeeToFile(employees);

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}