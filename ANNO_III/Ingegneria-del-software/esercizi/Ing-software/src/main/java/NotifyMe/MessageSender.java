package NotifyMe;

public abstract class MessageSender {
    private final String name;
    private MessageLogger logger = null;

    public MessageSender(String name) {
        this.name = name;
    }

    public void setLogger(MessageLogger logger) {
        this.logger = logger;
    }

    public final void sendMessage(String recipient, String text) {
        connect();
        Message msg = new Message(recipient, text, name);
        prepareAndFormat(msg);
        send(msg);
        disconnect();
        if (wantsLog()) {
            logger.insertLog(msg);
        }
    }

    public void connect() {
        System.out.println("Connecting to " + name + " servers");
    }

    public abstract void prepareAndFormat(Message msg);

    public void send(Message msg) {
        System.out.println("Sending message with rec. " + msg.recipient);
    }

    public void disconnect() {
        System.out.println("Disconnecting from " + name + " servers");
    }

    public abstract boolean wantsLog();
}
