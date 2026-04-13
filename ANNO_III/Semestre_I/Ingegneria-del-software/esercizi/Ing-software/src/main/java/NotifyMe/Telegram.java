package NotifyMe;

public class Telegram extends MessageSender{

    public Telegram() {
        super("Telegram");
    }

    @Override
    public void prepareAndFormat(Message msg) {
        // Do nothing here
        return;
    }

    @Override
    public boolean wantsLog() {
        return true; // logs needed
    }
}
