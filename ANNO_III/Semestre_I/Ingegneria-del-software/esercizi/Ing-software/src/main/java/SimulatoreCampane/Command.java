package SimulatoreCampane;

public class Command {
    protected final Campana campana;

    public Command(Campana campana) {
        this.campana = campana;
    }

    public void execute() {
        this.campana.suona();
    }
}
