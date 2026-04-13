package NotifyMe;

public class Message {
    String recipient;
    String text;
    String type;

    public Message(String recipient, String text, String type) {
        this.recipient = recipient;
        this.text = text;
        this.type = type;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getRecipient() {
        return recipient;
    }

    public void setRecipient(String recipient) {
        this.recipient = recipient;
    }

    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
    }

    @Override
    public String toString() {
        return "Message{" +
                "recipient='" + recipient + '\'' +
                ", text='" + text + '\'' +
                ", type='" + type + '\'' +
                '}';
    }
}
