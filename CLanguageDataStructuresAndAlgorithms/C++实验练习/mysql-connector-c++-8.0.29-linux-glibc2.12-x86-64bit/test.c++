#include <stdio.h>

#include "mysql/mysql.h"

int main()

{

  const char *host = "localhost";//ip地址

  const char *user = "gongna2";//数据库用户名

  const char *pass = "123456";//自己数据库密码

  const char *db   = "Test";//表名

  MYSQL mysql;

  mysql_init(&mysql);

  if (!mysql_real_connect(&mysql, host, user, pass, db, 0, NULL, 0)) {

    printf("%s", mysql_error(&mysql));

  }

  else {

    printf("YES, Conected succeed!");

  }

  mysql_close(&mysql);

  return 0;

}

