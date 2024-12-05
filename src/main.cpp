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

int main(int argc, char* argv[]) {
    // Receives a file path as an argument
    if (argc != 2) {
        std::cerr << "Usage: mergesort <path/to/employees.txt>\n";
        return 1;
    }

    std::string filePath = argv[1];

    try {
        // Read file and print data
        auto employees = readEmployeesFromFile(filePath);
        std::cout << "Successfully read " << employees.size() << " employees from the file.\n";

        // use loop print all data
        for (const auto& emp : employees) {
            std::cout << emp.id << "\t" << emp.lastName << "\t" << emp.firstName << "\t"
                      << emp.address << "\t" << emp.city << "\t" << emp.province << "\t"
                      << emp.postalCode << "\t" << emp.phone << "\t" << emp.gender << "\t"
                      << emp.age << "\t" << emp.numDependents << "\t" << emp.department << "\t"
                      << emp.unionMember << "\t" << emp.hourlyRate << "\n";
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}