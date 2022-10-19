package main

import (
	"encoding/gob"
	"fmt"
	"os"
)

func main() {
	info := map[string]string{
		"name": "测试",
	}
	name := "demo.gob"
	File, _ := os.OpenFile(name, os.O_RDWR|os.O_CREATE, 0777)
	defer File.Close()
	enc := gob.NewEncoder(File)
	if err := enc.Encode(info); err != nil {
		fmt.Println(err)
	}
}
