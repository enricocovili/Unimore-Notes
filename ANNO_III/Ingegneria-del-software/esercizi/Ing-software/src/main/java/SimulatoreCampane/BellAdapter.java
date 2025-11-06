package SimulatoreCampane;

public class BellAdapter extends Campana{
    CampanaUSA adaptee;

    public BellAdapter(CampanaUSA adaptee) {
        this.adaptee = adaptee;
    }

    public String getSuono() {
        return this.adaptee.getSound();
    }

    public void suona() {
        this.adaptee.ring();
    }
}
