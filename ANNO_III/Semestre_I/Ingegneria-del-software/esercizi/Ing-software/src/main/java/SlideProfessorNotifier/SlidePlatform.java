package SlideProfessorNotifier;

public abstract class SlidePlatform implements Observer{
    private final String name;
    private Subject subject;

    public SlidePlatform(Subject subject) {
        this.name = name;
        this.subject = subject;
        this.subject.registerObserver(this);
    }

    @Override
    public void update(Object object) {
        System.out.println("Ricevuta notifica da " + this.name);
    }

    public abstract void update();
}
