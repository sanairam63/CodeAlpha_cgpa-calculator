#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// Function to assign grade based on z-score (relative grading)
string getRelativeGrade(double z) {
    if (z >= 1.0) return "A";
    else if (z >= 0.5) return "B+";
    else if (z >= 0.0) return "B";
    else if (z >= -0.5) return "C+";
    else if (z >= -1.0) return "C";
    else if (z >= -1.5) return "D";
    else return "F";
}

// Function to convert grade to grade point
double gradeToPoint(const string& grade) {
    if (grade == "A+" || grade == "A") return 4.0;
    else if (grade == "A-") return 3.7;
    else if (grade == "B+") return 3.3;
    else if (grade == "B") return 3.0;
    else if (grade == "B-") return 2.7;
    else if (grade == "C+") return 2.3;
    else if (grade == "C") return 2.0;
    else if (grade == "C-") return 1.7;
    else if (grade == "D+") return 1.3;
    else if (grade == "D") return 1.0;
    else if (grade == "D-") return 0.7;
    else return 0.0;
}

int main() {
    int noSemester;
    int noCourses[20];
    string CourseName[20][100];
    string grade[20][100];
    int creditHours[20][100];
    double gradePoints[20][100];
    double gpa[20];
    int totalCreditHours = 0;
    double totalGradePoints = 0.0;

    cout << "--------------CGPA CALCULATOR------------------" << endl;
    cout << "Enter number of semesters: ";
    cin >> noSemester;

    for (int sem = 0; sem < noSemester; sem++) {
        cout << "-----SEMESTER " << sem + 1 << "-------" << endl;
        cout << "Enter the number of courses: ";
        cin >> noCourses[sem];
        cin.ignore();

        cout << "Choose grading method for this semester (1 = Absolute, 2 = Relative): ";
        int gradingMethod;
        cin >> gradingMethod;
        cin.ignore();

        int semesterCreditHours = 0;
        double semesterGradePoints = 0.0;

        vector<double> marks(noCourses[sem]);
        double mean = 0.0, stddev = 0.0;

        if (gradingMethod == 2) {
            // Input marks for relative grading
            for (int i = 0; i < noCourses[sem]; i++) {
                cout << "Enter the course name: ";
                getline(cin, CourseName[sem][i]);
                cout << "Enter total credit hours for the course: ";
                cin >> creditHours[sem][i];
                cout << "Enter marks obtained (out of 100): ";
                cin >> marks[i];
                cin.ignore();
            }
            // Calculate mean
            for (int i = 0; i < noCourses[sem]; i++) mean += marks[i];
            mean /= noCourses[sem];
            // Calculate standard deviation
            for (int i = 0; i < noCourses[sem]; i++) stddev += pow(marks[i] - mean, 2);
            stddev = sqrt(stddev / noCourses[sem]);
            // Assign grades based on z-score
            for (int i = 0; i < noCourses[sem]; i++) {
                double z = (stddev == 0) ? 0 : (marks[i] - mean) / stddev;
                grade[sem][i] = getRelativeGrade(z);
                gradePoints[sem][i] = creditHours[sem][i] * gradeToPoint(grade[sem][i]);
                semesterCreditHours += creditHours[sem][i];
                semesterGradePoints += gradePoints[sem][i];
            }
        } else {
            // Absolute grading (as before)
            for (int i = 0; i < noCourses[sem]; i++) {
                cout << "Enter the course name: ";
                getline(cin, CourseName[sem][i]);
                cout << "Enter total credit hours for the course: ";
                cin >> creditHours[sem][i];
                cout << "Enter the grade for the course (A+,A,A-,B+,B,B-,C+,C,C-,D+,D,D-,F): ";
                cin >> grade[sem][i];
                cin.ignore();

                double gradeValue = gradeToPoint(grade[sem][i]);
                gradePoints[sem][i] = creditHours[sem][i] * gradeValue;
                semesterCreditHours += creditHours[sem][i];
                semesterGradePoints += gradePoints[sem][i];
            }
        }

        gpa[sem] = semesterGradePoints / semesterCreditHours;
        totalCreditHours += semesterCreditHours;
        totalGradePoints += semesterGradePoints;

        cout << "\n--- Semester " << sem + 1 << " Results ---\n";
        for (int i = 0; i < noCourses[sem]; i++) {
            cout << "Course: " << CourseName[sem][i]
                 << ", Grade: " << grade[sem][i]
                 << ", Credit Hours: " << creditHours[sem][i]
                 << ", Grade Points: " << gradePoints[sem][i] << endl;
        }
        cout << "Total Credit Hours: " << semesterCreditHours << endl;
        cout << "Total Grade Points: " << semesterGradePoints << endl;
        cout << "GPA for Semester " << sem + 1 << ": " << gpa[sem] << endl << endl;
    }

    double cgpa = totalGradePoints / totalCreditHours;
    cout << "==============================" << endl;
    cout << "CGPA for " << noSemester << " semesters: " << cgpa << endl;

    return 0;
}