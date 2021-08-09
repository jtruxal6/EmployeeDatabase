#include "EmployeeDatabase.hpp"
EmployeeDatabase::EmployeeDatabase() {
    clearPrompt();
    newFile = "binaryFile";
    outputFile.open(newFile, std::ios::in | std::ios::out | std::ios::binary);
    if (!outputFile.is_open()) {
        std::fstream create(newFile, std::ios::out | std::ios::binary);
        create.close();
    }
    outputFile.open(newFile, std::ios::in | std::ios::out | std::ios::binary);
    outputFile.close();
}

void EmployeeDatabase::employeeInput() {
    std::string input;

    std::cout << "Employee Database:";
    std::cin >> input;

    int inputEnum = toCommandEnum(input);

    switch (inputEnum) {
        case HELP: {
            clearPrompt();
            std::cout << "Unrecognized Command: " << input << std::endl;
            helpPrompt();
            break; 
        }
        case DELETE: {
            deletePrompt();
            break; 
        }
        case LIST: {
            listPrompt();
            break; 
        }
        case SORT: {
            sortPrompt();
            break;
        }
        case CLEAR: {
            clearPrompt();
            break;
        }
        case ADD: {
            addPrompt();
            break; 
        }
        default: {
            //impossible to call, but just in case
            clearPrompt();
            std::cout << "Unrecognized Command: " << input << std::endl;
            helpPrompt();
            break;
        }
    }
}

void EmployeeDatabase::addEmployee(Employee e) {
    outputFile.open(newFile, std::ios::in | std::ios::out | std::ios::binary);
    this->outputFile.seekp(0, std::ios::end);
    
    if (!(removed.empty())) {
        std::cout << "removed is not empty" << std::endl;
        
        //gets old employee to get old id
        this->outputFile.seekp(removed[removed.size() - 1], std::ios::beg);
        this->idCur--;
        Employee oldE;
        this->outputFile.read((char*)&oldE, sizeof(Employee));
        e.setEmployeeId(oldE.getEmployeeId());

        //writes new employee over old
        this->outputFile.seekp(removed[removed.size() - 1], std::ios::beg);
        this->outputFile.write((char*)&e, sizeof(Employee));
        removed.pop_back();
    } else {
        this->outputFile.write((char*)&e, sizeof(Employee));
    }

    outputFile.close();

}

int EmployeeDatabase::toCommandEnum(std::string string) {
    transform(string.begin(), string.end(), string.begin(), ::toupper);
    int length = 0;
    for (std::string s: EnumsRefrences::commmandNames) {
        length++;
    }
    
    for (int i = 0; i < length; i++) {
        if (string == EnumsRefrences::commmandNames[i]) {
            return i;
        }
    }
    return 0;
}

int EmployeeDatabase::toJobTitleEnum(std::string string) {
    transform(string.begin(), string.end(), string.begin(), ::toupper);
    int length = 0;
    for (std::string s: EnumsRefrences::jobTitles) {
        length++;
    }
    
    for (int i = 0; i < length; i++) {
        if (string == EnumsRefrences::jobTitles[i]) {
            return i;
        }
    }
    return 0;
}

int EmployeeDatabase::toClearanceEnum(std::string string) {
    transform(string.begin(), string.end(), string.begin(), ::toupper);
    int length = 0;
    for (std::string s: EnumsRefrences::clearanceNames) {
        length++;
    }
    
    for (int i = 0; i < length; i++) {
        if (string == EnumsRefrences::clearanceNames[i]) {
            return i;
        }
    }
    return 0;
}

void EmployeeDatabase::helpPrompt() {
    std::cout << "You have the following commands available:" << std::endl;
    for (std::string s: EnumsRefrences::commmandNames) {
        std::cout << "--" << s << std::endl;
    }
}

void EmployeeDatabase::clearPrompt() {
    printf("\033c");
}

