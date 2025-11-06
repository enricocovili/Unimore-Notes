package CasaDomotica;

class SimpleAlarm implements Alarm {
    private boolean active = false;

    public void activate() {
        active = true;
        System.out.println("Allarme attivato");
    }

    public void deactivate() {
        active = false;
        System.out.println("Allarme disattivato");
    }

    boolean isActive() { return active; }
}
