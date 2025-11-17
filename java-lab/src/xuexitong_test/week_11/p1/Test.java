package xuexitong_test.week_11.p1;
/*
TODO:
某游戏有不同类型的soldier（士兵）（抽象类）
Spearman （枪兵）的攻击方式是“用枪射击”，
Rocketeer （火箭兵）的攻击方式是“发射火箭攻击”，
Grenadier （手雷兵）的攻击方式是“用手雷炸”。
如给定枪兵对象a，手雷兵对象b，a.attack(b)，输出结果是“枪兵用枪射击手雷兵”，b.attack(a)，输出结果是“手雷兵用手雷炸枪兵”。

模拟时，给定一个存放各类士兵对象的数组，x从头至尾，y从尾至头，执行x.attack(y)。
【提示】本题需要用到toString()


输出结果为：
枪兵用枪射击手雷兵
火箭兵发射火箭攻击火箭兵
手雷兵用手雷炸枪兵
 */

public class Test {
    public static void main(String[] args) {
        Soldier soldiers[] = new Soldier[3];
        soldiers[0] = new Spearman();
        soldiers[1] = new Rocketeer();
        soldiers[2] = new Grenadier();
        for(int x = 0, y = soldiers.length - 1; x < soldiers.length; x++, y--){
            soldiers[x].attack(soldiers[y]);
        }
    }
}

abstract class Soldier{
    abstract void attack(Soldier soldier_in);

}

class Spearman extends Soldier{
    @Override
    void attack(Soldier soldier_in) {
        System.out.println("枪兵用枪射击" + soldier_in);
    }

    @Override
    public String toString() {
        return "枪兵";
    }

}

class Rocketeer extends Soldier{
    @Override
    void attack(Soldier soldier_in) {
        System.out.println("火箭兵发射火箭攻击" + soldier_in);
    }

    @Override
    public String toString() {
        return "火箭兵";
    }

}

class Grenadier extends Soldier{
    @Override
    void attack(Soldier soldier_in) {
        System.out.println("手雷兵用手雷炸" + soldier_in);
    }

    @Override
    public String toString() {
        return "手雷兵";
    }

}