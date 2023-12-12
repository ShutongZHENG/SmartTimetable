#include "Graph.hpp"
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
Graph:: Graph(
        std::vector<Subject> subjects, std::vector<Lecturer> lecturers, std::vector<Course> courses, 
        std::vector<sameLecturer> sameLecturers, std::vector<Laboratory> laboratories, 
        std::vector<classPerWeekOfsubject> classPerWeekOfsubjects, std::vector<Classroom> classrooms, 
        std::vector<TimeSlot> timeSlots
    ){
    //std::vector<Node> nodes;
    //std::vector<Edge> edges;
    for (int i = 0; i < subjects.size(); i++){
        Node node;
        node.nodeID = subjects[i].subjectID;
        node.name = subjects[i].name;
        node.type = subjects[i].type;
        nodes.push_back(node); 
        
        }
    
    for (int i = 0 ; i< sameLecturers.size(); i++){
        for (int j = 0; j < sameLecturers[i].subjects.size(); j++){
            for (int k = j+1; k < sameLecturers[i].subjects.size(); k++){
                Edge edge(sameLecturers[i].subjects[j], sameLecturers[i].subjects[k]);
                edges.push_back(edge);
            }
        }
    }
    
    for (int i = 0; i < classPerWeekOfsubjects.size() ; i++)
    {
        std::vector<int> tmp;
        for (int j = 0; j < classPerWeekOfsubjects[i].classPerWeek.size(); j++)
        {
            if(classPerWeekOfsubjects[i].classPerWeek[j] != 0){
                tmp.push_back(j);
                nodes[j].NoClass = i+1;
                nodes[j].nbOfSubjects = classPerWeekOfsubjects[i].classPerWeek[j];
            }
        }

        for (int j = 0; j < tmp.size(); j++)
        {
            for (int k = j+1; k < tmp.size(); k++)
            {
                Edge edge(tmp[j], tmp[k]);
                edges.push_back(edge);
            }
        }
    
    }

    computeDegree();
    this->classSchedule = new ClassSchedule(timeSlots.size(), classPerWeekOfsubjects.size());
}

void Graph::printGraph()
{
    for (int i = 0; i < nodes.size(); i++)
    {
        std::cout << nodes[i].nodeID << " " << nodes[i].name << " " << nodes[i].degree << " " << nodes[i].type << " " << nodes[i].NoClass << " " << nodes[i].nbOfSubjects << std::endl;

    }
    for (int i = 0; i < edges.size(); i++)
    {
        std::cout << edges[i].getSrc() << " " << edges[i].getDest() << std::endl;
    }

    //classSchedule class subjects room 
   for (int i = 0; i < this->classSchedule->NUM_CLASSES; i++)
   {
       std::cout << "Subjects Class " << i << ": " << std::endl;
       for (int j = 0; j < this->classSchedule->NUM_DAYS; j++)
       {
              for (int k = 0; k < this->classSchedule->NUM_SLOTS; k++)
              {
                std::cout << this->classSchedule->subjectAllocations[i][j][k] << " ";
              }
                std::cout << std::endl;
       }
       std::cout << std::endl;
   }
   
     for (int i = 0; i < this->classSchedule->NUM_CLASSES; i++)
   {
        std::cout << "Room Class " << i << ": " << std::endl;
       for (int j = 0; j < this->classSchedule->NUM_DAYS; j++)
       {
              for (int k = 0; k < this->classSchedule->NUM_SLOTS; k++)
              {
                std::cout << this->classSchedule->roomAllocations[i][j][k] << " ";
              }
                std::cout << std::endl;
       }
       std::cout << std::endl;
   }
  

}


void Graph::computeDegree()
{
    for (int i = 0; i < edges.size(); i++)
    {
        nodes[edges[i].getSrc()].degree++;
        nodes[edges[i].getDest()].degree++;
    }
}
 
bool Graph::compareNodes(const Node& a, const Node& b){
     if(a.degree == b.degree) return a.type > b.type;
    return a.degree > b.degree;
}

void Graph::generateClassSchedule(){
// Trier les nœuds du plus grand au plus petit selon leur degré.
//    std::sort(nodes.begin(), nodes.end(), compareNodes);
 //   while()









}

Graph::~Graph()
{
}