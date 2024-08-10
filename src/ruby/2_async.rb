#!/usr/bin/env ruby

def check_email(address)
  # Generate a random integer between 1 and 3 seconds to simulate the
  # time it takes to retrieve messages from an IMAP server:
  random_server_latency = rand(1..3)
  random_unread_count = rand(1..5) # random number of unread messages

  sleep(random_server_latency) # Simulate waiting for the IMAP server

  # Display message results:
  puts "#{address}: #{random_unread_count} unread message(s) (#{random_server_latency} second(s))"

  return random_server_latency
end

def main()
  # Initialize a counter to keep track of the total time spent checking mail:
  total_cycles = 0

  # Record the current time at the start of the process:
  start_time = Time.now

  # Initialize an array to hold threads and another to store the total cycles:
  threads = []
  total_cycles = []

  # Create three threads, each calling the check_email method with different email
  # addresses. The results (latency) are stored in the total_cycles array:
  threads << Thread.new { total_cycles << check_email('john.doe@gmail.com') }
  threads << Thread.new { total_cycles << check_email('john.doe@outlook.com') }
  threads << Thread.new { total_cycles << check_email('john.doe@aol.com') }

  # Join the threads, waiting for all to complete before proceeding:
  threads.each(&:join)

  end_time = Time.now # Record the end time
  elapsed_time = end_time - start_time # Calculate the total elapsed time for the entire process

  # Print summary information:
  puts "\nTotal process time:  #{total_cycles.sum} seconds"
  puts "Actual elapsed time: #{elapsed_time.round} seconds"
end

main()
