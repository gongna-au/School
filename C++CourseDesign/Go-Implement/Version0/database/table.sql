drop  database  if  exists `Test`;
create database `Test`;
USE `Test`; 

/* CREATE TRIGGER `trigger_user_add` after insert
on `user_table` for each row
begin 
declare c int;
set c=(slect max(rank) from user);
update user set rank = c+1 where id = new.id;
end
 */
CREATE TABLE `book_table`(
    `id` bigint(20) AUTO_INCREMENT PRIMARY KEY ,
    `book_id`  varchar (20) UNIQUE ,
    `book_name` varchar (20) NOT NULL ,
    `book_information` varchar (100) NOT NULL ,
    `book_price` int    NOT  NULL,
    `book_state` int    NOT  NULL 
)ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=UTF8MB4;


CREATE TABLE `librarian_table`(
    `id` bigint(20) AUTO_INCREMENT PRIMARY KEY ,
    `librarian_id` bigint(20)   UNIQUE, 
    `password` varchar (20) NOT NULL 
    
)ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=UTF8MB4;

CREATE TABLE `reader_table`(
    `id` bigint(20) AUTO_INCREMENT PRIMARY KEY ,
    `reader_id` bigint(20)   UNIQUE, 
    `password` varchar (20) NOT NULL 

)ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=UTF8MB4;

CREATE TABLE `borrow_table`(
    `id` bigint(20) AUTO_INCREMENT PRIMARY KEY ,
    `book_id` varchar (20) NOT NULL ,
    `reader_id` bigint(20)  NOT NULL

)ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=UTF8MB4;




