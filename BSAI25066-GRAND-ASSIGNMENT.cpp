#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;
#define cap 100
struct Course {
    int courseID;
    char courseName[100];
    char instructor[50];
    int credits;
    int capacity;
    int enrolled;
};
struct Student {
    int studentID;
    char studentName[100];
    char department[50];
    int semester;
};
struct Enrollment {
    int studentID;
    int courseID;
    char enrollmentDate[20];
};
void resizeCourses(Course*& courses, int& capacity, int currentSize) {
    int newCap = capacity * 2;
     Course* newArr = new Course[newCap];
     for (int i = 0; i < currentSize; i++)
         newArr[i] = courses[i];
    delete[] courses;
    courses = newArr;
    capacity = newCap;
}

void resizeStudents(Student*& students, int& capacity, int currentSize) {
    int newCap = capacity * 2;
    Student* newArr = new Student[newCap];
    for (int i = 0; i < currentSize; i++)
        newArr[i] = students[i];
    delete[] students;
    students = newArr;
    capacity = newCap;
}

void resizeEnrollments(Enrollment*& enrollments, int& capacity, int currentSize) {
    int newCap = capacity * 2;
    Enrollment* newArr = new Enrollment[newCap];
    for (int i = 0; i < currentSize; i++)
        newArr[i] = enrollments[i];
    delete[] enrollments;
    enrollments = newArr;
    capacity = newCap;
}
void loadCoursesFromFile(Course* courses, int& numC, int& courseCap) {
    ifstream rdr("courses.txt");
    if (!rdr) {
        cout << "Could not open";
        return;
    }
    int size;
    rdr >> size;
    for (int i = 0; i < size; i++) {
        if (numC >= courseCap)
            resizeCourses(courses, courseCap, numC);
        rdr >> courses[numC].courseID;
        rdr.ignore();
        rdr.getline(courses[numC].courseName, 100, '|');
        rdr.getline(courses[numC].instructor, 50, '|');
        rdr >> courses[numC].credits;
        rdr.ignore();
        
        rdr >> courses[numC].capacity;
        rdr.ignore();
        
        rdr >> courses[numC].enrolled;
        rdr.ignore();
        if (rdr)
            numC++;
    }
    rdr.close();
}
void saveCoursesToFile(Course* courses, int numCourses) {
    ofstream write("courses.txt");
    if (!write) 
        return;
    write << numCourses << endl;
    for (int i = 0; i < numCourses; i++) {
        write << courses[i].courseID << "|"
            << courses[i].courseName << "|"
            << courses[i].instructor << "|"
            << courses[i].credits << "|"
            << courses[i].capacity << "|"
            << courses[i].enrolled << endl;
    }
    write.close();
}
void loadStudentsFromFile(Student*& students, int& numS, int& studentCap) {
    ifstream rdr("students.txt");
    if (!rdr) {
        cout << "Could not open";
        return;
    }
    int size;
    rdr >> size;
    for (int i = 0; i < size; i++) {
        if (numS >= studentCap)
            resizeStudents(students, studentCap, numS);
        rdr >> students[numS].studentID;
        rdr.ignore();
        rdr.getline(students[numS].studentName, 100, '|');
        rdr.getline(students[numS].department, 50, '|');
        rdr >> students[numS].semester;
        rdr.ignore();

        if (rdr)
            numS++;
    }
    rdr.close();
}

void saveStudentsToFile(Student* students, int numS) {
    ofstream write("students.txt");
    if (!write) 
        return;
    write << numS << endl;
    for (int i = 0; i < numS; i++) {
        write << students[i].studentID << "|"
            << students[i].studentName << "|"
            << students[i].department << "|"
            << students[i].semester << "|" << endl;
    }
    write.close();
}

void addStudent(Student*& students, int& numS, int& studentCap) {
    if (numS >= studentCap)
        resizeStudents(students, studentCap, numS);
    Student s;
    cout << "Enter student ID: ";
    cin >> s.studentID;

    for (int i = 0; i < numS; i++) {
        if (students[i].studentID == s.studentID) {
            cout << "Duplicate found" << endl;
            return;
        }
    }
    cin.ignore();
    cout << "Enter Student Name: ";
    cin.getline(s.studentName, 100);
    cout << "Enter department: ";
    cin.getline(s.department, 50);
    cout << "Enter semester: ";
    cin >> s.semester;

    students[numS] = s;
    numS++;
}

void viewAllStudents(Student* students, int numS) {
    if (numS == 0) {
        cout << "No data" << endl;
        return;
    }
    cout << endl << left << setw(10) << "ID" << setw(30) << "Name" <<
        setw(20) << "Department" << setw(10) << "Semester" << endl;
    for (int i = 0; i < numS; i++) {
        cout << left << setw(10) << students[i].studentID
            << setw(30) << students[i].studentName
            << setw(20) << students[i].department
            << setw(10) << students[i].semester << endl;
    }
}

