package org.example;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class ArrayExerciseTest {

    @Test
    void fillArray() {
        assertArrayEquals(new double[]{1}, ArrayExercise.fillArray(1, 1.0, false));
        assertArrayEquals(new double[]{5, 5, 5, 5, 5}, ArrayExercise.fillArray(5, 5.0, false));
        assertArrayEquals(new double[]{10, 10, 10, 10, 10}, ArrayExercise.fillArray(5, 10.0, true), 0.5);
        assertArrayEquals(new double[]{1, 1, 1, 1, 1}, ArrayExercise.fillArray(5, 1.0, true), 0.05);
    }

    @Test
    public void fibonacci() {
        assertArrayEquals(new long[]{0}, ArrayExercise.fibonacci(1));
        assertArrayEquals(new long[]{0, 1}, ArrayExercise.fibonacci(2));
        assertArrayEquals(new long[]{0, 1, 1, 2, 3}, ArrayExercise.fibonacci(5));
    }

    @Test
    void moveZerosEnd() {
        assertArrayEquals(new int[]{4, 2, 0, 0}, ArrayExercise.moveZerosEnd(new int[]{0, 0, 4, 2}));
        assertArrayEquals(new int[]{9, 4, 0, 0}, ArrayExercise.moveZerosEnd(new int[]{9, 0, 0, 4}));
        assertArrayEquals(new int[]{1, 0, 0, 0}, ArrayExercise.moveZerosEnd(new int[]{1, 0, 0, 0}));
    }
}