#pragma once
#include <vector>
#include <string>
#include <iostream>

enum TypeOfSubject {
    practical=3,
    tutorial=2,
    lecture=1
};
struct Class{
    std::string name;
    int classID;
    
};

struct Subject {
    int subjectID;
    std::string name;
    TypeOfSubject type;
};

struct Course {
    int courseID;    
    std::vector<int> subjects;
};  

struct Lecturer {
    int lecturerID;
    std::string name;
    
};

struct sameLecturer {
    std::vector<int> subjects;
};
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
struct Laboratory {
    int labID;
    int roomID;
};

struct classPerWeekOfsubject {
    int classID;
    std::vector<int> classPerWeek;
};

struct Classroom {
    int roomID;
};

struct TimeSlot {
   std::string time;
};





/*
NUM_CLASSES(numClasses) {
        subjectAllocations = new int*[NUM_DAYS];
        roomAllocations = new int*[NUM_DAYS];
        for (int i = 0; i < NUM_DAYS; ++i) {
            subjectAllocations[i] = new int[NUM_SLOTS] ;
            roomAllocations[i] = new int[NUM_SLOTS];
            for (int j = 0; j < NUM_SLOTS; ++j) {
            subjectAllocations[i][j] = -1; 
            roomAllocations[i][j] = -1;
            }
        }
    }

*/
struct ClassSchedule {
    const int NUM_DAYS;
    const int NUM_SLOTS;
    const int NUM_CLASSES;
    int*** subjectAllocations;
    int*** roomAllocations;

    ClassSchedule(int numSlots, int numClasses) : NUM_DAYS(5), NUM_SLOTS(numSlots), NUM_CLASSES(numClasses) {
        subjectAllocations = new int**[NUM_CLASSES];
        roomAllocations = new int**[NUM_CLASSES];
        for (int i = 0; i < NUM_CLASSES; ++i) {
            subjectAllocations[i] = new int*[NUM_DAYS];
            roomAllocations[i] = new int*[NUM_DAYS];
            for (int j = 0; j < NUM_DAYS; ++j) {
                subjectAllocations[i][j] = new int[NUM_SLOTS];
                roomAllocations[i][j] = new int[NUM_SLOTS];
                for (int k = 0; k < NUM_SLOTS; ++k) {
                    subjectAllocations[i][j][k] = -1; 
                    roomAllocations[i][j][k] = -1;
                }
            }
        }
    }

    ~ClassSchedule() {
        for (int i = 0; i < NUM_CLASSES; ++i) {
            for (int j = 0; j < NUM_DAYS; ++j) {
                delete[] subjectAllocations[i][j];
                delete[] roomAllocations[i][j];
            }
            delete[] subjectAllocations[i];
            delete[] roomAllocations[i];
        }
        delete[] subjectAllocations;
        delete[] roomAllocations;

        std::cout << "ClassSchedule deleted" << std::endl;
    }
};