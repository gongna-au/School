
create database library;
use library;
    
 

create table books (
    id int not null auto_increment,
    name varchar(1024) not null,
    author	varchar(1024) not null,
    price int not null default 0,
    quantity int not null default 1,
    primary key(id)
)DEFAULT CHARACTER SET = utf8;