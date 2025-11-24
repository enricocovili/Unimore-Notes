package MeteoState;

public class Meteo {
    MeteoState state;

    public Meteo() {
        state = new Soleggiato(this);
    }

    public void changeState(MeteoState new_state) {
        this.state = new_state;
    }

    public void nextIter() {
        this.state.changeState();
    }

    public MeteoState getState() {
        return state;
    }
}
