#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//测试数据：数组个数为3  元素为 89 67 56
int SortByOnesPlace(const void *a,const void *b){
    return (*(int *)a-*(int *)b);
}
void main(){

    printf("请输入你要输入的数组的个数\n");
    int arraySize;
    scanf("%d",&arraySize);

    printf("请输入一个整型数组：\n");
    int array1[arraySize];
    int array2[arraySize];
    int array3[arraySize];

    for (int i=0;i<arraySize;i++){
        scanf("%d",&array1[i]);
    }
    //对数组中的每个元素进行取个位数
    for (int i=0;i<arraySize; i++){
        int temp;
        temp=array1[i]%10;
        array2[i]=temp;
        array3[i]=temp;
    }
    //得到排完序号array2与未排完序号的array3
    qsort(array2,arraySize,sizeof(int),SortByOnesPlace);

    //测试：for(int i=0;i<arraySize;i++){
       // printf("%d  ",array2[i]);
    //}

    //array2与array3进行比较
    int IndexArray[arraySize];
    for (int i=0;i<arraySize; i++){
        int temp=array2[i];
        //去array[2]中进行查找
        for (int j=0;j<arraySize; j++){
            if (temp==array3[j]){
                IndexArray[i]=j;
            }
        }  

    }
    //测试：

    //for(int i=0;i<arraySize;i++){
      //  printf("%d  ",IndexArray[i]);
    //}

    //拿着序号表IndexArray把原来的数组进行排序
    int result[arraySize];
    for(int i=0;i<arraySize;i++){
        result[i]=array1[IndexArray[i]];
    }
    //打印
    printf("按照个位数从小到大排完序的结果为:\n");
    for(int i = 0 ; i< arraySize; i++ ) {
        printf("%d ",result[i]);
    }

}