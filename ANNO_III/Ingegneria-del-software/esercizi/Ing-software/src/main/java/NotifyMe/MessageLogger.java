package NotifyMe;

import java.util.ArrayList;

public class MessageLogger {
    private final ArrayList<Message> logs;

    public MessageLogger() {
        logs = new ArrayList<>();
    }

    public void insertLog(Message msg) {
        logs.add(msg);
        System.out.println("Message inserted to logs");
    }

    public ArrayList<Message> getLogs() {
        return logs;
    }
}
