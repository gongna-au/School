#include <stdio.h>
#include <string.h>

void diagmaxl(int **mat, int m, int n, int & maxlen, int & jpos);
void diagscan(int **mat, int i, int j, int m, int n, int & maxlen, int & jpos);
char* SubString(char *str, int s,int len);
char* maxsamesubstring(char *string1, char *string2);

void main()
{
    char str1[100], str2[100], *sub;
    printf("请输入字符串1：");
    gets(str1);
    printf("请输入字符串2：");
    gets(str2);

    sub = maxsamesubstring(str1, str2);
    printf("\n最长公共子串长度=%d \n", strlen(sub));
    puts(sub);
}

char* maxsamesubstring(char *string1, char *string2)
{// 本算法返回串string1和string2的最长公共子串sub
    int i, j, maxlen, jpos, **mat;
    char *p1 = string2;
    char *p2 = string1;
    char *sub;
    int m = strlen(string1);
    int n = strlen(string2);

    mat = new int*[n+1];
    for( i=0; i<=n; i++ ){
        mat[i] = new int[m+1];
    }
    for( i=0; i<=n; i++ ){
        for( j=0; j<=m; j++ ){
            if( *(p1+i) == *(p2+j) ){
                mat[i][j] = 1;
            }else {
                mat[i][j] = 0;
            } 
        }
    }    

    for( i=0; i<=n; i++ ){
        mat[i][m] = 0;
    } 
    for( j=0; j<=m; j++ ){
        mat[n][j] = 0;
    } 
     

/*
printf("  ");
    for( j=0; j<=m; j++ ) 
        printf("%c ", string1[j]);
    printf("\n");

for( i=0; i<=n; i++ )
{
    printf("%c ", string2[i]);
    for( j=0; j<=m; j++ )
        printf("%d ", mat[i][j]);
    printf("\n");
}
*/

    diagmaxl(mat, m, n, maxlen, jpos); // 利用mat[m+1][n+1]求得string1和string2的最长公共子串的长度maxlen以及它在string1中的起始位置jpos

    if( maxlen == 0)
    {   sub = new char[1];
        *sub = '\0';
    }
    else{
        sub = SubString(string1,jpos,maxlen);
    } // 求得最长公共子串
    return sub;
}//maxsamesubstring

void diagmaxl(int **mat, int m, int n, int & maxlen, int & jpos)
{
    int i, j, k, istart = 0;
    maxlen = 0;
    jpos = -1;
    for( k = -(m-1); k<=n-1; k++ )
    {
        //printf("\nistart = %d \n", istart);
        i = istart;
        j = i - k;
        diagscan(mat, i, j, m, n, maxlen, jpos);
        if( k >= 0 )
        istart++;
    }//for
}//diagmaxl

void diagscan(int **mat, int i, int j, int m ,int n, int & maxlen, int & jpos)
{
    int sj, eq = 0, len = 0, sum = 0;

    while(i<=n && j<=m)
    {
        if( mat[i][j] == 1 )
        {
            sum++;
            //printf("发现第%d个1，其行坐标=%d \n", sum,i);
            len++;
            if(!eq)
            {
                sj = j;
                eq = 1;
            }//if
        }//if
        else if(eq)
        {
            sum = 0;
            if( len > maxlen )
            {
            maxlen = len;
            jpos = sj;
            //printf("maxlen = %d, jpos = %d \n", maxlen, jpos);
            //printf("\n");
            }//if
            eq = 0;
            len = 0;
        }//else if
        i++;
        j++;
    }//while
}//diagscan

char* SubString(char *str, int s,int len)
{
    char *sub, *p;
    int k;

    sub = new char[len+1];
    p = str + s;
    k = len;
    while(k)
    {
        *sub++ = *p++;
        k--;
    }
    *sub = '\0';
    sub = sub - len;

    return sub;
}