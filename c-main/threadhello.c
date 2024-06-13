public class HelloWorldThread {
 
    public static void main(String[] args) {
        // Create a new thread
        Thread thread = new Thread(new Runnable() {
            @Override
            public void run() {
                // Code to run in the new thread
                System.out.println("Hello, World!");
            }
        });
 
        // Start the thread
        thread.start();
 
        // Wait for the thread to finish
        try {
            thread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
has context menu
Compose
