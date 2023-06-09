#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char surname[50];
    int studentId;
    int rating;
} Student;

int compareStudents(const void* a, const void* b) {
    const Student* studentA = (const Student*)a;
    const Student* studentB = (const Student*)b;

    if (studentA->rating < studentB->rating) {
        return 1;
    }
    else if (studentA->rating > studentB->rating) {
        return -1;
    }
    else {
        return 0;
    }
}

void printStudents(Student students[], int count) {
    printf("%-15s%-15s%-15s\n", "Surname", "Student ID", "Rating");

    for (int i = 0; i < count; i++) {
        printf("%-15s%-15d%-15d\n", students[i].surname, students[i].studentId, students[i].rating);
    }
}

int main() {
    int count;

    printf("Enter the number of students: ");
    scanf_s("%d", &count);

    if (count <= 0) {
        printf("Invalid number of students.\n");
        return 0;
    }

    // Clear the input buffer
    while (getchar() != '\n');

    Student* students = (Student*)malloc(count * sizeof(Student));

    if (students == NULL) {
        printf("Memory allocation failed.\n");
        return 0;
    }

    for (int i = 0; i < count; i++) {
        printf("Enter details for student %d:\n", i + 1);

        printf("Surname: ");
        fgets(students[i].surname, sizeof(students[i].surname), stdin);
        students[i].surname[strcspn(students[i].surname, "\n")] = '\0';  // Remove the trailing newline

        printf("Student ID: ");
        scanf_s("%d", &students[i].studentId);

        printf("Rating: ");
        scanf_s("%d", &students[i].rating);

        // Clear the input buffer
        while (getchar() != '\n');
    }

    // Sorting the array of students
    qsort(students, count, sizeof(Student), compareStudents);

    // Printing the sorted array of students
    printf("\nSorted table:\n");
    printStudents(students, count);

    // Writing the sorted array of students to a file
    FILE* file;
    if (fopen_s(&file, "students.txt", "w") != 0) {
        printf("Error opening file for writing.\n");
        free(students);
        return 0;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d %d\n", students[i].surname, students[i].studentId, students[i].rating);
    }

    fclose(file);

    free(students);

    // Read the data from the file
    if (fopen_s(&file, "students.txt", "r") != 0) {
        printf("Error opening file for reading.\n");
        return 0;
    }

    printf("\nData read from the file:\n");

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);

    return 0;
}