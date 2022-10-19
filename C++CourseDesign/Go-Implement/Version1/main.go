package main

import (
	"errors"
	"fmt"
	"time"

	//"net/http/internal"

	//"net/http/internal"
	"reflect"
	"regexp"
	"runtime"

	"strings"
	//"strconv"
	//"github.com/gin-vue-admin/server/model/system/response"
)

//用户一旦登陆就立即保存用户的登陆状态

var userToken string
var limitNum int

//拓展的功能的初步想法是
//设置一个时间的限制 超过时间后就需要用户重新登陆 也就是判断 userToken是否为空字符串 如果为空就需要执行主页面，要求用户重新登陆
//如果有时间就补充，没有时间就摆烂

// Observable 被观察者
type Observable interface {
	Attach(observer ...ObserverInterface) Observable
	Detach(observer ObserverInterface) Observable
	Notify() error
}

// ObservableConcrete 一个具体的订单状态变化的被观察者
type ObservableConcrete struct {
	observerList []ObserverInterface
}

// ObserverInterface 定义一个观察者的接口
type ObserverInterface interface {
	// 自身的业务
	Do(o Observable) error
}

//-----------------------Observable-------------------------
// Attach 注册观察者
// @param $observer ObserverInterface 观察者列表
// Attach 注册观察者
// @param $observer ObserverInterface 观察者列表
func (o *ObservableConcrete) Attach(observer ...ObserverInterface) Observable {
	o.observerList = append(o.observerList, observer...)
	return o
}

// Detach 注销观察者
// @param $observer ObserverInterface 待注销的观察者
func (o *ObservableConcrete) Detach(observer ObserverInterface) Observable {
	if len(o.observerList) == 0 {
		return o
	}
	for k, observerItem := range o.observerList {
		if observer == observerItem {
			fmt.Println(runFuncName(), "注销:", reflect.TypeOf(observer))
			o.observerList = append(o.observerList[:k], o.observerList[k+1:]...)
		}
	}
	return o
}

// Notify 通知观察者
func (o *ObservableConcrete) Notify() (err error) {
	// code ...
	for _, observer := range o.observerList {
		if err = observer.Do(o); err != nil {
			return err
		}
	}
	return nil
}

func ErrRespond(str string, err error) error {

	if err != nil {
		fmt.Println(str, "\tfunction Error")
		fmt.Printf("err=%v", err)
		return err
	} else {
		return nil
	}

}

//---------------------------------------------------------------------------------

//-----------------------------ObserverInterface---------------------
// OrderSt
type GeneralUserCreate struct {
	//用户类别  1 为超级用户 其他为普通用户
	Category           string
	DetailsInformation map[string]interface{}
}

//输入信息
func (u *GeneralUserCreate) Input() error {
	u.DetailsInformation = make(map[string]interface{})
	u.Category = "genera"
	var temp string
	fmt.Println("Please input userId:")
	fmt.Scan(&temp)
	_, err := regexp.MatchString("^[0-1]{1}$", temp)
	if err != nil {
		return errors.New("wrong happend in input user userId:")
	} else {
		u.DetailsInformation["userId"] = temp

	}
	fmt.Println("Please input user password:")
	fmt.Scan(&temp)
	_, err = regexp.MatchString("^[0-9a-zA-Z]{6,30}$", temp)
	if err != nil {
		return errors.New("wrong happend in input user password password length 6~30")
	}

	u.DetailsInformation["password"] = temp
	return nil

}

//插入数据库
func (u *GeneralUserCreate) Create() (err error) {
	//把数据和model绑定
	fmt.Println(" New user has been created!")
	return nil
}

// Do 具体业务
func (observer *GeneralUserCreate) Do(o Observable) (err error) {
	WaitingForLegalInput(observer)
	observer.Create()
	//observer输入完毕
	fmt.Println(runFuncName(), "新增用户相关的操作处理完毕...")
	return nil
}

//---------------------------------------------------------
type UserDelete struct {
	//用户类别  true 为超级用户 其他为普通用户
	userId   string
	password string
}

