package Model

import (
	//"errors"
	//"github.com/jinzhu/gorm"
	//"errors"
	"errors"
	"fmt"
	//"net/http/internal"

	//"fmt"
	DB "github.com/School/C++CourseDesign/Go-Implement/Version0/database"
	//"github.com/jinzhu/gorm"
)

type ResultSevice interface {
	GetResult() (res []interface{}, err error)
}
type ShowInformationService interface {
	ShowInformation() string
}

func GetResult(r ResultSevice) ([]interface{}, error) {
	switch t := r.(type) {
	case Book:

		res, err := t.GetResult()
		if err != nil {
			fmt.Println(" Book Result Sevice err")
			return []interface{}{}, err
		} else {
			return res, nil
		}
	case Reader:
		res, err := t.GetResult()
		if err != nil {
			fmt.Println(" Reader Result Sevice err")
			return []interface{}{}, err
		} else {
			return res, nil
		}
	case BorrowRecord:
		res, err := t.GetResult()
		if err != nil {
			fmt.Println(" BorrowRecord Result Sevice err")
			return []interface{}{}, err
		} else {
			return res, nil
		}

	}
	return []interface{}{}, nil

}

type UserService interface {
	Register() (err error)
	Login() (err error)
}

func RegisterService(u UserService) {

	switch t := u.(type) {
	case Librarian:

		err := t.Register()
		if err != nil {
			fmt.Println("Librarian register err")
		}
	case Reader:
		err := t.Register()
		if err != nil {
			fmt.Println("Reader register err")
		}
	}
}

func LoginService(u UserService) {
	switch t := u.(type) {
	case Librarian:
		err := t.Login()
		if err != nil {
			fmt.Println("Librarian login err")
		}
	case Reader:
		err := t.Login()
		if err != nil {
			fmt.Println("Reader login err")
		}
	}

}

type Librarian struct {
	ID          int
	LibrarianId string
	Password    string
}

func (lib Librarian) ShowInformation() {
	temp := Librarian{
		LibrarianId: lib.LibrarianId,
		Password:    lib.Password,
	}
	fmt.Println(temp)
}

func (lib Librarian) GetResult() ([]interface{}, error) {
	res := []interface{}{}

	libs := []Librarian{}
	d := DB.Eloquent.Table("librarian_table").Where("librarian_id = ?", lib.LibrarianId).Find(&libs)

	if d.Error != nil {
		return res, d.Error
	} else {
		for _, v := range libs {
			var temp interface{}
			temp = v
			res = append(res, temp)

		}
		return res, nil

	}
}
func (lib Librarian) Register() (err error) {

	d := DB.Eloquent.Table("librarian_table").Create(&lib)
	return d.Error

}

func (lib Librarian) Login() (err error) {
	l := Librarian{}
	d := DB.Eloquent.Table("librarian_table").Where("librarian_id = ? AND password = ?", lib.LibrarianId, lib.Password).First(&l)
	return d.Error
}

type Reader struct {
	ID       int
	ReaderId string
	Password string
}

func (r Reader) ShowInformation() {
	temp := Reader{
		ReaderId: r.ReaderId,
		Password: r.Password,
	}
	fmt.Println(temp)
}
func (r Reader) GetResult() ([]interface{}, error) {
	res := []interface{}{}

	readers := []Reader{}
	d := DB.Eloquent.Table("reader_table").Where("reader_id = ?", r.ReaderId).Find(&readers)

	if d.Error != nil {
		return res, d.Error
	} else {
		for _, v := range readers {
			var temp interface{}
			temp = v
			res = append(res, temp)
		}
		return res, nil

	}
}
func (r Reader) Register() (err error) {

	d := DB.Eloquent.Table("reader_table").Create(&r)
	return d.Error

}

func (r Reader) Login() (err error) {
	result := Reader{}
	d := DB.Eloquent.Table("reader_table").Where("reader_id = ? AND password = ?", r.ReaderId, r.Password).First(&result)

	if d.Error != nil {
		fmt.Println(d.Error)
	}
	return nil

}

