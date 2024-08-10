using System.Diagnostics; // Provides Stopwatch

internal class Program
{
    /// <summary>
    /// Simulate retrieving unread mail count from an IMAP server. Method is now asynchronous.
    /// </summary>
    /// <param name="address"></param>
    /// <returns>Amount of time (simulated) it took to retrieve the mail count.</returns>
    private static async Task<int> CheckEmail(string address)
    {
        // Generate:
        //   random unread mail count between 1 and 5, and
        //   random server response time between 1 and 3 (in seconds)
        Random rand = new();
        int randomMailCount = rand.Next(1, 5);
        int randomServerLatency = rand.Next(1, 4);

        // Since we're running inside an async method, we'll use a Task.Delay instead of Thread.Sleep to pause
        // and simulate the call to the IMAP server.
        await Task.Delay(randomServerLatency * 1000);

        // Write the results to the console.
        Console.WriteLine($"{address}: {randomMailCount} unread ({randomServerLatency} second(s))");

        return randomServerLatency;
    }

    private static async Task Main(string[] args)
    {
        int totalCycles = 0; // Use this to track the total latency for all email checks.

        Stopwatch stopwatch = Stopwatch.StartNew(); // Start time of operations.

        // Check 3 email addresses, tracking server latency for each.  Since the CheckEmail method is
        // asynchronous, we'll wait for each call to finish.
        totalCycles += await CheckEmail("john.doe@gmail.com");
        totalCycles += await CheckEmail("john.doe@outlook.com");
        totalCycles += await CheckEmail("john.doe@aol.com");

        stopwatch.Stop(); // End time of operations.

        // Send summary information to console:
        Console.WriteLine($"\nTotal process time:  {totalCycles} seconds");
        Console.WriteLine($"Actual elapsed time: {stopwatch.ElapsedMilliseconds / 1000} seconds");
    }
}