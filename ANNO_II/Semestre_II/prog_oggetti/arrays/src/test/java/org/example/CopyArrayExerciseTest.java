package org.example;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class CopyArrayExerciseTest {

    @Test
    void copyArray() {
        assertArrayEquals(new double[]{1, 1, 1}, ArrayExercise.copyArray(new double[]{1, 1, 1}));
        assertArrayEquals(new double[]{5, 4, 3, 1}, ArrayExercise.copyArray(new double[]{5, 4, 3, 1}));
        assertArrayEquals(new double[]{5, 4, 3, 1}, ArrayExercise.copyArray(new double[]{5, 4, 3, 1}));
    }
}