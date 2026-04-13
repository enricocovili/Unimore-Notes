package DistributoreCaffe;

public class Liquore extends AggiuntaDecoratore{
    public Liquore(Bevanda bevanda) {
        this.bevanda = bevanda;
    }

    public double cost() {
        return this.bevanda.getPrezzo() + 0.20;
    }

    @Override
    public String getDescription() {
        return "";
    }
}
