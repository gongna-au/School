#include <stdio.h>
// 把一个3*3的二维数组顺时针旋转90度

void RotateTheArray(int Array[3][3] ,int tempArray[3][3]){
    //把每一行数组取出来放到每一列
   for (int i=0;i<3;i++){
       for (int j=0;j<3;j++){
           tempArray[j][2-i]=Array[i][j];
       }
   }
   int  tag=0;
   for (int i=0;i<3;i++){
       for (int j=0;j<3;j++){
          
          
          printf("%-3d",tempArray[i][j]);
          tag++;
          if (tag%3==0){
              printf("\n");
          }

       }
   }
    

}

void main(){

    int array[3][3]={ {1,2,3}, {4,5,6}, {7,8,9}};
    int temparray[3][3]={0};
    int tag=0;
    for (int i=0;i<3;i++){
       for (int j=0;j<3;j++){
          
          
          printf("%-3d",array[i][j]);
          tag++;
          if (tag%3==0){
              printf("\n");
          }

       }
   }
    printf("翻转后90°得:\n");
    RotateTheArray(array,temparray);
    



}