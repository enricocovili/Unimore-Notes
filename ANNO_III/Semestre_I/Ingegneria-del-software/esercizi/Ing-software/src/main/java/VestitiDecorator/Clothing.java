package VestitiDecorator;

public abstract class Clothing {
    private String name;
    private PackagingStrategy packaging;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public PackagingStrategy getPackaging() {
        return packaging;
    }

    public void setPackaging(PackagingStrategy packaging) {
        this.packaging = packaging;
    }
}