void searchStudent(Student* students, int numS) {
    int id;
    cout << "Enter student ID: ";
    cin >> id;
    bool found = false;
    for (int i = 0; i < numS; i++) {
        if (students[i].studentID == id) {
            cout << "ID: " << students[i].studentID << endl;
            cout << "Name: " << students[i].studentName << endl;
            cout << "Department: " << students[i].department << endl;
            cout << "Semester: " << students[i].semester << endl;
            found = true;
            break;
        }
    }
    if (!found)
        cout << "Student not found" << endl;
}

void updateStudent(Student* students, int numS) {
    int id;
    cout << "Enter student ID to update: ";
    cin >> id;

    for (int i = 0; i < numS; i++) {
        if (students[i].studentID == id) {
            cin.ignore();
            cout << "Enter new name: ";
            cin.getline(students[i].studentName, 100);
            cout << "Enter new department: ";
            cin.getline(students[i].department, 50);
            cout << "Enter new semester: ";
            cin >> students[i].semester;
            return;
        }
    }
    cout << "Student not found" << endl;
}

void deleteStudent(Student*& students, int& numS) {
    int id;
    cout << "Enter student ID to delete: ";
    cin >> id;

    int index = -1;
    for (int i = 0; i < numS; i++) {
        if (students[i].studentID == id) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        for (int i = index; i < numS - 1; i++) {
            students[i] = students[i + 1];
        }
        numS--;
        cout << "Student Deleted" << endl;
    }
    else {
        cout << "Student not found" << endl;
    }
}

void loadEnrollmentsFromFile(Enrollment*& enrollments, int& numE, int& enrollmentCap) {
    ifstream rdr("enrollments.txt");
    if (!rdr) return;

    int size = 0;
    rdr >> size;

    for (int i = 0; i < size; i++) {
        if (numE >= enrollmentCap) 
            resizeEnrollments(enrollments, enrollmentCap, numE);

        rdr >> enrollments[numE].studentID;
        rdr.ignore();

        rdr >> enrollments[numE].courseID;
        rdr.ignore();

        rdr.getline(enrollments[numE].enrollmentDate, 20, '|');

        if (rdr)
            numE++;
    }
    rdr.close();
}
void saveEnrollmentsToFile(Enrollment*& enrollments, int& numE){
    ofstream write("enrollments.txt");
    if (!write) 
        return;
    write << numE << endl;
    for (int i = 0; i < numE; i++) {
        write << enrollments[i].studentID << "|"
            << enrollments[i].courseID << "|"
            << enrollments[i].enrollmentDate << "|" << endl;
    }

    write.close();
}

void enrollStudent(Enrollment*& enrollments, int& numE, int& enrollmentCap, Student* students, int numS, Course* courses, int numC) {
    int sID, cID;
    cout << "Enter Student ID: ";
    cin >> sID;
        bool sFound = false;
    for (int i = 0; i < numS; i++) {
        if (students[i].studentID == sID) {
            sFound = true;
            break;
        }
    }
    if (!sFound) {
        cout << "Student not found" << endl;
        return;
    }

    cout << "Enter course ID: ";
    cin >> cID;
    int cIndex = -1;
    for (int i = 0; i < numC; i++) {
        if (courses[i].courseID == cID) {
            cIndex = i;
            break;
        }
    }
    if (cIndex == -1) {
        cout << "Course not found" << endl;
        return;
    }

    if (courses[cIndex].enrolled >= courses[cIndex].capacity) {
        cout << "Course is full" << endl;
        return;
    }

    for (int i = 0; i < numE; i++) {
        if (enrollments[i].studentID == sID && enrollments[i].courseID == cID) {
            cout << "Student already enrolled in this course" << endl;
            return;
        }
    }

    if (numE >= enrollmentCap) resizeEnrollments(enrollments, enrollmentCap, numE);

    enrollments[numE].studentID = sID;
    enrollments[numE].courseID = cID;
    cin.ignore();
    cout << "Enter Enrollment Date: ";
    cin.getline(enrollments[numE].enrollmentDate, 20);

    courses[cIndex].enrolled++;
    numE++;
    cout << "Student enrolled successfully" << endl;
}

void viewStudentEnrollments(Enrollment* enrollments, int numE, Course* courses, int numC) {
    int sID;
    cout << "Enter student ID: ";
    cin >> sID;

    cout << "Courses for Student " << sID << ":" << endl;
    cout << left << setw(10) << "CourseID" << setw(30) << "Course Name" << setw(15) << "Date" << endl;
    
    bool foundAny = false;
    for (int i = 0; i < numE; i++) {
        if (enrollments[i].studentID == sID) {
            char cName[100] = "Unknown";
            for(int j=0; j<numC; j++) {
                if(courses[j].courseID == enrollments[i].courseID) {
                    strcpy(cName, courses[j].courseName);
                    break;
                }
            }
            cout << left << setw(10) << enrollments[i].courseID 
                 << setw(30) << cName 
                 << setw(15) << enrollments[i].enrollmentDate << endl;
            foundAny = true;
        }
    }
    if (!foundAny) cout << "No enrollments found for this student" << endl;
}

