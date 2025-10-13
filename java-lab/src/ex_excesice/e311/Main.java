package e311;

public class Main {
    public static void main(String[] args) {
        Person ming = new Person();
        ming.setName("小明");
        ming.setAge(12);
        System.out.println(ming.getName());
        System.out.println(ming.getAge());
    }
}

class Person {
    private String name;
    private int age;

    int getAge() {
        return age;
    }

    void setAge(int age){
        this.age = age;
    }

    String getName() {
        return name;
    }

    void setName(String name) {
        this.name = name;
    }
}
