#include <stdio.h>
#include <string.h>

#define MAXLINE 10

typedef struct node {
	char s[MAXLINE];
	int order;
}Node;

//Get the index of the element in the stack sequence

int order(Node s[], char str[], int n) {
	int i;
	for (i = 0; i <n; i++) {
		if (strcmp(str, s[i].s) == 0)
			return i;
	}
} 

int main()
{
	int i = 0, j, n1 = 0, n2 = 0;
	
	int cur1, cur2;//decrease judgment 
	Node s1[100];
	Node s2[100];
     

    printf("Please enter the stack sequence: ");
	while (1) {
		scanf("%s", &s1[i].s);
		s1[i].order = i; 
		i++;
		n1++;
		if (getchar() =='\n')
			break;
	}

   
	i = 0;
	printf("Please enter the pop sequence: ");
	while (1) {
		scanf("%s", &s2[i].s);
		s2[i].order = i; 
		i++;
		n2++;
		if (getchar() =='\n')
			break;
	}

    if (n2> n1) {
		printf("输入不合法!\n");
		return 1;
	} 

	

    //判断栈的顺序是否合法
	for (i = 0; i <n2-2; i++) {
		cur2 = 101;
		for (j = i + 1; j <n2; j++) {
			if (order(s1, s2[j].s, n1) <order(s1, s2[i].s, n1)) {
				cur1 = cur2;
				cur2 = order(s1, s2[j].s, n1);
				if (cur2> cur1) {
					printf("不可能!\n");
					return 1;

                } 
			}
		}
    }

    printf("可能!\n");
	
	return 0;	
} 

