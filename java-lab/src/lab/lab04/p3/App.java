package lab.lab04.p3;
/*
TODO:【游戏：棒子老虎鸡虫】
    有木棒、老虎、鸡、虫四种族，吃法如下：棒子可以吃老虎，老虎吃鸡，鸡吃虫子，虫子吃木棒。其它情形为和。现在要求编制程序实现如
    下功能：
        a.)用由四种族的对象若干组成的红黑两队成员（成员数相同）。
        b.)让红、黑两队成员一一对搏，获胜得1分，否则得0分，总分高者赢。
        c.)输出对搏情况以及总比分。

如：红方{棒子，老虎，鸡，虫，老虎}，黑方{虫，老虎，虫，鸡，棒子}，则输出：
```
棒子 VS 虫 红方输
老虎 VS 老虎 和局
鸡 VS 虫 红方胜只有底和高无法计算周长。
虫 VS 鸡 红方输
老虎 VS 棒子 红方输
总比分：红方 VS 黑方=1:3，红方输
```
 */
import java.util.Random;

import Quickverify.temp_circle.res;
public class App {
//    static int TEST_GROUP = 5;
    public static void main(String[] args) {
        // for(int i = 0; i < TEST_GROUP; i++){
        //     Random random = new Random();
        //     int chess_num_sum_per = random.nextInt(5) + 5;
        //     Chess_ctrl red = new Chess_ctrl(chess_num_sum_per,"红方");  //传入单int构造方法默认填充对应数量随机棋子，第二个传参为ID名
        //     Chess_ctrl black = new Chess_ctrl(chess_num_sum_per,"黑方");
        //     red.battle(black);
        // }
        Chess_ctrl red_example = new Chess_ctrl("棒子，老虎，鸡，虫，老虎","红方");     //指定棋子进行参赛
        Chess_ctrl black_example = new Chess_ctrl("虫，老虎，虫，鸡，棒子","黑方");     
        red_example.battle(black_example);
        
    }

}

class Chess_ctrl{
    private final String team_name;
    private final String chessForPrint;
    private final Chess[] chess_array;
    // private static final Class<?>[] TYPES = { Bangzi.class, Laohu.class, Ji.class, Bug.class };     //用到了泛型，存放四种棋子类型的Class对象，<?>的意思可以是任意类型相当于离散数学的任有，这回总知道专业课的用处了吧
    // private Random random = new Random();

    // public Chess_ctrl(int chess_num_sum_per, String team_name_in){
    //     team_name = team_name_in;
    //     chess_array = new Chess[chess_num_sum_per];
    //     for(int i = 0; i < chess_num_sum_per; i++){
    //         chess_array[i] = randomChess(); 
    //     }
    // }

    public Chess_ctrl(String chess_namelist_in_str, String team_name_in){
        team_name = team_name_in;
        chessForPrint = chess_namelist_in_str;
        String[] chess_name_array = chess_namelist_in_str.split("，");
        chess_array = new Chess[chess_name_array.length];
        for(int i = 0; i < chess_name_array.length; i++){
            chess_array[i] = createChessByName(chess_name_array[i].trim());
        }
    }
    
    // private Chess randomChess(){                
    //     int idx = random.nextInt(TYPES.length);

    // }    //这里似乎需要用到“反射”，等我先把基本用字符串创建写完，把相关内容学完了，再来一步一步敲

    private Chess createChessByName(String chess_name_in){
        switch (chess_name_in) {
            case "棒子":
                return new Bangzi();
            case "老虎":
                return new Laohu();
            case "鸡":
                return new Ji();
            case "虫":
                return new Bug();
            default:
                return null;
        }
    }

    public void battle(Chess_ctrl other){
        if(chess_array.length != other.chess_array.length){
            System.out.println("棋子数量不一致，请检查！");
        }
        int my_score = 0; int other_score = 0; int len = chess_array.length;
        System.out.println("\n== " + this.team_name + " VS " + other.team_name + " ==");
        for(int i = 0; i < len; i++){
            Chess a = chess_array[i];
            Chess b = other.chess_array[i];
            int result = a.compare(b);
            String result_msg = team_name;
            if(result == 1){
                my_score++;
                result_msg += "胜";
            }
            else if(result == -1){
                other_score++;
                result_msg += "输";
            }
            else{
                result_msg = "和局";
            }
            System.out.println(a + " VS " + b + " " + result_msg);
        }
        System.out.println("总比分：" + this.team_name + " VS " + other.team_name + "=" + my_score + ":" + other_score + "，" + (my_score > other_score ? this.team_name + "胜" : (my_score < other_score ? this.team_name + "输" : "平局")));

    }


    public String toString(){
        return "你的棋子数量为" + chess_array.length + "棋子为" + chessForPrint;
    }

}

abstract class Chess{              //抽象棋子类,虽然这里不用非得抽象父类直接把compare方法写死在子类也行，但我想好好练一下我的OOP
    protected String chess_name;
    public String getName(){
        return chess_name;
    }
    Chess(String name_in){
        chess_name = name_in;
    }
    abstract int compare(Chess other_chess_in);  //比较输赢，返回1表示胜，0表示和，-1表示输

    public String toString(){
        return chess_name;
    }
}

class Bangzi extends Chess{
    Bangzi(){
        super("棒子");
    }
    @Override
    int compare(Chess other_chess_in){
        if(other_chess_in instanceof Laohu){
            return 1;
        }
        if(other_chess_in instanceof Bug){
            return -1;
        }
        return 0;
    }
}

class Laohu extends Chess{
    Laohu(){
        super("老虎");
    }
    @Override
    int compare(Chess other_chess_in){
        if(other_chess_in instanceof Ji){
            return 1;
        }
        if(other_chess_in instanceof Bangzi){
            return -1;
        }
        return 0;
    }
}

class Ji extends Chess{
    Ji(){
        super("鸡");
    }
    @Override
    int compare(Chess other_chess_in){
        if(other_chess_in instanceof Bug){
            return 1;
        }
        if(other_chess_in instanceof Laohu){
            return -1;
        }
        return 0;
    }
}

class Bug extends Chess{
    Bug(){
        super("虫");
    }
    @Override
    int compare(Chess other_chess_in){
        if(other_chess_in instanceof Bangzi){
            return 1;
        }
        if(other_chess_in instanceof Ji){
            return -1;
        }
        return 0;
    }
}


