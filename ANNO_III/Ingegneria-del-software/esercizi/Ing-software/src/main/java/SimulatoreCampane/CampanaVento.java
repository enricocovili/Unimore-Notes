package SimulatoreCampane;

public class CampanaVento extends CampanaDecorator{
    public CampanaVento(Campana source) {
        super(source);
        this.setSuono(source.getSuono() + " FRIIII");
    }
}
