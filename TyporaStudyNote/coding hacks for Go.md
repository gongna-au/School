# coding hacks for Go

### 1.Checking if a key is in a map

> 检查键是否在map中

```

_, keyIsInMap := myMap["keyToCheck"]
if !keyIsInMap {
  fmt.Println("key not in map")
}

```

### 2.Check when casting a variable 

> 转换变量时检查

```
//value := data.(string)
value , ok := data.(string)
```

### 3. Specify the size of the array when using append

> 使用append时指定数组的大小

```
/*
var mySlice []int
for _,v := range inputSlice{
	mySlice = append(mySlice ,v)
}
哒咩哒咩哒咩
*/

//正确操作
mySlice:= make([]int,len(inputSlice))
for _,v := range inputSlice{
	mySlice = append(mySlice ,v)
}
//更加正确的操作
mySlice:= make([]int,0,len(inputSlice))
for _,v := range inputSlice{
	mySlice = append(mySlice ,v)
}
//它更具可读性，但也没有速度损失，因为在开始时分配大小。

```

### 4. Use “append” and **ellipsis** to concatenate an array.

> 使用“追加”和省略号来连接数组。

```
//myArray = append(myArray, value1)

myArray = append(myArray, value1, value2)
myArray = append(myArray, inputArray...)

```

### 5.Display the parameter names and values when printing.

> 打印时显示参数名称和值。

```
fmt.Printf("%+v \n", structToDisplay)
fmt.Printf("%#v \n", structToDisplay)

Without params:       {first value 2}
With params:          {Value1:first value Value2:2}
As go representation: main.MyStruct{Value1:"first value", Value2:2}
```

### 6. Use “iota” with custom types when enumerating

> 枚举时使用带有自定义类型的“iota”

```
//example 1
const (
	Red int = iota
	Orange
	Yellow
	Green
	Blue
	Indigo
	Violet
)

func main() {
	fmt.Printf("The value of Red    is %v\n", Red)
	fmt.Printf("The value of Orange is %v\n", Orange)
	fmt.Printf("The value of Yellow is %v\n", Yellow)
	fmt.Printf("The value of Green  is %v\n", Green)
	fmt.Printf("The value of Blue   is %v\n", Blue)
	fmt.Printf("The value of Indigo is %v\n", Indigo)
	fmt.Printf("The value of Violet is %v\n", Violet)
}
//上面的代码定义了三个类型的常量int。然后它使用iota标识符告诉 Go 编译器您希望第一个值从 开始0，然后1为每个后续常量递增。这将产生以下输出：
//results
The value of Red    is 0
The value of Orange is 1
The value of Yellow is 2
The value of Green  is 3
The value of Blue   is 4
The value of Indigo is 5
The value of Violet is 6

//example 2
const (
	Blue int = iota
	Green
	Indigo
	Orange
	Red
	Violet
	Yellow
)

func main() {
	fmt.Printf("The value of Red    is %v\n", Red)
	fmt.Printf("The value of Orange is %v\n", Orange)
	fmt.Printf("The value of Yellow is %v\n", Yellow)
	fmt.Printf("The value of Green  is %v\n", Green)
	fmt.Printf("The value of Blue   is %v\n", Blue)
	fmt.Printf("The value of Indigo is %v\n", Indigo)
	fmt.Printf("The value of Violet is %v\n", Violet)
}
正如我们现在运行程序时看到的那样，现在的值Red现在是4的值，以及所有其他值现在都不同了。Orange3
//results
The value of Red    is 4
The value of Orange is 3
The value of Yellow is 6
The value of Green  is 1
The value of Blue   is 0
The value of Indigo is 2
The value of Violet is 5

//example 3
const (
	_   int = iota // Skip the first value of 0
	Foo            // Foo = 1
	Bar            // Bar = 2
	_
	_
	Bin // Bin = 5
	// Using a comment or a blank line will not increment the iota value

	Baz // Baz = 6
)

//results 
The value of Foo is 1
The value of Bar is 2
The value of Bin is 5
The value of Baz is 6

// example 4
高级 Iota 使用
const (
	read   = 1 << iota // 00000001 = 1
	write              // 00000010 = 2
	remove             // 00000100 = 4

	// admin will have all of the permissions
	admin = read | write | remove
)

func main() {
	fmt.Printf("read =  %v\n", read)
	fmt.Printf("write =  %v\n", write)
	fmt.Printf("remove =  %v\n", remove)
	fmt.Printf("admin =  %v\n", admin)
}
//results 
read =  1
write =  2
remove =  4
admin =  7
在这里，创建一个自定义类型“PossibleStates”，然后每个枚举都是一个“PossibleState”类型，其值由“iota”分配。然后当任何人调用“UpdateState”时，编译器将确保只发送可能的状态，而不是任何旧的 int
```

