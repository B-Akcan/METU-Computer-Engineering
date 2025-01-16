// Solution 2 with two classes: Main and Scribe

import java.util.ArrayList;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Main {
    public static final Lock lock1 = new ReentrantLock();
    public static final Lock lock2 = new ReentrantLock();
    public static final Condition isBottleAvailable = lock1.newCondition();
    public static final Condition isPenAvailable = lock2.newCondition();
    public static int penCount = 2;
    public static int bottleCount = 4;

    public static void main(String[] args) {
        ArrayList<Thread> scribes = new ArrayList<>();
        for (int i = 1; i < 6; i++) {
            Thread s = new Scribe(i);
            scribes.add(s);
        }
        for (Thread s : scribes) {
            s.start();
        }
    }
}
