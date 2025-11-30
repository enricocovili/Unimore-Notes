package TrasfTestoCatenaRespon;

public abstract class AbstractTransformer implements TextTransformer {

    private TextTransformer nextHandler;

    @Override
    public TextTransformer setNext(TextTransformer handler) {
        this.nextHandler = handler;
        return handler;
    }

    protected String passToNext(String text, String operation) {
        if (nextHandler != null) {
            return nextHandler.transform(text, operation);
        }
        return "Errore: Operazione '" + operation + "' non riconosciuta.";
    }
}