#include <stdio.h>
#include <math.h>
void bubble(int a[]);				   //冒泡排序
void selection(int a[]);			   //选择排序
void group(int a[], int b[], int c[]); //数组合并，选择排序
void main()
{
	int a[10], b[10], c[20], i;
	printf("请输入一个包含10元素的数组：");
	for (i = 0; i < 10; i++)
		scanf("%d", &a[i]);
	bubble(a);
	for (i = 0; i < 10; i++)
		printf("%d\t", a[i]);
	printf("\n");
	printf("请输入第二个包含10元素的数组：");
	for (i = 0; i < 10; i++)
		scanf("%d", &b[i]);
	selection(b);
	for (i = 0; i < 10; i++)
		printf("%d\t", b[i]);
	printf("\n");
	group(a, b, c);
	printf("数组组合为：\t");
	for (i = 0; i < 20; i++)
		printf("%d\t", c[i]);
	printf("\n");
}
void bubble(int a[])
{
	int i, j, t;
	for (i = 1; i < 10; i++)
		for (j = 0; j < 10 - i; j++)
			if (a[j] < a[j + 1])
			{
				t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
			}
}
void selection(int a[])
{
	int i, j, k, t;
	for (i = 0; i < 9; i++)
	{
		k = i;
		for (j = i + 1; j < 10; j++)
			if (a[k] < a[j])
				k = j;
		if (k != i)
		{
			t = a[i];
			a[i] = a[k];
			a[k] = t;
		}
	}
}
void group(int a[], int b[], int c[])
{
	int i, j, k, t;
	for (i = 0; i < 10; i++)
		c[i] = a[i];
	for (i = 0; i < 10; i++)
		c[i + 10] = b[i];
	for (i = 0; i < 19; i++)
	{
		k = i;
		for (j = i + 1; j < 20; j++)
			if (c[k] < c[j])
				k = j;
		if (k != i)
		{
			t = c[i];
			c[i] = c[k];
			c[k] = t;
		}
	}
}
