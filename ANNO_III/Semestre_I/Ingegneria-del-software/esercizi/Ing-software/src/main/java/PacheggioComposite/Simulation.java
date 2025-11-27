package PacheggioComposite;

public class Simulation {
    public static void main(String[] args) {
        Parcheggio p = new Parcheggio("park", "turi-ipipip");

        p.add(new Parcheggio("area1", ""));
        p.add(new Parcheggio("area2", ""));
        p.add(new Parcheggio("area3", ""));

        p.getChild(0).add(new Parcheggio("sub1area1", ""));
        p.getChild(0).add(new Parcheggio("sub1area2", ""));
        p.getChild(1).add(new Parcheggio("sub2area1", ""));
        p.getChild(1).add(new Parcheggio("sub2area2", ""));
        p.getChild(2).add(new Parcheggio("sub3area1", ""));
        p.getChild(2).add(new Parcheggio("sub3area2", ""));

        p.state();

    }
}
