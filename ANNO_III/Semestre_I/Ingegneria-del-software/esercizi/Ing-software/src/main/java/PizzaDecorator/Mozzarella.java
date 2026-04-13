package PizzaDecorator;

public class Mozzarella extends
        CondimentDecorator {
    Pizza pizza;
    public Mozzarella (Pizza pizza) {
        this.pizza = pizza;
    }
    public String getDescription() {
        return pizza.getDescription() + ", Mozzarella";
    }
    public double cost() {
        return pizza.cost() + .70;
    }
}
