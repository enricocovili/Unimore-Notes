package PizzaDecorator;

public class Pizzeria{
    public static void main(String args[]) {
        Pizza pizza = new Italian();
        System.out.println(pizza.getDescription()
                + " euro " +pizza.cost());
        Pizza pizza2 = new Italian();
        pizza2 = new Mozzarella(pizza2);
        pizza2 = new Mozzarella(pizza2);
        pizza2 = new Tomato(pizza2);
        System.out.println(pizza2.getDescription()
                + " euro " + String.format("%.3f", pizza2.cost()));
    }
}