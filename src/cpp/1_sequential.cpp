// These are all standard libraries:
#include <chrono>   // time-measuring functions
#include <iostream> // I/O operations
#include <random>   // generate random numbers
#include <thread>   // manage threads, and sleeping

using namespace std;

/// @brief Generate a random number between 1 and 3, to be used to simulate
/// server latency
/// @return Random number (int)
int getRandomLatency() {
  random_device rd;  // Obtain a seed from the hardware
  mt19937 eng(rd()); // Use the seed to initialize a Mersenne Twister random
                     // number generator

  int min = 1; // Minimum value (inclusive)
  int max = 3; // Maximum value (inclusive)

  uniform_int_distribution<> distr(
      min, max); // generate a uniformly distributed random integer within the
                 // specified range

  int randomInt = distr(eng); // assign the generated value

  return (randomInt);
}

/// @brief Simulate checking unread mail count from an IMAP server
/// @param address Email address to check
/// @return latency: The time it took to retrieve the count
int checkEmail(const string &address) {
  int latency = getRandomLatency(); // get a random latency value

  this_thread::sleep_for(
      chrono::seconds(latency)); // sleep for that many seconds, simulating a
                                 // call to an IMAP server

  cout << "Finished retrieving messages for " << address << " in " << latency
       << " second(s)." << endl; // Display a status message for the retrieval

  return (latency);
}

int main() {
  auto start = chrono::high_resolution_clock::now(); // record the current time,
                                                     // indicating the start
                                                     // time of the operations

  int total_cycles = 0; // initialize total_cycles; we'll use this to accumulate
                        // the total latency

  // check three different email addresses, adding the time for each to
  // total_cycles
  total_cycles += checkEmail("john.doe@gmail.com");
  total_cycles += checkEmail("john.doe@outlook.com");
  total_cycles += checkEmail("john.doe@aol.com");

  auto end =
      chrono::high_resolution_clock::now(); // record the end time, indicating
                                            // the completion of the operations
  chrono::duration<double> elapsed =
      end - start; // calculate the elapsed time spent on the operations

  // Display summary information for the operations:
  cout << endl;
  cout << "Total process time:  " << total_cycles << " seconds" << endl;
  cout << "Actual elapsed time: " << round(elapsed.count()) << " seconds"
       << endl;

  return (0);
}