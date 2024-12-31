#include <stdio.h>
#include <string.h>
#include "Function.h"
	

void displayMenu(){
		printf("\n*** Student Management System Using C ***\n");
		printf(" \n");
		printf("         =========MENU=========\n");
		printf("         [1] Add A New Student.\n");
		printf("         [2] Show All Students.\n");
		printf("         [3] Edit A Student.\n");
		printf("         [4] Delete A Student.\n");
		printf("         [5] Search A Student.\n");
		printf("         [6] Arrange students\n");
		printf("         [0] Exit Program.\n");
		printf("         ======================\n");
		printf("         Enter Your Choice: ");
} 

void addStudent(){
	printf("\n          --- Add a New Student ---\n");
	FILE *file = fopen("student.bin", "ab");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return;
    }

    int numberStudents;
    printf("Enter the number of students you want to add: ");
    scanf("%d", &numberStudents);
    getchar();

    for (int i = 0; i < numberStudents; i++) {
        Student student;
        int isDuplicate;
        printf("\nStudent %d:\n", i + 1);
        do {
            isDuplicate = 0;
            printf("Enter ID: ");
            scanf("%d", &student.id);
            getchar();

            FILE *file = fopen("student.bin", "rb");
            
            Student temp;
            while (fread(&temp, sizeof(Student), 1, file)) {
                if (temp.id == student.id) {
                    printf("ID already exists. Please enter a different ID.\n");
                    isDuplicate = 1;
                    break;
                }
            }
                fclose(file);
        } while (isDuplicate);
        printf("Enter name: ");
        fgets(student.name, 50, stdin);
        student.name[strcspn(student.name, "\n")] = '\0';
        printf("Enter class: ");
        scanf("%d", &student.classroomId);
        getchar();
        printf("Enter gender: ");
        fgets(student.gender, 10, stdin);
        student.gender[strcspn(student.gender, "\n")] = '\0';
        printf("Enter email: ");
        fgets(student.email, 50, stdin);
        student.email[strcspn(student.email, "\n")] = '\0';
        printf("Enter phone: ");
        fgets(student.phone, 20, stdin);
        student.phone[strcspn(student.phone, "\n")] = '\0';

        fwrite(&student, sizeof(Student), 1, file);
    }
    fclose(file);
    printf("\n%d student added successfully.\n", numberStudents);
    pressToExitOrReturn();
}

void displayStudents() {
	printf("\n          --- Display All Students ---\n");
    FILE *file = fopen("student.bin", "rb");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return;
    }
    
    Student student;
    
    printf("\nStudent list:\n");
    printf("--------------------------------------------------------------------------------------\n");
    printf("ID   | Name                 | Class | Gender  | Email                     | Phone    \n");
    printf("--------------------------------------------------------------------------------------\n");
    
    while (fread(&student, sizeof(Student), 1, file)) {
        printf("%-4d | %-20s | %-5d | %-7s | %-25s | %-10s \n",
               student.id, student.name, student.classroomId, student.gender, student.email, student.phone);
    }
    printf("--------------------------------------------------------------------------------------\n");
    fclose(file);
    pressToExitOrReturn();
}

void updateStudents() {
	printf("\n          --- Update Student Information ---\n");
    FILE *file = fopen("student.bin", "rb+");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return;
    }

    Student student;
    int id; 
	int found = 0; 
    printf("Enter the ID of the student to update: ");
    scanf("%d",&id);
	getchar();
    while (fread(&student, sizeof(Student), 1, file)) {
        if (student.id == id) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with this ID was not found.\n");
        fclose(file);
        return;
    }

    printf("Current information:\n");
    printf("ID: %d\n", student.id);
    printf("Classroom ID: %d\n", student.classroomId);
    printf("Name: %s\n", student.name);
    printf("Gender: %s\n", student.gender);
    printf("Email: %s\n", student.email);
    printf("Phone: %s\n", student.phone);

    printf("Enter new Name: ");
    fgets(student.name, sizeof(student.name), stdin);
    student.name[strcspn(student.name, "\n")] = '\0'; 

    printf("Enter new Gender: ");
    fgets(student.gender, sizeof(student.gender), stdin);
    student.gender[strcspn(student.gender, "\n")] = '\0';

    printf("Enter new Email: ");
    fgets(student.email, sizeof(student.email), stdin);
    student.email[strcspn(student.email, "\n")] = '\0';

    printf("Enter new Phone: ");
    fgets(student.phone, sizeof(student.phone), stdin);
    student.phone[strcspn(student.phone, "\n")] = '\0';

    fseek(file, -sizeof(Student), SEEK_CUR);
    fwrite(&student, sizeof(Student), 1, file);

    printf("Student information updated successfully!\n");
    fclose(file);
    pressToExitOrReturn();
}

void pressToExitOrReturn() {
    char choice;
    printf("\n            [0] Exit      [b] Back to menu\n");
    scanf("%c", &choice);  
    getchar();  

    if (choice == '0') {
        printf("Exiting...\n");
        return 0; 
    } else if (choice == 'b') {
        return;
    } else {
        printf("Invalid choice. Returning to menu...\n");
        return;
    }
}
