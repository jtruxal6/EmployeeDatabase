#include "Employee.hpp"

Employee::Employee() {
    this->deleted = false;
}

std::ostream& operator<<(std::ostream& os, Employee e) {
    os << "Employee: " << e.firstName << " " << e.lastName << std::endl;
    os << "--EmployeeId: " << e.employeeId << std::endl;
    os << "--JobTitle: " << EnumsRefrences::jobTitles[e.jobTitle] << std::endl;
    os << "--Clearance: " << EnumsRefrences::clearanceNames[e.clearance] << std::endl;
    os << "--Salary: " << e.salary << std::endl;
    return os;
}

bool operator==(const Employee& a, const Employee& b) {
    return a.employeeId == b.employeeId
        && a.salary == b.salary
        && std::string(a.firstName) == std::string(b.firstName)
        && std::string(a.lastName) == std::string(b.lastName)
        && a.jobTitle == b.jobTitle
        && a.clearance == b.clearance;
}

bool operator<(const Employee& a, const Employee& b) {
    return a.salary < b.salary;
}

bool operator>(const Employee& a, const Employee& b) {
    return a.salary > b.salary;
}

//getters

bool Employee::getDeleted() {
    return this->deleted;
}

int Employee::getEmployeeId() {
    return this->employeeId;
}

int Employee::getSalary() {
    return this->salary;
}

char* Employee::getFirstName() {
    return this->firstName;
}

char* Employee::getLastName() {
    return this->lastName;
}

JobTitle Employee::getJobTitle() {
    return this->jobTitle;
}

Clearance Employee::getClearance() {
    return this->clearance;
}

//setters/

void Employee::setDeleted(bool deleted) {
    this->deleted = deleted;
}

void Employee::setEmployeeId(int employeeId) {
    this->employeeId = employeeId;
}

void Employee::setSalary(int salary) {
    this->salary = salary;
}

void Employee::setFirstName(char firstName[255]) {
    strcpy(this->firstName, firstName);
}

void Employee::setLastName(char lastName[255]) {
    strcpy(this->lastName, lastName);
}

void Employee::setJobTitle(JobTitle jobTitle) {
    this->jobTitle = jobTitle;
}

void Employee::setClearance(Clearance clearance) {
    this->clearance = clearance;
}