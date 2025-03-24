#include <iostream>
#include <cstring>
#include "function.h"

using namespace std;

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
            return 0;
        } else {
            cout << "Invalid choice!\n";
        }
    };
}