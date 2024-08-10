#include <chrono>   // time-measuring functions
#include <future>   // asynchronous operations
#include <iostream> // I/O operations
#include <mutex>    // thread synchronization
#include <random>   // generate random numbers
#include <thread>   // manage threads, and sleeping

using namespace std;

// [PATTERN] managing data races in asynchronous operations
std::mutex coutMutex; // used to synchronize access to the console output,
                      // preventing data races when multiple threads attempt to
                      // write to cout simultaneously.

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
  vector<std::future<int>>
      futures; // holds the results of asynchronous operations

  auto start = chrono::high_resolution_clock::now(); // record the current time,
                                                     // indicating the start
                                                     // time of the operations

  // Launch three asynchronous tasks to check email, pushing them into the
  // future vector for parallel processing:
  futures.push_back(
      std::async(std::launch::async, checkEmail, "john.doe@gmail.com"));
  futures.push_back(
      std::async(std::launch::async, checkEmail, "john.doe@outlook.com"));
  futures.push_back(
      std::async(std::launch::async, checkEmail, "john.doe@aol.com"));

  // collect the result of each future by calling get(), which blocks until the
  // result is available:
  std::vector<int> results;
  for (auto &fut : futures) {
    results.push_back(fut.get());
  }

  // Calculate the total latency by summing the results:
  int total_cycles = 0;
  for (const auto &result : results) {
    total_cycles += result;
  }

  auto end = chrono::high_resolution_clock::now(); // record the end time,
                                                   // indicating the completion
                                                   // of the operations

  std::chrono::duration<double> elapsed =
      end - start; // calculate the elapsed time spent on the operations

  // Display summary information for the operations:
  cout << endl;
  cout << "Total process time:  " << total_cycles << " seconds" << endl;
  cout << "Actual elapsed time: " << round(elapsed.count()) << " seconds"
       << endl;

  return (0);
}
