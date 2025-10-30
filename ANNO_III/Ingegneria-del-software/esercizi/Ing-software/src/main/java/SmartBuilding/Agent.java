package SmartBuilding;

public abstract class Agent implements Observer {
    @Override
    public void update(Object o) {
        if (this.check(o)) {
            this.act();
        }
    }

    public abstract boolean check(Object o);

    public void act() {
        System.out.println(this.getClass().getCanonicalName() + " in azione");
    }
}
