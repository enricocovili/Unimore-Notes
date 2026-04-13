package Campanello_Proxy;

import java.lang.reflect.*;


public class SimpleRoleHandler implements InvocationHandler {
	private final Doorbell target;
	private final Role role;
	public SimpleRoleHandler(Doorbell target, Role role) { this.target = target; this.role = role; }


	@Override
	public Object invoke(Object proxy, Method method, Object[] args) throws IllegalAccessException {
		try {
			String name = method.getName();
			// Letture sempre consentite
			if (name.startsWith("get")) {
				return method.invoke(target, args);
			}
			// Regole in base al ruolo (versione SENZA estensione):
			// - OWNER: pu� aprire (openDoor), NON suonare (ring)
			// - VISITOR: pu� suonare (ring), NON aprire (openDoor)
			if (role == Role.OWNER && name.equals("openDoor")) {
				return method.invoke(target, args);
			}
			if (role == Role.VISITOR && name.equals("ring")) {
				return method.invoke(target, args);
			}
			throw new IllegalAccessException("Method '" + name + "' not allowed for role " + role);
		} catch (InvocationTargetException e) {
			e.printStackTrace();
		}
		return null;
	}
}
