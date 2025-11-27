package PacheggioComposite;

import java.awt.*;
import java.util.Iterator;

public abstract class ParcheggioComponent {
    Iterator<ParcheggioComponent> iterator = null;

    public void add(ParcheggioComponent parcheggioComponent) {
        throw new UnsupportedOperationException();
    }
    public void remove(ParcheggioComponent parcheggioComponent) {
        throw new UnsupportedOperationException();
    }
    public ParcheggioComponent getChild(int i) {
        throw new UnsupportedOperationException();
    }
    public String getName() {
        throw new UnsupportedOperationException();
    }
    public String getDescription() {
        throw new UnsupportedOperationException();
    }
    public double getPrice() {
        throw new UnsupportedOperationException();
    }
    public boolean isVegetarian() {
        throw new UnsupportedOperationException();
    }
    public void print() {
        throw new UnsupportedOperationException();
    }
    public Iterator<ParcheggioComponent> createIterator() {
        return iterator;
    }
}
