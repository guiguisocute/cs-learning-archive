package lab.lab04.p2;

/*
TODO:利用重载、重写和 instanceof，实现：猫/狗闻到不同气味，给出不同反应。
     其中，气味包含主人、老虎、骨头、鱼
 */
class App{
    public static void main (String[] args) {
        Cat c=new Cat(); Dog d=new Dog();
        Qiwei[] qA={new FishQiwei(),new TigerQiwei(),new
                MasterQiwei(),new BoneQiwei()};
        System.out.println("让 猫 闻这组气味，结果为：");
        for(Qiwei q: qA)c.smell(q);
        System.out.println("\n 让 狗 闻这组气味，结果为：");
        for(Qiwei q: qA)d.smell(q);}
}
