package main

import (
	"fmt"       // formatted I/O operations
	"math"      // basic constants and mathematical functions
	"math/rand" // generate random numbers
	"time"      // measure time and introduce delays
)

func CheckMail(address string) int {
	randomServerLatency := rand.Intn(3) + 1 // random server latency between 1 and 3, as seconds
	randomUnreadCount := rand.Intn(5) + 1   // random number of unread emails

	time.Sleep(time.Duration(randomServerLatency) * time.Second) // simulate latency in call to IMAP server

	// display results:
	fmt.Printf("%s: %d unread (%d second(s))\n", address, randomUnreadCount, randomServerLatency)

	return randomServerLatency
}

func main() {
	start := time.Now() // capture start time of operations

	// Check two email accounts.  With the "go" keyword, these will run concurrently and the main function will not wait for them to finish
	go CheckMail("john.doe@gmail.com") // no await, and no way to get the return value
	go CheckMail("john.doe@outlook.com")

	// time.Sleep(6 * time.Second) // force an arbitrary wait time

	elapsed := time.Since(start) // calculate elapsed time for the operations

	fmt.Printf("Actual elapsed time: %d seconds\n", int(math.Round(elapsed.Seconds())))
}
