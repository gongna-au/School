#include <stdio.h>
#include "color.h"
#include "mysql.h"
#include<string.h>

#define DATABASE    "MyDatabase3"
#define TABLE       "ContactPerson"

int  Addrecord();
int  ListAllRecord();
int ModifyrecordByName();
int ModifyrecordByPhone();
int Deleterecord();
int Searchrecord();
void finish_with_error();
/**
 * @brief   基于MySQL的通讯录
 * @author  龚娜
 * @data    2021/07/12
*/


//联系人的结构体
struct person{
    char name[30];
    char company[30];
    char telephoneNumber[30];
    char emailAddress[30];
    char remarks[30];

};
//主函数
int main(){
     //利用宏定义函数
        //SET_BACKGROUND_COLOR(BACKGROUND_PURPLE);
        //SET_FRONT_COLOR(FRONT_GREEN);
        SET_BACKGROUND_COLOR(BACKGROUND_WHITE);
        SET_FRONT_COLOR(FRONT_BLUE);
       
        
        //初始化并连接数据库
        MYSQL *con = NULL;
        char buf[1000];
        char sql[10000];
        int flag=0;
        int choice;
        
       
        con = mysql_init(NULL);
        mysql_real_connect(con,"localhost","gongna2","123456","MyDatabase3",0,NULL,0);
        
         if (con==NULL){
            printf("MySQL init fail.\n");
            fprintf(stderr,"%s\n",mysql_error(con));
            return -1;
        }
        
        
//功能选择
do{ 


    printf("\n--------------------------------欢迎使用联系人功能------------------------------\n\n");
    printf("\t\t\t\t\t菜单\t\t\t\t\t\t\n\n");
    printf("\t\t1.新建联系人   \t2.查看联系人   \t3.修改联系人  \n\t\t4.查找联系人 \t5.删除联系人\t6.关闭退出\n");
    printf("\t\t请输入你的选择\n");
        scanf("%d",&choice);
        switch(choice){
            case 1:{

                printf("\t\t请输入新建联系人的信息：\n");
                struct person contactPersonNew;
                //初始化结构体变量
                memset(&contactPersonNew,0,sizeof(struct person));
                printf("\n\t\t请输入新建联系人的姓名?\n");
                scanf("%s",contactPersonNew.name);
                scanf("%*[^\n]");
                scanf("%*c");
                printf("\n\t\t请输入新建联系人的公司?\n");
                scanf("%s",contactPersonNew.company);
                scanf("%*[^\n]");
                scanf("%*c");
                printf("\n\t\t请输入新建联系人的电话号码?\n");
                scanf("%s",contactPersonNew.telephoneNumber);
                scanf("%*[^\n]");
                scanf("%*c");
                printf("\n\t\t请输入新建联系人的邮件地址?\n");
                scanf("%s",contactPersonNew.emailAddress);
                scanf("%*[^\n]");
                scanf("%*c");
                printf("\n\t\t请输入新建联系人的备注?\n");
                scanf("%s",contactPersonNew.remarks);
                scanf("%*[^\n]");
                scanf("%*c");

                Addrecord(con,TABLE,contactPersonNew);
            break;
            }
            
            case 2: 

                ListAllRecord(con,TABLE,buf);
            break;
            
            case 3:{
                int temp;
                //先清空输入缓冲区
                fflush(stdin);
                printf("\n\t\t请问你要修改谁的信息?\n");
                printf("\n\t\t根据姓名修改  Or  根据电话号码修改?\n\t\t根据姓名修改->1\t\t根据电话修改->2\n");
                scanf("%d",&temp);
                switch (temp)
                {
                case 1:{
                    char contactPersonInfo[30];
                    struct person contactPersonModify;
                    scanf("%*[^\n]");
                    scanf("%*c");
                    printf("\n\t\t请输入要修改的联系人的姓名\n");
                    scanf("%s",contactPersonInfo);
                    scanf("%*[^\n]");
                    scanf("%*c");
                    
                    //初始化结构体
                    memset(&contactPersonModify,0,sizeof(struct person));
                    //获取结构体的值
                    printf("\n\t\t输入该用户新的公司地址：");
                    scanf("%s",contactPersonModify.company);
                    scanf("%*[^\n]");
                    scanf("%*c");
                    printf("\n\t\t输入该用户新的Email地址：");
                    scanf("%s",contactPersonModify.emailAddress);
                    scanf("%*[^\n]");
                    scanf("%*c");
                    printf("\n\t\t输入该用户新的电话号码：");
                    scanf("%s",contactPersonModify.telephoneNumber);
                    scanf("%*[^\n]");
                    scanf("%*c");
                    printf("\n\t\t输入该用户新的备注:");
                    scanf("%s",contactPersonModify.remarks);

                    ModifyrecordByName(con,TABLE,contactPersonModify,contactPersonInfo);
                    printf("\n\t\t修改成功！\n");
                    break;
                }
                case 2:{
                    char contactPersonInfo[30];
                    scanf("%*[^\n]");
                    scanf("%*c");
                    printf("\n\t\t请输入要修改的联系人的电话号码\n");
                    scanf("%s",contactPersonInfo);
                    struct person contactPersonModify;
                    //初始化结构体
                    memset(&contactPersonModify,0,sizeof(struct person));
                    //获取结构体的值
                    scanf("%*[^\n]");
                    scanf("%*c");
                    printf("\n\t\t输入联系人昵称：");
                    scanf("%s",contactPersonModify.name);
                    scanf("%*[^\n]");
                    scanf("%*c");
                    printf("\n\t\t输入公司地址：");
                    scanf("%s",contactPersonModify.company);
                    scanf("%*[^\n]");
                    scanf("%*c");
                    printf("\n\t\t输入Email地址");
                    scanf("%s",contactPersonModify.emailAddress);
                    scanf("%*[^\n]");
                    scanf("%*c");
                    printf("\n\t\t输入备注:");
                    scanf("%s",contactPersonModify.remarks);

                    ModifyrecordByPhone(con,TABLE,contactPersonModify,contactPersonInfo);
                    break;
                }
                default:
                    break;
                }
            break; 
            }
            
            case 4:{ 
                int temp4;
                struct person contactPersonForSearch;
                //结构体的初始化
                memset(&contactPersonForSearch,0,sizeof(struct person));
                //获取结构体的值
                /*
                    scanf("%*[^\n]");
                    scanf("%*c");
                    printf("\n\t\t输入联系人昵称：");
                    scanf("%s",contactPersonForSearch.name);
                    scanf("%*[^\n]");
                    scanf("%*c");
                    printf("\n\t\t输入公司地址：");
                    scanf("%s",contactPersonForSearch.company);
                    scanf("%*[^\n]");
                    scanf("%*c");
                    printf("\n\t\t输入Email地址");
                    scanf("%s",contactPersonForSearch.emailAddress);
                    scanf("%*[^\n]");
                    scanf("%*c");
                    printf("\n\t\t输入备注:");
                    scanf("%s",contactPersonForSearch.remarks);

*/              printf("\n\t\t根据姓名查找  Or  根据电话号码查找?\n\t\t根据姓名查找->1\t\t根据电话查找->2\n");
                scanf("%d",&temp4);
                    switch (temp4)
                    {
                        case 1:{
                            char contactPersonInfo[30];
                            printf("\n\t\t输入联系人昵称：\n");
                            scanf("%s",contactPersonForSearch.name);
                            Searchrecord(con,TABLE,contactPersonForSearch,buf);
                            break;
                
                        }
                        case 2:{
                            char contactPersonInfo[30];
                            printf("\n\t\t输入联系人电话号码：\n");
                            scanf("%s",contactPersonForSearch.telephoneNumber);
                            Searchrecord(con,TABLE,contactPersonForSearch,buf);
                            break;
                
                        }

                    }
                break;
            }
            case 5:{
                char name[30];
                scanf("%*[^\n]");
                scanf("%*c");
                printf("\t\t请输入你要删除的联系人的姓名:\n");
                scanf("%s",name);
                Deleterecord(con,TABLE,name);
                printf("\t\t删除成功！\n");
            break;
            }
            case 6: 
                exit(0);
            break;

            
            


        }

        
        printf("\t\t是否继续？\n  Yes->1  No->2\n");
        scanf("%d",&flag);
        scanf("%*[^\n]");
        scanf("%*c");




}while(flag==1);


    




        

    return 0;
}



