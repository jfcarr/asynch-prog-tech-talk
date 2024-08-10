use rand::{prelude, Rng}; // Generate random numbers. Added dependency.
use std::time::Instant; // Measure time.
use tokio::time::{sleep, Duration}; // Allows the program to pause execution asynchronously for a specified duration.

// Function is asynchronous:
async fn check_mail(address: String) -> i32 {
    let mut rng: prelude::ThreadRng = rand::thread_rng(); // Random number generator

    let random_message_count: u64 = rng.gen_range(1..=5); // Generate a random number between 1 and 5, representing unread messages.
    let random_server_latency: u64 = rng.gen_range(1..=3); // Generate a random number between 1 and 3, representing the simulated server latency in seconds.

    sleep(Duration::from_secs(random_server_latency)).await; // Asynchronously wait for the generated latency.

    // Print results:
    println!(
        "{}: {} unread messages ({} second(s))",
        address, random_message_count, random_server_latency
    );

    return random_server_latency.try_into().unwrap();
}

// Main function is marked with #[tokio::main], indicating that it is the entry point for a Tokio asynchronous application:
#[tokio::main]
async fn main() {
    let mut total_cycles: i32 = 0; // Initialize to keep track of the total server latency.

    let start_time: Instant = Instant::now(); // Record the start time of the operations.

    // Call check_mail for three different email addresses, awaiting each call and adding the returned latency to total_cycles:
    total_cycles += check_mail(String::from("john@gmail.com")).await;
    total_cycles += check_mail(String::from("john@outlook.com")).await;
    total_cycles += check_mail(String::from("john@aol.com")).await;

    // Calculate the elapsed time since the start of the process, convert to seconds:
    let elapsed: Duration = start_time.elapsed();
    let elapsed_seconds: f64 = elapsed.as_secs_f64();

    // Print summary information:
    println!("\nTotal process time:  {} seconds", total_cycles);
    println!("Actual elapsed time: {:.0} seconds", elapsed_seconds);
}
