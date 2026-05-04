# User Guide: Grade Calculator

## Introduction
The Grade Calculator is a C++ console application designed for students and educators to manage grades for Homework, Quizzes, and Exams. It allows users to create customized grading schemes and calculate both points-based and weighted final grades.

## Getting Started
To run the program, first compile the source code using the instructions provided in the README. Once compiled, you can start the program by executing the `GradeCalculator` binary.

## Menu Walkthrough
### 1. Set Grading Scheme
- **Function:** Define or update the weights and letter-grade cutoffs for Homework, Quizzes, and Exams.
- **Input:** Weights for Homework (%), Quizzes (%), and Exams (%).
- **Data Type:** Floats; the total must be 100%.
- **Constraints:** Each input must be a valid number. Total weights must sum to 100%.

### 2. Add Graded Item
- **Function:** Add new items to the grade tracker.
- **Input:** Category (1 for Homework, 2 for Quiz, 3 for Exam), Name, Points possible, Points earned.
- **Data Type:** Integer for category; strings for name; floats for points.
- **Constraints:** Earned points cannot exceed possible points.

### 3. View All Items
- **Function:** Display a list of all graded items.
- **Input:** None.
- **Output:** Table format showing name, category, points, and percentage.

### 4. Remove Item
- **Function:** Remove a specific graded item from the list.
- **Input:** Item number.
- **Data Type:** Integer.
- **Constraints:** Valid item number required.

### 5. Calculate Grade (Points-Based)
- **Function:** Calculate the overall grade based on total points earned and possible.
- **Input:** None.
- **Output:** Percentage and letter grade.

### 6. Calculate Grade (Weighted)
- **Function:** Calculate the final grade using weighted averages according to the grading scheme.
- **Input:** None.
- **Output:** Weighted percentage and letter grade.

### 7. Filter Items by Category
- **Function:** Show items only from a specified category.
- **Input:** Category (Homework, Quiz, Exam).
- **Data Type:** String.

### 8. Count Items by Category
- **Function:** Count and display the number of items in each category.
- **Input:** None.
- **Output:** Count of items per category.

### 9. Save Grading Scheme
- **Function:** Save the current grading scheme.
- **Input:** Scheme name.
- **Data Type:** String.

### 10. Load Grading Scheme
- **Function:** Load a previously saved grading scheme.
- **Input:** Scheme name.
- **Data Type:** String.

### 0. Exit
- **Function:** Gracefully exit the application.

## Sample Session
```plaintext
Enter choice: 1
Enter weight for Homework (%): 20
Enter weight for Quizzes (%): 30
Enter weight for Exams (%): 50
Weights saved!

Enter choice: 2
Select category: 
1. Homework
2. Quiz
3. Exam
Choice: 1
Name: Homework 1
Points possible: 100
Points earned: 85
Item added!

Enter choice: 3
# | Name        | Category   |   Earned |  Possible |   Percent
--------------------------------------------------------------
1 | Homework 1  | Homework   |  85      |  100      |  85.0%

Enter choice: 5
Total Earned: 85 / 100
Overall: 85.0%
Letter Grade: B

Sprint Features
Input Validation with Exceptions
Auto-invoked: Ensures valid numeric inputs.
Count Items by Category
Access: Menu option 8 — view counts.
Save and Load Grading Schemes
Access: Save (option 9), Load (option 10).
Range-Based Loops and auto Usage
Integration: Enhances code clarity and performance.
Understanding Your Results
Points-Based Grading: Direct total points comparison.
Weighted Grading: Uses category weights for nuanced evaluation.
Known Limitations
Incorrect numeric inputs may require re-entry.
Unsaved data isn't retained after exiting.
Troubleshooting
Invalid Input: Re-enter valid numbers when prompted.
Total Weights Incorrect: Ensure weights sum to 100% before saving.
