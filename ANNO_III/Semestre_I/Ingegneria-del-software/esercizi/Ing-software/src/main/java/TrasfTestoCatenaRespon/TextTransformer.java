package TrasfTestoCatenaRespon;

public interface TextTransformer {
    TextTransformer setNext(TextTransformer handler);
    String transform(String text, String operation);
}
