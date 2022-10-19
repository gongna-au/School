//A string is a palindrome if it reads the same forward and backwards, 
//E.g. mom and dad are palindromes
//but uncle and aunt are not.
//Please write a program to check whether a string is a palindrome.
#include<iostream>
#include <math.h>
#include <string>
using namespace std;

bool isPalindrome(const string &s);
bool isPalindrome(const string &s){
    string reverseStr;
    int i;
    int j;
    bool tag=true;
    for(i=s.length()-1,j=0;i>=0;i--){
        if(i==j){
            break;
        }
        if (s[j]!=s[i]){
            tag=false;
            break;
        }
        j++;
    }
    return tag;

}
int main(){
    string s1;
    cout<<"enter a string :";
    cin >> s1;
    
    bool IsPalin=isPalindrome(s1);
    if(IsPalin){
        cout<<"the str you input is Palindrome"<<endl;
    }else{
        cout<<"the str you input is not Palindrome"<<endl;
    }
   
}
