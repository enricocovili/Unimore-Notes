package PacheggioComposite;

public class Posto extends ParcheggioComponent{
    boolean stato;

    public Posto(boolean stato) {
        this.stato = stato;
    }

    public boolean isStato() {
        return stato;
    }

    public void setStato(boolean stato) {
        this.stato = stato;
    }
}
