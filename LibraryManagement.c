#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct {
    char title[100];
    char author[100];
    char subject[100];
    char major[50];       
    int available;
    int totalCopies;
    int timesBorrowed;    // تعداد دفعات امانت گرفته شده
    char borrowedBy[10][50];  // نام کاربری امانت‌گیرندگان
} Book;



typedef struct {
    char username[50];  
    char bookTitle[100];  
    int accepted;  // وضعیت پذیرش (0: در انتظار، 1: قبول، -1: رد شده)
} Request;



typedef struct {
    char username[50];    
    char password[50];     
    char major[50];       
    Book borrowedBooks[10];// کتاب‌های امانت گرفته شده توسط دانشجو
    int borrowedCount;     // تعداد کتاب‌های امانت گرفته شده
} Student;



typedef struct {
    char username[50];     
    char password[50];     
} Librarian;

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int login(char* username, char* password, Librarian* librarians, int librarianCount, Student* students, int studentCount, int* userIndex, int* isAdmin) {
    for (int i = 0; i < librarianCount; i++) {

        if (strcmp(librarians[i].username, username) == 0 && strcmp(librarians[i].password, password) == 0) {
            printf("Welcome, Librarian %s!\n", username);
            *userIndex = i;
            *isAdmin = 1;
            return 1; // موفقیت‌آمیز برای کتابدار
        }
    }
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].username, username) == 0 && strcmp(students[i].password, password) == 0) {
            printf("Welcome, Student %s!\n", username);
            *userIndex = i;
            *isAdmin = 0;
            return 2; // موفقیت‌آمیز برای دانشجو
        }
    }
    printf("Invalid username or password.\n");
    return 0; // ناموفق
}



void addStudent(Student* students, int* studentCount, char* username, char* password, char* major) {

    strcpy(students[*studentCount].username, username);
    strcpy(students[*studentCount].password, password);
    strcpy(students[*studentCount].major, major);
    students[*studentCount].borrowedCount = 0;
    (*studentCount)++;
    printf("Student %s added successfully.\n", username);
}



void addLibrarian(Librarian* librarians, int* librarianCount, char* username, char* password) {

    strcpy(librarians[*librarianCount].username, username);
    strcpy(librarians[*librarianCount].password, password);
    (*librarianCount)++;
    printf("Librarian %s added successfully.\n", username);
}



void addNewBook(Book* books, int* bookCount) {

    char title[100], author[100], subject[100], major[50];
    int totalCopies;
    printf("Enter book title: ");
    scanf(" %[^\n]", title);
    printf("Enter book author: ");
    scanf(" %[^\n]", author);
    printf("Enter book subject: ");
    scanf(" %[^\n]", subject);
    printf("Enter book major: ");
    scanf(" %[^\n]", major);
    printf("Enter total number of copies: ");
    scanf("%d", &totalCopies);

    strcpy(books[*bookCount].title, title);
    strcpy(books[*bookCount].author, author);
    strcpy(books[*bookCount].subject, subject);
    strcpy(books[*bookCount].major, major);
    books[*bookCount].totalCopies = totalCopies;
    books[*bookCount].available = totalCopies;
    books[*bookCount].timesBorrowed = 0;
    (*bookCount)++;
    printf("Book \"%s\" added successfully.\n", title);
}



void deleteBook(Book* books, int* bookCount, char* title) {
    int found = 0;
    for (int i = 0; i < *bookCount; i++) {
        if (strcmp(books[i].title, title) == 0) {
            found = 1;
            for (int j = i; j < *bookCount - 1; j++) {
                books[j] = books[j + 1];
            }
            (*bookCount)--;
            printf("Book \"%s\" deleted successfully.\n", title);
            break;
        }
    }
    if (!found) {
        printf("Book \"%s\" not found.\n", title);
    }
}



