#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

#include "Employee.hpp"

class EmployeeDatabase {
    public:
        EmployeeDatabase();
        void employeeInput();
        void addEmployee(Employee e);
        void employeeListData();
        void addEmployeePrompt();
        void deleteEmployeePrompt();
        void sortEmployeePrompt();
        void clearPrompt();
        void helpPrompt();
        void addPrompt();
        void listPrompt();
        void deletePrompt();
        void sortPrompt();

        int toCommandEnum(std::string string);
        int toJobTitleEnum(std::string string);
        int toClearanceEnum(std::string string);

    private:
        int idCur = 0;
        std::vector<int> removed;
        std::string newFile;
        std::fstream outputFile;
};