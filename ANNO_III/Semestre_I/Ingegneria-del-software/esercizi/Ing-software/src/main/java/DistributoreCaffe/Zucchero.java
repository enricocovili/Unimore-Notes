package DistributoreCaffe;

public class Zucchero extends AggiuntaDecoratore {

    public Zucchero(Bevanda bevanda) {
        this.bevanda = bevanda;
    }

    public double cost() {
        return this.bevanda.getPrezzo() + 0.10;
    }

    @Override
    public String getDescription() {
        return "";
    }
}
