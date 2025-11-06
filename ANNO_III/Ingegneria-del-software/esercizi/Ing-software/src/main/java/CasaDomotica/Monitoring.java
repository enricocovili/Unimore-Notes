package CasaDomotica;


public class Monitoring {
    HomeFacade house;

    public Monitoring(HomeFacade house) {
        this.house = house;
    }

    public void activate() {
        house.update();
    };
}
