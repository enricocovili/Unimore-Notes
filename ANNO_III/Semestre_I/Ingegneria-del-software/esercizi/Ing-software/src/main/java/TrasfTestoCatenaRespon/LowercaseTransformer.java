package TrasfTestoCatenaRespon;

public class LowercaseTransformer extends AbstractTransformer{
    private static final String OPERATION = "MINUSCOLO";

    @Override
    public String transform(String text, String operation) {
        if (operation.equalsIgnoreCase(OPERATION)) {
            System.out.println("-> Eseguo Trasformazione: MAIUSCOLO");
            return text.toLowerCase();
        } else {
            return super.passToNext(text, operation);
        }
    }
}
