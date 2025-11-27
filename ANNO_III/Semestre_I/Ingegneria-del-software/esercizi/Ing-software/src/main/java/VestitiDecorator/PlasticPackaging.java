package VestitiDecorator;

public class PlasticPackaging extends PackagingStrategy{

    @Override
    public void pack() {
        System.out.println("Packaging using plastic");
    }
}
