#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iomanip> // For std::setw

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

// Merge function to merge two sorted halves
void merge(std::vector<Employee>& arr, int left, int mid, int right, int field_index) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<Employee> leftArr(n1), rightArr(n2);

    // Copy data to temp arrays leftArr[] and rightArr[]
    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArr[j] = arr[mid + 1 + j];
    }

    // Merge the temp arrays back into arr[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        bool condition = false;

        // Sorting logic based on field_index
        switch (field_index) {
            case 13: // Sort by HourlyRate, numerically
                condition = leftArr[i].hourlyRate < rightArr[j].hourlyRate;
                break;
            case 0: // Sort by EmployeeID, alphanumerically
                condition = leftArr[i].id < rightArr[j].id;
                break;
            case 9: // Sort by Age, numerically
                condition = leftArr[i].age < rightArr[j].age;
                break;
            case 11: // Sort by Department alphabetically
                condition = leftArr[i].department < rightArr[j].department;
                break;
            case 1: // Sort by Last Name alphabetically
                condition = leftArr[i].lastName < rightArr[j].lastName;
                break;
            case 2: // Sort by First Name alphabetically
                condition = leftArr[i].firstName < rightArr[j].firstName;
                break;
            case 3: // Sort by Address alphabetically
                condition = leftArr[i].address < rightArr[j].address;
                break;
            case 4: // Sort by City alphabetically
                condition = leftArr[i].city < rightArr[j].city;
                break;
            case 5: // Sort by Province alphabetically
                condition = leftArr[i].province < rightArr[j].province;
                break;
            case 6: // Sort by PostalCode alphabetically
                condition = leftArr[i].postalCode < rightArr[j].postalCode;
                break;
            case 7: // Sort by Phone number alphabetically
                condition = leftArr[i].phone < rightArr[j].phone;
                break;
            case 8: // Sort by Gender alphabetically
                condition = leftArr[i].gender < rightArr[j].gender;
                break;
            case 10: // Sort by Number of Dependents numerically
                condition = leftArr[i].numDependents < rightArr[j].numDependents;
                break;
            case 12: // Sort by Union Member alphabetically
                condition = leftArr[i].unionMember < rightArr[j].unionMember;
                break;
        }

        if (condition) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }

    // Copy the remaining elements of leftArr[] and rightArr[]
    while (i < n1) {
        arr[k++] = leftArr[i++];
    }
    while (j < n2) {
        arr[k++] = rightArr[j++];
    }
}

// Merge sort function to recursively divide and merge
void mergeSort(std::vector<Employee>& arr, int left, int right, int field_index) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Recursively sort the first and second halves
        mergeSort(arr, left, mid, field_index);
        mergeSort(arr, mid + 1, right, field_index);

        // Merge the sorted halves
        merge(arr, left, mid, right, field_index);
    }
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

// Save employee data to file
void saveEmployeeToFile(const std::vector<Employee>& employees) {
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

        outFile.close();
    } else {
        std::cerr << "Unable to open file for writing\n";
    }
}

int main(int argc, char* argv[]) {
    // Receives a file path as an argument
    if (argc != 3) {
        std::cerr << "Usage: mergesort <employees.txt> -field=<fieldno>\n";
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

        // Perform merge sort
        mergeSort(employees, 0, employees.size() - 1, field_index);

        saveEmployeeToFile(employees);

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}