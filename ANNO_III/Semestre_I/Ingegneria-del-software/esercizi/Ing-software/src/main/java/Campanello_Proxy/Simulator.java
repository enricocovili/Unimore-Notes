package Campanello_Proxy;

public class Simulator {
	public static void main(String[] args) {
		Doorbell real = new SmartDoorbell();
		Doorbell asOwner = DoorbellProxyFactory.create(real, Role.OWNER);
		Doorbell asVisitor = DoorbellProxyFactory.create(real, Role.VISITOR);

        Remote remote = new Remote();
        remote.setBtn1(new OpenDoorCommand(asOwner));
        remote.setBtn2(new RingCommand(asOwner));
		System.out.println("Initial: " + real.getStatus());

        System.out.print("pressing 1: ");
        remote.press1();
        System.out.println(real.getStatus());
        System.out.print("pressing 2: ");
        remote.press2();
        System.out.println(real.getStatus());

		System.out.println("Final: " + real.getStatus());
	}
}

