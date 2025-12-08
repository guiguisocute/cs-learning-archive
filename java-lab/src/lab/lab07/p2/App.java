package lab.lab07.p2;
/*
TODO:功能：实现多人竞争打电话，借助互斥机制，确保每个人的说话是连续的。
 */

class App{
    public static void main (String[] args) {
        DianHuaTing d=new DianHuaTing();
        String[] s1={"1","2","3"};
        String[] s2={"A","B","C","D","E"};
        String[] s3={"你好，","我也好，","大家都好！"};
        Talkers t1=new Talkers(d,"张三",s1);
        Talkers t2=new Talkers(d,"李四",s2);
        Talkers t3=new Talkers(d,"王五",s3);
        t1.start (); t2.start (); t3.start ();
    }
}

class DianHuaTing{      //此类对象仅提供多人打电话的共享资源
    private final String dht="我是电话亭";
}