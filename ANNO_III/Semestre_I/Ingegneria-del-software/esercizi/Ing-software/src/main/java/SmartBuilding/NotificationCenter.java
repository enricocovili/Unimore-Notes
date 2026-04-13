package SmartBuilding;

public class NotificationCenter extends Observable implements Observer {
    private static NotificationCenter uniqueInstance = new NotificationCenter();

    private NotificationCenter() {};

    public static NotificationCenter getInstance() {
        return uniqueInstance;
    }

    @Override
    public void update(Object o) {
        System.out.println("Activated ::: " + o + ". Sending signals");
        this.activate(o);
    }
}
