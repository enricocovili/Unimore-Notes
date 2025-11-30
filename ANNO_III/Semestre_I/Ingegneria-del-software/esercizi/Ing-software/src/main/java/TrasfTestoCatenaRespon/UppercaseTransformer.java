package TrasfTestoCatenaRespon;

public class UppercaseTransformer extends AbstractTransformer {

    private static final String OPERATION = "MAIUSCOLO";

    @Override
    public String transform(String text, String operation) {
        if (operation.equalsIgnoreCase(OPERATION)) {
            System.out.println("-> Eseguo Trasformazione: MAIUSCOLO");
            return text.toUpperCase();
        } else {
            return super.passToNext(text, operation);
        }
    }
}