func (u *UserDelete) Input() (err error) {

	fmt.Println("Please input user Id:")
	fmt.Scan(&u.userId)
	_, err = regexp.MatchString("^[0-1]{10}$", u.userId)
	if err != nil {
		return errors.New("wrong happend in input user userId")
	}

	fmt.Println("Please input user password:")
	fmt.Scan(&u.password)
	_, err = regexp.MatchString("^[0-9a-zA-Z]{6,30}$", u.password)
	if err != nil {
		return errors.New("wrong happend in input user password")
	}

	return nil

}
func (u *UserDelete) Verify() (err error) {
	fmt.Println("Verify.....")
	return err
}
func (u *UserDelete) Search() (err error) {
	fmt.Println("User searching in DB...")

	return nil
}
func (u *UserDelete) Delete() (err error) {

	fmt.Println("User has been deleted!")
	return nil
}

// Do 具体业务
func (observer *UserDelete) Do(o Observable) (err error) {
	WaitingForLegalInput(observer)
	observer.Search()
	observer.Verify()
	observer.Delete()
	fmt.Println(runFuncName(), "删除用户相关的操作处理完毕...")
	return nil
}

// BookCreate-------------------------------------------------------
type BookCreate struct {
	DetailsInformation map[string]interface{}
}

func NewBookCreate() *BookCreate {
	b := &BookCreate{}
	b.DetailsInformation = make(map[string]interface{})
	return b
}

func (b *BookCreate) Input() (err error) {

	b.DetailsInformation = make(map[string]interface{})

	prompt := NewPrompt()
	prompt.Show("bookClassification")
	classificationMap := map[string]bool{"A": true, "B": true, "C": true, "D": true, "E": true, "F": true, "G": true, "H": true, "I": true, "J": true, "K": true, "N": true, "O": true, "P": true, "Q": true, "R": true, "S": true, "T": true, "U": true, "V": true, "X": true, "Z": true}

	var temp string
	fmt.Print("Please input book classification:")
	fmt.Scanln(&temp)
	if classificationMap[temp] != true {
		return errors.New("wrong happend in input")
	} else {
		b.DetailsInformation["classification"] = temp
	}

	fmt.Print("Please input Book Author：")
	fmt.Scanln(&temp)
	b.DetailsInformation["bookAuthor"] = temp

	fmt.Print("Please input Book Name：")
	fmt.Scanln(&temp)
	b.DetailsInformation["bookName"] = temp

	fmt.Print("Please input Book Price:：")
	fmt.Scanln(&temp)
	b.DetailsInformation["bookPrice"] = temp

	fmt.Print("Please enter whether to put on the shelf (Y|N）or(y|n)[ Y-Yes| N-No ]")
	//y Y代表书籍是上架的状态
	fmt.Scanln(&temp)

	if strings.ToLower(string(temp[0])) == "y" {
		b.DetailsInformation["bookState"] = "y"
	} else if strings.ToLower(temp) == "n" {
		b.DetailsInformation["bookState"] = "n"
	} else {
		return errors.New("wrong happend in input")
	}
	//"classification"  "bookState"   "bookPrice" "bookAuthor"
	return err

}
func (b *BookCreate) Create() (err error) {

	fmt.Println("Book has been created!")
	return err
}

// Do 具体业务
func (observer *BookCreate) Do(o Observable) (err error) {
	// code...
	observer = NewBookCreate()
	WaitingForLegalInput(observer)
	fmt.Println(observer.DetailsInformation)
	observer.Create()
	fmt.Println(runFuncName(), "新增书籍相关的操作已处理完毕...")
	return nil
}

type Prompt struct {
	prompt map[string]interface{}
}

