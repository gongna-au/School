#include <stdlib.h>
#include <stdio.h>

//定义枚举类型

enum Sex
{
    man,
    female
};

//定义学生的结构体
struct StudentInFo
{
    char studentId[10];
    char studentName[25];
    enum Sex studentSex;
    unsigned int older;
    unsigned int class;
    float grade;
};
//定义结构体一定记得打分号；
// typedef struct     结构体类型名
typedef struct StudentInFo Student;

//获取一个学生信息
Student *GetStudentInformation(int i)
{
    Student *p;
    char sex;

    p = (Student *)malloc(sizeof(Student));
    if (p == NULL)
        return NULL;
    printf("\n===input%dthe student's information===\n", i + 1);
    printf("请输入学生信息：\n");
    printf("请输入学生学号：\n");
    scanf("%s", p->studentId);
    printf("请输入学生姓名：\n");
    scanf("%s", p->studentName);
    fflush(stdin);
    while (1)
    {
        printf("Sex(M/F)\n");
        scanf("%c", &sex);
        if (sex == 'M' || sex == 'F')
            break;
        fflush(stdin);
    }
    p->studentSex = (sex == 'M') ? man : female;

    printf("请输入学生年龄：\n");
    scanf("%d", &p->older);
    printf("请输入学生班级：\n");
    scanf("%d", &p->class);
    printf("请输入学生成绩：\n");
    scanf("%f", &p->grade);

    return (p);
}
//将获取的学生信息排序
void SortStudentInFo(Student **pstudent, int num)
{
    Student *pmax;
    //把学生按分数从大到小排序;
    int i, j, k;
    //选择排序
    for (i = 0; i < num - 1; i++)
    {
        k = i;
        pmax = pstudent[i];
        for (j = i + 1; j < num; j++)
        {
            if (pstudent[i] < pstudent[j])
            {
                k = j;
                pmax = pstudent[j];
            }
        }
        pstudent[k] = pstudent[i];
        pstudent[i] = pmax;
    }
}
//释放获取的内存空间
void FreeMeMorySpace(Student **pstudent, int num)
{
    for (int i = 0; i < num; i++)
    {
        free(pstudent[i]);
        free(pstudent);
    }
}

void main()
{
    Student **pstudent;
    int num, i;
    printf("请输入学生的人数：\n");
    scanf("%d", &num);
    if (num < 0)
    {
        return;
    }
    pstudent = (Student **)malloc(num * sizeof(Student *));
    if (pstudent == NULL)
    {
        printf("没有足够的空间来分配内存！！！\n");
        return;
    }
    for (i = 0; i < num; i++)
    {
        pstudent[i] = GetStudentInformation(i);
        if (pstudent[i] == NULL)
        {
            printf("没有足够的空间来分配内存！！！\n");
            FreeMeMorySpace(pstudent, i);
            return;
        }
    }
    SortStudentInFo(pstudent, num);
    printf("\n============================sort result==========================\n");
    for (i = 0; i < num; i++)
        printf("%12s%20s%9s%5d%5d%8.1f\n", pstudent[i]->studentId, pstudent[i]->studentName, (pstudent[i]->studentSex == man) ? "man" : "female", pstudent[i]->older, pstudent[i]->class, pstudent[i]->grade);

    FreeMeMorySpace(pstudent, num);
}
