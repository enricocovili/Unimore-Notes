package MeteoState;

public class Nuvoloso extends MeteoState{
    public Nuvoloso(Meteo m) {
        super(m);
    }

    public void changeState() {
        double r = super.timeTick();
        if (r <= 0.3) {
            meteo.changeState(new Soleggiato(this.meteo));
        } else if (r > 0.3 && r <= 0.5){
            // pass, remain nuvoloso
        } else {
            meteo.changeState(new Piovigginoso(this.meteo));
        }
    }
}
