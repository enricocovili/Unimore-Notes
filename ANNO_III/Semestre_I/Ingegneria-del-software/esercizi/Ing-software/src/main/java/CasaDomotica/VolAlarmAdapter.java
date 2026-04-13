package CasaDomotica;

public class VolAlarmAdapter implements Alarm{
    private AdvancedAlarm alarm;

    public VolAlarmAdapter(AdvancedAlarm alarm) {
        this.alarm = alarm;
    }

    @Override
    public void activate() {
        this.alarm.armVolumetric();
    }

    @Override
    public void deactivate() {
        this.alarm.deactivate();
    }
}