func NewPrompt() *Prompt {
	p := &Prompt{
		make(map[string]interface{}),
	}
	p.prompt["bookClassification"] = "\nA马克思主义、列宁主义、毛泽东思想、邓小平理论\nB哲学、宗教\nC社会科学总论\nD政治、法律\nE军事\nF经济\nG文化、科学、教育、体育\nH语言、文字\nI文学\nJ艺术\nK历史、地理\nN自然科学总论\nO数理科学和化学\nP天文学、地球科学\nQ生物科学\nR医药、卫生\nS农业科学\nT工业技术\nU交通运输\nV航空、航天\nX环境科学、安全科学\nZ综合性图书\n"
	p.prompt["bookClassificationMap"] = map[string]string{"A": "马克思主义、列宁主义、毛泽东思想、邓小平理论", "B": "哲学、宗教", "C": "社会科学总论", "D": "政治、法律", "E": "军事", "F": "经济", "G": "文化、科学、教育、体育", "H": "语言、文字", "I": "文学", "J": "艺术", "K": "历史、地理", "N": "自然科学总论", "O": "数理科学和化学", "P": "天文学、地球科学", "Q": "生物科学", "R": "医药、卫生", "S": "农业科学", "T": "工业技术", "U": "交通运输", "V": "航空、航天", "X": "环境科学、安全科学", "Z": "综合性图书"}

	//其他的提示信息
	p.prompt["bookSearchInfo"] = "\n1.bookName书籍名查找\n2.bookKey其他有关书籍的信息\n3.bookAuthor书籍作者\n4.bookClassification书籍分类查找\n5.bookState根据书籍的借阅状态查\n"
	p.prompt["bookSearchInfoMap"] = map[string]string{"1": "bookName", "2": "bookKey", "3": "bookAuthor", "4": "bookClassification", "5": "bookState"}
	return p
}
func (p *Prompt) Show(str string) {
	//classificationMap := map[string]bool{"00": true, "10": true, "20": true, "21": true, "27": true, "31": true, "34": true, "36": true, "37": true, "41": true, "42": true, "48": true, "49": true, "50": true, "51": true, "52": true, "53": true, "54": true, "55": true, "56": true, "58": true, "61": true, "65": true, "71": true, "90": true}
	fmt.Println(p.prompt[str])

}

type BookSearch struct {
	target string
	key    map[string]interface{}
}

func (b *BookSearch) Input() (err error) {
	p := NewPrompt()

	fmt.Println(p.prompt["bookSearchInfo"])
	fmt.Print("Please input your choice:")
	var temp string
	fmt.Scan(&temp)
	switch k := p.prompt["bookSearchInfoMap"].(type) {
	case map[string]string:

		v, ok := k[temp]
		if ok {
			b.target = v
		} else {
			return errors.New("Input illegal!")
		}
	}
	return nil
}

func NewBookSerach() *BookSearch {
	b := &BookSearch{
		"",
		make(map[string]interface{}),
	}
	b.key["bookName"] = ""
	//关键字查找
	b.key["bookKey"] = ""
	//作者查
	b.key["bookAuthor"] = ""
	//书籍分类查找
	b.key["bookClassification"] = ""
	//根据书籍的借阅状态查
	b.key["bookState"] = ""

	b.key["result"] = ""

	return b

}

func (b *BookSearch) Search() (err error) {

	//已经知道用户是想要按照什么类别来查找了 b.target
	fmt.Println("Acording ", b.target, " to search......")
	p := NewPrompt()
	// 只有当b.target == bookClassification时我才会展示书籍的分类 ,得到用户的输入然后拿一个字母去数据库查找
	// 其他的情况都是模糊查找，直接拿数据去查，而不是精确查找
	if b.target == "bookClassification" {
		p.Show(b.target)
	} else if b.target == "bookState" {
		fmt.Println("目前本图书馆可以借阅的书籍有:.....")
		b.key["result"] = "平凡的世界\n楚门的世界\n生命不能承受之重\n"
		fmt.Println(b.key["result"])
		return nil
	} else {
		fmt.Println("Reminder: Please enter no more than 30 letters to find......")
	}
	var temp string
	fmt.Scanf("%30s", &temp)
	b.key[b.target] = temp
	//fmt.Println("b.key[b.target]", b.key[b.target])
	// b.key已经被赋值，现在根据b.target 以及查找所需要的数据去数据库查找了
	fmt.Println("Searching in DB...")
	//把查找到的所有的结果都存放在result键值对里面
	b.key["result"] = map[string]interface{}{"Id": 1, "classification": "A", "bookState": "y", "bookPrice": 100, "bookAuthor": "鲁迅"}
	fmt.Println("Searching in DB success!")
	//打印查询结果
	//b.SerchInDB()Result 获取到结果 存储在Result里面
	//如果想要对Result.result 做进一步的处理，就继续写个函数
	//如果不处理就直接打印或者存储
	fmt.Println("Results are ......", b.key["result"])
	//在数据库查询结果并存储

	return nil

}

