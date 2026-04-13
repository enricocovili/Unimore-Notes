package org.example;

import java.util.Random;
import java.util.Arrays;

public class ArrayExercise {
    public static double[] copyArray(double[] v) {
        return v.clone();
    }

    public static double[] fillArray(int size, double value, boolean addNoise) {
        double[] numbers = new double[size];
        Random rand = new Random();
        Arrays.fill(numbers, value);
        if (addNoise) {
            for(int i = 0; i<size; i++) {
                numbers[i] += numbers[i] * (rand.nextDouble(0.10)-0.05);
            }
        }
        return numbers;
    }

    public static long[] fibonacci(int n) {
        long[] res = new long[n];
        for (int i = 0; i<n; i++) {
            if (i == 0) res[0] = 0;
            else if (i == 1) res[1] = 1;
            else res[i] = res[i-2] + res[i-1];
        }
        return res;
    }

    public static int[] moveZerosEnd(int[] v) {
        int[] res = new int[v.length];
        int ix = 0;
        for (int e : v) {
            if (e != 0) res[ix++] = e;
        }
        return res;
    }
}
