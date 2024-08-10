package main

import (
	"fmt"
	"math"
	"math/rand"
	"sync"
	"time"
)

func CheckMail(address string, wg *sync.WaitGroup, mu *sync.Mutex, totalCycles *int) int {
	defer wg.Done() // Decrement the wait group counter when the goroutine completes

	randomServerLatency := rand.Intn(3) + 1 // random server latency between 1 and 3, as seconds
	randomUnreadMail := rand.Intn(5) + 1    // random number of unread emails

	time.Sleep(time.Duration(randomServerLatency) * time.Second) // simulate latency in call to IMAP server

	// display results:
	fmt.Printf("%s: %d unread (%d second(s))\n", address, randomUnreadMail, randomServerLatency)

	mu.Lock()                           // The mutex protects the shared variable, preventing race conditions
	*totalCycles += randomServerLatency // Add to our ongoing latency count
	mu.Unlock()                         // Release the shared variable, making it available to other processes

	return randomServerLatency
}

func main() {
	totalCycles := 0 // used to track total server latency

	start := time.Now() // capture start time of operations

	var wg sync.WaitGroup // Initialize a wait group to track the goroutines.  (You could also use a channel)
	var mu sync.Mutex     // Initialize a mutex. We'll pass this to the goroutine.

	wg.Add(1) // Increment the wait group counter (the wait group has to know how many processes it's tracking)
	go CheckMail("john.doe@gmail.com", &wg, &mu, &totalCycles)

	wg.Add(1)
	go CheckMail("john.doe@outlook.com", &wg, &mu, &totalCycles)

	wg.Add(1)
	go CheckMail("john.doe@aol.com", &wg, &mu, &totalCycles)

	wg.Wait() // Wait for all of the goroutines to finish

	elapsed := time.Since(start) // calculate elapsed time for operations

	// Print summary info:
	fmt.Printf("Total process time:  %d seconds\n", totalCycles)
	fmt.Printf("Actual elapsed time: %d seconds\n", int(math.Round(elapsed.Seconds())))
}
