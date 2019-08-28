package main

import (
	"fmt"
	"os"
)

type AppPath struct {
	App string
}

func (a *AppPath) Delete() {
	if err := os.RemoveAll(a.App); err != nil {
		fmt.Errorf("发生错误：", err.Error())
	}
}

func main() {
	app := AppPath{App: "./test"}
	fmt.Println(app.App)
	app.Delete()
}
