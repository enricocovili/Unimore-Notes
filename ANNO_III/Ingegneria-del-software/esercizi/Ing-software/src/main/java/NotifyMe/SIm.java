package NotifyMe;

public class SIm {
    public static void main(String[] args) {
        MessageLogger logger = new MessageLogger();

        Telegram tgram = new Telegram();
        tgram.setLogger(logger);
        Email mail = new Email();
        mail.setLogger(logger);
        SMS sms = new SMS();

        tgram.sendMessage("test", "ciao ciao");
        System.out.println("-------------------------------------------");
        mail.sendMessage("test1", "caio caio");
        System.out.println("-------------------------------------------");
        sms.sendMessage("sms recipient", "bing long text");

        System.out.println("\n\n");
        for (Message log : logger.getLogs()) {
            System.out.println(log);
        }
    }
}