// Do 具体业务
func (observer *BookSearch) Do(o Observable) (err error) {
	// code..
	observer = NewBookSerach()
	WaitingForLegalInput(observer)
	observer.Search()
	fmt.Println(runFuncName(), "查询书籍相关的操作已经处理完毕...")

	return
}

//---------------------------------------------------------
type Result struct {
	response string
	result   []interface{}
}

func NewResult() *Result {

	return &Result{}

}

func (b *Result) Show() (err error) {

	fmt.Println("Result are: ", b.result)
	return err
}

// Do 具体业务
func (observer *Result) Do(o Observable) (err error) {
	// code..
	observer = NewResult()
	//存储数据库信息
	fmt.Println("Result Stored")
	observer.Show()
	fmt.Println(runFuncName(), "展示相关结果.已经处理完毕...")
	return nil
}

// 获取正在运行的函数名
func runFuncName() string {
	pc := make([]uintptr, 1)
	runtime.Callers(2, pc)
	f := runtime.FuncForPC(pc[0])
	return f.Name()
}

//----------------------------------------另外的设计

type Button struct {
	information string
	bePressed   int
	orders      []ObserverInterfaceSlice
}
type ObserverInterfaceSlice []ObserverInterface

func newButton(info string) *Button {
	b := &Button{}
	b.information = info
	return b
}
func (b *Button) showPageInformation() {
	fmt.Println(b.information)
}

func (b *Button) listenButtonBePressed() {
	fmt.Scan(&b.bePressed)
	fmt.Println(b.bePressed, "button is  pressed.....")

}

//--------------------------------------------

type UserLogin struct {
	userId   string
	password string
}

func (u *UserLogin) Login() error {
	//拿着userId password杂u数据库里面查找
	//找到了
	fmt.Println("User login success!")
	return nil
}
func (u *UserLogin) Input() (err error) {
	fmt.Println("Please input user Id:")
	fmt.Scan(&u.userId)
	_, err = regexp.MatchString("^[0-1]{10}$", u.userId)
	if err != nil {
		return errors.New("wrong happend in input user userId")
	}

	fmt.Println("Please input user password:")
	fmt.Scan(&u.password)
	_, err = regexp.MatchString("^[0-9a-zA-Z]{6,30}$", u.password)
	if err != nil {
		return errors.New("wrong happend in input user password")
	}

	return nil

}

func (u *UserLogin) Search() (err error) {
	fmt.Println("User password and account search success!")
	return nil
}

// Do 具体业务
func (observer *UserLogin) Do(o Observable) (err error) {
	// code...
	WaitingForLegalInput(observer)
	err = observer.Login()
	//登陆成功才会更改userToken
	if err == nil {
		userToken = observer.userId
	}
	fmt.Println(runFuncName(), "用户登陆的相关的操作已处理完毕...")
	return nil
}
func limitNumInit() {
	limitNum = 4
	//其他限制的初始化

}

// 客户端调用
func main() {
	//每个人最多可以借四本书 等等
	limitNumInit()
	app := NewApp()
	app.Run()
	// 未来可以快速的根据业务的变化 创建新的主题 从而快速构建新的业务接口
	fmt.Println("----------------------- 未来的扩展...")

}

//------------------------其他的函数

type Inputinterface interface {
	Input() error
}

func WaitingForLegalInput(w Inputinterface) {
	for {
		err := w.Input()
		if err == nil {
			break
		} else {
			fmt.Println("Illegal input, Please input again!")
		}

	}

}

type ButtonFunc func()

type App struct {
	funcNum  int
	funcList []ButtonFunc
}

//------------------------------------------------------------------------
func MainPageOrdersInit() []ObserverInterfaceSlice {
	orders := []ObserverInterfaceSlice{
		{
			&GeneralUserCreate{},

			//这是一个切片
			//还可以添加更多的切片
		},
		{
			&UserLogin{},
		},
		{
			&BookSearch{},
		},
		//超级管理员登陆
		{
			&RootUser{},
		},
		//退出App

	}

	return orders

}