void saveLibrarians(Librarian* librarians, int librarianCount) {
    FILE *file = fopen("librarians.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(file, "%d\n", librarianCount);
    for (int i = 0; i < librarianCount; i++) {
        fprintf(file, "%s %s\n", librarians[i].username, librarians[i].password);
    }
    fclose(file);
}



void saveStudents(Student* students, int studentCount) {
    FILE *file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(file, "%d\n", studentCount);
    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "%s %s %s %d\n", students[i].username, students[i].password, students[i].major, students[i].borrowedCount);
        for (int j = 0; j < students[i].borrowedCount; j++) {
            fprintf(file, "%s %s %s %d %d %d\n", students[i].borrowedBooks[j].title, students[i].borrowedBooks[j].author, students[i].borrowedBooks[j].subject, students[i].borrowedBooks[j].available, students[i].borrowedBooks[j].totalCopies, students[i].borrowedBooks[j].timesBorrowed);
        }
    }
    fclose(file);
}



void saveBooks(Book* books, int bookCount) {
    FILE *file = fopen("books.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(file, "%d\n", bookCount);
    for (int i = 0; i < bookCount; i++) {
        fprintf(file, "%s %s %s %s %d %d %d\n", books[i].title, books[i].author, books[i].subject, books[i].major, books[i].available, books[i].totalCopies, books[i].timesBorrowed);
        for (int j = 0; j < books[i].timesBorrowed; j++) {
            fprintf(file, "%s\n", books[i].borrowedBy[j]);
        }
    }
    fclose(file);
}



void loadLibrarians(Librarian* librarians, int* librarianCount) {
    FILE *file = fopen("librarians.txt", "r");
    if (file == NULL) {
        printf("No librarians file found.\n");
        *librarianCount = 0;
        return;
    }
    fscanf(file, "%d", librarianCount);
    for (int i = 0; i < *librarianCount; i++) {
        fscanf(file, "%s %s", librarians[i].username, librarians[i].password);
    }
    fclose(file);
}



void loadStudents(Student* students, int* studentCount) {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("No students file found.\n");
        *studentCount = 0;
        return;
    }
    fscanf(file, "%d", studentCount);
    for (int i = 0; i < *studentCount; i++) {
        fscanf(file, "%s %s %s %d", students[i].username, students[i].password, students[i].major, &students[i].borrowedCount);
        for (int j = 0; j < students[i].borrowedCount; j++) {
            fscanf(file, "%s %s %s %d %d %d", students[i].borrowedBooks[j].title, students[i].borrowedBooks[j].author, students[i].borrowedBooks[j].subject, &students[i].borrowedBooks[j].available, &students[i].borrowedBooks[j].totalCopies, &students[i].borrowedBooks[j].timesBorrowed);
        }
    }
    fclose(file);
}



void loadBooks(Book* books, int* bookCount) {
    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("No books file found.\n");
        *bookCount = 0;
        return;
    }
    fscanf(file, "%d", bookCount);
    for (int i = 0; i < *bookCount; i++) {
        fscanf(file, "%s %s %s %s %d %d %d", books[i].title, books[i].author, books[i].subject, books[i].major, &books[i].available, &books[i].totalCopies, &books[i].timesBorrowed);
        for (int j = 0; j < books[i].timesBorrowed; j++) {
            fscanf(file, "%s", books[i].borrowedBy[j]);
        }
    }
    fclose(file);
}



void editBookInformation(Book* books, int bookCount, char* title) {
    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].title, title) == 0) {
            found = 1;
            printf("Enter new book title: ");
            scanf(" %[^\n]", books[i].title);
            printf("Enter new book author: ");
            scanf(" %[^\n]", books[i].author);
            printf("Enter new book subject: ");
            scanf(" %[^\n]", books[i].subject);
            printf("Enter new total number of copies: ");
            scanf("%d", &books[i].totalCopies);
            books[i].available = books[i].totalCopies;
            printf("Book \"%s\" information updated successfully.\n", title);
            break;
        }
    }
    if (!found) {
        printf("Book \"%s\" not found.\n", title);
    }
}


void viewLibraryBooks(Book* books, int bookCount) {
    printf("Library Books:\n");
    for (int i = 0; i < bookCount; i++) {
        printf("Title: %s, Author: %s, Subject: %s, Major: %s, Available: %d\n", 
               books[i].title, books[i].author, books[i].subject, books[i].major, books[i].available);
    }
}


