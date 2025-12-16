// ProjectTwo.cpp
// Gary Travis
// ABCU Course Planner - CS 300 Project Two
// All code in a single CPP file, using a binary search tree of Course objects.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <limits>

using namespace std;

// =========================
// Data Structures
// =========================

// Course object to hold course data
struct Course {
    string courseId;                // e.g., "CSCI100"
    string title;                   // e.g., "Introduction to Computer Science"
    vector<string> prerequisites;   // e.g., {"CSCI100", "MATH201"}
};

// Node for the binary search tree
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(const Course& aCourse) {
        course = aCourse;
        left = nullptr;
        right = nullptr;
    }
};

// Binary search tree storing Course objects ordered by courseId
class CourseBST {
private:
    Node* root;

    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    void addNode(Node*& node, const Course& course) {
        if (node == nullptr) {
            node = new Node(course);
            return;
        }

        if (course.courseId < node->course.courseId) {
            addNode(node->left, course);
        }
        else if (course.courseId > node->course.courseId) {
            addNode(node->right, course);
        }
        else {
            // Duplicate courseId; overwrite data (or ignore if preferred)
            node->course = course;
        }
    }

    void inOrder(Node* node) const {
        if (node == nullptr) {
            return;
        }
        inOrder(node->left);
        cout << node->course.courseId << ", " << node->course.title << endl;
        inOrder(node->right);
    }

    Node* search(Node* node, const string& courseId) const {
        if (node == nullptr) {
            return nullptr;
        }

        if (courseId == node->course.courseId) {
            return node;
        }

        if (courseId < node->course.courseId) {
            return search(node->left, courseId);
        }
        else {
            return search(node->right, courseId);
        }
    }

public:
    CourseBST() {
        root = nullptr;
    }

    ~CourseBST() {
        destroyTree(root);
        root = nullptr;
    }

    void Clear() {
        destroyTree(root);
        root = nullptr;
    }

    void Insert(const Course& course) {
        addNode(root, course);
    }

    // Print all courses in alphanumeric order
    void PrintCourseList() const {
        if (root == nullptr) {
            cout << "No courses loaded. Please load the data structure first." << endl;
            return;
        }
        cout << "Here is a sample schedule:" << endl;
        inOrder(root);
    }

    // Return pointer to the course node; nullptr if not found
    const Course* FindCourse(const string& courseId) const {
        Node* node = search(root, courseId);
        if (node == nullptr) {
            return nullptr;
        }
        return &(node->course);
    }
};

// =========================
// Helper Functions
// =========================

// Trim leading and trailing whitespace from a string
string trim(const string& s) {
    size_t start = 0;
    while (start < s.size() && isspace(static_cast<unsigned char>(s[start]))) {
        ++start;
    }

    if (start == s.size()) {
        return "";
    }

    size_t end = s.size() - 1;
    while (end > start && isspace(static_cast<unsigned char>(s[end]))) {
        --end;
    }

    return s.substr(start, end - start + 1);
}

// Convert a string to uppercase (for case-insensitive course input)
string toUpper(const string& s) {
    string result = s;
    for (char& c : result) {
        c = static_cast<char>(toupper(static_cast<unsigned char>(c)));
    }
    return result;
}

// Load course data from CSV file into the BST
bool LoadCoursesFromFile(const string& fileName, CourseBST& courseTree) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error: Could not open file \"" << fileName << "\"." << endl;
        return false;
    }

    courseTree.Clear();

    string line;
    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        string token;

        Course course;

        // First token: course number
        if (!getline(ss, token, ',')) {
            continue; // malformed line
        }
        course.courseId = trim(token);

        // Second token: course title
        if (!getline(ss, token, ',')) {
            continue; // malformed line (no title)
        }
        course.title = trim(token);

        // Remaining tokens: prerequisites (0 or more)
        while (getline(ss, token, ',')) {
            string prereq = trim(token);
            if (!prereq.empty()) {
                course.prerequisites.push_back(prereq);
            }
        }

        // Insert course into the tree
        courseTree.Insert(course);
    }

    file.close();
    cout << "Data structure loaded successfully." << endl;
    return true;
}

// Print detailed information for a specific course
void PrintCourseInformation(const CourseBST& courseTree, const string& courseIdInput) {
    string courseId = toUpper(courseIdInput);

    const Course* course = courseTree.FindCourse(courseId);
    if (course == nullptr) {
        cout << "Course " << courseId << " not found." << endl;
        return;
    }

    cout << course->courseId << ", " << course->title << endl;

    if (course->prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
        return;
    }

    cout << "Prerequisites: ";
    for (size_t i = 0; i < course->prerequisites.size(); ++i) {
        string prereqId = course->prerequisites[i];
        const Course* prereqCourse = courseTree.FindCourse(prereqId);

        cout << prereqId;
        if (prereqCourse != nullptr) {
            cout << " (" << prereqCourse->title << ")";
        }

        if (i + 1 < course->prerequisites.size()) {
            cout << ", ";
        }
    }
    cout << endl;
}

// =========================
// Main Menu / Program
// =========================

void PrintMenu() {
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
    cout << "What would you like to do? ";
}

int main() {
    CourseBST courseTree;
    bool dataLoaded = false;
    bool running = true;

    cout << "Welcome to the course planner." << endl;

    while (running) {
        int choice;
        PrintMenu();

        if (!(cin >> choice)) {
            // Handle non-numeric input
            cin.clear();
            string badInput;
            getline(cin, badInput); // discard invalid input
            cout << "Invalid input. Please enter a number from the menu." << endl;
            continue;
        }

        // Clear newline left in stream for subsequent getline calls
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1: {
            string fileName;
            cout << "Enter the file name to load: ";
            getline(cin, fileName);
            fileName = trim(fileName);

            if (fileName.empty()) {
                cout << "File name cannot be empty." << endl;
                break;
            }

            if (LoadCoursesFromFile(fileName, courseTree)) {
                dataLoaded = true;
            }
            break;
        }

        case 2:
            if (!dataLoaded) {
                cout << "Please load the data structure first (option 1)." << endl;
            }
            else {
                courseTree.PrintCourseList();
            }
            break;

        case 3: {
            if (!dataLoaded) {
                cout << "Please load the data structure first (option 1)." << endl;
                break;
            }

            string courseId;
            cout << "What course do you want to know about? ";
            getline(cin, courseId);
            courseId = trim(courseId);

            if (courseId.empty()) {
                cout << "Course ID cannot be empty." << endl;
                break;
            }

            PrintCourseInformation(courseTree, courseId);
            break;
        }

        case 9:
            cout << "Thank you for using the course planner!" << endl;
            running = false;
            break;

        default:
            cout << choice << " is not a valid option." << endl;
            break;
        }

        if (running) {
            cout << endl;
        }
    }

    return 0;
}
