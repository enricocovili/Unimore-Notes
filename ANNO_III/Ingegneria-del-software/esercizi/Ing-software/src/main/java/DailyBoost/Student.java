package DailyBoost;

public class Student extends Observer{
    private String name;

    public Student(String name) {
        this.name = name;
    }

    @Override
    void update(Message message) {
        System.out.println("Studente " + this.name + "ha ricevuto" + message.getContent());
    }
}