void viewBookHistory(Book* books, int bookCount) {

    printf("Book History:\n");
    for (int i = 0; i < bookCount; i++) {
        printf("Title: %s, Author: %s, Times Borrowed: %d, Available: %d\n", 
               books[i].title, books[i].author, books[i].timesBorrowed, books[i].available);
        for (int j = 0; j < books[i].timesBorrowed; j++) {
            printf("  Borrowed by: %s\n", books[i].borrowedBy[j]);
        }
    }
}



void requestBook(Student* student, Book* books, int bookCount, Request* requests, int* requestCount) {

    char title[100];
    printf("Enter book title to request: ");
    scanf(" %[^\n]", title);

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].title, title) == 0) {
        
            if (strcmp(books[i].major, student->major) == 0  ||  strcmp(books[i].major, "generic") == 0) {

                // اگر رشته تحصیلی تطبیق داشت یا کتاب generic بود، درخواست ثبت می‌شود

                strcpy(requests[*requestCount].username, student->username);
                strcpy(requests[*requestCount].bookTitle, title);
                requests[*requestCount].accepted = 0;  
                (*requestCount)++;
                printf("Request for book \"%s\" submitted successfully.\n", title);

            } else {
               
                printf("You cannot request this book as it is not related to your major.\n");
            }
            return;
        }
    }
    printf("Book \"%s\" not found in library.\n", title);
}




void returnBook(Student* student, Book* books, int bookCount, char* title) {
    int foundBookInStudent = 0;
    for (int i = 0; i < student->borrowedCount; i++) {
        if (strcmp(student->borrowedBooks[i].title, title) == 0) {
            foundBookInStudent = 1;
            student->borrowedCount--;
            for (int j = i; j < student->borrowedCount; j++) {
                student->borrowedBooks[j] = student->borrowedBooks[j + 1];
            }

            for (int k = 0; k < bookCount; k++) {
                if (strcmp(books[k].title, title) == 0) {
                    books[k].available++;
                    break;
                }
            }
            printf("Book \"%s\" returned successfully.\n", title);
            return;
        }
    }
    if (!foundBookInStudent) {
        printf("Book \"%s\" not found in student's borrowed list.\n", title);
    }
    
}


void viewReservedBooks(Student* student) {
    if (student->borrowedCount == 0) {
        printf("You have no reserved books.\n");
    } else {
        printf("Your Reserved Books:\n");
        for (int i = 0; i < student->borrowedCount; i++) {
            printf("Title: %s, Author: %s, Subject: %s\n", 
                   student->borrowedBooks[i].title, 
                   student->borrowedBooks[i].author, 
                   student->borrowedBooks[i].subject);
        }
    }
}






void viewBookRequests(Request* requests, int* requestCount, Book* books, int bookCount, Student* students, int studentCount) {
    int choice;
    for (int i = 0; i < *requestCount; i++) {
        printf("Request from %s for book \"%s\" - Status: %s\n", 
                requests[i].username, 
                requests[i].bookTitle, 
                requests[i].accepted == 0 ? "Pending" : (requests[i].accepted == 1 ? "Accepted" : "Rejected"));

        if (requests[i].accepted == 0) {  // فقط درخواست‌های در انتظار بررسی می‌شوند
            printf("Enter 1 to accept or -1 to reject: ");
            scanf("%d", &choice);
            requests[i].accepted = choice;
            if (choice == 1) {
                
                for (int j = 0; j < bookCount; j++) {
                    if (strcmp(books[j].title, requests[i].bookTitle) == 0 && books[j].available > 0) {
                        books[j].available--;

                       
                        strcpy(books[j].borrowedBy[books[j].timesBorrowed], requests[i].username);
                        books[j].timesBorrowed++; 

                        
                        for (int k = 0; k < studentCount; k++) {
                            if (strcmp(students[k].username, requests[i].username) == 0) {
                                students[k].borrowedBooks[students[k].borrowedCount] = books[j];
                                students[k].borrowedCount++;
                                printf("Request accepted and book \"%s\" issued to %s.\n", requests[i].bookTitle, requests[i].username);
                                break;
                            }
                        }
                        break;
                    }
                }
            } else {
                printf("Request rejected.\n");
            }
        }
    }
}