func (a *App) MainPageAppFuncListChangeInit() []ButtonFunc {
	/*

	 */

	appFuncListChange := []ButtonFunc{
		a.PageMain,
		a.PageSubtitle1,
		a.PageMain,
		a.PageSubtitle2,
	}
	return appFuncListChange
}
func (a *App) Subtitle1PageOrdersInit() []ObserverInterfaceSlice {

	orders := []ObserverInterfaceSlice{
		{
			//之后更改 &BookBorrow{}
			&BookBorrow{},
		},
		{
			//之后更改 &BookBack{}
			&BookBack{},
		},
		{
			//之后更改
			&BookSearch{},
		},
		{
			//之后更改&BookBorrowedRecord
			&BookBorrowedRecord{},
		},
	}

	return orders

}
func (a *App) Subtitle1PageFuncListChangeInit() []ButtonFunc {

	appFuncListChange := []ButtonFunc{
		a.PageSubtitle1,
		a.PageSubtitle1,
		a.PageSubtitle1,
		a.PageSubtitle1,
	}
	return appFuncListChange

}

//------------------------------------------------------------------------------------
func NewApp() *App {
	a := &App{
		funcNum: 1,
	}
	orders := MainPageOrdersInit()
	appFuncListChange := a.MainPageAppFuncListChangeInit()
	pageMainStr := ">>1.用户注册\n>>2.用户登陆\n>>3.书籍查询\n>>4.图书管理员登陆\n"
	a.Page(pageMainStr, orders, appFuncListChange)
	return a
}

func (a *App) AppFuncListChange(b ButtonFunc) {
	a.funcList = append(a.funcList, b)
	a.funcNum = a.funcNum + 1
}

func (a *App) Run() {

	for i := 0; i < a.funcNum; i++ {
		fmt.Println("这是第 ", i, "次执行")
		a.funcList[i]()
	}
}

//a.PageMain
//[]ButtonFunc{a.PageMain,a.PageSubtitle1,a.PageMain}
func (a *App) Page(str string, orders []ObserverInterfaceSlice, appFuncListChange []ButtonFunc) {
	button := newButton(str)
	button.showPageInformation()
	button.listenButtonBePressed()
	splitStr := strings.Split(str, "\n")
	//执行按钮对应的函数
	a.ExecuteItem(splitStr[button.bePressed-1], orders[button.bePressed-1])
	//添加下一个要执行的函数到队列
	a.AppFuncListChange(appFuncListChange[button.bePressed-1])
	a.funcNum = a.funcNum + 1
}

func (a *App) PageMain() {

	str := ">>1.用户注册\n>>2.用户登陆\n>>3.书籍查询\n"
	button := newButton(str)
	//页面按钮信息展示
	button.showPageInformation()
	//监听哪个按钮被按下
	button.listenButtonBePressed()

	//页面按钮选项
	orders := []ObserverInterfaceSlice{
		{
			&GeneralUserCreate{},
		},
		{
			&UserLogin{},
		},
		{
			&BookSearch{},
		},
	}
	splitStr := strings.Split(str, "\n")
	//执行按钮对应的函数

	a.ExecuteItem(splitStr[button.bePressed-1], orders[button.bePressed-1])
	//并展示这个按钮对应的下一个要执行的函数 把他添加到
	if button.bePressed == 1 {
		a.AppFuncListChange(a.PageMain)
	} else if button.bePressed == 2 {
		a.AppFuncListChange(a.PageSubtitle1)
	} else if button.bePressed == 3 {
		a.AppFuncListChange(a.PageMain)
	}

}

