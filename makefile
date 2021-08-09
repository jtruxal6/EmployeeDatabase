all: Driver Clean

Driver: Driver.cpp Employee.o EmployeeDatabase.o Enums.o
	c++ Driver.cpp Employee.o EmployeeDatabase.o Enums.o

Employee.o: Employee.cpp Employee.hpp
	c++ -c Employee.cpp

EmployeeDatabase.o: EmployeeDatabase.cpp EmployeeDatabase.hpp
	c++ -c  EmployeeDatabase.cpp

Enums.o: Enums.cpp Enums.hpp
	c++ -c Enums.cpp
Clean:
	rm *.o