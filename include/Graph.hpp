#pragma once
#include "DataStructures.hpp"
class Edge{
    private:
        int src, dest;
    public:
        Edge(int src, int dest){
            this->src = src;
            this->dest = dest;
        }
        int getSrc(){
            return this->src;
        }
        int getDest(){
            return this->dest;
        }
};

struct Node
{
   bool isSelected = false;
   int degree = 0;
   int nodeID;
   int nbOfSubjects = 0;
   int NoClass = 0;
   int NoLecturer = -1;
   
   std::string name;
   TypeOfSubject type;
};

class Graph
{
private:
    /* data */
     std::vector<Node> nodes;
     std::vector<Edge> edges;
     std::vector<int> labRooms;
     std::vector<int> Rooms;
     ClassSchedule* classSchedule;
     std::vector<sameLecturer> sameLecturers;

private:
    void computeDegree();
    static bool compareNodes(const Node& a, const Node& b);
    std::vector<int> findSameLecturerSubjects(const int& subjectID);
    std::vector<int> findRoomDaySlot(const TypeOfSubject& typeOfSubject , const int& noClass, const std::pair<int, int>& DaySlot, const std::vector<int>& sameLecturerSubjects);
public:
    Graph(
        std::vector<Subject> subjects, std::vector<Lecturer> lecturers, std::vector<Course> courses, std::vector<sameLecturer> sameLecturers, 
        std::vector<Laboratory> laboratories, std::vector<classPerWeekOfsubject> classPerWeekOfsubjects, std::vector<Classroom> classrooms, std::vector<TimeSlot> timeSlots
    );
    void generateClassSchedule();
    void printGraph();
    ~Graph();

};
