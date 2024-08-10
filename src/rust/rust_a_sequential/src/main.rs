use rand::{prelude, Rng}; // Generate random numbers. Added dependency.
use std::thread; // Create threads, sleeping.
use std::time::{Duration, Instant}; // Measure time and create durations.

fn check_mail(address: String) -> i32 {
    let mut rng: prelude::ThreadRng = rand::thread_rng();

    let random_message_count: u64 = rng.gen_range(1..=5); // Generate a random number between 1 and 5, representing unread messages.
    let random_server_latency: u64 = rng.gen_range(1..=3); // Generate a random number between 1 and 3, representing the simulated server latency in seconds.

    // Sleep for the duration of random_server_latency to simulate waiting for a server response:
    let duration: Duration = Duration::new(random_server_latency, 0);
    thread::sleep(duration);

    // Print results:
    println!(
        "{}: {} unread messages ({} second(s))",
        address, random_message_count, random_server_latency
    );

    return random_server_latency.try_into().unwrap();
}

fn main() {
    let mut total_cycles: i32 = 0; // Initialize to keep track of the total server latency.

    let start_time: Instant = Instant::now(); // Record the start time of the operations.

    // Check three different email addresses, accumulating the total server latency in total_cycles:
    total_cycles += check_mail(String::from("john.doe@gmail.com"));
    total_cycles += check_mail(String::from("john.doe@outlook.com"));
    total_cycles += check_mail(String::from("john.doe@aol.com"));

    // Calculate the elapsed time since the start of the process, convert to seconds:
    let elapsed: Duration = start_time.elapsed();
    let elapsed_seconds: f64 = elapsed.as_secs_f64();

    // Print summary information:
    println!("\nTotal process time:  {} seconds", total_cycles);
    println!("Actual elapsed time: {:.0} seconds", elapsed_seconds);
}
