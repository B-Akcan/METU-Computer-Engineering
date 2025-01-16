// Solution 1 in a single class Scribes that has inner class ScribeTask

import java.util.ArrayList;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Scribes {
    private static final Lock penLock = new ReentrantLock();
    private static final Lock bottleLock = new ReentrantLock();
    private static final Condition isPenAvailable = penLock.newCondition();
    private static final Condition isBottleAvailable = bottleLock.newCondition();
    private static int penCount;
    private static int bottleCount;

    public static void main(String[] args) {
        int scribeCount = Integer.parseInt(args[0]);
        penCount = Integer.parseInt(args[1]);
        bottleCount = Integer.parseInt(args[2]);

        ArrayList<Thread> threads = new ArrayList<>();

        for (int i = 0; i < scribeCount; i++) {
            Thread thread = new Thread(new ScribeTask(i));
            threads.add(thread);
        }

        for (Thread t : threads) {
            t.start();
        }
    }

    private static class ScribeTask implements Runnable {
        private final int id;
        ScribeTask(int i) {
            id = i;
        }

        public void takePen(int id) {
            penLock.lock();
            try {
                while (penCount == 0) {
                    isPenAvailable.await();
                }
                penCount--;
                Actions.takePen(id);
            } catch (InterruptedException _) {
            } finally {
                penLock.unlock();
            }
        }

        public void takeBottle(int id) {
            bottleLock.lock();
            try {
                while (bottleCount == 0) {
                    isBottleAvailable.await();
                }
                bottleCount--;
                Actions.takeBottle(id);
            } catch (InterruptedException _) {
            } finally {
                bottleLock.unlock();
            }
        }

        public void putPen(int id) {
            penLock.lock();
            try {
                penCount++;
                Actions.putPen(id);
                isPenAvailable.signal();
            } finally {
                penLock.unlock();
            }
        }

        public void putBottle(int id) {
            bottleLock.lock();
            try {
                bottleCount++;
                Actions.putBottle(id);
                isBottleAvailable.signal();
            } finally {
                bottleLock.unlock();
            }
        }

        @Override
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
}
