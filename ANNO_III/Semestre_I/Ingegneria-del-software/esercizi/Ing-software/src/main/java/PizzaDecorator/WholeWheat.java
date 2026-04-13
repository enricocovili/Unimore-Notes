package PizzaDecorator;

public class WholeWheat extends Pizza{
    public WholeWheat () {
        description = " WholeWheat base";
    }
    public double cost() {
        return 5.30;
    }
}