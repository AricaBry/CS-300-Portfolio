// Name:    ABCUProjectTwo.cpp
// Author:  Arica Bryant
// Course:  CS-300
// Description: CPP and H Class files containing data members and methods to implement a Course object
//

#include "Course.h"
#include <iostream>
#include <string>
#include <vector>

// Default constructor
Course::Course() {
	courseId = "";
	courseTitle = "";
	coursePrereqs;
}

Course::Course(string id, string title, vector<string> prereqs) {
	this->courseId = id;
	this->courseTitle = title;
	this->coursePrereqs = prereqs;
}

// Getters
string Course::getCourseId() {
	return this->courseId;
}

string Course::getCourseTitle() {
	return this->courseTitle;
}

vector<string> Course::getCoursePrereqs() {
	return this->coursePrereqs;
}