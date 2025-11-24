package MeteoState;

public class Sim {
    public static void main(String[] args) {
        Meteo meteo = new Meteo();

        System.out.println("Stato: " + meteo.getState().getClass().toString());
        meteo.nextIter();
        System.out.println("Stato: " + meteo.getState().getClass().toString());
        meteo.nextIter();
        System.out.println("Stato: " + meteo.getState().getClass().toString());
        meteo.nextIter();
        System.out.println("Stato: " + meteo.getState().getClass().toString());
        meteo.nextIter();
        System.out.println("Stato: " + meteo.getState().getClass().toString());
        meteo.nextIter();
        System.out.println("Stato: " + meteo.getState().getClass().toString());
    }
}

