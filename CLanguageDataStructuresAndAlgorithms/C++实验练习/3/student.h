#include <math.h>

#include <fstream>
#include <iostream>
#include <string>

#define DataOffset  (8+4+4)
using namespace std;

class student{
    private:
        string studentId;
        string studentName;
        int studentScore;

    public:

        student(string id,string name,int score){
            this->studentId = id;
            this->studentName = name;
            this->studentScore = score;

        };
        student(string id){
            this->studentId = id;
            

        };

        
         ~student(){

        };

        int getStudentScore(){
            return this->studentScore;
        };
        string getStudentId(){
           return  this->studentId;
        };
        string  getStudentName(){
           return  this->studentName;
        };
        
};


    


 



