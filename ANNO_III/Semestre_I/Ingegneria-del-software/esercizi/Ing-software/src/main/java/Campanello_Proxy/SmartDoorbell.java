
package Campanello_Proxy;

public class SmartDoorbell implements Doorbell {
private boolean open = false;
private int ringCount = 0;


@Override public void openDoor() { open = true; }
@Override public void ring() { ringCount++; }
@Override public String getStatus() {
return (open ? "OPEN" : "CLOSED") + ", rings=" + ringCount;
}
@Override public String toString() { return "SmartDoorbell{" + getStatus() + "}"; }
}