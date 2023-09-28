#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

struct Student {
    int rollNumber;
    char name[100];
    float marks;
};

void addStudent(struct Student *students, int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Maximum number of students reached.\n");
        return;
    }

    struct Student *newStudent = &students[*count];

    printf("Enter the roll number: ");
    scanf("%d", &(newStudent->rollNumber));

    printf("Enter the student name: ");
    scanf(" %[^\n]s", newStudent->name);

    printf("Enter the student marks: ");
    scanf("%f", &(newStudent->marks));

    (*count)++;

    printf("Student added successfully.\n");
}

void displayStudents(struct Student *students, int count) {
    if (count == 0) {
        printf("No students found.\n");
        return;
    }

    printf("Student Details:\n");
    for (int i = 0; i < count; i++) {
        printf("Roll Number: %d\n", students[i].rollNumber);
        printf("Name: %s\n", students[i].name);
        printf("Marks: %.2f\n", students[i].marks);
        printf("----------------------------\n");
    }
}

int searchStudent(struct Student *students, int count, int rollNumber) {
    for (int i = 0; i < count; i++) {
        if (students[i].rollNumber == rollNumber) {
            return i;
        }
    }
    return -1;
}

void deleteStudent(struct Student *students, int *count, int rollNumber) {
    int index = searchStudent(students, *count, rollNumber);
    if (index == -1) {
        printf("Student not found.\n");
        return;
    }

    for (int i = index; i < *count - 1; i++) {
        students[i] = students[i + 1];
    }

    (*count)--;

    printf("Student deleted successfully.\n");
}

void saveStudentsToFile(struct Student *students, int count, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, file);
    fwrite(students, sizeof(struct Student), count, file);

    fclose(file);

    printf("Students saved to file successfully.\n");
}

void loadStudentsFromFile(struct Student *students, int *count, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fread(count, sizeof(int), 1, file);
    fread(students, sizeof(struct Student), *count, file);

    fclose(file);

    printf("Students loaded from file successfully.\n");
}

int main() {
    struct Student students[MAX_STUDENTS];
    int count = 0;
    int choice;

    do {
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Save Students to File\n");
        printf("6. Load Students from File\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(students, &count);
                break;

            case 2:
                displayStudents(students, count);
                break;

            case 3: {
                int rollNumber;
                printf("Enter the roll number to search: ");
                scanf("%d", &rollNumber);
                int index = searchStudent(students, count, rollNumber);
                if (index == -1) {
                    printf("Student not found.\n");
                    printf("Student found:\n");
                    printf("Roll Number: %d\n", students[index].rollNumber);
                    printf("Name: %s\n", students[index].name);
                    printf("Marks: %.2f\n", students[index].marks);
                }
                break;
            }

            case 4: {
                int rollNumber;
                printf("Enter the roll number to delete: ");
                scanf("%d", &rollNumber);
                deleteStudent(students, &count, rollNumber);
                break;
            }

            case 5: {
                char filename[100];
                printf("Enter the filename to save: ");
                scanf("%s", filename);
                saveStudentsToFile(students, count, filename);
                break;
            }

            case 6: {
                char filename[100];
                printf("Enter the filename to load: ");
                scanf("%s", filename);
                loadStudentsFromFile(students, &count, filename);
                break;
            }

            case 7:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

        printf("\n");
    } while (choice != 7);

    return 0;
}
