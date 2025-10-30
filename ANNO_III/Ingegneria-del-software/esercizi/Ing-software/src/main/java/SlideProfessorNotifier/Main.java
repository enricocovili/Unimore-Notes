package SlideProfessorNotifier;

public class Main {
    public Main() {
    }

    public static void main(String[] args) {
        Professor testProf = new Professor();
        TelegramSubscriber testTelegram = new TelegramSubscriber("Telegram", testProf);
    }
}
