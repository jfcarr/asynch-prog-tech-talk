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
    # Initialize a counter to keep track of the total time spent checking mail:
    total_cycles = 0

    # Record the current time at the start of the process:
    start_time = time.time()

    # Call the check_mail function for three different email addresses,
    # accumulating the total time taken in total_cycles.  We're awaiting
    # each call, so operations will still occur sequentially:
    total_cycles = total_cycles + await check_mail("john.doe@gmail.com")
    total_cycles = total_cycles + await check_mail("john.doe@outlook.com")
    total_cycles = total_cycles + await check_mail("john.doe@aol.com")

    end_time = time.time()  # Record the end time
    
    elapsed_time = end_time - start_time  # Calculate the total elapsed time for the entire process

    # Print summary information:
    print(f"\nTotal process time:  {total_cycles} seconds")
    print(f"Actual elapsed time: {elapsed_time:.0f} seconds")

if __name__ == '__main__':
    # Initialize using the asynchronous runtime:
    asyncio.run(main())
