// C++ implementation to print the longest common substring
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

/* function to find and print the longest common
substring of X[0..m-1] and Y[0..n-1] */
void printLCSubStr(char* X, char* Y, int m, int n)
{
	
    // 创建一个来存储最长公共长度 子串的后缀。注意 LCSuff[i][j] 包含 X[0..i-1] 的最长公共后缀的长度  和 Y[0..j-1]。
    // 第一行和第一列 没有逻辑意义，它们仅用于程序简单
	int LCSuff[m + 1][n + 1];

	// To store length of the longest common substring
	int len = 0;

   // 存储包含单元格的索引 最大值。此单元格的索引有助于构建 从右到左向上排列最长的公共子串。
	int row, col;

	// 以下步骤 LCSuff[m+1][n+1]

	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= n; j++) {
			if (i == 0 || j == 0)
				LCSuff[i][j] = 0;

			else if (X[i - 1] == Y[j - 1]) {
				LCSuff[i][j] = LCSuff[i - 1][j - 1] + 1;
				if (len < LCSuff[i][j]) {
					len = LCSuff[i][j];
					row = i;
					col = j;
				}
			}
			else
				LCSuff[i][j] = 0;
		}
	}

	// if true, then no common substring exists
	if (len == 0) {
		cout << "No Common Substring";
		return;
	}

	// allocate space for the longest common substring
	char* resultStr = (char*)malloc((len + 1) * sizeof(char));
    // 从 (row, col) 单元格对角向上遍历 直到 LCSuff[row][col] != 0
	while (LCSuff[row][col] != 0) {
		resultStr[--len] = X[row - 1];

    // 沿对角线向上移动到上一个单元格
		row--;
		col--;
	}

	// required longest common substring
	cout << resultStr;
}

/* Driver program to test above function */
int main()
{
	char  X[20];
	char  Y[20];
    cout << "please input:X"<< endl; 
    cin >> X;
    cout << "please input:Y"<< endl;
    cin >> Y;


    

	int m = strlen(X);
	int n = strlen(Y);
    cout << "Result is:"<< endl;
	printLCSubStr(X, Y, m, n);
    cout <<  endl;
	return 0;
}
