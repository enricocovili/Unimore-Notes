package SimulatoreCampane;

public abstract class CampanaDecorator extends Campana{
    protected Campana source;

    public CampanaDecorator(Campana source) {
        this.source = source;
    }

}
