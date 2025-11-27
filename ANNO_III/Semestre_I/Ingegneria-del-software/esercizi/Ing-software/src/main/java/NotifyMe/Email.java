package NotifyMe;

public class Email extends MessageSender{
    public Email() {
        super("Email");
    }

    @Override
    public void prepareAndFormat(Message msg) {
        System.out.println("Formatting HTML");
    }

    @Override
    public boolean wantsLog() {
        return true;
    }
}
