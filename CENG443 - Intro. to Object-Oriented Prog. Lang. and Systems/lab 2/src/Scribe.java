// Solution 2 with two classes: Main and Scribe

public class Scribe extends Thread {
    private final int id;

    public Scribe(int id) {
        this.id = id;
    }

    public static void takePen(int id) {
        Main.lock2.lock();
        try {
            while (Main.penCount == 0) {
                Main.isPenAvailable.await();
            }
            Main.penCount--;
            Actions.takePen(id);
        } catch (InterruptedException e) {
        } finally {
            Main.lock2.unlock();
        }
    }

    public static void takeBottle(int id) {
        Main.lock1.lock();
        try {
            while (Main.bottleCount == 0) {
                Main.isBottleAvailable.await();
            }
            Main.bottleCount--;
            Actions.takeBottle(id);
        } catch (InterruptedException e) {
        } finally {
            Main.lock1.unlock();
        }
    }

    public static void putPen(int id) {
        Main.lock2.lock();
        try {
            Main.penCount++;
            Main.isPenAvailable.signal();
            Actions.putPen(id);
        } finally {
            Main.lock2.unlock();
        }
    }

    public static void putBottle(int id) {
        Main.lock1.lock();
        try {
            Main.bottleCount++;
            Main.isBottleAvailable.signal();
            Actions.putBottle(id);
        } finally {
            Main.lock1.unlock();
        }
    }
    public void run() {
        while (true) {
            takePen(id);
            takeBottle(id);
            Actions.write(id);
            putPen(id);
            putBottle(id);
        }
    }
}