func (r Reader) Borrow() (err error) {
	return nil

}
func (r Reader) Search() (err error) {
	for {
		err := r.Login()
		if err != nil {
			fmt.Println("Sorry account or password wrong!Please input again")
		} else {
			break
		}
	}
	return err
}

type CreateService interface {
	Create() (err error)
}

func Create(c CreateService) (err error) {
	switch t := c.(type) {
	case Book:
		err = t.Create()
		if err != nil {
			fmt.Println("Book create err")
		}
	case BorrowRecord:
		err = t.Create()
		if err != nil {
			fmt.Println(" BorrowRecord create err")
		}
	default:

	}

	if err != nil {
		fmt.Printf("CreateService fail")
	}
	return err
}

type SearchService interface {
	Search() (err error)
}

func Search(s SearchService) (err error) {
	switch t := s.(type) {
	case Book:
		err = t.Search()
		if err != nil {
			fmt.Println("Book Search Service err")
		}
	case Reader:
		err = t.Search()
		if err != nil {
			fmt.Println("Reader Search Service err")
		}
	default:
	}
	return err

}

type DeleteService interface {
	Delete() (err error)
}

func Delete(d DeleteService) (err error) {
	switch t := d.(type) {
	case Book:
		err = t.Delete()

	default:
	}
	if err != nil {
		fmt.Println("Book Delete Service err")
	}
	return err

}

type UpdataService interface {
	Updata() (err error)
}

func Updata(u UpdataService) (err error) {
	switch t := u.(type) {
	case Book:
		err = t.Updata()
	default:
	}

	if err != nil {
		fmt.Printf("UpdataService fail")
		return err
	}
	return err

}

type Book struct {
	ID              int
	BookId          string
	BookName        string
	BookInformation string
	BookPrice       int
	BookState       int
}

func (b Book) ShowInformation() string {
	return fmt.Sprintf("BookIBM:%vBookName:%vBookInformation:%vBookPrice:%vBookState:%v\n", b.BookId, b.BookName, b.BookInformation, b.BookPrice, b.BookState)
}

func (b Book) GetResult() ([]interface{}, error) {
	if b.BookName != "" {
		res := []interface{}{}
		books := []Book{}
		d := DB.Eloquent.Table("book_table").Where("book_name = ?", b.BookName).Find(&books)

		if d.Error != nil {
			fmt.Println(d.Error)
			return res, d.Error
		} else {
			for _, v := range books {
				var temp interface{}
				temp = v
				res = append(res, temp)
			}
			return res, nil
		}
	} else if b.BookId != "" {
		res := []interface{}{}
		books := []Book{}
		d := DB.Eloquent.Table("book_table").Where("book_id = ?", b.BookId).Find(&books)
		if d.Error != nil {
			return res, d.Error
		} else {
			for _, v := range books {
				var temp interface{}
				temp = v
				res = append(res, temp)
			}
			return res, nil
		}

	} else if b.BookInformation != "" {
		res := []interface{}{}
		books := []Book{}
		d := DB.Eloquent.Table("book_table").Where("book_information like ?", "%"+b.BookInformation).Find(&books)
		if d.Error != nil {
			return res, d.Error
		} else {
			for _, v := range books {
				var temp interface{}
				temp = v
				res = append(res, temp)
			}
			return res, nil
		}

	} else {
		return []interface{}{}, errors.New("Please input some information to search !")
	}

}

func (b Book) TableName() string {
	return "book_table"
}

func (b Book) Create() (err error) {
	fmt.Print("before", b)
	d := DB.Eloquent.Table("book_table").Create(&b)
	fmt.Print("after", b)
	return d.Error

}
func (b Book) Search() (err error) {
	books := []Book{}
	d := DB.Eloquent.Table("book_table").Where("book_name = ?", b.BookName).Find(&books)
	if d.Error != nil {
		fmt.Println(d.Error)
		return d.Error
	} else {
		fmt.Println(books)
		return nil
	}

}

