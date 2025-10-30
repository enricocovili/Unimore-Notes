package DailyBoost;

public abstract class Message {
    private Object content;
    private String type;
    private String language;

    public Message(Object content, String type, String language) {
        this.content = content;
        this.type = type;
        this.language = language;
    }

    public Object getContent() {
        return content;
    }

    public String getType() {
        return type;
    }

    public String getLanguage() {
        return language;
    }
}
