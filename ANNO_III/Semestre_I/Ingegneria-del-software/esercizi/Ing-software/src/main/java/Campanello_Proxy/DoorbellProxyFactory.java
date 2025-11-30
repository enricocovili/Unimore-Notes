package Campanello_Proxy;

import java.lang.reflect.*;

public class DoorbellProxyFactory {
	public static Doorbell create(Doorbell target, Role role) {
		InvocationHandler h = new SimpleRoleHandler(target, role);
		return (Doorbell) Proxy.newProxyInstance(
				target.getClass().getClassLoader(),
				new Class<?>[]{ Doorbell.class },
				h);
	}
}