void viewCourseEnrollments(Enrollment* enrollments, int numE, Student* students, int numS) {
    int cID;
    cout << "Enter course ID: ";
    cin >> cID;

    cout << "Students in Course " << cID << ":" << endl;
    cout << left << setw(10) << "StudentID" << setw(30) << "Student Name" << setw(15) << "Date" << endl;

    bool foundAny = false;
    for (int i = 0; i < numE; i++) {
        if (enrollments[i].courseID == cID) {
            char sName[100] = "unknown";
            for (int j = 0; j < numS; j++) {
                if (students[j].studentID == enrollments[i].studentID) {
                    strcpy(sName, students[j].studentName);
                    break;
                }
            }
            cout << left << setw(10) << enrollments[i].studentID 
                 << setw(30) << sName 
                 << setw(15) << enrollments[i].enrollmentDate << endl;
            foundAny = true;
        }
    }
    if (!foundAny) cout << "No enrollments found for this course " << endl;
}

void dropStudent(Enrollment*& enrollments, int& numE, Course* courses, int numC) {
    int sID, cID;
    cout << "Enter student ID: ";
    cin >> sID;
    cout << "Enter course ID: ";
    cin >> cID;

    int index = -1;
    for (int i = 0; i < numE; i++) {
        if (enrollments[i].studentID == sID && enrollments[i].courseID == cID) {
            index = i;
            break;
        }
    }

    if (index != -1) {
         for (int i = 0; i < numC; i++) {
            if (courses[i].courseID == cID) {
                if (courses[i].enrolled > 0) courses[i].enrolled--;
                break;
            }
        }
        
        for (int i = index; i < numE - 1; i++) {
            enrollments[i] = enrollments[i + 1];
        }
        numE--;
        cout << "Student dropped from course " << endl;
    }
    else {
        cout << "Enrollment not found" << endl;
    }
}
void addCourse(Course*& courses, int& numC, int& courseCap) {
    if (numC >= courseCap)
        resizeCourses(courses, courseCap, numC);
    Course c;
    cout << "Enter course ID: ";
    cin >> c.courseID;

    for (int i = 0; i < numC; i++) {
        if (courses[i].courseID == c.courseID) {
            cout << "Duplicate found" << endl;
            return;
        }
    }
    cin.ignore();
    cout << "Enter course name: ";
    cin.getline(c.courseName, 100);
    cout << "Enter instructor: ";
    cin.getline(c.instructor, 50);
    cout << "Enter credits: ";
    cin >> c.credits;
    cout << "Enter capacity: ";
    cin >> c.capacity;
    c.enrolled = 0;

    courses[numC] = c;
    numC++;
}
void viewAllCourses(Course* courses, int numC) {
    if (numC == 0) {
        cout << "No data" << endl;
        return;
    }
    cout << endl << left << setw(10) << "ID" << setw(30) << "Name" <<
        setw(20) << "Instructor" << setw(10) << "Filled" << endl;
    for (int i = 0; i < numC; i++) {
        cout << left << setw(10) << courses[i].courseID
            << setw(30) << courses[i].courseName
            << setw(20) << courses[i].instructor
            << courses[i].enrolled << "/" << courses[i].capacity << endl;
    }
}
void searchCourse(Course* courses, int numC) {
    int id;
    cout << "Entre course ID: ";
    cin >> id;
    bool found = false;
    for (int i = 0; i < numC; i++) {
        if (courses[i].courseID == id) {
            cout << "ID: " << courses[i].courseID << endl;
            cout << "Name: " << courses[i].courseName<< endl;
            cout << "Instructor: " << courses[i].instructor << endl;
            cout << "credits: " << courses[i].credits << endl;
            cout << "Enrollments: " << courses[i].enrolled << "/" << courses[i].capacity << endl;
            found = true;
            break;
        }
    }
    if (!found)
        cout << "Course not found";
}
void updateCourse(Course* courses, int numC) {
    int id;
    cout << "Enter course ID to update: ";
    cin >> id;

    for (int i = 0; i < numC; i++) {
        if (courses[i].courseID == id) {
            cin.ignore();
            cout << "Enter new name: ";
            cin.getline(courses[i].courseName, 100);

            cout << "Enter new instructor: ";
            cin.getline(courses[i].instructor, 50);

            cout << "Enter new capacity: ";
            int newCap;
            cin >> newCap;

            if (newCap < courses[i].enrolled) {
                cout << "Enter again" << endl;
            }
            return;
        }
    }
    cout << "Course not found" << endl;
}