//功能函数
//新建联系人功能
/**
 * 往数据库中插入用户信息
 * @param con 成功连接的MySQL变量
 * @param table 需要更新的表
 * @param contactPerson 联系人的信息
 * @return 成功返回0，失败则返回-1
*/
int  Addrecord(MYSQL *con, const char* table, struct person contactPerson ){
    char sql[10000];
    //先在数据库中查找要新建的联系人的人名是否存在
    //若存在则给出提示信息


    //构造完整sql语句
    if(contactPerson.name!=NULL){
        sprintf(sql, "insert into ContactPerson(Name,Company,TelephoneNumber,EmailAddress,Remarks)values('%s','%s','%s','%s','%s');",contactPerson.name,contactPerson.company,contactPerson.telephoneNumber,contactPerson.emailAddress,contactPerson.remarks);
    }
    if(mysql_query(con,sql)){
        finish_with_error(con);
        return -1;
    }
    return 0;
    
}



//查看联系人功能
/**
 * 从数据库返回所有的用户信息
 * @param con 成功连接的MySQL变量
 * @param table 需要查询的表
 * @param id 用户id
 * @param buf 存放查询结果的缓冲区
 * @return 成功返回0，失败则返回-1
*/
int  ListAllRecord(MYSQL *con, const char* table, char* buf){
    char sql[10000];
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;
    unsigned int num_fields;
    //构造完整sql语句
    sprintf(sql, "select * from %s;",  table);
    //查询
    if(mysql_query(con,sql)){
        finish_with_error(con);
        return -1;
    }
    //获取并存储查询结果
    result = mysql_store_result(con);
    if(NULL == result)
    {
        finish_with_error(con);
        return -1;
    }

 
        num_fields = mysql_num_fields(result);
        //num_fields是记录条数
        printf("\n--------------------------------查询结果---------------------------------\n\n");
        while ((row = mysql_fetch_row(result))){
            //lengths是字段数
            
            printf("\t\tId:%s   \tName:%s   \tCompany:%s\n\t\tTelephoneNumber:%s    \tEmailAddress:%s   \tRemarks:%s\n",row[0],row[1],row[2],row[3],row[4],row[5]);
        }
   
        
        /*
        //动态分配内存
        char **recordArray=(char**)malloc((result->row_count)*sizeof(char*));
        for (int i=0;i<(result->field_count);i++){
            recordArray[i]=(char *)malloc((result->field_count)*sizeof(char));
        }
        //往数组里存值
        
        for(int i=0; i < (result->row_count); i++){
            
            strcpy(recordArray[i], row[i]);

        }

        //把值打印出来
        printf("\n--------------------------------查询结果---------------------------------\n\n");

        for(int i=0; i < result->field_count; i++){
            printf("\t\tId:%s   \tName:%s   \tCompany:%s\n\t\tTelephoneNumber:%s    \tEmailAddress:%s   \tRemarks:%s\n",recordArray[i][0],recordArray[i][1],recordArray[i][2],recordArray[i][3],recordArray[i][4],recordArray[i][5]);
        }
        

       //释放二维数组的内存
        for (int i = 0; i < (result->row_count); i++)
            free(recordArray[i]);

            free(recordArray); */
    
    mysql_free_result(result);

    return 0;


}



