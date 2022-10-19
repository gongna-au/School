#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include"ImplementStackByList.h"

// Input: exp = “[()]{}{[()()]()}” 
// Output: Balanced

// Input: exp = “[(])” 
// Output: Not Balanced 
// 
bool isMatchingPair(char ch1,char ch2){

    if(( ch1=='(' ) && ( ch2 ==')')){
        return true;
    }else if(( ch1=='{' ) && ( ch2 =='}')) {
        return true;
    }else if(( ch1=='[' ) && ( ch2 ==']')) {
        return true;
    }else{
        return false;
    }
}

bool areBracketsBalanced(char exp[]){
   Stack* root=NULL;
   int i=0;
   while(exp[i]){

    /*Method1
       if(( exp[0]=='}' || (exp[i]==']') || (exp[i]==')') )){
           return false;
       }
        if(exp[i] == '}' || exp[i] == ')'|| exp[i] == ']'){ 
            if (root == NULL){
                return 0;
            }else if (!isMatchingPair(Pop(&root),exp[i])){
                return false;
            }

            
       }
       */
      //Method 2
        if(( exp[0]=='}' || (exp[i]==']') || (exp[i]==')') )){
           return false;
        }
        if(exp[i] == '}' || exp[i] == ')'|| exp[i] == ']'){
            if(root==NULL){
                return false;
            }else{
                char top=Peek(root);
                if( isMatchingPair(top,exp[i])){
                    Pop(&root);
                }else{
                    return false;
                }

            }
        }
       i++;
   }

   if (root==NULL){
       return true;
   }else{
       return false;
   }
}