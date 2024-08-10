To collect the results of multiple asynchronous calls in Java, you can use `CompletableFuture.allOf()` or `CompletableFuture.anyOf()`. The `allOf()` method is particularly useful when you want to wait for all the asynchronous tasks to complete and then collect their results.

Here’s an example that demonstrates how to make multiple asynchronous calls and collect their results:

### Example: Collecting Results from Multiple Asynchronous Calls

```java
import java.util.concurrent.CompletableFuture;
import java.util.List;
import java.util.ArrayList;

public class AsyncMultipleCallsExample {

    // Asynchronous function that simulates a long-running task
    public static CompletableFuture<String> fetchDataAsync(int id) {
        return CompletableFuture.supplyAsync(() -> {
            try {
                // Simulate a delay (e.g., fetching data from a database or an API)
                Thread.sleep(2000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            return "Data fetched for ID: " + id;
        });
    }

    public static void main(String[] args) {
        System.out.println("Calling multiple asynchronous functions...");

        // Create a list to hold the CompletableFutures
        List<CompletableFuture<String>> futures = new ArrayList<>();

        // Initiate multiple asynchronous calls
        for (int i = 1; i <= 5; i++) {
            futures.add(fetchDataAsync(i));
        }

        // Combine all futures into a single CompletableFuture
        CompletableFuture<Void> allOf = CompletableFuture.allOf(futures.toArray(new CompletableFuture[0]));

        // Wait for all futures to complete
        allOf.join();

        // Collect results from all futures
        List<String> results = new ArrayList<>();
        for (CompletableFuture<String> future : futures) {
            results.add(future.join()); // Get the result of each future
        }

        // Print the collected results
        System.out.println("Collected Results:");
        results.forEach(System.out::println);
        System.out.println("Main method completed.");
    }
}
```

### Explanation:

1. **Asynchronous Function**: The `fetchDataAsync(int id)` method simulates a long-running task and returns a `CompletableFuture<String>` with a message that includes the ID.

2. **Main Method**:
   - It prints a message indicating that multiple asynchronous functions are being called.
   - It creates a list of `CompletableFuture<String>` to hold the futures returned by the asynchronous calls.
   - It initiates multiple asynchronous calls in a loop, adding each future to the list.
   - It uses `CompletableFuture.allOf()` to create a combined future that completes when all the individual futures complete.
   - It calls `allOf.join()` to wait for all the asynchronous tasks to finish.
   - It then collects the results from each future using `future.join()` and stores them in a list.
   - Finally, it prints the collected results.

### Output:

When you run this program, you will see output similar to the following:

```
Calling multiple asynchronous functions...
Collected Results:
Data fetched for ID: 1
Data fetched for ID: 2
Data fetched for ID: 3
Data fetched for ID: 4
Data fetched for ID: 5
Main method completed.
```

This demonstrates how to make multiple asynchronous calls, wait for all of them to complete, and collect their results in Java using `CompletableFuture`.
