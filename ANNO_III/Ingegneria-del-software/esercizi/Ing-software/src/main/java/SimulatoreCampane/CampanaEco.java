package SimulatoreCampane;

public class CampanaEco extends CampanaDecorator{
    public CampanaEco(Campana source) {
        super(source);
        this.setSuono(source.suono + " " + source.suono);
    }

}
