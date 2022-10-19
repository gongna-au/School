package main

import (
	"fmt"
	model "github.com/School/C++CourseDesign/Go-Implement/Version0/Model"
	DB "github.com/School/C++CourseDesign/Go-Implement/Version0/database"
	_ "github.com/go-sql-driver/mysql" //加载mysql
	"os"
)

func showMenu() {
	fmt.Println("欢迎登录本系统")
	fmt.Println(">>1.添加书籍")
	fmt.Println(">>2.删除书籍")
	fmt.Println(">>3.查询书籍")
	fmt.Println(">>4.更新书籍")
	fmt.Println(">>5.管理员注册")
	fmt.Println(">>6.管理员登陆")
	fmt.Println(">>7.读者注册")
	fmt.Println(">>8.读者登陆")
	fmt.Println(">>9.读者借书")
	fmt.Println(">>10.读者还书")
	fmt.Println(">>11.退出")

}
func drawtop() {
	fmt.Println("\n                                         Welcome to the library management system                                         \n")
	fmt.Println("\n--------------------------------------------------------------------------------------------------------------------------\n")
}
func drawline() {
	fmt.Println("\n--------------------------------------------------------------------------------------------------------------------------\n")
}

func drawlow() {
	fmt.Println("\n--------------------------------------------------------------------------------------------------------------------------\n")
}

//BookManagementSystem
func main() {
	//程序启动连接数据库
	DB.InitDB()
	defer DB.Eloquent.Close()

	for {
		drawtop()
		showMenu()
		drawlow()
		var option int
		fmt.Scanln(&option)
		switch option {
		case 1:
			drawline()
			model.BookCreate()
			drawline()
		case 2:
			drawline()
			model.BookDelete()
			drawline()
		case 3:
			drawline()
			model.BookSearch()
			drawline()
		case 4:
			drawline()
			model.BookUpdate()
			drawline()
		case 5:
			drawline()
			model.LibrarianRegister()
			drawline()
		case 6:
			drawline()
			model.LibrarianLogin()
			drawline()
		case 7:
			drawline()
			model.ReaderRegister()
			drawline()
		case 8:
			drawline()
			model.ReaderLogin()
			drawline()
		case 9:
			drawline()
			model.ReadBorrowBook()
			drawline()

		case 10:
			drawline()
			model.ReadBackBook()
			drawline()
		case 11:
			fmt.Println("感谢使用！")
			os.Exit(0)
		}

	}
}
