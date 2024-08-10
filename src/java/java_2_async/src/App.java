import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.concurrent.CompletableFuture; // a class that represents a future result of an asynchronous computation.

public class App {
    public static CompletableFuture<Integer> checkMail(String address) {
        Random random = new Random();
        int randomServerLatency = random.nextInt(3) + 1; // random int between 1 and 3 (inclusive), simulating server
                                                         // response time in seconds
        int randomMessageCount = random.nextInt(5) + 1; // random int between 1 and 5 (inclusive), simulating the number
                                                        // of unread messages

        // start an asynchronous operation that will run in a separate thread:
        return CompletableFuture.supplyAsync(() -> {
            try {
                Thread.sleep(randomServerLatency * 1000); // simulate server delay
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            // print the results:
            System.out.println(
                    String.format("%s: %d unread (%d second(s))", address, randomMessageCount, randomServerLatency));

            return randomServerLatency;
        });
    }

    public static void main(String[] args) throws Exception {
        int totalCycles = 0; // used to track total server latency

        long startTime = System.currentTimeMillis(); // capture start time of operations

        // Create a list to hold the CompletableFutures instances:
        List<CompletableFuture<Integer>> futures = new ArrayList<>();

        // call checkMail for three different email addresses and add the resulting
        // CompletableFuture objects to the list:
        futures.add(checkMail("john.doe@gmail.com"));
        futures.add(checkMail("john.doe@outlook.com"));
        futures.add(checkMail("john.doe@aol.com"));

        // Combine all futures into a single CompletableFuture<Void> that completes when
        // all the individual futures complete:
        CompletableFuture<Void> allOf = CompletableFuture.allOf(futures.toArray(new CompletableFuture[0]));

        // block the current thread until all futures are complete:
        allOf.join();

        long endTime = System.currentTimeMillis(); // capture end time of operations
        long elapsedTime = (endTime - startTime) / 1000; // calculate elapsed time for operations

        // Collect the results from each CompletableFuture into a list:
        List<Integer> results = new ArrayList<>();
        for (CompletableFuture<Integer> future : futures) {
            results.add(future.join()); // Get the result of each future
        }

        // Sum the server latencies to get the total cycles:
        for (Integer number : results) {
            totalCycles += number;
        }

        // Print summary info:
        System.out.println(String.format("\nTotal process time:  %d seconds", totalCycles));
        System.out.println(String.format("Actual elapsed time: %d seconds", elapsedTime));
    }
}
