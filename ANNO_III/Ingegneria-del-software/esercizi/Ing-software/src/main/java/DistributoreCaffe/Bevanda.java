package DistributoreCaffe;

public abstract class Bevanda {
    private double prezzo;

    public Bevanda() {
        this.prezzo = 0.60;
    }

    public double getPrezzo() {
        return prezzo;
    }
}
