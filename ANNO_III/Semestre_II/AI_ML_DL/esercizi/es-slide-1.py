import numpy as np

# es 1 slide
test_1d_array = np.array([1, 2, 3, 4, 5, 6, 7])
reverse_array = test_1d_array[::-1]
np.flip

# es 2 slide
test_es2_array = np.array([[1, 3, 8], [-1, 3, 0], [-3, 9, 2]])
a = test_es2_array.diagonal().prod()

# es 3 slide
mean_es3 = np.random.rand(3, 6).mean()

# es 4
a = np.array([[1, 5, 6, 8], [2, -3, 13, 23], [0, -10, -9, 7]])
b = np.array([[-3, 0, 8, 1], [-20, -9, -1, 32], [7, 7, 7, 7]])

count = (a > b).sum()

# es 5
matrix_test_es5 = np.array(
    [[0.35, -0.27, 0.56], [0.15, 0.65, 0.42], [0.73, -0.78, -0.08]]
)
matrix_test_es5 = (matrix_test_es5 - matrix_test_es5.min()) / (
    matrix_test_es5.max() - matrix_test_es5.min()
)

pass