### 7.mocking an interface, have functions matching the interface functions as parameters.

> 模拟接口时，将与接口函数匹配的函数作为参数。

```
type DataPersistence interface {
 SaveData(string, string) error
 GetData(string) (string, error)
}

type MockDataPersistence struct {
 SaveDataFunc func(string, string) error
 GetDataFunc func(string) (string, error)
}

// SaveData just calls the parameter SaveDataFunc
func (mdp MockDataPersistence) SaveData(key, value string) error {
 return mdp.SaveDataFunc(key, value)
}


// GetData just calls the parameter GetDataFunc
func (mdp MockDataPersistence) GetData(key string) (string, error) {
 return mdp.GetDataFunc(key)
}
```

这意味着当我们在测试时，我们可以设置函数以在测试本身中执行我们需要的任何操作：

```
type MockDataPersistence struct {
 SaveDataFunc func(string, string) error
 GetDataFunc func(string) (string, error)
}
// SaveData 只是调用参数 SaveDataFunc
func (mdp MockDataPersistence) SaveData(key, value string) error {
 return mdp.SaveDataFunc(key, value)
}
// GetData 只是调用 GetDataFunc 参数
func (mdp MockDataPersistence) GetData(key string) (string, error) {
 return mdp.GetDataFunc(key)
}
//这确实有助于提高可读性，因为您可以清楚地看到模拟在每个测试中的内容。这也意味着您可以访问模拟函数中的测试数据，而无需维护外部数据文件。


```

### 8. If someone didn’t create an interface, just create your own.

> 如果有人没有创建interface，请创建你自己的interface。

```
type OtherLibsStruct struct {}
func (ols OtherLibsStruct) DoCoolStuff(input string) error {
 return nil
}
//那么在你的代码中，只需创建一个可以实现的接口：
```

```
type InterfaceForOtherLibsStruct interface {
 DoCoolStuff(string) error
}
//然后你可以编写你的代码来接受这个接口。使用时传入另一个库的结构。然后当你想测试它时，从上面做模拟接口技巧。
```

### 9.Instantiating nested anonymous structs

> 实例化嵌套匿名结构

我在使用生成的代码时遇到过几次。有时在生成代码时，您会得到一个嵌套的匿名结构。例子：

```
type GeneratedStuct struct {
  Value1 string `json:"value1"`
  Value2 int `json:"value2"`
  Value3 *struct {
    NestedValue1 string `json:"NestedValue1"`
    NestedValue2 string `json:"NestedValue2"`
  } `json:"value3,ommitempty"`
}
```

现在说你想创建这个结构的一个实例来使用，你会怎么做？Value1 和 Value2 很简单，但是如何实例化指向匿名结构（Value3）的指针呢？我的第一个解决方案是用 JSON 编写它，然后将其编组到结构中，但这太可怕了，而且很hacky。事实证明，在实例化它时需要使用另一个匿名结构：

```
myGeneratedStruct := GeneratedStuct{ 
  Value3: &struct { 
   NestedValue1 string `json:"NestedValue1"` 
   NestedValue2 string `json:"NestedValue2"` 
  }{ 
   NestedValue1: "foo", 
   NestedValue2: "bar", 
  }, 
}
```

这似乎很明显，但请注意，它需要*完全*匹配，甚至可以匹配到 JSON 标签。虽然上述方法可行，但由于类型不匹配，以下内容将无法编译：

myGeneratedStruct := GeneratedStuct{ 
  Value3: &struct { 
   NestedValue1 string `json:"nestedValue1"` 
   NestedValue2 string `json:"nestedValue2"` 
  }{ 
   NestedValue1: "foo", 
   NestedValue2: "bar", 
  }, 
}