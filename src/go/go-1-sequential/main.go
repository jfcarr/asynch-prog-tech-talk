package main

import (
	"fmt"       // formatted I/O operations
	"math"      // basic constants and mathematical functions
	"math/rand" // generate random numbers
	"time"      // measure time and introduce delays
)

func CheckMail(address string) int {
	randomServerLatency := rand.Intn(3) + 1 // random server latency between 1 and 3, as seconds
	randomUnreadMail := rand.Intn(5) + 1    // random number of unread emails

	time.Sleep(time.Duration(randomServerLatency) * time.Second) // simulate latency in call to IMAP server

	// display results:
	fmt.Printf("%s: %d unread (%d second(s))\n", address, randomUnreadMail, randomServerLatency)

	return randomServerLatency
}

func main() {
	var totalCycles int = 0 // used to track total server latency

	start := time.Now() // capture start time of operations

	// Check each email, in sequence:
	totalCycles = totalCycles + CheckMail("john.doe@gmail.com")
	totalCycles = totalCycles + CheckMail("john.doe@outlook.com")
	totalCycles = totalCycles + CheckMail("john.doe@aol.com")

	elapsed := time.Since(start) // calculate elapsed time for operations

	// Print summary info:
	fmt.Printf("Total process time:  %d seconds\n", totalCycles)
	fmt.Printf("Actual elapsed time: %d seconds\n", int(math.Round(elapsed.Seconds())))
}
