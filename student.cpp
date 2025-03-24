#include <iostream>
#include <cstring>
#include <cstdio>
#include "function.h"

using namespace std;

struct Student {
    char firstName[50];
    char lastName[50];
    int age;
    double averageGrade;
};

Student students[100];
int studentCount = 0;

void loadFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file){
        return;
    }
    studentCount = 0;
    while (fscanf(file, "%s %s %d %lf", students[studentCount].firstName, students[studentCount].lastName, &students[studentCount].age, &students[studentCount].averageGrade) == 4) {
        studentCount++;
    }
    fclose(file);
}

void saveToFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "%s %s %d %.2lf\n", students[i].firstName, students[i].lastName, students[i].age, students[i].averageGrade);
    }
    fclose(file);
}

void addStudent(const char* filename) {
    if (studentCount >= 100) {
        printf("Student list is full!\n");
        return;
    }
    printf("Enter first name, last name, age, and average grade: ");
    scanf("%s %s %d %lf", students[studentCount].firstName, students[studentCount].lastName, &students[studentCount].age, &students[studentCount].averageGrade);
    studentCount++;
    saveToFile(filename);
}

void removeStudent(const char* filename) {
    char lastName[50];
    printf("Enter last name of student to remove: ");
    scanf("%s", lastName);
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].lastName, lastName) == 0) {
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            saveToFile(filename);
            return;
        }
    }
    printf("Student not found.\n");
}

void updateStudent(const char* filename) {
    char lastName[50];
    printf("Enter last name of student to update: ");
    scanf("%s", lastName);
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].lastName, lastName) == 0) {
            printf("Enter new first name, last name, age, and average grade: ");
            scanf("%s %s %d %lf", students[i].firstName, students[i].lastName, &students[i].age, &students[i].averageGrade);
            saveToFile(filename);
            return;
        }
    }
    printf("Student not found.\n");
}

void showAllStudent() {
    if (studentCount == 0) {
        printf("No students to display.\n");
        return;
    }
    for (int i = 0; i < studentCount; i++) {
        printf("First Name: %s, Last Name: %s, Age: %d, Average Grade: %.2lf\n",students[i].firstName, students[i].lastName, students[i].age, students[i].averageGrade);
    }
}

void searchStudent() {
    char lastName[50];
    printf("Enter last name of student to search for: ");
    scanf("%s", lastName);
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].lastName, lastName) == 0) {
            printf("Student found: First Name: %s, Last Name: %s, Age: %d, Average Grade: %.2lf\n",students[i].firstName, students[i].lastName, students[i].age, students[i].averageGrade);
            return;
        }
    }
    printf("Student not found.\n");
}

void sortStudent() {
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = i + 1; j < studentCount; j++) {
            if (students[i].averageGrade < students[j].averageGrade) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    printf("Students sorted by average grade.\n");
}

void showExcellentStudents() {
    bool found = false;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].averageGrade >= 9.0) {
            printf("Excellent Student - First Name: %s, Last Name: %s, Age: %d, Average Grade: %.2lf\n",students[i].firstName, students[i].lastName, students[i].age, students[i].averageGrade);
            found = true;
        }
    }
    if (!found) {
        printf("No excellent students found.\n");
    }
}

int main() {
    char filename[100];
    cout << "Enter the filename: ";
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;
    
    loadFromFile(filename);
    int choice;
    void (*functions[])(const char*) = {addStudent, removeStudent, updateStudent};
    void (*noArgFunctions[])() = {showAllStudent, searchStudent, sortStudent, showExcellentStudents};
    
    while(1){
        cout << "\n1. Add Student\n2. Remove Student\n3. Update Student\n4. Show All Students\n";
        cout << "5. Search Student\n6. Sort Students\n7. Show Excellent Students\n8. Exit\nChoice: ";
        cin >> choice;
        
        if (choice >= 1 && choice <= 3) {
            functions[choice - 1](filename);
        } else if (choice >= 4 && choice <= 7) {
            noArgFunctions[choice - 4]();
        } else if (choice == 8) {
            break;
        } 
        else {
            cout << "Invalid choice!\n";
        }
    };
}