package Quickverify.VSC;


public class testforIDK {
    public static void main(String[] args) {
        print(new GraduateStudent());
    }

    public static void print(Object x) {
        System.out.println(x.toString());
    }
}

class Person {
    public String toString() {
        return "Person";
    }
}

    class Student extends Person {
        public String toString() {
            return "Student";
        }
    }


class GraduateStudent extends Student {
}
