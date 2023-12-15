#include <iostream>
#include <vector>
#include "DataStructures.hpp"
#include "Graph.hpp"
using namespace std;

int main(int, char**){
   
    vector<TimeSlot> timeSlots = {TimeSlot{"T1"}, TimeSlot{"T2"}, TimeSlot{"T3"}, TimeSlot{"T4"}, TimeSlot{"T5"}, TimeSlot{"T6"} };
    
    vector<Subject> subjects = {
        Subject{1, "Math1", lecture}, Subject{2, "Math2", lecture}, Subject{3, "Math3", practical}, 
        Subject{4, "Physics1", lecture}, Subject{5, "Physics2", lecture}, Subject{6, "Physics3", practical},
        Subject{7, "Chemistry1", lecture}, Subject{8, "Chemistry2", lecture}, Subject{9, "Chemistry3", practical}, 
        Subject{10, "Biology1", lecture}, Subject{11, "Biology2", lecture}, Subject{12, "Biology3", practical},
        Subject{13, "English1", lecture}, Subject{14, "English2", practical}, Subject{15, "English3", practical}, 
        Subject{16, "History1", lecture}, Subject{17, "History2", practical}, Subject{18, "History3", practical}
    };
    
    vector<Lecturer> lecturers = {
        Lecturer{1, "Tom"}, Lecturer{2, "Jerry"}, Lecturer{3, "Donald"}, 
        Lecturer{4, "Mickey"}, Lecturer{5, "Minnie"}, Lecturer{6, "Daisy"},
        Lecturer{7, "Goofy"}, Lecturer{8, "Pluto"}, Lecturer{9, "Huey"}, 
        Lecturer{10, "Dewey"}, Lecturer{11, "Louie"}, Lecturer{12, "Scrooge"},
        Lecturer{13, "Chip"}, Lecturer{14, "Dale"}
        };

    vector<Classroom> classrooms = {Classroom{1}, Classroom{2}, Classroom{3}, Classroom{4}, Classroom{5}, Classroom{6} };
    
    vector<Laboratory> laboratories = {Laboratory{1, 4}};
    
    vector<Course> courses = {
        Course{1, {1, 2, 3}}, Course{2, {4, 5, 6}}, Course{3, {7, 8, 9}},
        Course{4, {10, 11, 12}}, Course{5, {13, 14, 15}}, Course{6, {16, 17, 18}}
    };
    
    vector<sameLecturer> sameLecturers = {
        sameLecturer{{1,10}}, sameLecturer{{7,16}},
        sameLecturer{{4, 13}}, sameLecturer{{9,18}}
    };

    vector<classPerWeekOfsubject> classPerWeekOfsubjects = {
        classPerWeekOfsubject{1, {2,2,2,2,2,3,3,3,1,0,0,0,0,0,0,0,0,0}},
        classPerWeekOfsubject{2, {0,0,0,0,0,0,0,0,0,2,2,2,2,3,3,3,3,1}}

    };

    Graph graph(subjects, lecturers, courses, sameLecturers, laboratories, classPerWeekOfsubjects, classrooms, timeSlots);
    
   graph.printGraph();
    
    graph.generateClassSchedule();

    graph.printGraph();
    return 0;

}
