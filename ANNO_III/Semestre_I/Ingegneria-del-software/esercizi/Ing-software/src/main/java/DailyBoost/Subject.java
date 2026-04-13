package DailyBoost;

import java.util.ArrayList;

public abstract class Subject {
    private MessageStrategy messageStrategy;
    private ArrayList<Observer> observers;

    public void registerObserver(Observer o) {
        observers.add(o);
    }
    public void removeObserver(Observer o) {
        int i = observers.indexOf(o);
        if (i >= 0) {
            observers.remove(i);
        }
    }

    public void notifyObservers() {
        for (DailyBoost.Observer observer : observers)
        {
            messageStrategy.update(this);
        }
    }
}
