#include <string>

enum JobTitle{
    SOFTWARE_ENGINEER, ELECTRICAL_ENGINEER, IT_SPECIALIST, SECRETARY
};

enum Clearance {
    NONE, CONFIDENTIAL, SECRET, TOP_SECRET
};

enum Command {
    HELP, DELETE, LIST, SORT, CLEAR, ADD,
};

struct EnumsRefrences {
    static const std::string jobTitles[4];

    static const std::string commmandNames[6];

    static const std::string clearanceNames[4];
};