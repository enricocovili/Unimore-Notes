package CasaDomotica;

public class HomeFacade {
    boolean occupied;

    Light l;
    Alarm alarm;
    Heating h;

    public HomeFacade(Light l, Alarm alarm, Heating h) {
        this.l = l;
        this.alarm = alarm;
        this.h = h;
        occupied = false;
    }

    public void entrance() {
        l.turnOn();
        alarm.deactivate();
        h.setTemperature(20);
    }

    public void exit() {
        l.turnOff();
        alarm.activate();
        h.setTemperature(0);

    }

    public void update() {
        if (occupied)
            exit();
        else
            entrance();
        System.out.println("---------------------");
        this.occupied = !this.occupied;
    }
}
