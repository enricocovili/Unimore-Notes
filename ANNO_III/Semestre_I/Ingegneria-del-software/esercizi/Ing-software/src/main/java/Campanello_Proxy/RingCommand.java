package Campanello_Proxy;

public class RingCommand implements Command{
    Doorbell doorbell;

    public RingCommand(Doorbell doorbell) {
        this.doorbell = doorbell;
    }

    @Override
    public void execute() {
        this.doorbell.ring();
    }
}
