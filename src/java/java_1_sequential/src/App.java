import java.util.Random; // The Random class is used to generate random numbers

public class App {
    public static int checkEmail(String address) {
        Random random = new Random();
        int randomServerLatency = random.nextInt(3) + 1; // random int between 1 and 3 (inclusive), simulating server
                                                         // response time in seconds
        int randomMessageCount = random.nextInt(5) + 1; // random int between 1 and 5 (inclusive), simulating the number
                                                        // of unread messages

        // pause operations for randomServerLatency seconds, simulating the time taken
        // for the IMAP server to respond:
        try {
            Thread.sleep(randomServerLatency * 1000);
        } catch (InterruptedException ex) {
            System.err.println(String.format("Sleep was interrupted: %s", ex.getMessage()));
        }

        // print the results:
        System.out.println(
                String.format("%s: %d unread (%d second(s))", address, randomMessageCount, randomServerLatency));

        return randomServerLatency;
    }

    public static void main(String[] args) throws Exception {
        int totalCycles = 0; // used to track total server latency

        long startTime = System.currentTimeMillis(); // capture start time of operations

        // Check each email, in sequence:
        totalCycles += checkEmail("john.doe@gmail.com");
        totalCycles += checkEmail("john.doe@outlook.com");
        totalCycles += checkEmail("john.doe@aol.com");

        long endTime = System.currentTimeMillis(); // capture end time of operations
        long elapsedTime = (endTime - startTime) / 1000; // calculate elapsed time for operations

        // Print summary info:
        System.out.println(String.format("Total process time:  %d seconds", totalCycles));
        System.out.println(String.format("Actual elapsed time: %d seconds", elapsedTime));
    }
}
