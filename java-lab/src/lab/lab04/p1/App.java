package lab.lab04.p1;
/*
TODO:
    2.设计满足如下要求的三角形类：
    (1) 至少有 6 个成员：三边及三边上的高；
    (2) 构造时必须提供三边或者底和高。之后可补充或重新设置三角形相关属性。
        要求三角形满足一致性规则：
        三边必须大于 0，两边之和要大于第三边，条件不满足不能创造三角形；
        三边值未填写则值为 0；最多创建 3 个三角形对象。
    (3) 两种计算面积的方法：用底*高计算出来的面积与用海伦公式计算出的面积。
    (4) 输出类的成员信息。
 */
import java.util.Arrays;


class App {

    public static void main(String[] args) {

        SanJiao s1 = SanJiao.creatSanJiao(2, 3, 4);
        s1.showInfo();
        System.out.println("面积为：" + s1.heronArea());// 海伦公式计算面积
        s1.resetEdges(1, 1, 3);// 重设三边
        s1.resetEdges(2, 2, 3);
        s1.showInfo();
        SanJiao s2 = SanJiao.creatSanJiao(5, 6);
        s2.showInfo();
        System.out.println("面积为：" + s2.area());// 底*高计算面积

    }

}

class SanJiao {
    private static int count = 0;
    private static final int MAX_COUNT = 3;

    double long_1;
    double long_2;
    double long_3;
    double long_1_h;
    double long_2_h;
    double long_3_h;


    double heronArea() {
        double p = (long_1 + long_2 + long_3) / 2.0;
        return Math.sqrt(p * (p - long_1) * (p - long_2) * (p - long_3));
    }

    double area() {
        return long_1 * long_1_h / 2.0;
    }

    void showInfo() {

        System.out.println("本三角形三条边为：a=" + long_1 + ",b=" + long_2 + ",c=" + long_3);
        if (long_2 == 0) {
            System.out.println("该三角形的高ha为：" + long_1_h);
        }

    }

    void resetEdges(double long_1_in, double long_2_in, double long_3_in) {
        if (creatSanJiao(long_1_in, long_2_in, long_3_in) == null) {
            System.out.println("无法重新设置，三边参数不正确！");
        } else {
            long_1 = long_1_in;
            long_2 = long_2_in;
            long_3 = long_3_in;
            long_1_h = heronArea() / long_1;
            long_2_h = heronArea() / long_2;
            long_3_h = heronArea() / long_3;
        }

    }

    private SanJiao(double long_1_in, double long_2_in, double long_3_in) {
        long_1 = long_1_in;
        long_2 = long_2_in;
        long_3 = long_3_in;
        long_1_h = heronArea() / long_1;
        long_2_h = heronArea() / long_2;
        long_3_h = heronArea() / long_3;
    }

    private SanJiao(double di_in, double gao_in) {
        this(di_in, 0.0, 0.0);
        long_1_h = gao_in;
    }

    public static SanJiao creatSanJiao(double long_1_in, double long_2_in, double long_3_in) {
        double[] temp = { long_1_in, long_2_in, long_3_in };
        Arrays.sort(temp);
        if (long_1_in > 0 && long_2_in > 0 && long_3_in > 0 && temp[0] + temp[1] > temp[2] && count <= MAX_COUNT) {
            count++;
            return new SanJiao(long_1_in, long_2_in, long_3_in);
        }
        return null;
    }

    public static SanJiao creatSanJiao(double di_in, double gao_in) {
        return new SanJiao(di_in, gao_in);
    }
}
