package VeicoloAbstractFactory;

public interface CarFactory {
    Motor craftMotor();
    Bodywork craftBodywork();
    Internals craftInternals();
}
