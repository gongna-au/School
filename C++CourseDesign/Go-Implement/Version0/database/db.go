package database

import (
	"fmt"
	_ "github.com/go-sql-driver/mysql" //加载mysql
	"github.com/jinzhu/gorm"
)

//跟数据库相关
var Eloquent *gorm.DB

//初始化连接数据库
func InitDB() {
	var err error
	Eloquent, err = gorm.Open("mysql", "gongna2:123456@tcp/Test?charset=utf8&parseTime=True&loc=Local")

	if err != nil {
		fmt.Printf("connect DB failed, err:%v\n", err)
		return
	}
	if Eloquent.Error != nil {
		fmt.Printf("database error %v", Eloquent.Error)
	}
}
