package SimulatoreCampane;

public abstract class Campana {
    protected String suono;

    public void suona() {
        System.out.println(suono);
    }

    public String getSuono() {
        return suono;
    }

    public void setSuono(String suono) {
        this.suono = suono;
    }
}
