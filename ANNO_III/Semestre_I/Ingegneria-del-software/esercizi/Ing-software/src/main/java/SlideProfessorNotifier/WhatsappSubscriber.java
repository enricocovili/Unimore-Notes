package SlideProfessorNotifier;

public class WhatsappSubscriber extends SlidePlatform{
    public WhatsappSubscriber() {
        this.name = "Whatsapp";
    }

    @Override
    public void update() {
        System.out.println("Notifica da Whatsapp");
    }
}