func (b Book) Delete() (err error) {

	d := DB.Eloquent.Table("book_table").Where("book_id = ?", b.BookId).Delete(&b)
	return d.Error
}
func (b Book) Updata() (err error) {
	if b.ID != 0 {
		if b.BookState == 200 {
			d := DB.Eloquent.Model(&Book{ID: b.ID}).Update("book_state", 400)

			if d.Error != nil {
				fmt.Println(d.Error)
				return errors.New("Update book state fail!")
			} else {
				return nil

			}
		} else if b.BookState == 400 {
			d := DB.Eloquent.Model(&Book{ID: b.ID}).Update("book_state", 200)
			if d.Error != nil {
				fmt.Println(d.Error)
				return errors.New("Update book state fail!")
			} else {
				return nil

			}
		} else {
			return errors.New(" book state wrong")
		}
	} else if b.ID != 0 && b.BookId != "" && b.BookInformation != "" && b.BookName != "" {
		d := DB.Eloquent.Model(&Book{ID: b.ID}).Updates(Book{BookName: b.BookName, BookInformation: b.BookInformation})
		if d.Error != nil {
			fmt.Println(d.Error)
			return errors.New("Update book information fail!")
		} else {
			return nil
		}
	}
	return nil

}

type BorrowService interface {
	Borrow() (err error)
}

func Borrow(b BorrowService) (err error) {

	switch t := b.(type) {
	case Reader:
		err = t.Borrow()
	default:
	}

	if err != nil {
		fmt.Printf("BorrowService fail")
	}
	return err

}

type BorrowRecord struct {
	ID       int
	BookId   string
	ReaderId string
}

func (b BorrowRecord) GetResult() ([]interface{}, error) {
	res := []interface{}{}
	records := []BorrowRecord{}
	d := DB.Eloquent.Table("borrow_table").Where("reader_id = ?", b.ReaderId).Find(&records)
	if d.Error != nil {
		fmt.Println(d.Error)
		return []interface{}{}, d.Error
	}

	if d.Error != nil {
		fmt.Println(d.Error)
		return res, d.Error
	} else {
		for _, v := range records {
			res = append(res, interface{}(v))
		}

		return res, nil
	}

}

func (b BorrowRecord) TableName() string {
	return "borrow_table"
}

func (b BorrowRecord) Create() (err error) {
	d := DB.Eloquent.Table("borrow_table").Create(&b)
	if d.Error != nil {
		fmt.Println(d.Error)
		return d.Error
	} else {
		fmt.Println("record create success!")
		return nil
	}

}
func (b BorrowRecord) Search() (err error) {
	var records []BorrowRecord
	d := DB.Eloquent.Table("borrow_table").Where("reader_id = ?", b.ReaderId).First(&records)
	if d.Error != nil {
		fmt.Println(d.Error)
	} else {
		fmt.Println(records)
	}
	return d.Error
}
func (b BorrowRecord) Delete() (err error) {

	book := Book{}
	d2 := DB.Eloquent.Table("book_table").Where("book_id = ?", b.BookId).First(&book)
	if d2 != nil {
		fmt.Println(d2)
	} else {
		fmt.Println(book)
	}
	d1 := DB.Eloquent.Table("borrow_table").Where("book_id = ? AND reader_id = ?", b.BookId, b.ReaderId).Delete(&b)
	if d1 != nil {
		fmt.Println(d1)
	} else {
		fmt.Println(b)
	}
	bookAfterChange := Book{
		book.ID,
		book.BookId,
		book.BookName,
		book.BookInformation,
		book.BookPrice,
		200,
		//200代表没有被借走了
		//400代表被借走了
	}
	d := DB.Eloquent.Table("book_table").Where("book_id = ?", bookAfterChange.BookId).Save(&bookAfterChange)
	return d.Error
}
func (b BorrowRecord) Updata() (err error) {

	return nil
}
