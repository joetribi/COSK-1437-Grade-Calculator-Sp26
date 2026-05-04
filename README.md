# COSK-1437-Grade-Calculator-Sp26
# Grade Calculator (OOP Edition)

A C++ console application that tracks graded items (homework, quizzes, exams),
calculates points-based and weighted final grades, and persists data between sessions.
Built around an inheritance hierarchy with a menu-driven interface.

## Author
Alexander Sjogreen - COSC 1437, Spring

## Description
This application allows students and educators to manage and calculate grades for various assessments. 
It supports customization of grading schemes and provides both points-based and weighted grading options, 
offering a comprehensive tool for academic evaluation.

## Features
- Menu-driven interface (add / view / remove / calculate / exit)
- Three graded-item categories: Homework, Quiz, Exam
- Custom grading scheme: category weights + letter-grade cutoffs
- Two grade modes: points-based and weighted
- Save and load grades to/from a text file
- [List your sprint enhancements here]

## Files
| File         | Purpose                                          |
|--------------|--------------------------------------------------|
| main.cpp     | Driver program: menu loop and orchestration     |
| GradedItem.h | Base class for all graded items                 |
| Homework.h   | Derived class - homework items                  |
| Quiz.h       | Derived class - quiz items                      |
| Exam.h       | Derived class - exam items                      |
| USER_GUIDE.md| End-user instructions                           |

## How to Build
Using g++ (Linux / macOS / WSL / MinGW):

    g++ -std=c++17 *.cpp -o GradeCalculator

## How to Run
    ./GradeCalculator        # macOS / Linux
    GradeCalculator.exe      # Windows

## Requirements
- C++17 or newer compiler (g++, clang, or MSVC)

## Course Concepts Demonstrated
Chapters 11-18 of "Fundamentals of Programming C++ (Draft) by Richard L. Halterman, School of Computing, Southern Adventist University, September 25, 2018" plus four UX enhancement sprints (Labs 19-22).
