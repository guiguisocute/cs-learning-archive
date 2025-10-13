package e312;

public class Main {

    public static void main(String[] args) {
        Person2 ming = new Person2();
        ming.setName("Xiao Ming");
        System.out.println(ming.getName());
        Person2 hong = new Person2();
        // FIXME: 给Person增加重载方法setName(String, String):
        hong.setName("Xiao", "Hong");
        System.out.println(hong.getName());
    }

}
class Person2 {

    private String name;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
    public void setName(String name1,String name2) {
        name=name1+" "+name2;
    }

}
