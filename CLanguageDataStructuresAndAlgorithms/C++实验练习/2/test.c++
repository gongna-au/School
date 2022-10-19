#include <iostream>
#include <fstream>
using namespace std;
const int ID_SIZE = 10, NAME_SIZE = 4,Score_SIZE=3;
//声明记录的结构
struct StudentInfo
{
    char studentID[ID_SIZE];
    char studentName[NAME_SIZE];
    char studentScore[Score_SIZE];
};

// Function Prototypes
long byteNum(int);
void showRecord(StudentInfo);

int main()
{
    // Person information
    StudentInfo student;
    // Create file object and open the file
    fstream fs("student.txt", ios::in | ios::binary);
    if (!fs)
    {
        cout << "Error opening file. Program aborting.\n"; return 0;
    }
    // Skip forward and read record 1 in the file
    cout << "Here is record 1:\n";
    fs.seekg(byteNum(1), ios::beg);
    fs.read(reinterpret_cast<char *>(&student), sizeof (student));
    showRecord(student);
    // Skip backwards and read record 0 in the file
    cout << "\nHere is record 0:\n";
    fs.seekg(byteNum(0), ios::beg);
    fs.read(reinterpret_cast<char *>(&student), sizeof (student));
    showRecord(student);
    // Close the file
    fs.close();
    return 0;
}
long byteNum(int recNum)
{
    return sizeof (StudentInfo) * recNum;
}
void showRecord(StudentInfo record)
{
    cout << "studentID:";
    cout << record.studentID << endl;
    cout << "studentName: ";
    cout << record.studentName<< endl;
    cout << "studentScore: ";
    cout << record.studentScore << endl;
    
}