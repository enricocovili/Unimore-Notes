package VeicoloFactoryMethod;

public class PetrolFactory implements CarFactory{

    @Override
    public Car assemble(String carrozzeria, String interni) {
        return new PetrolCar(carrozzeria, interni, "Petrol");
    }
}
