//
// Created by Walton Zhang on 2024-12-05.
//

#ifndef ASSIGNMENT4_SRC_EMPLOYEE_UTILS_H_
#define ASSIGNMENT4_SRC_EMPLOYEE_UTILS_H_

#include <vector>
#include <string>

// Employee struct
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

// Function declarations
std::vector<Employee> readEmployeesFromFile(const std::string& filePath);
void saveEmployeeToFile(const std::vector<Employee>& employees);

#endif //ASSIGNMENT4_SRC_EMPLOYEE_UTILS_H_
