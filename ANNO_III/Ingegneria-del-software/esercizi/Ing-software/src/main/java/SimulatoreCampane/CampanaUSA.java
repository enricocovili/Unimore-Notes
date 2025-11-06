package SimulatoreCampane;

public class CampanaUSA {
    String sound;

    public CampanaUSA() {
        this.sound = "Beep";
    }

    public String getSound() {
        return this.sound;
    }

    public void ring() {
        System.out.println(sound);
    }
}