void EmployeeDatabase::addPrompt() {
    clearPrompt();

    std::string employeeId;
    std::string salary;
    char firstName[255];
    char lastName[255];
    std::string jobTitle;
    std::string clearance;

    std::cout << "Please fill out the following employee fields" << std::endl;
    std::cout << "First Name: ";
    std::cin >> firstName;
    clearPrompt();
    std::cout << "Last Name: ";
    std::cin >> lastName;
    clearPrompt();
    std::cout << "Salary: ";
    std::cin >> salary;
    clearPrompt();
    std::cout << "JobTitle: ";
    std::string temp;
    std::getline(std::cin, temp);
    std::getline(std::cin, jobTitle);
    clearPrompt();
    std::cout << "Clearance: ";
    std::getline(std::cin, clearance);
    clearPrompt();

    int jobTitleEnum = toJobTitleEnum(jobTitle);
    int clearanceEnum = toClearanceEnum(clearance);
    int salaryInt = 0;
    int employeeIdInt = 0;
    try {
        salaryInt = stoi(salary);
        this->idCur++;

        Employee e;
        e.setClearance((Clearance)clearanceEnum);
        e.setJobTitle((JobTitle)jobTitleEnum);
        e.setSalary(salaryInt);
        e.setEmployeeId(this->idCur);
        e.setFirstName(firstName);
        e.setLastName(lastName);

        this->addEmployee(e);

        std::cout << "Your new employee is: " << std::endl;
        std::cout << e << std::endl;

    } catch (std::invalid_argument) {
        std::cout << "Salary and Employee must be an integer, try again" << std::endl;
    }
}

void EmployeeDatabase::listPrompt() {
    outputFile.open(newFile, std::ios::in | std::ios::out | std::ios::binary);

    clearPrompt();

    Employee rtr;
    this->outputFile.seekg(0, std::ios::beg);
    while(this->outputFile.read((char*)&rtr, sizeof(Employee))) {
        if (!rtr.getDeleted()) {
            std::cout << rtr << std::endl;
        }
    }
    outputFile.close();
}

void EmployeeDatabase::deletePrompt() {
    this->outputFile.open(newFile, std::ios::in | std::ios::out | std::ios::binary);

    clearPrompt();
    std::string firstName;
    std::string lastName;  
    std::string employeeId;

    std::cout << "Please type in the name of the employee you are deleting: " << std::endl;
    std::cout << "First Name: ";
    std::cin >> firstName;

    transform(firstName.begin(), firstName.end(), firstName.begin(), ::toupper);
    if (firstName == "ALL") {
        std::string userInput;
        std::cout << "Are you sure you want to delete the entire database?" << std::endl;
        std::cout << "[y/n]: ";
        std::cin >> userInput;
        if (userInput == "y") {
            std::cout << "DElETING..." << std::endl;
            std::fstream create(newFile, std::ios::out | std::ios::binary);
            outputFile.close();
        } else {
            std::cout << "cancelling" << std::endl;
        }
        return;
    }

    std::cout << "Last Name: ";
    std::cin >> lastName;
    std::cout << "Employee Id: ";
    std::cin >> employeeId;

    transform(lastName.begin(), lastName.end(), lastName.begin(), ::toupper);

    Employee rtr;
    bool caught = false;
    this->outputFile.seekg(0, std::ios::beg);
    while(this->outputFile.read((char*)&rtr, sizeof(Employee))) {
        std::string firstNameE = rtr.getFirstName();
        std::string lastNameE = rtr.getLastName();

        transform(firstNameE.begin(), firstNameE.end(), firstNameE.begin(), ::toupper);
        transform(lastNameE.begin(), lastNameE.end(), lastNameE.begin(), ::toupper);

        if (firstName == firstNameE && lastName == lastNameE && rtr.getEmployeeId() == stoi(employeeId)) {
            //delete
            caught = true;
            this->removed.push_back(this->outputFile.tellg() - (long)sizeof(Employee));
            rtr.setDeleted(true);

            this->outputFile.seekp(this->outputFile.tellg() - (long)sizeof(Employee));
            this->outputFile.write((char*)&rtr, sizeof(Employee));
            break;
        }
    }

    if (!caught) {
        std::cout << "There is no one in the Database with the inputed credentials" << std::endl;
    }

    this->outputFile.close();
}

void EmployeeDatabase::sortPrompt() {
    std::cout << "wip" << std::endl;
}