func (a *App) PageSubtitle1() {
	str := ">>1.借书\n>>2.还书\n>>3.查询书籍\n>>4.查看借阅记录"
	button := newButton(str)
	button.showPageInformation()
	button.listenButtonBePressed()
	splitStr := strings.Split(str, "\n")
	orders := []ObserverInterfaceSlice{
		{
			//之后更改 &BookBorrow{}
			&BookBorrow{},
		},
		{
			//之后更改 &BookBack{}
			&BookBack{},
		},
		{
			//之后更改
			&BookSearch{},
		},
		{
			//之后更改&BookBorrowedRecord
			&BookBorrowedRecord{},
		},
	}
	//执行按钮对应的函数
	a.ExecuteItem(splitStr[button.bePressed-1], orders[button.bePressed-1])
	//并展示这个按钮对应的下一个要执行的函数 把他添加到
	if button.bePressed == 1 {
		a.AppFuncListChange(a.PageSubtitle1)
	} else if button.bePressed == 2 {
		a.AppFuncListChange(a.PageSubtitle1)
	} else if button.bePressed == 3 {
		a.AppFuncListChange(a.PageSubtitle1)
	} else {
		a.AppFuncListChange(a.PageSubtitle1)
	}

}
func (a *App) PageSubtitle2() {
	str := ">>1.上架书籍\n>>2.下架书籍\n>>3.查询书籍\n>>4.查看读者借阅记录"
	button := newButton(str)
	button.showPageInformation()
	button.listenButtonBePressed()
	splitStr := strings.Split(str, "\n")
	orders := []ObserverInterfaceSlice{
		{
			//之后更改 &BookBorrow{}
			&BookCreate{},
		},
		{
			//之后更改 &BookBack{}
			&BookRemove{},
		},
		{
			//之后更改
			&BookSearch{},
		},
		{
			//之后更改&BookBorrowedRecord
			&BookBorrowedRecord{},
		},
	}
	//执行按钮对应的函数
	a.ExecuteItem(splitStr[button.bePressed-1], orders[button.bePressed-1])
	//并展示这个按钮对应的下一个要执行的函数 把他添加到
	if button.bePressed == 1 {
		a.AppFuncListChange(a.PageSubtitle2)
	} else if button.bePressed == 2 {
		a.AppFuncListChange(a.PageSubtitle2)
	} else if button.bePressed == 3 {
		a.AppFuncListChange(a.PageSubtitle2)
	} else {
		a.AppFuncListChange(a.PageSubtitle2)
	}

}

type BookBorrow struct {
	//是否处在处罚时间内 如果用户处于处罚时间内他将不可以借书
	IsInPenaltyTime bool
	//用户借书的时候应该需要知道这个用户已经借了几本书借书的数量应该有限制
	borrowUserHasBorrowBookNum int
	//borrowUserId 是用户登陆的账号
	borrowUserId string
	//borrowedBook 是借书过程，我们通过数据库得到的书籍的信息
	borrowedBook string
	//通过这两个数据可以新增一个借书记录在数据库当中
}

func NewBookBorrow() *BookBorrow {
	b := &BookBorrow{}
	return b

}
func (b *BookBorrow) Input() error {
	if userToken != "" {
		b.borrowUserId = userToken
	} else {
		fmt.Println("Login timed out! Please login again!")
		u := &UserLogin{}
		WaitingForLegalInput(u)
		err := u.Login()
		//登陆成功才会更改userToken
		if err == nil {
			b.borrowUserId = userToken
		}
		fmt.Println("用户重新登陆成功...")
	}
	chooseBook := NewBookSerach()
	WaitingForLegalInput(chooseBook)
	chooseBook.Search()
	//将查到的书籍的结果存储
	value, ok := chooseBook.key["result"]
	if ok {
		switch v := value.(type) {
		case string:
			b.borrowedBook = v

		}
	} else {
		fmt.Println("No books selected")
	}

	fmt.Println(b)
	//拿着数据去数据库增加借阅记录，以及更该书籍被借阅的状态
	fmt.Println(runFuncName(), "存储借书相关的信息已经处理完毕...")
	return nil

}

func (b *BookBorrow) Create() error {
	fmt.Println("Borrow Record Create ....")
	fmt.Println("User:", b.borrowUserId, "has succeeded borrowed book ", b.borrowedBook)
	return nil
}
func (b *BookBorrow) Update() error {
	fmt.Println("Borrow State Update ....")
	fmt.Println(b.borrowedBook, "state has changed")
	return nil
}

func (b *BookBorrow) Search() error {
	fmt.Println("Borrow Book Search ....")
	return nil
}
func (b *BookBorrow) Verify() error {
	fmt.Println("The system is judging whether you can borrow books now....")
	//拿着 BookBorrow.borrowUserId去记录表里面查找
	if b.IsInPenaltyTime == false && b.borrowUserHasBorrowBookNum < limitNum {
		fmt.Println("Congratulations ~ You have  passed verification")
		return nil
	} else {
		//由于您之前未按照指定的时间还书，您现在仍然处于不可借书阶段
		fmt.Println("Sorry ~ You have not passed verification\nYou are still in the no-borrowing stage because you did not return the book by the specified time")
		return errors.New("Dont not passed verification")
	}

}