//修改联系人功能

int ModifyrecordByName(MYSQL *con, const char* table, struct person contactPerson, char*contactPersonInfo){

    char sql[10000];
    MYSQL_RES *result = NULL;
 
    MYSQL_ROW row; 
    

    
   sprintf(sql, "update %s set Company ='%s',TelephoneNumber='%s',EmailAddress='%s',Remarks='%s' where Name='%s';", table,contactPerson.company,contactPerson.telephoneNumber,contactPerson.emailAddress,contactPerson.remarks,contactPersonInfo);

    if(mysql_query(con,sql)){
        
        finish_with_error(con);
        return -1;
    }
    
    return 0;


}



int  ModifyrecordByPhone(MYSQL *con, const char* table, struct person contactPerson, char*contactPersonInfo){

    char sql[10000];
    
    MYSQL_RES *result = NULL;
    MYSQL_ROW row; 
    bool tag;
    //构造完整sql语句并执行

    sprintf(sql, "update %s set Name='%s',Company='%s',EmailAddress='%s',Remarks='%s' where TelephoneNumber='%s';", table,contactPerson.name,contactPerson.company,contactPerson.emailAddress,contactPerson.remarks,contactPersonInfo);

    if(mysql_query(con,sql)){
        
        finish_with_error(con);
        return -1;
    }
   





   /* //获取并存储查询结果
    result = mysql_store_result(con);
    if(NULL == result){
        tag=0;
    }else{
        tag=1;
    }
*/

    //查询结束
    //没有查找到联系人
   
    //查询成功返回结果
   /* if(tag){
    //根据用户输入的信息插入数据
        if(contactPerson.name!=NULL){
            //构造完整sql语句并执行
            sprintf(sql, "update %s set Name='%s' where TelephoneNumber='%s';", table,contactPerson.name,contactPersonInfo);
            
            if(mysql_query(con,sql)){
                finish_with_error(con);
                return -1;
            }
        }
        if(contactPerson.company!=NULL){
             
            //构造完整sql语句并执行
            sprintf(sql, "update %s set Company='%s' where TelephoneNumber='%s';", table,contactPerson.company,contactPersonInfo);
                
            if(mysql_query(con,sql)){
                finish_with_error(con);
                return -1;
            }
        }
        if(contactPerson.emailAddress!=NULL){
            
            //构造完整sql语句并执行
            sprintf(sql, "update %s set EmailAddress='%s' where TelephoneNumber='%s';", table,contactPerson.emailAddress,contactPersonInfo);
            if(mysql_query(con,sql)){
                finish_with_error(con);
                return -1;
            }

        }
       
        if(contactPerson.remarks!=NULL){
            
            //构造完整sql语句并执行
            sprintf(sql, "update %s set Remarks='%s' where TelephoneNumber='%s';", table,contactPerson.remarks,contactPersonInfo);
            if(mysql_query(con,sql)){
                finish_with_error(con);
                return -1;
            }
        }
    }
    mysql_free_result(result);
    
    */
    return 0;

}






