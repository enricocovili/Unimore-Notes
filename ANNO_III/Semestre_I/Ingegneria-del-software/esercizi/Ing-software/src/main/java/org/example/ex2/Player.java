package org.example.ex2;

public abstract class Player {
    String name;
    Weapon weapon;
    MovingBehaviour vehicle;

    public Player(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Weapon getWeapon() {
        return weapon;
    }

    public void setWeapon(Weapon weapon) {
        this.weapon = weapon;
    }

    public MovingBehaviour getVehicle() {
        return vehicle;
    }

    public void setVehicle(MovingBehaviour vehicle) {
        this.vehicle = vehicle;
    }

    public abstract void move();
    public abstract void attack();
}
