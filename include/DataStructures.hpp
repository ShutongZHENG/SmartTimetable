#include <vector>
#include <string>
struct Course {
    std::string name;
};

// struct Student {
//     std::string name;
//     std::vector<Course> courses;
// };
struct Lecturer {
    std::string name;
    std::vector<Course> courses;
};

struct ClassSection {
    std::string sectionID;
};

struct CourseWithSections {
    std::string courseName;
    std::vector<ClassSection> sections;
};

struct Laboratory {
    std::string labID;
    std::vector<std::string> sharedClassrooms;
};

struct CourseSchedule {
    std::string courseName;
    int weeklyClasses;
};

struct Classroom {
    std::string roomID;
};

struct TimeSlot {
    std::string day;
    std::string startTime;
    std::string endTime;
};