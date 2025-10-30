package SmartBuilding;

public class TemperatureObservable extends Observable {
    int tempLimit;
    int temp;

    public TemperatureObservable(int tempLimit) {
        this.tempLimit = tempLimit;
        this.temp = 0;
    }

    public int getTempLimit() {
        return tempLimit;
    }

    public void setTempLimit(int tempLimit) {
        this.tempLimit = tempLimit;
    }

    public void setTemp(int temp) {
        this.temp = temp;
        if (temp > tempLimit) {
            this.activate();
        }
    }
}
