package SmartBuilding;

public class Manutenzione extends Agent {

    @Override
    public boolean check(Object o) {
        if (o instanceof MalfunctionObservable) {
            return true;
        }
        return false;
    }
}
