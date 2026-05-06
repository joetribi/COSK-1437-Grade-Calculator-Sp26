/*
 * Grade Calculator (OOP Edition) — Final Project
 * Author: Alexander Sjogreen
 * Course: COSC 1437, Spring 2026
 *
 * Concepts Demonstrated (Chapters 11-18 + Sprints 19-22)
 * ------------------------------------------------------
 * Ch 11 - Foundation from COSC 1436: std::vector, control flow, modular code
 * Ch 12 - <algorithm>: [name what you used, e.g., std::sort by percentage]
 * Ch 13 - <fstream> file I/O: saveGrades() / loadGrades() to "grades.txt"
 * Ch 14 - User-defined class: GradedItem with private fields + getters
 * Ch 15 - Object refinement: parameterized constructor, getPercentage(), encapsulation
 * Ch 16 - Menu-driven UI: switch statement, <iomanip> formatting, helper functions
 * Ch 17 - Inheritance + polymorphism: Homework / Quiz / Exam derive from GradedItem
 * Ch 18 - Smart pointers: std::vector<std::unique_ptr<GradedItem>>; GradingScheme struct
 *
 * Sprint 19 - Input validation with exceptions: Robust user input management by handling and rejecting non-numeric inputs
 * Sprint 20 - Count items by category: Added functionality to count and display the number of items in each category for better organization and tracking
 * Sprint 21 - Save and load grading schemes: Introduced flexibility to save different grading schemes and reload them as needed
 * Sprint 22 - Range-based loops and 'auto': Enhanced code clarity and performance using range-based loops and the 'auto' keyword
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <memory>
#include <string>
#include <limits>
#include <map>
#include <unordered_map>
#include "GradedItem.h"
#include "Homework.h"
#include "Quiz.h"
#include "Exam.h"

using namespace std;

struct GradingScheme {
    float homeworkWeight = 0.20f;
    float quizWeight = 0.30f;
    float examWeight = 0.50f;
    float cutoffA = 90.0f;
    float cutoffB = 80.0f;
    float cutoffC = 70.0f;
    float cutoffD = 60.0f;
};

void displayHeader(const string& title) {
    const string reset = "\033[0m";  // Reset color
    const string color = "\033[1;32m"; // Bold green text

    cout << "\n" << string(50, '=') << '\n';
    cout << color << "  " << title << reset << '\n'; // Apply color
    cout << string(50, '=') << '\n';
}

void displaySeparator() {
    cout << string(50, '-') << '\n';
}

float readFloat(const string& prompt) {
    float value;
    while (true) {
        try {
            cout << prompt;
            cin >> value;
            if (cin.fail()) {
                throw invalid_argument("Invalid input. Please enter a number.");
            }
            return value; // Return value if valid
        }
        catch (const invalid_argument& e) {
            cout << e.what() <<" Please enter numeric value. " << '\n';
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
        }
    }
}

void displayMenu() {
    displayHeader("GRADE CALCULATOR - MAIN MENU");
    cout << "1. Set Grading Scheme\n";
    cout << "2. Add Graded Item\n";
    cout << "3. View All Items\n";
    cout << "4. Remove Item\n";
    cout << "5. Calculate Grade (Points-Based)\n";
    cout << "6. Calculate Grade (Weighted)\n";
    cout << "7. Filter Items by Category\n";
    cout << "8. Count Items by Category\n";
    cout << "9. Save Grading Scheme\n";
    cout << "10. Load Grading Scheme\n";
    cout << "0. Exit\n";
    displaySeparator();
}

char getLetterGrade(float percentage, const GradingScheme& scheme) {
    if (percentage >= scheme.cutoffA) return 'A';
    if (percentage >= scheme.cutoffB) return 'B';
    if (percentage >= scheme.cutoffC) return 'C';
    if (percentage >= scheme.cutoffD) return 'D';
    return 'F';
}

void setGradingScheme(GradingScheme& scheme) {
    displayHeader("SET GRADING SCHEME");

    float hw = readFloat("Enter weight for Homework (%): ");
    float qz = readFloat("Enter weight for Quizzes (%): ");
    float ex = readFloat("Enter weight for Exams (%): ");

    float total = hw + qz + ex;
    if (total != 100.0f) {
        cout << "Weights must sum to 100%. Got " << total << "%. Try again.\n";
        return;
    }

    scheme.homeworkWeight = hw / 100.0f;
    scheme.quizWeight = qz / 100.0f;
    scheme.examWeight = ex / 100.0f;
    cout << "Weights saved!\n";
    // Similar changes for grade cutoffs using readFloat
}

void addGradedItem(vector<unique_ptr<GradedItem>>& items) {
    displayHeader("ADD GRADED ITEM");

    cout << "Select category:\n";
    cout << "1. Homework\n";
    cout << "2. Quiz\n";
    cout << "3. Exam\n";
    cout << "Choice: ";

    int category;
    cin >> category;
    cin.ignore();  // ignore leftover newline

    cout << "Name: ";
    string name;
    getline(cin, name);

    float possible = readFloat("Points possible: ");
    float earned = readFloat("Points earned: ");

    if (earned < 0 || earned > possible) {
        cout << "Points earned cannot exceed points possible.\n";
        return;
    }

    switch (category) {
        case 1:
            items.push_back(make_unique<Homework>(name, earned, possible));
            break;
        case 2:
            items.push_back(make_unique<Quiz>(name, earned, possible));
            break;
        case 3:
            items.push_back(make_unique<Exam>(name, earned, possible));
            break;
        default:
            cout << "Invalid category.\n";
            return;
    }
    cout << "Item added!\n";
}

void viewItems(const vector<unique_ptr<GradedItem>>& items) {
    displayHeader("ALL GRADED ITEMS");
    if (items.empty()) {
        cout << "No items entered yet.\n";
        return;
    }
    cout << left << setw(5) << "#"
         << setw(20) << "Name"
         << setw(12) << "Category"
         << right << setw(10) << "Earned"
         << setw(10) << "Possible"
         << setw(10) << "Percent" << '\n';
    displaySeparator();
    cout << fixed << setprecision(1);
    for (size_t i = 0; i < items.size(); ++i) {
        cout << left << setw(5) << (i + 1)
             << setw(20) << items[i]->getName()
             << setw(12) << items[i]->getCategory()
             << right << setw(10) << items[i]->getPointsEarned()
             << setw(10) << items[i]->getPointsPossible()
             << setw(9) << items[i]->getPercentage() << "%\n";
    }
}

void removeItem(vector<unique_ptr<GradedItem>>& items) {
    displayHeader("REMOVE ITEM");
    if (items.empty()) {
        cout << "No items to remove.\n";
        return;
    }
    for (size_t i = 0; i < items.size(); ++i) {
        cout << (i + 1) << ". " << items[i]->getCategory()
             << " - " << items[i]->getName() << '\n';
    }
    cout << "Enter item number to remove (0 to cancel): ";
    int index;
    cin >> index;

    if (index < 1 || index > static_cast<int>(items.size())) {
        cout << "Cancelled.\n";
        return;
    }
    cout << "Removed: " << items[index - 1]->getName() << '\n';
    items.erase(items.begin() + (index - 1));
}

void calculatePointsBased(const vector<unique_ptr<GradedItem>>& items,
                           const GradingScheme& scheme) {
    displayHeader("POINTS-BASED GRADE");
    if (items.empty()) {
        cout << "No items to calculate.\n";
        return;
    }

    float totalEarned = 0, totalPossible = 0;
    for (const auto& item : items) {
        totalEarned += item->getPointsEarned();
        totalPossible += item->getPointsPossible();
    }

    float percentage = (totalPossible > 0) ? (totalEarned / totalPossible) * 100 : 0;

    cout << fixed << setprecision(1);
    cout << "Total Earned: " << totalEarned << " / " << totalPossible << '\n';
    cout << "Overall: " << percentage << "%\n";
    cout << "Letter Grade: " << getLetterGrade(percentage, scheme) << '\n';
}



void calculateWeighted(const vector<unique_ptr<GradedItem>>& items, const GradingScheme& scheme) {
    displayHeader("WEIGHTED GRADE CALCULATION");
    if (items.empty()) {
        cout << "No items to calculate.\n";
        return;
    }

    auto categoryAvg = [&](const string& category) {
        float total = 0;
        int count = 0;
        for (const auto& item : items) {
            if (item->getCategory() == category) {
                total += item->getPercentage();
                count++;
            }
        }
        return count > 0 ? total / count : 0;
    };

    float hwAvg = categoryAvg("Homework");
    float quizAvg = categoryAvg("Quiz");
    float examAvg = categoryAvg("Exam");

    float finalGrade = (hwAvg * scheme.homeworkWeight)
                     + (quizAvg * scheme.quizWeight)
                     + (examAvg * scheme.examWeight);

    cout << fixed << setprecision(1);
    cout << "Homework Average:  " << hwAvg << "% (" << (scheme.homeworkWeight * 100) << "% weight)\n";
    cout << "Quiz Average:      " << quizAvg << "% (" << (scheme.quizWeight * 100) << "% weight)\n";
    cout << "Exam Average:      " << examAvg << "% (" << (scheme.examWeight * 100) << "% weight)\n";
    cout << "\nFinal Weighted Grade: " << finalGrade << "%\n";
    cout << "Letter Grade: " << getLetterGrade(finalGrade, scheme) << '\n';
}

void filterItemsByCategory(const vector<unique_ptr<GradedItem>>& items, const string& category) {
    displayHeader("FILTERED ITEMS");
    if (items.empty()) {
        cout << "No items to display.\n";
        return;
    }

    // Lambda function to print items of a specific category
    auto printCategory = [&](const string& cat) {
        bool found = false;
        for (const auto& item : items) {
            if (item->getCategory() == cat) {
                cout << left << setw(20) << item->getName();
                cout << right << setw(10) << item->getPointsEarned();
                cout << setw(10) << item->getPointsPossible();
                cout << setw(10) << item->getPercentage() << "%\n";
                found = true;
            }
        }
        if (!found) {
            cout << "No items found in category: " << cat << "\n";
        }
    };

    printCategory(category);
}

void countItemsByCategory(const vector<unique_ptr<GradedItem>>& items) {
    map<string, int> categoryCount;
    for (const auto& item : items) {
        categoryCount[item->getCategory()]++;
    }

    displayHeader("ITEM COUNT BY CATEGORY");
    for (const auto& category : categoryCount) {
        cout << category.first << ": " << category.second << '\n';
    }
    if (categoryCount.empty()) {
        cout << "No items to count.\n";
    }
}

void saveGradingScheme(const GradingScheme& scheme, const string& name, unordered_map<string, GradingScheme>& schemes) {
    schemes[name] = scheme;
    cout << "Scheme '" << name << "' saved!\n";
}

void loadGradingScheme(GradingScheme& scheme, const string& name, const unordered_map<string, GradingScheme>& schemes) {
    auto it = schemes.find(name);
    if (it != schemes.end()) {
        scheme = it->second;
        cout << "Scheme '" << name << "' loaded!\n";
    } else {
        cout << "Scheme '" << name << "' not found.\n";
    }
}

int main() {
    GradingScheme scheme;
    vector<unique_ptr<GradedItem>> items;
    unordered_map<string, GradingScheme> schemes;

    int choice = 0;
    do {
        displayMenu();
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: setGradingScheme(scheme); break;
            case 2: addGradedItem(items); break;
            case 3: viewItems(items); break;
            case 4: removeItem(items); break;
            case 5: calculatePointsBased(items, scheme); break;
            case 6: calculateWeighted(items, scheme); break;
            case 7: {
                cout << "Enter category to filter (Homework/Quiz/Exam): ";
                string category;
                cin >> category;
                filterItemsByCategory(items, category);
                break;
            }
            case 8: countItemsByCategory(items); break;
            case 9: {
                cout << "Enter scheme name to save: ";
                string name;
                cin >> name;
                saveGradingScheme(scheme, name, schemes);
                break;
            }
            case 10: {
                cout << "Enter scheme name to load: ";
                string name;
                cin >> name;
                loadGradingScheme(scheme, name, schemes);
                break;
            }
            case 0:
                displayHeader("GOODBYE");
                cout << "Thank you for using Grade Calculator!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
