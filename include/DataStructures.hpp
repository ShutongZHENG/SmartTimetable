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



struct ClassSchedule {
    const int NUM_DAYS;
    const int NUM_SLOTS;
    const int NUM_CLASSES;
    int*** subjectAllocations; //list of 
    int*** roomAllocations;

    //constructor sur struct classSchedule
    //pour initaliser  les tableaux de 3D


    
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

 std::pair<int, int> findAvailableSlot(const int& classNumber) {
    if (classNumber >= NUM_CLASSES || classNumber < 0) {
        throw std::invalid_argument("Invalid class number");
    }

    for (int day = NUM_DAYS - 1; day >= 0; --day) {
        for (int slot = NUM_SLOTS - 1; slot >= 0; --slot) {
            if (subjectAllocations[classNumber][day][slot] == -1 && roomAllocations[classNumber][day][slot] == -1) {
                int preDay = (slot == 0 && day > 0) ? day - 1 : day;
                int preSlot = (slot == 0 && day > 0) ? NUM_SLOTS - 1 : (slot > 0 ? slot - 1 : 0);

                if (day > 0 || slot > 0) { 
                    if (subjectAllocations[classNumber][preDay][preSlot] != -1 && roomAllocations[classNumber][preDay][preSlot] != -1) {
                        return {day, slot};
                    }
                } else {
                    return {0, 0};
            }
        }
    }
    }
    return {-1, -1};
}
    



                        

//


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