//查找联系人功能
int Searchrecord(MYSQL *con, const char* table, struct person contactPerson, char* buf){
    char sql[10000];
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;
    unsigned int num_fields;
    if(contactPerson.name!=NULL){ 
        //构造完整sql语句
        sprintf(sql, "select * from %s where Name = '%s';",  table, contactPerson.name);
        //执行
        if(mysql_query(con,sql)){
            finish_with_error(con);
            return -1;
        }
        //获取并存储查询结果
        result = mysql_store_result(con);
        if(NULL == result){
            finish_with_error(con);
            return -1;
        }
        num_fields = mysql_num_fields(result);
        //num_fields是记录条数
        printf("\n--------------------------------查询结果---------------------------------\n\n");
        while ((row = mysql_fetch_row(result))){
            //lengths是字段数
            
            printf("\t\tId:%s   \tName:%s   \tCompany:%s\n\t\tTelephoneNumber:%s    \tEmailAddress:%s   \tRemarks:%s\n",row[0],row[1],row[2],row[3],row[4],row[5]);
        }


    }
    if((contactPerson.telephoneNumber!=NULL)){
        //构造完整sql语句
        sprintf(sql, "select * from %s where TelephoneNumber='%s';",  table, contactPerson.telephoneNumber);
        //执行
        if(mysql_query(con,sql)){
            finish_with_error(con);
            return -1;
        }
        //获取并存储查询结果
        result = mysql_store_result(con);
        if(NULL == result){
            finish_with_error(con);
            return -1;
        }
    }
    //返回查询结果
        if(row = mysql_fetch_row(result)){
            printf("\n--------------------------------查询结果---------------------------------\n\n");
            printf("\t\tId:%s   \tName:%s   \tCompany:%s\n\t\tTelephoneNumber:%s    \tEmailAddress:%s   \tRemarks:%s\n",row[0],row[1],row[2],row[3],row[4],row[5]);
        }
        mysql_free_result(result);
        return 0;

}


//删除联系人功能
int  Deleterecord(MYSQL *con, const char* table, const char* name){
    char sql[10000]; 
    
    //构造完整sql语句
    sprintf(sql, "delete from %s where Name='%s';", table, name);
    //执行
    if(mysql_query(con,sql))
    {
        finish_with_error(con);
        return -1;
    }

    return 0;

    
}



//错误处理功能函数
/** 
 * 语句执行出错处理
 * @param con 需要处理的MYSQL变量
 * @return -1;
*/

void finish_with_error(MYSQL *con)
{
    fprintf(stderr,"%s\n",mysql_error(con));
    mysql_close(con);
}













