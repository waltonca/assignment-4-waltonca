//
// Created by Walton Zhang on 2024-12-05.
//

#include "merge_sort.h"
#include <vector>
#include <algorithm>

void merge_sort(std::vector<Employee>& employees, int field_index) {
    if (employees.size() <= 1) return;

    // Divide the Vector into Halves:
    std::vector<Employee> left(employees.begin(), employees.begin() + employees.size() / 2);
    std::vector<Employee> right(employees.begin() + employees.size() / 2, employees.end());

    // Recursive Calls
    merge_sort(left, field_index);
    merge_sort(right, field_index);

    // Merge the Sorted Halves
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

        // Merging the Elements
        if (condition) {
            employees[k++] = left[i++];
        } else {
            employees[k++] = right[j++];
        }
    }

    // Copy Remaining Elements (if any)
    while (i < left.size()) employees[k++] = left[i++];
    while (j < right.size()) employees[k++] = right[j++];
}
