## Project Setup

### Create Project Directory

```bash
mkdir my-go-project

cd my-go-project
```

### Initialize the Project

```bash
go mod init my-go-project
```

### Create the Main Go File

```bash
touch main.go
```

```go
package main

import "fmt"

func main() {
    fmt.Println("Hello, World!")
}
```

### Run Project

```bash
go run main.go
```
