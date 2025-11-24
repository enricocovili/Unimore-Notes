package MeteoState;

public class Piovigginoso extends MeteoState{
    public Piovigginoso(Meteo m) {
        super(m);
    }

    public void changeState() {
        double r = super.timeTick();
        if (r <= 0.2) {
            // pass, remain nuvoloso
        } else {
            meteo.changeState(new Nuvoloso(this.meteo));
        }
    }
}
