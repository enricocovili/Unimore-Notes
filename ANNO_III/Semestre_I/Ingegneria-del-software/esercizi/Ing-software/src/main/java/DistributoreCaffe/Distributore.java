package DistributoreCaffe;

public class Distributore {
    public static void main(String args[]) {
        Bevanda caffe = new Caffe();
        caffe = new Zucchero(caffe);
        System.out.println();
    }
}
