package SmartBuilding;

public class Main {

    public static void main(String[] args) {
        // WORKING. i implemented only Manutenzione for now because of lazyness, but logic is the same

        NotificationCenter center = NotificationCenter.getInstance();
        Manutenzione manutentori = new Manutenzione();

        center.registerObserver(manutentori);

        TemperatureObservable tempSens = new TemperatureObservable(20);
        tempSens.registerObserver(center);
        tempSens.setTemp(40);

        MalfunctionObservable malfunction = new MalfunctionObservable();
        malfunction.registerObserver(center);
        malfunction.activate();
    }
}
