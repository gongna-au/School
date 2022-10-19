#include <stdio.h>
// 实现一个二分搜索函数并在主函数里测试
// 二分查找
int binarySearch(int list[],int key,int arrySize){
    int low = 0;
    int high = key - 1;
    while(low<=high){
        int mid =(low+high)/2;
        int temp=list[mid];
        if(temp<key){
            low=mid+1;
        }else if(temp>key){
            high=mid-1;
        }else{
            return mid;
        }
    }
    return -1;
}
void main(){
    int key;
    int searchResult;
    int nums[10] = {4, 5, 2, 10, 7, 1, 8, 3, 6, 9};
    int arrySize=sizeof(nums)/sizeof(nums[0]);
    int i, j, temp;
    //冒泡排序算法：进行 n-1 轮比较
    for(i=0; i<10-1; i++){
        //每一轮比较前 n-1-i 个，也就是说，已经排序好的最后 i 个不用比较
        for(j=0; j<10-1-i; j++){
            if(nums[j] > nums[j+1]){
                temp = nums[j];
                nums[j] = nums[j+1];
                nums[j+1] = temp;
            }
        }
    }
   
    //输出排序后的数组
    //for(i=0; i<10; i++){
       // printf("%d ", nums[i]);
    //}

    //开始查找
    printf("请输入你要查找的Key\n");
    scanf("%d",&key);
   searchResult= binarySearch(nums,key,arrySize);
   printf("%d",searchResult);
   if (searchResult){
       printf("该元素在这个List当中");
   }else{
       printf("该元素不在这个List当中");
   } 

    printf("\n");
   
}
    
    