// Do 具体业务
func (observer *BookBorrow) Do(o Observable) (err error) {
	// code..
	observer = NewBookBorrow()
	WaitingForLegalInput(observer)
	err = observer.Verify()
	if err != nil {
		fmt.Println(err)
		return errors.New("BookBorrow  Verify Error")
	}

	err = observer.Create()

	if err != nil {
		fmt.Println(err)
		return errors.New("BookBorrow Create Error")
	}

	err = observer.Update()
	if err != nil {
		fmt.Println(err)
		return errors.New("BookBorrow Update Error")
	}

	fmt.Println(runFuncName(), "借书相关的操作已经处理完毕...")
	return
}

type BookBack struct {
	//需要显示用户还书时间是否逾期

	//如果逾期就交罚款 或者限制用户在某个时间内不可以再次借书 更新

	//borrowUserId 是用户登陆的账号
	backedBookUserId string
	//borrowedBook 是借书过程，我们通过数据库得到的书籍的信息
	backedBook string
	//通过这两个数据可以新增一个借书记录在数据库当中

}

func NewBookBack() *BookBack {
	b := &BookBack{}
	return b
}

func (b *BookBack) Input() error {

	if userToken != "" {
		b.backedBookUserId = userToken
	} else {
		fmt.Println("Login timed out! Please login again!")
		u := &UserLogin{}
		WaitingForLegalInput(u)
		err := u.Login()
		//登陆成功才会更改userToken
		if err == nil {
			b.backedBookUserId = userToken
		}
		fmt.Println("用户重新登陆成功...")
	}

	fmt.Println("Please input the book")
	fmt.Scan(&b.backedBook)

	//让用户核对你所归还的书籍的信息
	fmt.Println("User:", b.backedBookUserId, "Please check the information on the books you returned", b.backedBook)
	//在还书的时候如果用户已经逾期，告诉他的信誉已经受损 本次还完书之后将会有为期30天的处罚期
	//在处罚期间将不可以借书
	err := b.Search()
	if err != nil {
		//您的信誉已经受到损伤，本次成功还完书籍之后将会有30天的处罚期，在处罚期间，你将不可以借书
		fmt.Println("Your credit has been damaged,there will be a 30-day penalty period after the book is successfully repaid this time. During the penalty period, you will not be able to borrow the book")
		return errors.New("Input Illegal!")

	}

	return nil

}

//更新所还书籍的状态
func (b *BookBack) Update() error {
	fmt.Println("Update in DB .....")
	fmt.Println("Book:", b.backedBook, " state has update!")
	return nil

}

//查找所借的书的时间 然后判断用户是否逾期，如果逾期要给他提示
func (b *BookBack) Search() error {
	//拿着BookBack.backedBook去查询用户是否确实借了这么一本书
	fmt.Println("The system is determining whether you have borrowed the book ", b.backedBook, "......")
	err := b.Verify()
	if err != nil {
		fmt.Println(err)
		return errors.New("BookBack Error!")
	} else {
		fmt.Println("BookBack Verify success!")
	}
	fmt.Println("The  book you borrowed time is ", time.Now())
	fmt.Println("没有逾期")
	return nil
}
func (b *BookBack) Verify() error {
	//拿着BookBack.backedBook去查询用户是否确实借了这么一本书
	fmt.Println("Verify the  book", b.backedBook, " whether you borrowed ......")
	return nil
}

// Do 具体业务
func (observer *BookBack) Do(o Observable) (err error) {
	// code..
	observer = NewBookBack()
	WaitingForLegalInput(observer)
	observer.Update()
	fmt.Println(runFuncName(), "还书籍相关的操作已经处理完毕...")
	return nil
}

type BookBorrowedRecord struct {
	borrowedBookUserId string
	record             map[string]interface{}
}

func NewBookBorrowedRecord() *BookBorrowedRecord {
	b := &BookBorrowedRecord{}
	b.record = map[string]interface{}{}
	return b
}
func (b *BookBorrowedRecord) Input() error {
	b = NewBookBorrowedRecord()
	if userToken != "" {
		b.borrowedBookUserId = userToken
	} else {
		fmt.Println("Login timed out! Please login again!")
		u := &UserLogin{}
		WaitingForLegalInput(u)
		err := u.Login()
		//登陆成功才会更改userToken
		if err == nil {
			b.borrowedBookUserId = userToken
		}
		fmt.Println("用户重新登陆成功...")
	}
	err := b.Search()
	if err != nil {
		fmt.Println(err)
		return errors.New("BookBorrowedRecord Search Error!")
	}

	return nil

}

