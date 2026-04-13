package MeteoState;

public class Soleggiato extends MeteoState{
    public Soleggiato(Meteo m) {
        super(m);
    }

    public void changeState() {
        double r = super.timeTick();
        if (r <= 0.5) {
            meteo.changeState(new Nuvoloso(this.meteo));
        }
    }
}
