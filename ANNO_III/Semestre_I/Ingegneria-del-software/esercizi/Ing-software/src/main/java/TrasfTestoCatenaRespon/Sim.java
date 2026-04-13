package TrasfTestoCatenaRespon;

public class Sim {
    public static TextTransformer createChain() {
        TextTransformer uppercase = new UppercaseTransformer();
        TextTransformer lowercase = new LowercaseTransformer();

        uppercase.setNext(lowercase);

        return uppercase;
    }

    public static void main(String[] args) {
        TextTransformer chain = createChain();

        String input = "ecco un teStO di Prova";

        System.out.println("Testo Originale: \"" + input + "\"");
        System.out.println("------------------------------------------");

        String result1 = chain.transform(input, "MAIUSCOLO");
        System.out.println("Risultato MAIUSCOLO: \"" + result1 + "\"\n");

        String result2 = chain.transform(input, "MINUSCOLO");
        System.out.println("Risultato MINUSCOLO: \"" + result2 + "\"\n");
    }
}