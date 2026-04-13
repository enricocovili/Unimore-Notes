package PacheggioComposite;

import java.util.Iterator;
import java.util.Stack;

public class ParcheggioIterator {
    Stack<Iterator<ParcheggioComponent>> stack = new Stack<Iterator<ParcheggioComponent>>();

    public ParcheggioIterator(Iterator iterator) {
        stack.push(iterator);
    }

    public ParcheggioComponent next() {
        if (hasNext()) {
            Iterator<ParcheggioComponent> iterator = stack.peek();
            ParcheggioComponent component = iterator.next();
            stack.push(component.createIterator());
            return component;
        } else {
            return null;
        }
    }

    public boolean hasNext() {
        if (stack.empty()) {
            return false;
        } else {
            Iterator<ParcheggioComponent> iterator = stack.peek();
            if (iterator == null || !iterator.hasNext()) {
                stack.pop();
                return hasNext();
            } else {
                return true;
            }
        }
    }
}
