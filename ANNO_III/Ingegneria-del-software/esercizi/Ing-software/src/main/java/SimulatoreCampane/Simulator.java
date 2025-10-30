package SimulatoreCampane;

import java.util.ArrayList;

public class Simulator {
    public static void main(String[] args) {
        ArrayList<Command> commandList = new ArrayList<>();
        int len = 5;
        for (int i = 0; i<len; i++) {
            int rand = (int) (Math.random() * 3);
            switch (rand) {
                case 0:
                    commandList.add(new Command(new CampanaTic(new CampanaDin())));
                    break;
                case 1:
                    commandList.add(new Command(new CampanaEco(new CampanaDon())));
                    break;
                case 2:
                    commandList.add(new Command(new CampanaVento(new CampanaEco(new CampanaDan()))));
                    break;
                default:
                    System.out.println("error." + rand);
            }
        }

        for (Command cmd : commandList) {
            cmd.execute();
        }

    }
}
