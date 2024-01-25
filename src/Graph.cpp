#include "Graph.hpp"
#include <iostream>
#include <algorithm>
#include <queue>
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
        this->sameLecturers = sameLecturers;
        //  if node.nodeID exist in sameLecturers[i].subjects

        for (int j = 0; j < sameLecturers.size(); j++)
        {
            for (int k = 0; k < sameLecturers[j].subjects.size(); k++)
            {
                if (node.nodeID == sameLecturers[j].subjects[k])
                {
                    node.NoLecturer = j+1;
                }
                
            }
            
        }

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
    for (int i = 0; i < laboratories.size(); i++)
    {
        labRooms.push_back(laboratories[i].roomID);
    }

    for (int i = 0; i < classrooms.size(); i++)
    {
        Rooms.push_back(classrooms[i].roomID);
    }

    computeDegree();
    this->classSchedule = new ClassSchedule(timeSlots.size(), classPerWeekOfsubjects.size());
}

void Graph::printGraph()
{
    for (int i = 0; i < nodes.size(); i++)
    {
        std::cout << nodes[i].nodeID << " " << nodes[i].name << " " << nodes[i].degree << " " << nodes[i].type << "  No Class: " << nodes[i].NoClass 
        << " " << nodes[i].nbOfSubjects << " NoLecturer: " << nodes[i].NoLecturer << std::endl;

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
                if(this->classSchedule->roomAllocations[i][j][k] == -1) std::cout << "-1 ";
                else
                std::cout << "R" <<this->classSchedule->roomAllocations[i][j][k] << " ";
              }
                std::cout << std::endl;
       }
       std::cout << std::endl;
   }
  

}
// chaque node(suject), on a ID, le prof, No class, temps, room. (the base of Degree)
// si les cours ont le meme prof, on doit augmenter le degree pour ces cours.  le cours "Phy" a Porf A , et le cours "Math" a aussi prof A. 
// les nodes de "phy" et "Math " doit agumenter leurs degree. (+1) 
// les cours de class 1  <-----constraint -----> les cours de class 2. // Dans les graphe, c'est  les edges
// un cours pour les autres cours( meme class ). c'est aussi un constraint. parce que,  le meme temps, on just peut suivi un cours .
// si les nodes a meme degree, on doit chosisir les TypeOfSubject (practical > lecture), c'est a dire. le degree de node va agmenter. (practical +3, lecture +1, tutorial +2)

// on doir tire les list de nodes selon le degree. (max to min). c'est just pour les cours


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
    std::sort(nodes.begin(), nodes.end(), compareNodes);
    std::cout << "Sorted nodes" << std::endl;
    printGraph();
    std::queue<Node> nodeQueue;
    for (int i = 0; i < nodes.size(); i++)
    {
        for (int j = 0; j < nodes[i].nbOfSubjects; j++)
        {
            nodeQueue.push(nodes[i]);
        }
        

    }
 


    while (!nodeQueue.empty() )
    {

        Node node = nodeQueue.front();
        int NoClass = node.NoClass-1;
        int NoLecturer = node.NoLecturer;
        TypeOfSubject type = node.type;
        int nodeID = node.nodeID;

        //      找到空闲的时间，找到时间表中的不是-1的slot。如果都是-1，就找第一个-1为当前时间
        //      然后判断这个时间 没有没房间可用（需要循环其他房间表）比如 roomAllocations[1][1][1] == -1 roomAllocations[2][1][1] == -1
        //      如果没有房间可用，就找下一个时间 直到有房间可用 （需要循环其他房间表）
        //      如果有房间可用，再查看这个时间段老师是不是空闲的 需要循环其他课程表。如果不空闲，则找下一个时间。
        

        std::pair<int, int> availableSlot = this->classSchedule->findAvailableSlot(NoClass);
 
        if(availableSlot.first == -1 && availableSlot.second == -1){
                std::cout << "No available slot for subject " << nodeID << std::endl;
                nodeQueue.pop();
                break;
        }
       
        
        
     
        std::vector<int> sameLecturerSubjects = findSameLecturerSubjects(nodeID);
        std::vector<int> roomDaySlot = findRoomDaySlot(type, NoClass, availableSlot, sameLecturerSubjects);
        int room = roomDaySlot[0];
        int day = roomDaySlot[1];
        int slot = roomDaySlot[2];
        if(room == -1){
            std::cout << "No available room for subject " << nodeID << std::endl;
            nodeQueue.pop();
            break;
        }

        this->classSchedule->subjectAllocations[NoClass][day][slot] = nodeID;
        this->classSchedule->roomAllocations[NoClass][day][slot] = room;


   
        nodeQueue.pop();


    
    }
    

}



  std::vector<int> Graph::findRoomDaySlot(const TypeOfSubject& typeOfSubject, const int& noClass, const std::pair<int, int>& DaySlot,
                                        const std::vector<int>& sameLecturerSubjects) {
    int day = DaySlot.first;
    int slot = DaySlot.second;
    const int nbOfClasses = this->classSchedule->NUM_CLASSES;
    std::vector<int>& rooms = (typeOfSubject == practical) ? this->labRooms : this->Rooms;

    bool isRoomAvailable = false;
    while (!isRoomAvailable && day != -1) {
        int nbOfRoomOccupied = 0;
        for (int i = 0; i < nbOfClasses; ++i) {
            for (int j = 0; j < rooms.size(); ++j) {
                if (std::find(sameLecturerSubjects.begin(), sameLecturerSubjects.end(), 
                              this->classSchedule->subjectAllocations[i][day][slot]) != sameLecturerSubjects.end()) {
                    nbOfRoomOccupied = rooms.size();
                    break;
                }
                if (this->classSchedule->roomAllocations[i][day][slot] == rooms[j]) {
                    nbOfRoomOccupied++;
                }
            }
            if (nbOfRoomOccupied >= rooms.size()) {
                break;
            }
        }
        isRoomAvailable = nbOfRoomOccupied < rooms.size();

        if (!isRoomAvailable) {
            slot++;
            if (slot == this->classSchedule->NUM_SLOTS) {
                slot = 0;
                day++;
                if (day == this->classSchedule->NUM_DAYS) {
                    day = -1;
                }
            }
        }
    }

    int roomReady = -1;
    if (day != -1) {
        for (int i = 0; i < rooms.size(); ++i) {
            bool roomFound = true;
            for (int j = 0; j < nbOfClasses; ++j) {
                if (this->classSchedule->roomAllocations[j][day][slot] == rooms[i]) {
                    roomFound = false;
                    break;
                }
            }
            if (roomFound) {
                roomReady = rooms[i];
                break;
            }
        }
    }

    return {roomReady, day, slot};
}



std::vector<int> Graph::findSameLecturerSubjects(const int& subjectID){
    std::vector<int> sameLecturerSubjects;
    for (int i = 0; i < sameLecturers.size(); i++)
    {
        for (int j = 0; j < sameLecturers[i].subjects.size(); j++)
        {
            if(subjectID == sameLecturers[i].subjects[j]){
                sameLecturerSubjects = sameLecturers[i].subjects;
                sameLecturers.erase(sameLecturers.begin() + j);

                break;
            }
        }
        
    }
    return sameLecturerSubjects;
    


}



Graph::~Graph()
{
    delete this->classSchedule;
    std::cout << "Graph deleted" << std::endl;
}