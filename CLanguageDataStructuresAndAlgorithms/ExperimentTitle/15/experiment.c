#include <stdio.h>
#include <stdlib.h>
int main()
{
	//选择排序
	int arr[10], min, m, i, j;
	for (int i = 0; i < 10; i++)
	{
		scanf("%d", &arr[i]);
	}
	for (i = 0; i < 9; i++)
	{
		min = arr[i];
		m = i;
		for (j = i + 1; j < 10; j++)
		{
			if (arr[j] < min)
			{
				min = arr[j];
				m = j;
			}
		}
		arr[m] = arr[i];
		arr[i] = min;
	}
	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", arr[i]);
	}

	system("pause");
	return 0;
}
