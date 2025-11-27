package CasaDomotica;

public class HouseSim {
    public static void main(String[] args) {
        HomeFacade house = new HomeFacade(new Light(), new PerAlarmAdapter(new AdvancedAlarm()), new Heating());
        Monitoring monitor = new Monitoring(house);

        monitor.activate();

        monitor.activate();
    }
}
