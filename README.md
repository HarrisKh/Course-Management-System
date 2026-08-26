# Course Management System

## Overview

This is a C++ console-based Course Management System. The program manages three related types of data:

- Courses
- Students
- Enrollments

The system uses dynamically allocated arrays, structures, file handling, searching, updating, deleting, and menu-driven interaction.

Data is stored in text files so that information is available again when the program is restarted.

## Main Features

- Add, view, update, delete, and search students
- Add, view, update, delete, and search courses
- Enroll students in courses
- View a student's enrolled courses
- View students enrolled in a course
- Drop a student from a course
- Check course capacity
- Prevent duplicate student IDs
- Prevent duplicate course IDs
- Prevent duplicate enrollments
- Automatically resize dynamic arrays
- Load data when the program starts
- Save data when the program exits
- Generate basic enrollment reports

---

# Data Structures

The project uses three structures.

## Course

```cpp
struct Course {
    int courseID;
    char courseName[100];
    char instructor[50];
    int credits;
    int capacity;
    int enrolled;
};
```

A course stores its ID, name, instructor, credit hours, maximum capacity, and current enrollment count.

## Student

```cpp
struct Student {
    int studentID;
    char studentName[100];
    char department[50];
    int semester;
};
```

A student stores an ID, name, department, and current semester.

## Enrollment

```cpp
struct Enrollment {
    int studentID;
    int courseID;
    char enrollmentDate[20];
};
```

An enrollment connects a student with a course and stores the enrollment date.

Instead of storing complete student and course objects inside an enrollment, the program stores their IDs and uses those IDs to find the corresponding records.

---

# Dynamic Arrays

The program starts each array with a capacity of:

```cpp
#define cap 100
```

Three dynamic arrays are created:

```cpp
Course* courses = new Course[cap];
Student* students = new Student[cap];
Enrollment* enrollments = new Enrollment[cap];
```

The program also keeps track of:

- Current number of records
- Current array capacity

When an array becomes full, its capacity is doubled.

For example:

```text
100 -> 200 -> 400 -> 800 -> ...
```

The resizing functions are:

```cpp
resizeCourses()
resizeStudents()
resizeEnrollments()
```

Each function creates a larger array, copies the existing records, deletes the old array, and updates the pointer.

---

# File Handling

The program uses three text files:

```text
courses.txt
students.txt
enrollments.txt
```

When the program starts, it loads all three files.

When the user exits, it saves all current data.

This gives the program persistent storage even though it does not use a database.

---

# Course File Format

A course is stored using `|` as a separator.

Example format:

```text
courseID|courseName|instructor|credits|capacity|enrolled
```

The first line of the file stores the total number of courses.

---

# Student File Format

Students are stored as:

```text
studentID|studentName|department|semester|
```

Again, the first line stores the number of students.

---

# Enrollment File Format

Enrollments are stored as:

```text
studentID|courseID|enrollmentDate|
```

The first line stores the number of enrollments.

---

# Course Management

The Course Management menu contains:

```text
1. Add courses
2. View courses
3. Update courses
4. Delete courses
5. Search courses
6. Back
```

## Add Course

`addCourse()` asks for:

- Course ID
- Course name
- Instructor
- Credits
- Capacity

The enrollment count is automatically initialized to:

```cpp
0
```

The function also checks that the course ID is not already being used.

---

## View Courses

`viewAllCourses()` displays all courses in a formatted table.

It shows:

```text
ID
Name
Instructor
Filled
```

The filled value is displayed as:

```text
enrolled/capacity
```

For example:

```text
CS101   Programming   Ali   25/40
```

---

## Search Course

`searchCourse()` searches for a course using its ID.

If found, it displays:

- ID
- Name
- Instructor
- Credits
- Enrollment count
- Capacity

If no course has the requested ID, it displays:

```text
Course not found
```

---

## Update Course

`updateCourse()` searches for a course by ID and allows the user to enter:

- New course name
- New instructor
- New capacity

The program checks that a new capacity is not smaller than the current number of enrolled students.

---

## Delete Course

`deleteCourse()` searches for a course by ID.

A course cannot be deleted if students are currently enrolled in it.

The program displays:

```text
Drop the enrolled students first
```

This prevents an enrollment from referring to a course that no longer exists.

---

# Student Management

The Student Management menu contains:

```text
1. Add Student
2. View Student
3. Update Student
4. Delete Student
5. Search Student
6. Back
```

## Add Student

`addStudent()` asks for:

- Student ID
- Student name
- Department
- Semester

The ID must be unique.

If the ID already exists, the student is not added.

---

## View Students

`viewAllStudents()` displays:

```text
ID
Name
Department
Semester
```

in a formatted table.

---

## Search Student

`searchStudent()` searches using the student ID.

If found, it displays all stored information about the student.

---

## Update Student

`updateStudent()` finds a student by ID and allows the user to change:

- Name
- Department
- Semester

The student's ID remains unchanged.

---

## Delete Student

`deleteStudent()` finds the requested student and removes the record by shifting all later elements one position to the left.

For example:

```text
[A][B][C][D]
```

Deleting `B` results in:

```text
[A][C][D]
```

The number of students is then decreased.

---

# Enrollment Management

The Enrollment Management menu contains:

```text
1. Enroll student in course
2. View Student enrollment
3. View course enrollment
4. Drop student from course
5. Back
```

## Enroll Student

`enrollStudent()` performs several checks before creating an enrollment.

### 1. Student Exists

The entered student ID must exist.

### 2. Course Exists

The entered course ID must exist.

### 3. Course Has Space

