package Model

import (
	"fmt"
)

func LibrarianRegister() {
	lib := Librarian{}

	fmt.Println("请根据提示输入相关内容")
	fmt.Print("请输入管理员账号：")
	fmt.Scanln(&lib.LibrarianId)
	fmt.Print("请输入管理员密码：")
	fmt.Scanln(&lib.Password)

	RegisterService(lib)
}
func ReaderRegister() {
	reader := Reader{}

	fmt.Println("请根据提示输入相关内容")
	fmt.Print("请输入读者账号：")
	fmt.Scanln(&reader.ReaderId)
	fmt.Print("请输入读者密码：")
	fmt.Scanln(&reader.Password)
	RegisterService(reader)
}
func LibrarianLogin() {
	lib := Librarian{}

	fmt.Println("请根据提示输入相关内容")
	fmt.Print("请输入管理员账号：")
	fmt.Scanln(&lib.LibrarianId)
	fmt.Print("请输入管理员密码：")
	fmt.Scanln(&lib.Password)
	LoginService(lib)
}
func ReaderLogin() {
	reader := Reader{}

	fmt.Println("请根据提示输入相关内容")
	fmt.Print("请输入读者账号：")
	fmt.Scanln(&reader.ReaderId)
	fmt.Print("请输入读者密码：")
	fmt.Scanln(&reader.Password)
	LoginService(reader)
}
func BookCreate() {
	book := Book{}
	fmt.Println("请根据提示输入相关内容")
	fmt.Print("请输入书籍IBM：")
	fmt.Scanln(&book.BookId)
	fmt.Print("请输入书籍名称：")
	fmt.Scanln(&book.BookName)
	fmt.Print("请输入书籍信息：")
	fmt.Scanln(&book.BookInformation)
	fmt.Print("请输入书籍价格：")
	fmt.Scanln(&book.BookPrice)
	book.BookState = 200
	fmt.Println(book)
	Create(book)
}
func BookDelete() {
	book := Book{}
	fmt.Println("请根据提示输入相关内容")
	fmt.Print("请输入书籍IBM：")
	fmt.Scanln(&book.BookId)
	Delete(book)
}
func BookUpdate() {
	book := Book{}
	fmt.Println("请根据提示输入相关内容")
	fmt.Print("请输入书籍IBM：")
	fmt.Scanln(&book.BookId)
	Updata(book)
}
func BookSearch() {
	book := Book{}
	fmt.Println("请根据提示输入相关内容")
	fmt.Print("请输入书籍名称：")
	fmt.Scanln(&book.BookName)
	Search(book)

}
func ReadBorrowBook() {
	//读者身份验证
	choseInformation := BorrowRecord{}
	reader := Reader{}
	res := []interface{}{}

	for {
		var err error
		fmt.Print("请输入读者账号：")
		fmt.Scanln(&reader.ReaderId)
		fmt.Print("请输入读者账号密码：")
		fmt.Scanln(&reader.Password)
		err = reader.Login()
		if err != nil {
			fmt.Println("Sorry account or password wrong!Please input again")
		} else {
			fmt.Println("Login success!")
			choseInformation.ReaderId = reader.ReaderId
			break
		}
	}
	bookState := []string{}
	bookIduserCanChose := []string{}
	//根据书籍名称查
	for {
		var err error
		book := Book{}
		fmt.Println("请根据提示输入相关内容")
		fmt.Print("请输入书籍名称：")
		fmt.Scanln(&book.BookName)
		res, err = GetResult(book)
		if err != nil {
			fmt.Println("Books you are finding are not exists!")
		} else {

			fmt.Print("Search success !\n")
			for _, v := range res {
				switch t := v.(type) {
				case Book:
					str := fmt.Sprintf("BookId:%vBookState:%v", t.BookId, t.BookState)
					bookState = append(bookState, str)
					bookIduserCanChose = append(bookIduserCanChose, t.BookId)
				}
			}
			break
		}
	}
	fmt.Println("200 represent can be borrowed/400 represent can not be borrowed!")
	fmt.Println(bookState)

	for {
		var err error
		temp := Book{}
		//根据书籍bookID查
		fmt.Print("请输入你要借阅的书籍ID：")
		fmt.Scanln(&temp.BookId)
		if InSlice(bookIduserCanChose, temp.BookId) {
			choseInformation.BookId = temp.BookId
			res, err = GetResult(temp)
			if err != nil {
				fmt.Println(err)
			} else {
				switch t := res[0].(type) {
				case Book:
					temp.ID = t.ID
					temp.BookState = t.BookState
					if t.BookState == 400 {
						fmt.Println("Sorry ,book has been borrowed!")
					} else if t.BookState == 200 {
						err = Updata(temp)
						if err != nil {
							fmt.Println(err)
						} else {
							err = Create(choseInformation)
							if err != nil {
								fmt.Println(err)
							} else {
								return
							}

						}

					}

				}

			}
			break
		} else {
			continue
		}
	}

}
func ReadBackBook() {
	//读者身份验证
	choseInformation := BorrowRecord{}
	reader := Reader{}
	res := []interface{}{}

	for {
		var err error
		fmt.Print("请输入读者账号：")
		fmt.Scanln(&reader.ReaderId)
		fmt.Print("请输入读者账号密码：")
		fmt.Scanln(&reader.Password)
		err = reader.Login()
		if err != nil {
			fmt.Println("Sorry account or password wrong!Please input again")
		} else {
			fmt.Println("Login success!")
			choseInformation.ReaderId = reader.ReaderId
			break
		}
	}
	var err error

	bookBorrow := []string{}
	bookBorrowId := []string{}
	res, err = GetResult(choseInformation)

	if err != nil {
		fmt.Println("You do not borrow any books!")
		return
	} else {
		for k, v := range res {
			switch t := v.(type) {
			case BorrowRecord:
				if k == 0 {
					fmt.Println("ReadId:=", t.ReaderId)
				}
				str := fmt.Sprintf("BookId:%v", t.BookId)
				str2 := fmt.Sprintf("%v", t.BookId)

				bookBorrow = append(bookBorrow, str)
				bookBorrowId = append(bookBorrowId, str2)

			}
		}
		fmt.Println("You borrow Information")
		fmt.Println(bookBorrow)

	}
	for {
		var err error
		temp := Book{}
		//根据书籍bookID查
		fmt.Print("请输入你要归还的书籍ID：")
		fmt.Scanln(&temp.BookId)
		if InSlice(bookBorrowId, temp.BookId) {

			res, err = GetResult(temp)
			if err != nil {
				fmt.Println(err)
			} else {
				fmt.Println(res)
				switch t := res[0].(type) {
				case Book:
					temp.ID = t.ID
					temp.BookState = t.BookState
					if t.BookState == 400 {
						err = Updata(temp)
						if err != nil {
							fmt.Println(err)
						} else {
							err = Delete(choseInformation)
							if err != nil {
								fmt.Println(err)
							} else {
								return
							}

						}

					} else if t.BookState == 200 {
						fmt.Println("The book you have back ")

					}

				}

			}

		}

	}

}

func InSlice(items []string, item string) bool {
	for _, eachItem := range items {
		if eachItem == item {
			return true
		}
	}
	return false
}
