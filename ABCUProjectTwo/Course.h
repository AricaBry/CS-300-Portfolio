// Name:    ABCUProjectTwo.cpp
// Author:  Arica Bryant
// Course:  CS-300
//

#pragma once
#ifndef ABCUPROJECTTWO_COURSE_H_
#define ABCUPROJECTTWO_COURSE_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Course Class for handling Course objects
class Course {
    // Defining public fields for the course object
public:
    Course();
    Course(string id, string title, vector<string> prereqs);
    string getCourseId();
    string getCourseTitle();
    vector<string> getCoursePrereqs();

    // Defining private fields for the course object
private:
    string courseId;
    string courseTitle;
    vector<string> coursePrereqs;
};

#endif //ABCUPROJECTTWO_COURSE_H_