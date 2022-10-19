use  `MyDatabase3`
-- 联系人信息表(student)
create table `ContactPerson`(
       
    `Id`                 int        AUTO_INCREMENT      comment "ID",
    `Name`               varchar(30)     UNIQUE              comment "姓名",
    `Company`            varchar(30)     not null            comment "公司",
    `TelephoneNumber`    varchar(30)     UNIQUE              comment "电话号码",
    `EmailAddress`       varchar(30)     null                comment "邮件地址",
    `Remarks`            varchar(30)     null                comment "备注",

  
-- 添加约束
primary key (`Id`)

)ENGINE=InnoDB DEFAULT CHARSET=UTF8MB4;