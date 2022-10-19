#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void  GameStart(int RobotXiaoBing,int RobotXiaoNa ){
    if (RobotXiaoBing==0){
        printf("RobotXiaoBing punches for stone   ");
        if (RobotXiaoNa==0){
            printf("RobotXiaoNa punches for stone\n");
            printf("RobotXiaoBing  and  RobotXiaoNa drew\n平局\n ");
        }
        if (RobotXiaoNa==1){
            printf("RobotXiaoNa punches for cloth\n");
            printf("RobotXiaoNa wins \n小娜获胜\n ");
        }
        if (RobotXiaoNa==2){
            printf("RobotXiaoNa punches for scissors\n");
            printf("RobotXiaoBing wins \n小冰获胜\n");
        }
    }
    if (RobotXiaoBing==1){
        printf("RobotXiaoBing punches for  cloth   \n");
        if (RobotXiaoNa==0){
            printf("RobotXiaoNa punches for stone\n");
            printf("RobotXiaoBing wins \n小冰获胜\n");
        }
        if (RobotXiaoNa==1){
            printf("RobotXiaoNa punches for cloth\n");
            printf("RobotXiaoBing  and  RobotXiaoNa drew\n平局\n");
        }
        if (RobotXiaoNa==2){
            printf("RobotXiaoNa punches for scissors\n");
            printf("RobotXiaoNa wins \n小娜获胜\n");
        }
    }
    if (RobotXiaoBing==2){
        printf("RobotXiaoBing punches for scissors   \n");
        if (RobotXiaoNa==0){
            printf("RobotXiaoNa punches for stone\n");
            printf("RobotXiaoNa wins \n小娜获胜\n");
        }
        if (RobotXiaoNa==1){
            printf("RobotXiaoNa punches for cloth\n");
            printf("RobotXiaoBing wins \n小冰获胜\n");
        }
        if (RobotXiaoNa==2){
            printf("RobotXiaoNa punches for scissors\n");
            printf("RobotXiaoBing  and  RobotXiaoNa drew\n平局\n");
        }
    }

    
}



void main(){
    int RobotXiaoBing;
    srand(time(NULL));
    RobotXiaoBing= rand()%3;
    int RobotXiaoNa;
    RobotXiaoNa= rand()%3;
    char IsStart;
    printf("是否开始游戏？Y=是/N=否\n");
    scanf("%c",&IsStart);
    if (IsStart=='Y'){
        printf("3 2 1游戏开始.....\n");  
    }
    GameStart(RobotXiaoBing,RobotXiaoNa);
}
