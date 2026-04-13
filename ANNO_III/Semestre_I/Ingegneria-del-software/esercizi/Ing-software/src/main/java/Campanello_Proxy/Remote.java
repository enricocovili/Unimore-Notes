package Campanello_Proxy;

public class Remote {
    Command btn1;
    Command btn2;

    public void press1() {
        btn1.execute();
    }

    public void press2() {
        btn2.execute();
    }

    public void setBtn1(Command btn1) {
        this.btn1 = btn1;
    }

    public void setBtn2(Command btn2) {
        this.btn2 = btn2;
    }
}
