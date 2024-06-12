import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

// Class representing the bounded buffer
class BoundedBuffer {
    private final int capacity;
    private final Queue<Integer> queue;
    private int nextValue = 0;

    public BoundedBuffer(int capacity) {
        this.capacity = capacity;
        this.queue = new LinkedList<>();
    }

    // Method to produce an item
    public synchronized void produce() throws InterruptedException {
        while (queue.size() == capacity) {
            System.out.println("Buffer is full. Producer is waiting...");
            wait();
        }
        queue.add(nextValue);
        System.out.println("Produced: " + nextValue);
        nextValue++;
        notifyAll();
    }

    // Method to consume an item
    public synchronized int consume() throws InterruptedException {
        while (queue.isEmpty()) {
            System.out.println("Buffer is empty. Consumer is waiting...");
            wait();
        }
        int value = queue.poll();
        System.out.println("Consumed: " + value);
        notifyAll();
        return value;
    }

    public synchronized boolean isFull() {
        return queue.size() == capacity;
    }

    public synchronized boolean isEmpty() {
        return queue.isEmpty();
    }
}

// Class representing a producer
class Producer implements Runnable {
    private final BoundedBuffer buffer;

    public Producer(BoundedBuffer buffer) {
        this.buffer = buffer;
    }

    @Override
    public void run() {
        try {
            buffer.produce();
            Thread.sleep((int) (Math.random() * 1000)); // Simulate work
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}

// Class representing a consumer
class Consumer implements Runnable {
    private final BoundedBuffer buffer;

    public Consumer(BoundedBuffer buffer) {
        this.buffer = buffer;
    }

    @Override
    public void run() {
        try {
            buffer.consume();
            Thread.sleep((int) (Math.random() * 1000)); // Simulate work
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}

// Main class to run the producer-consumer example
public class ProducerConsumerExample {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Get buffer capacity
        System.out.print("Enter buffer capacity: ");
        int bufferCapacity = scanner.nextInt();
        BoundedBuffer buffer = new BoundedBuffer(bufferCapacity);

        // Display menu once
        System.out.println("\nMenu:");
        System.out.println("1. Produce");
        System.out.println("2. Consume");
        System.out.println("3. Exit");

        while (true) {
            System.out.print("Enter your choice: ");
            int choice = scanner.nextInt();

            switch (choice) {
                case 1:
                    // Producer operation
                    Thread producer = new Thread(new Producer(buffer));
                    producer.start();
                    try {
                        producer.join();
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                    }
                    break;

                case 2:
                    // Consumer operation
                    Thread consumer = new Thread(new Consumer(buffer));
                    consumer.start();
                    try {
                        consumer.join();
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                    }
                    break;

                case 3:
                    // Exit operation
                    System.out.println("Exiting...");
                    scanner.close();
                    System.exit(0);
                    break;

                default:
                    System.out.println("Invalid choice. Please enter 1, 2, or 3.");
                    break;
            }

            // Check if buffer is either full or empty to exit
            if (buffer.isFull()) {
                System.out.println("Buffer is full. Exiting...");
                scanner.close();
                System.exit(0);
            } else if (buffer.isEmpty()) {
                System.out.println("Buffer is empty. Exiting...");
                scanner.close();
                System.exit(0);
            }
        }
    }
}
