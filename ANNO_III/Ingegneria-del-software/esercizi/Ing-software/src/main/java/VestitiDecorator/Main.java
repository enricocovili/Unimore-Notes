package VestitiDecorator;

public class Main {
    public static void main(String[] args) {
        Clothing dress = new Clothing() {
            @Override
            public String getName() {
                return super.getName();
            }

            @Override
            public void setName(String name) {
                super.setName(name);
            }

            @Override
            public PackagingStrategy getPackaging() {
                return super.getPackaging();
            }

            @Override
            public void setPackaging(PackagingStrategy packaging) {
                super.setPackaging(packaging);
            }
        };
    }
}
