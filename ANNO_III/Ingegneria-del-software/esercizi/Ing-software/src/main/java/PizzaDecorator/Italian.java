package PizzaDecorator;

public class Italian extends Pizza{
    public Italian() {
        description = "Italian base";
    }
    public double cost() {
        return 4.50;
    }
}