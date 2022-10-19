//Write a function that returns the common characters of two strings:
//string commonChars(const string& s1, const string& s2)

//Write a test program that prompts the user to enter two strings and display their common characters.
 
//sample runs:
//enter a string s1: abcd
//enter a string s2: aecaten
//the common characters are ac

#include<iostream>
#include <math.h>
#include <string>
using namespace std;

string commonChars(const string& s1, const string& s2){
    string result;
    int index=0;
    for(int i=0;i<s1.length();i++){
        index = s2.find(s1[i],0);
        if(index < s2.length()){
           result= result+s1[i];
        }
    }
    return result;
}
int main(){
    string s1;
    string s2;
    cout<<"enter a string s1:";
    cin >> s1;
    cout<<"enter a string s2:";
    cin >> s2;
    string str=commonChars(s1,s2);
    cout<<"the common characters are :"<<str<<endl;
    
}


