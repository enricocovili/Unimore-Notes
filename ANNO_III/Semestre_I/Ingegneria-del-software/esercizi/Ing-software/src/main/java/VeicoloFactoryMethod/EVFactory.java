package VeicoloFactoryMethod;

public class EVFactory implements CarFactory {
    @Override
    public Car assemble(String carrozzeria, String interni) {
        return new EVCar(carrozzeria, interni, "EV");
    }
}
