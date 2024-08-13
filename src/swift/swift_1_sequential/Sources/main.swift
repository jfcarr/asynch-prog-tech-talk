import Foundation // Provides sleep() function

func check_email(address: String) -> UInt32 {
    // A random delay (simulating server latency) between 1 and 3 seconds:
    let random_server_latency: UInt32 = UInt32.random(in: 1...3)
    // A random number of unread messages between 1 and 5:
    let random_message_count: Int = Int.random(in: 1...5)

    // Pause for the duration of random_server_latency seconds to simulate the time taken by a server to respond:
    sleep(random_server_latency)

    // Print the results:
    print("\(address): \(random_message_count) unread message(s) (\(random_server_latency) second(s))")

    return(random_server_latency)
}

// Keep track of the total latency across all email checks:
var total_cycles: UInt32 = 0

// Record start time of the operations:
let start_time: Date = Date()

// Call check_email three times with different email addresses, and
// accumulate the returned latency in total_cycles:
total_cycles += check_email(address: "john.doe@gmail.com")
total_cycles += check_email(address: "john.doe@outlook.com")
total_cycles += check_email(address: "john.doe@aol.com")

// Record end time of the operations and calculate how much time elapsed:
let end_time: Date = Date()
let elapsed_time: TimeInterval = end_time.timeIntervalSince(start_time)

// Print summary of the results:
print("\nTotal process time:  \(total_cycles) seconds")
print("Actual elapsed time: \(Int(round(elapsed_time))) seconds")
