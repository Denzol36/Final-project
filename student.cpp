#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;

struct Student {
    char firstName[50];
    char lastName[50];
    int age;
    double* grades;
    int gradeCount;
    double averageGrade;
};

Student students[100];
int studentCount = 0;

void loadFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return;
    
    studentCount = 0;
    while (fscanf(file, "%s %s %d %d", students[studentCount].firstName, students[studentCount].lastName, &students[studentCount].age, &students[studentCount].gradeCount) == 4) {
        students[studentCount].grades = (double*)malloc(students[studentCount].gradeCount * sizeof(double));
        double sum = 0;
        for (int i = 0; i < students[studentCount].gradeCount; i++) {
            fscanf(file, "%lf", &students[studentCount].grades[i]);
            sum += students[studentCount].grades[i];
        }
        students[studentCount].averageGrade = sum / students[studentCount].gradeCount;
        studentCount++;
    }
    fclose(file);
}

void saveToFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "%s %s %d %d", students[i].firstName, students[i].lastName, students[i].age, students[i].gradeCount);
        for (int j = 0; j < students[i].gradeCount; j++) {
            fprintf(file, " %.2lf", students[i].grades[j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void addStudent(const char* filename) {
    if (studentCount >= 100) return;

    printf("Enter first name, last name, and age: ");
    scanf("%s %s %d", students[studentCount].firstName, students[studentCount].lastName, &students[studentCount].age);
    
    printf("How many grades do you want to enter?: ");
    scanf("%d", &students[studentCount].gradeCount);
    
    students[studentCount].grades = (double*)malloc(students[studentCount].gradeCount * sizeof(double));
    double sum = 0;
    for (int i = 0; i < students[studentCount].gradeCount; i++) {
        scanf("%lf", &students[studentCount].grades[i]);
        sum += students[studentCount].grades[i];
    }
    students[studentCount].averageGrade = sum / students[studentCount].gradeCount;
    studentCount++;
    saveToFile(filename);
}

void removeStudent(const char* filename) {
    char lastName[50];
    printf("Enter last name of student to remove: ");
    scanf("%s", lastName);
    
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].lastName, lastName) == 0) {
            printf("Student found: %s %s, Age: %d, Grades: ", students[i].firstName, students[i].lastName, students[i].age);
            for (int j = 0; j < students[i].gradeCount; j++) {
                printf("%.2lf ", students[i].grades[j]);
            }
            printf("| Average Grade: %.2lf\n", students[i].averageGrade);
            char confirmation;
            printf("Are you sure you want to remove this student? (y/n): ");
            scanf(" %c", &confirmation);

            if (confirmation == 'y' || confirmation == 'Y') {
                free(students[i].grades);
                for (int j = i; j < studentCount - 1; j++) {
                    students[j] = students[j + 1];
                }
                studentCount--;
                saveToFile(filename);
                printf("Student removed successfully.\n");
                return;
            } else {
                printf("Student remove canceled.\n");
                return;
            }
        }
    }
    printf("Student not found.\n");
}

void showAllStudents() {
    for (int i = 0; i < studentCount; i++) {
        printf("%s %s, Age: %d, Avg Grade: %.2lf\n", students[i].firstName, students[i].lastName, students[i].age, students[i].averageGrade);
    }
}

void searchStudent() {
    char lastName[50];
    printf("Enter last name to search: ");
    scanf("%s", lastName);
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].lastName, lastName) == 0) {
            printf("Found: %s %s, Age: %d, Avg Grade: %.2lf\n", students[i].firstName, students[i].lastName, students[i].age, students[i].averageGrade);
            return;
        }
    }
    printf("Student not found.\n");
}

void showExcellentStudents() {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].averageGrade >= 10.0) {
            printf("%s %s, Age: %d, Avg Grade: %.2lf\n", students[i].firstName, students[i].lastName, students[i].age, students[i].averageGrade);
        }
    }
}

void sortStudentsByGrade() {
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

int main() {
    char filename[100];
    printf("Enter the filename: ");
    scanf("%s", filename);
    loadFromFile(filename);

    int choice;
    while (true) {
        printf("\n1. Add Student\n2. Remove Student\n3. Show All Students\n4. Search Student\n5. Show Excellent Students\n6. Sort Students By Grade\n7. Exit\nChoice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: 
                addStudent(filename); 
                break;
            case 2: 
                removeStudent(filename); 
                break;
            case 3: 
                showAllStudents(); 
                break;
            case 4: 
                searchStudent(); 
                break;
            case 5:
                showExcellentStudents(); 
                break;
            case 6: 
                sortStudentsByGrade(); 
                break;
            case 7: 
                for (int i = 0; i < studentCount; i++) free(students[i].grades);
                return 0;
            default: 
                printf("Invalid choice!\n");
        }
    }
}