// Name:    ABCUProjectTwo.cpp
// Author:  Arica Bryant
// Course:  CS-300
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Course.h";

using namespace std;


// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a course
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};

// Class containing data members and methods to implement a binary search tree
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);

public:
    BinarySearchTree();
    void InOrder();
    void Insert(Course course);
    Course Search(string courseId);
};

// Default constructor
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

// Traverses the tree in order
void BinarySearchTree::InOrder() {
    this->inOrder(root);
}

// Insert a Course
void BinarySearchTree::Insert(Course course) {
    if (root == nullptr) {
        root = new Node(course);
    }

    else {
        this->addNode(root, course);
    }
}

// Searches for a course
Course BinarySearchTree::Search(string courseId) {
    Node* current = root;

    // Keep looping downwards until bottom reached or matching courseId found
    while (current != nullptr) {
        // If match found, return current course
        if (current->course.getCourseId().compare(courseId) == 0) {
            return current->course;
        }

        // UPDATED: If course is smaller than current node then traverse left
        else if (courseId.compare(current->course.getCourseId()) < 0) {
            current = current->left;
        }
        // UPDATED: Else course is larger so traverse right
        else {
            current = current->right;
        }
    }

    Course course;
    return course;
}

void BinarySearchTree::addNode(Node* node, Course course) {
    // If node is larger then add to left
    if (node->course.getCourseId().compare(course.getCourseId()) > 0) {
        // If no left node
        if (node->left == nullptr) {
            // This node becomes left
            node->left = new Node(course);
        }
        // Else recurse down the left node
        else {
            this->addNode(node->left, course);
        }
    }

    else {
        // If no right node
        if (node->right == nullptr) {
            // This node becomes right
            node->right = new Node(course);
        }
        // Else recurse down the right node
        else {
            this->addNode(node->right, course);
        }
    }
}

// Traverse and outputs courses in order
void BinarySearchTree::inOrder(Node* node) {
    //If node is not equal to null ptr
    if (node != nullptr) {
        // InOrder not left
        inOrder(node->left);
        // Output courseID, title, prerequisites
        cout << node->course.getCourseId() << "," << node->course.getCourseTitle() << endl;
        // InOder right
        inOrder(node->right);
    }
}

// Displays specific course information
void displayCourse(Course course) {
    vector<string> coursePrereqs = course.getCoursePrereqs();
    string prereqs;

    // Checks course to determine whether there are prerequisites
    if (coursePrereqs.size() == 1) { // If there is only 1 prereq
        prereqs = course.getCoursePrereqs()[0];
    }

    else if (coursePrereqs.size() > 1) { // If there are multiple prereqs
        for (int i = 0; i < coursePrereqs.size() - 1; ++i) {
            prereqs += coursePrereqs[i] + ", ";
        }
        prereqs += coursePrereqs.back();
    }

    else {
        prereqs = "none";
    }

    // Displays course information to the console
    cout << course.getCourseId() << ", " << course.getCourseTitle() << endl;
    cout << "Prerequisites: " << prereqs << endl;

    return;
}

// Method for opening and reading data from the courses.txt file
void loadCourses(string inputFile, BinarySearchTree* bst) {
    ifstream file(inputFile);
    string current;

    // If block used for testing if the file is opened successfully
    if (!file.is_open()) {
        cerr << "File not opened successfully" << endl;
        return;
    }

    // Reads contents of text file a, creates course objects, and inserts into Binary Search Tree
    while (std::getline(file, current)) {
    stringstream ss(current);
    string substr, id, title;
    vector<string> prerequisites;
    int index = 0;

        while (!ss.eof()) {
        getline(ss, substr, ',');
            if (index == 0) {
                id = substr;
            }
            else if (index == 1) {
                title = substr;
            }
            else {
                prerequisites.push_back(substr);
            }
            index++;
        }
        Course course = Course(id, title, prerequisites);
        bst->Insert(course);
    }
    cout << "Courses loaded successfully!" << endl;

    file.close();
}

// The main() method
int main()
{
    // User input variables
    string fileInput, courseKey;

    // Defines a binary search tree to hold all courses
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course course;
    

    cout << "Welcome to the course planner." << endl;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Course" << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do?" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            // Calls method for loading the data structure
            cout << "Please enter the full name of the text file:" << endl;
            cin >> fileInput;
            loadCourses(fileInput, bst);
            break;

        case 2:
            // Calls method to print course list in alphanumerical order
            cout << "Here is a sample schedule:" << endl;
            bst->InOrder();
            break;

        case 3:
            // Calls method that prints out one specific course
            cout << "Please enter the course ID you wish to search for" << endl;
            cin >> courseKey;
            course = bst->Search(courseKey);

            if (!course.getCourseId().empty()) {
                displayCourse(course);
            }

            else {
                cout << "Course Id " << courseKey << " not found." << endl;
            }
            break;

        case 9:
            // Exits the program
            cout << "Thank your for using the Course Planner!" << endl;
            break;

        default:
            // Catches any incorrect choices and outputs error message
            cout << "Sorry. " << choice << " is not a valid option. Please try again." << endl;
            cin.clear();
            break;
        }

    }
}

