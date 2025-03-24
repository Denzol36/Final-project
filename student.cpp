#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

struct Student {
    char firstName[50];
    char lastName[50];
    int age;
    double grades[10];
    int gradeCount;
    double averageGrade;
};

Student students[100];
int studentCount = 0;

void loadFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        return;
    }
    studentCount = 0;
    while (fscanf(file, "%s %s %d %d", students[studentCount].firstName, students[studentCount].lastName, &students[studentCount].age, &students[studentCount].gradeCount) == 4) {
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
    if (studentCount >= 100) {
        printf("Student list is full!\n");
        return;
    }

    printf("Enter first name, last name, and age: ");
    scanf("%s %s %d", students[studentCount].firstName, students[studentCount].lastName, &students[studentCount].age);

    printf("How many grades do you want to enter? (max 10): ");
    scanf("%d", &students[studentCount].gradeCount);

    if (students[studentCount].gradeCount > 10) {
        students[studentCount].gradeCount = 10;
    }

    double sum = 0;
    printf("Enter %d grades (between 1 and 12):\n", students[studentCount].gradeCount);
    for (int i = 0; i < students[studentCount].gradeCount; i++) {
        while (true) {
            scanf("%lf", &students[studentCount].grades[i]);
            if (students[studentCount].grades[i] >= 1 && students[studentCount].grades[i] <= 12) {
                break;
            }
            printf("Invalid! Grade must be between 1 and 12. Try again: ");
        }
        sum += students[studentCount].grades[i];
    }

    students[studentCount].averageGrade = sum / students[studentCount].gradeCount;
    studentCount++;
    saveToFile(filename);
}

void showAllStudents() {
    if (studentCount == 0) {
        printf("No students to display.\n");
        return;
    }
    for (int i = 0; i < studentCount; i++) {
        printf("First Name: %s, Last Name: %s, Age: %d, Grades: ", students[i].firstName, students[i].lastName, students[i].age);
        for (int j = 0; j < students[i].gradeCount; j++) {
            printf("%.2lf ", students[i].grades[j]);
        }
        printf("| Average Grade: %.2lf\n", students[i].averageGrade);
    }
}

int main() {
    char filename[100];
    cout << "Enter the filename: ";
    cin >> filename;

    loadFromFile(filename);

    int choice;
    while (true) {
        cout << "\n1. Add Student\n2. Show All Students\n3. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            addStudent(filename);
        } else if (choice == 2) {
            showAllStudents();
        } else if (choice == 3) {
            break;
        } else {
            cout << "Invalid choice!\n";
        }
    }
}