The current enrollment count must be less than the course capacity.

### 4. No Duplicate Enrollment

The same student cannot be enrolled in the same course twice.

If all checks pass, the program asks for the enrollment date and creates the enrollment.

The course's enrollment count is also increased.

---

# View Student Enrollments

`viewStudentEnrollments()` asks for a student ID and searches the enrollment array.

For every matching enrollment, it finds the corresponding course and displays:

```text
Course ID
Course Name
Enrollment Date
```

If there are no enrollments, it displays:

```text
No enrollments found for this student
```

---

# View Course Enrollments

`viewCourseEnrollments()` works in the opposite direction.

It asks for a course ID and finds every enrollment belonging to that course.

For each enrollment, it finds the student and displays:

```text
Student ID
Student Name
Enrollment Date
```

This provides a list of all students taking a particular course.

---

# Drop Student From Course

`dropStudent()` asks for:

```text
Student ID
Course ID
```

It searches for the matching enrollment.

If found:

1. The course enrollment count is decreased.
2. The enrollment is removed.
3. Remaining enrollment records are shifted left.
4. The enrollment count is decreased.

If no matching enrollment exists, the program reports:

```text
Enrollment not found
```

---

# Reports

The Reports menu provides three options:

```text
1. Display all Courses with enrollment Count
2. Display Students enrolled in specific course
3. Display courses taken by specific student
```

These reports reuse the existing course and enrollment functions instead of duplicating the logic.

---

# Program Flow

The overall program works like this:

```text
Start
  |
  v
Create dynamic arrays
  |
  v
Load courses.txt
Load students.txt
Load enrollments.txt
  |
  v
Display Main Menu
  |
  +--> Course Management
  |
  +--> Student Management
  |
  +--> Enrollment Management
  |
  +--> Reports
  |
  +--> Exit
          |
          v
      Save all data
          |
          v
      Free memory
          |
          v
         End
```

---

# Main Menu

The main menu is:

```text
Course Management System

1. Course management
2. Student management
3. Enrollemnt management
4. Reports
5. Exit
```

The program repeatedly displays this menu until the user chooses option `5`.

A `switch` statement is used to select the appropriate subsystem.

---

# Memory Management

The program uses dynamic memory:

```cpp
new Course[cap]
new Student[cap]
new Enrollment[cap]
```

The arrays are resized manually when required.

At the end of the program, the memory is released using:

```cpp
delete[] courses;
delete[] students;
delete[] enrollments;
```

This is important because the arrays were created using `new[]`.

---

# C++ Concepts Demonstrated

Although the project is primarily procedural and uses structures rather than classes, it demonstrates several important C++ concepts.

## Structures

`Course`, `Student`, and `Enrollment` group related information together.

## Pointers

The program uses pointers to dynamically allocated arrays:

```cpp
Course*
Student*
Enrollment*
```

Some functions take references to these pointers so they can replace the allocated array during resizing.

## Dynamic Memory

The program manually manages dynamically allocated arrays and their capacity.

## File Handling

It uses:

```cpp
ifstream
ofstream
```

to load and save data.

## Character Arrays

The project uses fixed-size C-style strings:

```cpp
char courseName[100];
char studentName[100];
char instructor[50];
```

## Searching

Linear search is used throughout the program to find students, courses, and enrollments.

## Array Deletion

Records are deleted by shifting the elements after the deleted item.

## Menu-Driven Programming

Nested menus and `switch` statements provide the user interface.

---

# Relationships Between the Data

The three structures are connected through IDs:

```text
Student
  |
  | studentID
  v
Enrollment
  |
  | courseID
  v
Course
```

For example:

```text
Student 101
    |
    +-- Enrollment -> Course 501
    |
    +-- Enrollment -> Course 502
```

This allows one student to take multiple courses and one course to contain multiple students.

---

# Important Validation

The program performs several useful checks:

- Duplicate student IDs are rejected.
- Duplicate course IDs are rejected.
- A student must exist before enrollment.
- A course must exist before enrollment.
- Full courses reject new enrollments.
- Duplicate student-course enrollments are rejected.
- Courses with enrolled students cannot be deleted.
- Dropping a course enrollment decreases its enrollment count.
- Dynamic arrays resize when their capacity is reached.

---

# Limitations

The current implementation is a straightforward data-management project and has some areas that could be improved.

- It uses linear searches, which can become slower with large datasets.
- It uses fixed-size C-style character arrays.
- There is no input validation for incorrect data types.
- Enrollment dates are stored as plain strings.
- There is no authentication or separate user roles.
- The course update function checks an invalid capacity but does not actually assign a valid new capacity to the course.
- Deleting a student does not automatically remove that student's existing enrollments.
- Deleting a student can therefore leave enrollment records referring to a student that no longer exists.
- The program is console based and does not have a graphical interface or database backend.

---

# Possible Improvements

The system could be extended by adding:

- `std::string` instead of character arrays
- `std::vector` instead of manual dynamic arrays
- Faster searching using maps or other data structures
- Input validation
- Student login and administrator login
- Automatic cleanup of enrollments when a student is deleted
- Better date validation
- Course prerequisites
- Semester-based course registration
- GPA and transcript management
- More detailed reports
- Database integration
- A graphical user interface

---

# Conclusion

This project implements a complete console-based Course Management System using C++ structures, dynamic arrays, file handling, and menu-driven programming.

The system keeps students, courses, and enrollments connected through IDs and provides the basic operations required to manage them.

The project is particularly useful for understanding how dynamic memory, file persistence, searching, record deletion, and relationships between different data structures can be combined into one larger C++ application.
