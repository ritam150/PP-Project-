#include <stdio.h>
#include <stdlib.h>

// Define the base class Employee
typedef struct {
    char name[50];
    int empId;
    double salary;

    void (*calculateSalary)(void*); // Function pointer for polymorphism
} Employee;

// Define the derived class RegularEmployee
typedef struct {
    Employee base;
    double hourlyRate;
    int hoursWorked;
} RegularEmployee;

// Define the derived class Manager
typedef struct {
    Employee base;
    double monthlyBonus;
} Manager;

// Function to calculate salary for regular employees
void calculateRegularEmployeeSalary(void* emp) {
    RegularEmployee* regularEmp = (RegularEmployee*)emp;
    regularEmp->base.salary = regularEmp->hourlyRate * regularEmp->hoursWorked;
}

// Function to calculate salary for managers
void calculateManagerSalary(void* emp) {
    Manager* manager = (Manager*)emp;
    manager->base.salary = manager->monthlyBonus;
}

int main() {
    int choice;
    int numEmployees = 0;
    Employee* employees[100]; // Assuming a maximum of 100 employees

    do {
        printf("Employee Payroll System\n");
        printf("1. Add Regular Employee\n");
        printf("2. Add Manager\n");
        printf("3. Calculate Salary\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Create a new regular employee
                employees[numEmployees] = (Employee*)malloc(sizeof(RegularEmployee));
                printf("Enter employee name: ");
                scanf("%s", employees[numEmployees]->name);
                printf("Enter employee ID: ");
                scanf("%d", &employees[numEmployees]->empId);
                printf("Enter hourly rate: ");
                scanf("%lf", &((RegularEmployee*)employees[numEmployees])->hourlyRate);
                printf("Enter hours worked: ");
                scanf("%d", &((RegularEmployee*)employees[numEmployees])->hoursWorked);
                employees[numEmployees]->calculateSalary = calculateRegularEmployeeSalary;
                numEmployees++;
                break;

            case 2:
                // Create a new manager
                employees[numEmployees] = (Employee*)malloc(sizeof(Manager));
                printf("Enter manager name: ");
                scanf("%s", employees[numEmployees]->name);
                printf("Enter manager ID: ");
                scanf("%d", &employees[numEmployees]->empId);
                printf("Enter monthly bonus: ");
                scanf("%lf", &((Manager*)employees[numEmployees])->monthlyBonus);
                employees[numEmployees]->calculateSalary = calculateManagerSalary;
                numEmployees++;
                break;

            case 3:
                // Calculate and display salaries for all employees
                for (int i = 0; i < numEmployees; i++) {
                    employees[i]->calculateSalary(employees[i]);
                    printf("Employee Name: %s, ID: %d, Salary: $%.2lf\n", employees[i]->name, employees[i]->empId, employees[i]->salary);
                }
                break;

            case 4:
                // Free allocated memory and exit
                for (int i = 0; i < numEmployees; i++) {
                    free(employees[i]);
                }
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (1);

    return 0;
}
