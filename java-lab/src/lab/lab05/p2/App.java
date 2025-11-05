package lab.lab05.p2;

/*
TODO:写一个圆柱体类,包含一个内部类圆.要求圆的面积和周长,圆柱体的表面积和体积.
 */

public class App {
    public static void main(String[] args) {
        Cylinder cy1 = new Cylinder(3.0, 3.0);
        cy1.disVol();
        cy1.disSurfaceArea();
        cy1.circle.disArea();
        cy1.circle.disPerimeter();
    }
}

class Cylinder {
    double high;
    Circle circle;

    Cylinder(double Circle_r_in, double Cylinder_high_in) {
        circle = new Circle(Circle_r_in);
        high = Cylinder_high_in;

    }

    void disVol() {
        System.out.printf("该圆柱体的体积为：%.2f\n", circle.r * circle.r * 3.14 * high);
    }

    void disSurfaceArea() {
        System.out.printf("该圆柱体的表面积为：%.2f\n", 2 * circle.r * circle.r * 3.14 + circle.r * 2 * 3.14 * high);
    }

    class Circle {
        double r;

        Circle(double Circle_r_in) {
            r = Circle_r_in;
        }

        void disPerimeter() {
            System.out.printf("该圆柱里的圆周长为：%.2f\n", r * 2 * 3.14);
        }

        void disArea() {
            System.out.printf("该圆柱里的圆面积为：%.2f\n", r * r * 3.14);
        }

    }
}
