import numpy as np

from data_io import load_got_dataset, gaussians_dataset
from visualization import plot_boundary
from logistic_regression import LogisticRegression

np.random.seed(191090)


def main():
    """Main function"""

    # x_train, y_train, x_test, y_test = gaussians_dataset(2, [100, 150], [[1, 3], [-4, 8]], [[2, 3], [4, 1]])
    x_train, y_train, train_names, x_test, y_test, test_names, feature_names = (
        load_got_dataset(path="data/got.csv", train_split=0.8)
    )

    x = np.array([0.2, 0.7, 0.99, 0.35])
    labels = np.array([1, 0, 0, 1])
    label_try = np.array([0, 1, 1, 1])

    logistic_reg = LogisticRegression()
    logistic_reg.sigmoid(x)
    logistic_reg.loss(labels, label_try)
    logistic_reg.dloss_dw(labels, label_try, x)

    # train
    logistic_reg.fit_gd(
        x_train, y_train, n_epochs=10000, learning_rate=0.01, verbose=True
    )

    # test
    predictions = logistic_reg.predict(x_test)

    accuracy = float(np.sum(predictions == y_test)) / y_test.shape[0]
    print(f"Test accuracy: {accuracy}")

    # plot_boundary(x_train, y_train, logistic_reg, title='Training Set')


# entry point
if __name__ == "__main__":
    main()
