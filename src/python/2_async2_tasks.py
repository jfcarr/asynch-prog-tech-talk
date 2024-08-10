#!/usr/bin/env python3

import asyncio  # write concurrent code using the async/await syntax
import random   # generate random numbers
import time     # time-related functions

async def check_mail(address):
    # Generate a random integer between 1 and 3 seconds to simulate the
    # time it takes to retrieve messages from an IMAP server:
    random_server_latency = random.randint(1,3)
    random_message_count = random.randint(1,5)  # random number of unread messages

    # Asynchronously wait for the generated server latency time:
    await asyncio.sleep(random_server_latency)

    # Display message results:
    print(f"{address}: {random_message_count} unread message(s) ({random_server_latency} second(s))")

    return random_server_latency

# main() is asynchronous, to support the asynchronous runtime:
async def main():
    # Record the current time at the start of the process:
    start_time = time.time()

    # Create a list of tasks to check mail for three different email addresses using
    # asyncio.create_task(), which schedules the check_mail function to run concurrently:
    tasks = [
        asyncio.create_task(check_mail("john@gmail.com")),
        asyncio.create_task(check_mail("john@outlook.com")),
        asyncio.create_task(check_mail("john@aol.com")),
    ]

    # Run all the tasks concurrently and wait for their completion, returning their results:
    results = await asyncio.gather(*tasks)

    # Calculate the total time taken for all the simulated server latencies by summing the results
    # gathered from the task list:
    total_cycles = sum(results)

    end_time = time.time()  # Record the end time
    
    elapsed_time = end_time - start_time  # Calculate the total elapsed time for the entire process

    # Print summary information:
    print(f"\nTotal process time:  {total_cycles} seconds")
    print(f"Actual elapsed time: {elapsed_time:.0f} seconds")

if __name__ == '__main__':
    # Initialize using the asynchronous runtime:
    asyncio.run(main())
