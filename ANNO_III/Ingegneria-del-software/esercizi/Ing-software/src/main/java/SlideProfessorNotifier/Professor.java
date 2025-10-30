package SlideProfessorNotifier;

public class Professor extends Subject{
    public void sendMessage() {
        this.notifyObservers();
    }
}
