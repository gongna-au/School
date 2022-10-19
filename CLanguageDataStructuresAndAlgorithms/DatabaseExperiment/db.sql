/* 创建模式 */
/* create schema `ccnu`; */
/* 首先创建一个登录名为AbolrousHazem的 SQL Server */
/* USE `firstdb` */
/*然后在 中创建一个对应的数据库 teacher 用户 */
/* CREATE USER `teacher` FOR LOGIN `csccnu`  WITH DEFAULT_SCHEMA=`ccnu`; */
/* EXEC sp_addrolemember 'db_ddladmin', 'teacher'; */
drop  database  if  exists `firstdb`;
create database `firstdb`;
USE `firstdb`; 

CREATE TABLE `Student`(
    `Sno`   varchar(9)  PRIMARY KEY,
    `Sname` varchar(20) DEFAULT NULL,        
    `Ssex`  varchar(2) DEFAULT NULL,
    `Sage`  SMALLINT  ,
    `Sdept` varchar(20)
);


CREATE TABLE `Course`(
    `Cno`     varchar(4)  PRIMARY KEY,
    `Cname`   varchar(40) DEFAULT NULL,
    `Cpno`    varchar(4)  DEFAULT NULL,
    `Ccredit` SMALLINT
  
); 

CREATE TABLE `C`(

   
    `Cno` varchar(4) PRIMARY KEY,
    `CName` varchar(10) DEFAULT NULL,
    `Teacher` varchar(10) DEFAULT NULL

);

CREATE TABLE `SC`(

    `Sno` varchar(9) ,
    `Cno` varchar(4) ,
    `Grade` SMALLINT,
    PRIMARY KEY (Sno,Cno),
    CONSTRAINT Sc_s_key FOREIGN KEY(Sno) REFERENCES Student(Sno),
    CONSTRAINT Sc_c_key FOREIGN KEY (Cno) REFERENCES C(Cno)
 
); 




INSERT INTO Student ( Sno,Sname,Sage, Ssex)
VALUES ("20200001","李强",23,"男");
INSERT INTO Student ( Sno,Sname,Sage, Ssex)
VALUES ("20200002","刘丽",22,"女");
INSERT INTO Student ( Sno,Sname,Sage, Ssex)
VALUES ("20200005","张友",22,"男");

INSERT INTO C ( Cno ,CName,Teacher)
VALUES ("K1","C语言","王华");
INSERT INTO C( Cno ,CName,Teacher)
VALUES ("K5","数据库原理","程军");
INSERT INTO C ( Cno ,CName,Teacher)
VALUES ("K8","编译原理","程军");

INSERT INTO SC ( Sno ,Cno,Grade)
VALUES ("20200001","K1",83);
INSERT INTO SC ( Sno ,Cno,Grade)
VALUES ("20200002","K1",85);
INSERT INTO SC ( Sno ,Cno,Grade)
VALUES ("20200005","K1",92);
INSERT INTO SC ( Sno ,Cno,Grade)
VALUES ("20200002","K5",90);
INSERT INTO SC ( Sno ,Cno,Grade)
VALUES ("20200005","K5",84);
INSERT INTO SC ( Sno ,Cno,Grade)
VALUES ("20200005","K8",80);