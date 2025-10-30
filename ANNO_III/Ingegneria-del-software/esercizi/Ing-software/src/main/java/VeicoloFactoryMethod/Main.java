package VeicoloFactoryMethod;

public class Main {

    public static void main(String[] args) {
        EVFactory ev_factory = new EVFactory();
        PetrolFactory petrol_factory = new PetrolFactory();

        Car test1 = ev_factory.assemble("Berlina", "Standard");

        Car test2 = petrol_factory.assemble("CityCar", "Sportivi");
    }
    ;
}
