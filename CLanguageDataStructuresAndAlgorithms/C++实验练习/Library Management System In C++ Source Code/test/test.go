package main

import "fmt"

type Menu struct {
	command Command
}

func (m *Menu) press() {
	m.command.execute()
}

type Command interface {
	BookCreate()
	BookUpdate()
	BookDelete()
}

type command struct {
	device device
}

func (c *command) BookCreate() {

	c.device.Create()
}
func (c *command) BookUpdate() {

	c.device.Update()
}
func (c *command) BookDelete() {
	c.device.Delete()

}

type device interface {
	Input()
	Create()
	Delete()
	Update()
}

type Book struct {
	name            string
	ISBN            string
	author          string
	publishingHouse string
	category        string
	borrowedBy      string
	price           int
	state           int
}

func NewBook() *Book {
	return &Book{
		name:            "",
		ISBN:            "",
		author:          "",
		publishingHouse: "",
		category:        "",
		borrowedBy:      "",
		price:           0,
		state:           200,
	}

}

func (b *Book) Input() {

}
func (b *Book) Create() {

	fmt.Println("Please input Book name:")
	fmt.Scanf("%s", b.name)
	fmt.Println("Please input Book ISBN:")
	fmt.Scanf("%s", b.ISBN)
	fmt.Println("Please input Book author:")
	fmt.Scanf("%s", b.author)
	fmt.Println("Please input Book publishingHouse:")
	fmt.Scanf("%s", b.publishingHouse)
	fmt.Println("Please input Book category:")
	fmt.Scanf("%s", b.category)
	fmt.Println("Please input Book price:")
	fmt.Scanf("%d", b.price)

}
func (b *Book) Delete() {
	fmt.Println("Please input Book ISBN:")
	fmt.Scanf("%s", b.ISBN)
	fmt.Println("has been delete")
}
func (b *Book) Update() {

	fmt.Println("Please input Book borrowedBy :")
	fmt.Scanf("%s", b.borrowedBy)
	b.state = 400
}

func main() {
	book := NewBook()
	oncommand := &Oncommand{
		book,
	}
	button := Button{
		oncommand,
	}
	button.press()
}
