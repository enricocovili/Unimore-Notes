package VeicoloFactoryMethod;

public abstract class Car {
    String carrozzeria;
    String interni;
    String motore;

    public Car(String carrozzeria, String interni, String motore) {
        this.carrozzeria = carrozzeria;
        this.interni = interni;
        this.motore = motore;
    }

    public String getCarrozzeria() {
        return carrozzeria;
    }

    public void setCarrozzeria(String carrozzeria) {
        this.carrozzeria = carrozzeria;
    }

    public String getInterni() {
        return interni;
    }

    public void setInterni(String interni) {
        this.interni = interni;
    }
}
