package DailyBoost;

public abstract class Observer {
    LanguageStrategy language;

    abstract void update(Message message);
}
