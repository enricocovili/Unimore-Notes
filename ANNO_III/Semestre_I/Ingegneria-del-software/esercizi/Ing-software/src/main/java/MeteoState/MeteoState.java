package MeteoState;

public abstract class MeteoState{
    Meteo meteo;

    public MeteoState(Meteo meteo) {
        this.meteo = meteo;
    }

    double r;

    public double timeTick() {
        return Math.random();
    }

    public abstract void changeState();

    @Override
    public String toString() {
        return "MeteoState{" +
                "meteo=" + meteo +
                ", r=" + r +
                '}';
    }
}
