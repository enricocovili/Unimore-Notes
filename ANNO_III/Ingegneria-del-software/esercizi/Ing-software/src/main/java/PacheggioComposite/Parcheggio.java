package PacheggioComposite;

import java.awt.*;
import java.util.ArrayList;
import java.util.Iterator;

public class Parcheggio extends ParcheggioComponent{
    ArrayList<ParcheggioComponent> parcheggioComponents = new ArrayList<ParcheggioComponent>();
    String name;
    String description;
    public Parcheggio(String name, String description) {
        this.name = name;
        this.description = description;
    }

    public void add(ParcheggioComponent parcheggioComponent) {
        parcheggioComponents.add(parcheggioComponent);

    }
    public void remove(ParcheggioComponent parcheggioComponent) {
        parcheggioComponents.remove(parcheggioComponent);
    }

    public ParcheggioComponent getChild(Integer i) {
        return parcheggioComponents.get(i);
    }

    public String getName() {
        return name;
    }

    public String getDescription() {
        return description;
    }

    @Override
    public Iterator<ParcheggioComponent> createIterator() {
        if (iterator == null) {
            iterator = new Iterator<ParcheggioComponent>(parcheggioComponents.iterator());
        }
        return iterator;
    }

    public void state() {
        for
    }
}
