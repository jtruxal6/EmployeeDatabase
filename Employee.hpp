#include <iostream>
#include <string>
#include <cstring>

#include "Enums.hpp"

class Employee {
    public:
        Employee();
        friend std::ostream& operator<<(std::ostream& os, Employee e);
        friend bool operator==(const Employee& a, const Employee& b);
        friend bool operator<(const Employee& a, const Employee& b);
        friend bool operator>(const Employee& a, const Employee& b);
        //getters//
        bool getDeleted();
        int getEmployeeId();
        int getSalary();
        char* getFirstName();
        char* getLastName();
        JobTitle getJobTitle();
        Clearance getClearance();

        //setters//
        void setDeleted(bool deleted);
        void setEmployeeId(int employeeId);
        void setSalary(int salary);
        void setFirstName(char firstName[255]);
        void setLastName(char lastName[255]);
        void setJobTitle(JobTitle jobTitle);
        void setClearance(Clearance clearance);

    private:
        int employeeId;
        int salary;
        int deleted;
        char firstName[255];
        char lastName[255];
        JobTitle jobTitle;
        Clearance clearance;
};