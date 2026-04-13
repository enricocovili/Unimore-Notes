package Campanello_Proxy;

public class OpenDoorCommand implements Command{
    Doorbell doorbell;

    public OpenDoorCommand(Doorbell doorbell) {
        this.doorbell = doorbell;
    }


    @Override
    public void execute() {
        this.doorbell.openDoor();
    }
}
