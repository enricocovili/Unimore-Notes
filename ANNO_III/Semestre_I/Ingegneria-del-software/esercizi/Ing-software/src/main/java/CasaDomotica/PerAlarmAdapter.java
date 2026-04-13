package CasaDomotica;

public class PerAlarmAdapter implements Alarm{
    private AdvancedAlarm alarm;

    public PerAlarmAdapter(AdvancedAlarm alarm) {
        this.alarm = alarm;
    }

    @Override
    public void activate() {
        this.alarm.armPerimeter();
    }

    @Override
    public void deactivate() {
        this.alarm.deactivate();
    }
}
