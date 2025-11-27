package SimulatoreCampane;

import java.awt.desktop.SystemEventListener;

public class CampanaTic extends CampanaDecorator{
    public CampanaTic(Campana source) {
        super(source);
        this.setSuono(source.getSuono() + " TIC");
    }
}
