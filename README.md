Library Management System
This project is a basic library management system written in C. It allows librarians and students to manage books, requests, and user information. The system supports functionalities like adding new books, managing student and librarian accounts, handling book requests, and viewing borrowed book history.

Features
User Authentication:

Librarian and student login with username and password.
Librarian Functions:

Add new students and librarians.
Add new books to the library.
View and manage book requests.
View history of borrowed books.
Edit book information.
Delete books from the library.
Student Functions:

Request books.
View available library books.
Return borrowed books.
View their reserved books.
File Structure
LibraryManagement.c: The main source file containing the implementation of the library management system.
librarians.txt: Stores librarian information.
students.txt: Stores student information.
books.txt: Stores book information.
How to Run
Compile the program:

sh
gcc LibraryManagement.c -o LibraryManagement
Run the executable:

sh
./LibraryManagement
Usage
Librarian Login:

Default username: ali
Default password: ali123
The default librarian account is created if the librarians' file is empty.
Student Login:

Students need to be added by a librarian.
Functions
login: Authenticates librarians and students.
addStudent: Adds a new student to the system.
addLibrarian: Adds a new librarian to the system.
addNewBook: Adds a new book to the library.
deleteBook: Deletes a book from the library.
saveLibrarians: Saves librarian information to a file.
saveStudents: Saves student information to a file.
saveBooks: Saves book information to a file.
loadLibrarians: Loads librarian information from a file.
loadStudents: Loads student information from a file.
loadBooks: Loads book information from a file.
editBookInformation: Edits information of a book.
viewLibraryBooks: Displays all books in the library.
viewBookHistory: Displays history of borrowed books.
requestBook: Allows a student to request a book.
returnBook: Allows a student to return a borrowed book.
viewReservedBooks: Displays reserved books of a student.
viewBookRequests: Displays and manages book requests.

Notes
The system clears the console screen using system("CLS");, which may not be portable to non-Windows systems. You may need to adjust this for your operating system