void studentMenu(Student* student, Book* books, int bookCount, Request* requests, int* requestCount) {
    int choice;
    do {
        printf("Student Menu:\n");
        printf("1. Request Book\n");
        printf("2. View Library Books\n");
        printf("3. Return Book\n");
        printf("4. View Reserved Books\n"); 
        printf("0. Logout\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                requestBook(student, books, bookCount, requests, requestCount);
                break;
            case 2:
                viewLibraryBooks(books, bookCount);
                break;
            case 3: {
                char title[100];
                printf("Enter book title to return: ");
                scanf(" %[^\n]", title);
                returnBook(student, books, bookCount, title);
                break;
            }
            case 4:
                viewReservedBooks(student);
                break;
            case 0:
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}


void librarianMenu(Librarian* librarian, Student* students, int* studentCount, Librarian* librarians, int* librarianCount, Book* books, int* bookCount, Request* requests, int* requestCount) {
    int choice;
    do {
        printf("Librarian Menu:\n");
        printf("1. Add Student\n");
        printf("2. Add Librarian\n");
        printf("3. View Book Requests\n");
        printf("4. Add New Book\n");
        printf("5. View Book History\n");
        printf("6. Delete Book\n");
        printf("7. Edit Book Information\n");
        printf("0. Logout\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char studentUsername[50];
                char studentPassword[50];
                char studentMajor[50];
                printf("Enter student username: ");
                scanf("%s", studentUsername);
                printf("Enter student password: ");
                scanf("%s", studentPassword);
                printf("Enter student major: ");
                scanf("%s", studentMajor);
                addStudent(students, studentCount, studentUsername, studentPassword, studentMajor);
                break;
            }
            case 2: {
                char librarianUsername[50];
                char librarianPassword[50];
                printf("Enter librarian username: ");
                scanf("%s", librarianUsername);
                printf("Enter librarian password: ");
                scanf("%s", librarianPassword);
                addLibrarian(librarians, librarianCount, librarianUsername, librarianPassword);
                break;
            }
            case 3:
                
                viewBookRequests(requests, requestCount, books, *bookCount, students, *studentCount);
                break;
            case 4:
                
                addNewBook(books, bookCount);
                break;
            case 5:
                
                viewBookHistory(books, *bookCount);
                break;
            case 6: {
                char title[100];
                printf("Enter book title to delete: ");
                scanf(" %[^\n]", title);
                deleteBook(books, bookCount, title);
                break;
            }
            case 7: {
                char title[100];
                printf("Enter book title to edit: ");
                scanf(" %[^\n]", title);
                editBookInformation(books, *bookCount, title);
                break;
            }
            case 0:
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main() {

    Librarian librarians[20];
    Student students[200];
    Book books[200];
    Request requests[300];  
    int librarianCount = 0;
    int studentCount = 0;
    int bookCount = 0;
    int requestCount = 0;
    int userIndex;
    int isAdmin;


    loadLibrarians(librarians, &librarianCount);
    loadStudents(students, &studentCount);
    loadBooks(books, &bookCount);

    // ایجاد کتابدار پیش‌فرض در صورت خالی بودن فایل
    if (librarianCount == 0) {
        strcpy(librarians[0].username, "ali");
        strcpy(librarians[0].password, "ali123");
        librarianCount++;
        saveLibrarians(librarians, librarianCount);  // ذخیره کتابدار پیش‌فرض در فایل
    }

    char username[50];
    char password[50];
    int loginResult;
    while (1) {

        system("CLS");
        printf("Library Management System\n");
        printf("Enter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        loginResult = login(username, password, librarians, librarianCount, students, studentCount, &userIndex, &isAdmin);
        if (loginResult == 1) {
            librarianMenu(&librarians[userIndex], students, &studentCount, librarians, &librarianCount, books, &bookCount, requests, &requestCount);
        } else if (loginResult == 2) {
            studentMenu(&students[userIndex], books, bookCount, requests, &requestCount);
        } else {
            printf("Login failed. Please try again.\n");
            continue; 
        }

        
        saveLibrarians(librarians, librarianCount);
        saveStudents(students, studentCount);
        saveBooks(books, bookCount);
    }

    return 0;
}