func (b *BookBorrowedRecord) Search() error {
	fmt.Println("The system is querying the borrowing status of the user：", b.borrowedBookUserId)
	fmt.Println("Search success!")
	b.record["result"] = "TestBookId-userborrowed"
	fmt.Println("Your borrowed loan results are", b.record["result"])
	return nil

}

// Do 具体业务
func (observer *BookBorrowedRecord) Do(o Observable) (err error) {
	// code..
	observer = NewBookBorrowedRecord()
	WaitingForLegalInput(observer)
	fmt.Println(runFuncName(), "查询书籍借阅记录的相关的操作已经处理完毕...")
	return
}

func Test1(order ObserverInterface, info ...string) {
	// 创建 新增用户 “主题”
	fmt.Println(info, " “主题” ")
	orderUnPaidCancelSubject := &ObservableConcrete{}
	orderUnPaidCancelSubject.Attach(
		order,
	)
	orderUnPaidCancelSubject.Notify()
	fmt.Println(info, " “主题”操作完毕 ")

}

func (a *App) ExecuteItem(info string, order ObserverInterfaceSlice) {
	// 创建 新增用户 “主题”
	fmt.Println(info[4:], " “主题” ")
	orderUnPaidCancelSubject := &ObservableConcrete{}
	for _, v := range order {
		orderUnPaidCancelSubject.Attach(
			v,
		)
	}

	orderUnPaidCancelSubject.Notify()
	fmt.Println(info[4:], " “主题”操作完毕 ")

}

type RootUser struct {
	account  string
	password string
}

func NewRootUser() *RootUser {
	r := &RootUser{}
	return r
}
func (r *RootUser) Input() error {

	fmt.Println("Please Input New Root User Account:")
	fmt.Scan(&r.account)
	_, err := regexp.MatchString("^[0-1]{10}$", r.account)
	if err != nil {
		return errors.New("wrong happend in input Root User Account")
	}

	fmt.Println("Please input Root User Password:")
	fmt.Scan(&r.password)
	_, err = regexp.MatchString("^[0-9a-zA-Z]{6,30}$", r.password)
	if err != nil {
		return errors.New("wrong happend in input user password")
	}

	return nil

}

type LoginInterface interface {
	Login() error
}

func LoginService(l LoginInterface) {
	for {
		err := l.Login()
		if err == nil {
			break
		}
	}
}
func (r *RootUser) Login() error {
	//等待合法的输入
	WaitingForLegalInput(r)
	err := r.SerchInDB()
	if err != nil {
		fmt.Println("输入的账号或者密码不正确...")
		return err
	} else {
		fmt.Println("Root User login  success!")
	}
	//如果查找失败就返回err
	return nil
}

func (r *RootUser) SerchInDB() error {

	fmt.Println("User password and account search success!")
	fmt.Println("Account and password are verified...")
	return nil
}

func (observer *RootUser) Do(o Observable) (err error) {
	observer = NewRootUser()
	LoginService(observer)
	fmt.Println(runFuncName(), "Root用户登陆的相关的操作已处理完毕...")
	return nil
	//
}

//下架书籍
type BookRemove struct {
	bookId int
	//要下架的书籍在数据库的id
	//根据要下架的信息查找
	information map[string]interface{}
	target      string
}

func NewBookRemove() *BookRemove {
	b := &BookRemove{
		0,
		make(map[string]interface{}),
		"",
	}
	return b
}

func (b *BookRemove) Update() error {

	fmt.Println("The information for the book to be removed is: ", b.information)
	fmt.Print("Update Success ！The status of the book has been changed to not available for borrowing！")
	return nil
}

func (observer *BookRemove) Do(o Observable) (err error) {
	bookForSearch := NewBookSerach()
	WaitingForLegalInput(bookForSearch)
	bookForSearch.Search()
	fmt.Println(runFuncName(), "查询书籍相关的操作已经处理完毕...")
	observer = NewBookRemove()
	// Copy from the original map to the target map
	for key, value := range bookForSearch.key {
		if key == "result" {
			observer.information[key] = value
		}

	}
	observer.Update()
	return nil
}
