#include "color.h"
#include<mysql/mysql.h>
#include<string.h>
#include<iostream>
using namespace std;


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
        mysql_real_connect(con,"localhost","gongna2","123456","Test",0,NULL,0);
        
         if (con==NULL){
            printf("MySQL init fail.\n");
            fprintf(stderr,"%s\n",mysql_error(con));
            return -1;
        }
        char sql[10000];
        sprintf(sql, "select * from %s where book_name = '%s';",  "book_table", "gh");
        if(mysql_query(con,sql)){
            //finish_with_error(con);
            printf("err");
            return -1;
        }
        MYSQL_RES * result = mysql_store_result(con);
        if(NULL == result){
            //finish_with_error(con);
            printf("err");
            return -1;
        }
       unsigned int num_fields = mysql_num_fields(result);
        MYSQL_ROW row;
       while ((row = mysql_fetch_row(result))){
            //lengths是字段数
            
            printf("\t\t\tBookId:%s   \tBookName:%s\n\t\tBookInformation:%s    \tBookPrice:%s   \tBookState:%s\n",row[1],row[2],row[3],row[4],row[5]);
        }
        



}