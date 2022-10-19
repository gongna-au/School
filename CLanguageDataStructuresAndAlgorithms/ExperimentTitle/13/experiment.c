#include <stdio.h>

void writeNumber(int arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%-3d ", arr[i]);
    }
    printf("\n");
}

void swapNumber(int *a, int *b)
{ //交换两个数
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selectionSort(int arr[], int len)
{
    int i, j;

    for (i = 0; i < len - 1; i++)
    {
        int max = i;
        for (j = i + 1; j < len; j++)
            if (arr[j] > arr[max])
                max = j;
        swapNumber(&arr[max], &arr[i]);
    }
}

void sortNumber(int arr[], int len)
{
    for (int i = 0; i < 10; i++)
    {
        int tag = 0;
        for (int j = 0; j < 10 - i - 1; j++)
        {
            if (arr[j] < arr[j + 1])
            {
                swapNumber(&arr[j], &arr[j + 1]);
                tag = 1;
            }
        }
        if (tag == 0)
        {
            break;
        }
    }
}

void main()
{
    int nums_a[10], nums_b[10], nums[20];
    for (int i = 0; i < 20; i++)
    {
        if (i < 10)
        {
            scanf("%d", &nums_a[i]);
            nums[i] = nums_a[i];
        }
        else
        {
            scanf("%d", &nums_b[i - 10]);
            nums[i] = nums_b[i - 10];
        }
    }

    //冒泡排序
    sortNumber(nums_a, 10);
    writeNumber(nums_a, 10);

    //选择排序
    selectionSort(nums_b, 10);
    writeNumber(nums_b, 10);

    //再次用选择排序将大数组排序合并
    selectionSort(nums, 20);
    writeNumber(nums, 20);
}
