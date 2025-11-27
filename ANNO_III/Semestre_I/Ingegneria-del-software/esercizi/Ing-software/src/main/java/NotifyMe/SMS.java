package NotifyMe;

public class SMS extends MessageSender{
    private final int SIZE_LIMIT = 5;

    public SMS() {
        super("SMS");
    }

    @Override
    public void prepareAndFormat(Message msg) {
        msg.setText(msg.getText().substring(0, Math.min(msg.getText().length(), SIZE_LIMIT)));
        System.out.println("trimmed SMS is: " + msg.getText());
    }

    @Override
    public boolean wantsLog() {
        return false;
    }
}
