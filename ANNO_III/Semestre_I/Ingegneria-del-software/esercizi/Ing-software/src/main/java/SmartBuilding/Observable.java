package SmartBuilding;

import java.util.ArrayList;

public abstract class Observable {
    ArrayList<Observer> observers;

    public Observable() {
        this.observers = new ArrayList<Observer>();
    }

    public void registerObserver(Observer o) {
        observers.add(o);
    }

    public void removeObserver(Observer o) {
        observers.remove(o);
    }

    public void activate() {
        for (Observer o : observers) {
            o.update(this);
        }
    };

    public void activate(Object o) {
        for (Observer obs : observers) {
            obs.update(o);
        }
    }
}