void deleteCourse(Course* courses, int& numC) {
    int id;
    cout << "Enter course ID to delete: ";
    cin >> id;

    int index = -1;
    for (int i = 0; i < numC; i++) {
        if (courses[i].courseID == id) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        if (courses[index].enrolled > 0) {
            cout << "Drop the enrolled students first" << endl;
            return;
        }
        for (int i = index; i < numC - 1; i++) {
            courses[i] = courses[i + 1];
        }
        numC--;
        cout << "Course deleted" << endl;
    }
    else {
        cout << "Course not found" << endl;
    }
}

int main() {
    int courseCap = cap;
    int numCourses = 0;
    Course* courses = new Course[cap];
    
    int studentCap = cap;
    int numStudents = 0;
    Student*students = new Student[cap];

    int enrollmentCap = cap;
    int numEnrollments = 0;
    Enrollment* enrollments = new Enrollment[cap];

    loadCoursesFromFile(courses, numCourses, courseCap);
    loadStudentsFromFile(students, numStudents, studentCap);
    loadEnrollmentsFromFile(enrollments, numEnrollments, enrollmentCap);

    int choice = 0;
    while (choice != 5) {
        cout << endl << "Course Management System " << endl;
        cout << "1. Course management " << endl;
        cout << "2. Student management " << endl;
        cout << "3. Enrollemnt management " << endl;
        cout << "4. Reports " << endl;
        cout << "5. Exit " << endl;
        cin >> choice;

        switch(choice){
        case 1: {
            int subC;
            cout << endl << " Course menu" << endl;
            cout << "1. Add courses " << endl;
            cout << "2. View courses " << endl;
            cout << "3. Update courses " << endl;
            cout << "4. Delete courses " << endl;
            cout << "5. Search courses " << endl;
            cout << "6. Back " << endl;
            cin >> subC;
            if (subC == 1)
                addCourse(courses, numCourses, courseCap);
            else if (subC == 2)
                viewAllCourses(courses, numCourses);
            else if (subC == 3)
               updateCourse(courses, numCourses);
            else if (subC == 4)
                deleteCourse(courses, numCourses);
            else if (subC == 5)
                searchCourse(courses, numCourses);
            break;
        }
        case 2: {
            int subC;
            cout << endl << " Student menu" << endl;
            cout << "1. Add Student " << endl;
            cout << "2. View Student " << endl;
            cout << "3. Update Student " << endl;
            cout << "4. Delete Student " << endl;
            cout << "5. Search Student " << endl;
            cout << "6. Back " << endl;
            cin >> subC;
            if (subC == 1)
                addStudent(students, numStudents, studentCap);
            else if (subC == 2)
                viewAllStudents(students, numStudents);
            else if (subC == 3)
               updateStudent(students, numStudents);
            else if (subC == 4)
                deleteStudent(students, numStudents);
            else if (subC == 5)
                searchStudent(students, numStudents);
            break;
        }
        case 3: {
            int subC;
            cout << endl << " Enrollment menu" << endl;
            cout << "1. Enroll student in course " << endl;
            cout << "2. View Student enrollment " << endl;
            cout << "3. View course enrollment " << endl;
            cout << "4. Drop student from course " << endl;
            cout << "5. Back " << endl;
            cin >> subC;
            if (subC == 1)
                enrollStudent(enrollments, numEnrollments, enrollmentCap, students, numStudents, courses, numCourses);
            else if (subC == 2)
                viewStudentEnrollments(enrollments, numEnrollments, courses, numCourses);
            else if (subC == 3)
                viewCourseEnrollments(enrollments, numEnrollments, students, numStudents);
            else if (subC == 4)
                dropStudent(enrollments, numEnrollments, courses, numCourses);
            break;
        }
        case 4: {
            int subC;
            cout << " Reports Menu " << endl;
            cout << "1. Display all Courses with enrollment Count" << endl;
            cout << "2. Display Students enrolled in specific course" << endl;
            cout << "3. Display courses taken by specific student" << endl;
            cout << "4. Back" << endl;
            cin >> subC;

            if (subC == 1)
                viewAllCourses(courses, numCourses);
            else if (subC == 2)
                viewCourseEnrollments(enrollments, numEnrollments, students, numStudents);
            else if (subC == 3)
                viewStudentEnrollments(enrollments, numEnrollments, courses, numCourses);
            break;
        }
        }
    }
    saveCoursesToFile(courses, numCourses);
    saveStudentsToFile(students, numStudents);
    saveEnrollmentsToFile(enrollments, numEnrollments);

    delete[] courses;
    delete[] students;
    delete[] enrollments;

    return 0;
}