import Foundation // Provides sleep() function

// Define an asynchronous function to check email:
func check_email(address: String) async -> UInt32 {
    // A random delay (simulating server latency) between 1 and 3 seconds:
    let random_server_latency: UInt32 = UInt32.random(in: 1...3)
    // A random number of unread messages between 1 and 5:
    let random_message_count: Int = Int.random(in: 1...5)

    // Pause for the duration of random_server_latency seconds to simulate the time taken by a server to respond:
    try? await Task.sleep(nanoseconds: UInt64(random_server_latency) * 1_000_000_000)

    // Print the results:
    print("\(address): \(random_message_count) unread message(s) (\(random_server_latency) second(s))")

    return random_server_latency
}

func main() async {
    // Keep track of the total latency across all email checks:
    var total_cycles: UInt32 = 0

    // Record start time of the operations:
    let start_time: Date = Date()

    // Define an array of email addresses to check:
    let email_addresses: [String] = [
        "john.doe@gmail.com",
        "john.doe@outlook.com",
        "john.doe@aol.com"
    ]

    // Map each email address to a Task that calls the check_email function asynchronously:
    let tasks: [Task<UInt32, Never>] = email_addresses.map { address in
        Task {
            await check_email(address: address)
        }
    }

    // Iterate over the tasks, await their completion and sum the returned latencies into total_cycles:
    for task: Task<UInt32, Never> in tasks {
        total_cycles += await task.value
    }

    // Record end time of the operations and calculate how much time elapsed:
    let end_time: Date = Date()
    let elapsed_time: TimeInterval = end_time.timeIntervalSince(start_time)

    // Print summary of the results:
    print("\nTotal process time:  \(total_cycles) seconds")
    print("Actual elapsed time: \(Int(round(elapsed_time))) seconds")
}

// Call main() asynchronously, starting the entire process of checking emails:
await main()
