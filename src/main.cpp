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
        if (field_index == 13) {
            condition = left[i].hourlyRate < right[j].hourlyRate;
        } else if (field_index == 1) { // lastName (字段 1)
            condition = left[i].lastName < right[j].lastName;
        }
        // Add more here...

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

        std::cout << "Unsorted Employee Data:\n";
        printEmployees(employees);

        // perform merge sort
        merge_sort(employees, field_index);

        std::cout << "Sorted Employee Data (Field " << field_index << "):\n";
        printEmployees(employees);

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}