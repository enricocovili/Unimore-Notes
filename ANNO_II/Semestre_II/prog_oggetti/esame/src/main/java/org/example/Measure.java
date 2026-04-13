package org.example;

public class Measure {

    public static <T> T max(T[] array, Measurer<T> measurer) {
        T max = array[0];
        for (T elem : array) {
            if (measurer.measure(elem) > measurer.measure(max)) {
                max = elem;
            }
        }
        return max;
    }

    public static <T> T min(T[] array, Measurer<T> measurer) {
        T min = array[0];
        for (T elem : array) {
            if (measurer.measure(elem) < measurer.measure(min)) {
                min = elem;
            }
        }
        return min;
    }

    public interface Measurer<T> {
        double measure(T item);
    }
}