package org.example;

import java.util.List;

public class SpeedTEst {
    public static long insertBeginning(List<String> list, String item, int times) {
        long start = System.nanoTime();
        for (int i = 0; i<times; i++) {
            list.addFirst(item);
        }
        long end = System.nanoTime();
        return end - start;
    }
    public static long insertEnd(List<String> list, String item, int times) {
        long start = System.nanoTime();
        for (int i=0; i < times; i++) {
            list.addLast(item);
        }
        long end = System.nanoTime();
        return end - start;
    }
}



