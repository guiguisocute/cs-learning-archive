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

class Animal{
    void smell(Qiwei qiwei_in){
        System.out.println("动物闻到气味");
    }
}

class Cat extends Animal{
    @Override
    void smell(Qiwei qiwei_in){
        if(qiwei_in instanceof BoneQiwei){
            smell((BoneQiwei)qiwei_in);
        } else if(qiwei_in instanceof TigerQiwei){
            smell((TigerQiwei)qiwei_in);
        } else if(qiwei_in instanceof MasterQiwei){
            smell((MasterQiwei)qiwei_in);
        } else if(qiwei_in instanceof FishQiwei){
            smell((FishQiwei)qiwei_in);
        }
    }
    
    void smell(BoneQiwei qiwei_in){
        System.out.println("猫闻到" + qiwei_in.getName() + "：不感兴趣");
    }
    void smell(TigerQiwei qiwei_in){
        System.out.println("猫闻到" + qiwei_in.getName() + "：躲起来");
    }
    void smell(MasterQiwei qiwei_in){
        System.out.println("猫闻到" + qiwei_in.getName() + "：暗中观察");
    }
    void smell(FishQiwei qiwei_in){
        System.out.println("猫闻到" + qiwei_in.getName() + "：想吃");
    }
}

class Dog extends Animal{
    @Override
    void smell(Qiwei qiwei_in){
        if(qiwei_in instanceof BoneQiwei){
            smell((BoneQiwei)qiwei_in);
        } else if(qiwei_in instanceof TigerQiwei){
            smell((TigerQiwei)qiwei_in);
        } else if(qiwei_in instanceof MasterQiwei){
            smell((MasterQiwei)qiwei_in);
        } else if(qiwei_in instanceof FishQiwei){
            smell((FishQiwei)qiwei_in);
        }
    }
    
    void smell(BoneQiwei qiwei_in){
        System.out.println("狗闻到" + qiwei_in.getName() + "：想吃");
    }
    void smell(TigerQiwei qiwei_in){
        System.out.println("狗闻到" + qiwei_in.getName() + "：躲起来");
    }
    void smell(MasterQiwei qiwei_in){
        System.out.println("狗闻到" + qiwei_in.getName() + "：蹭蹭");
    }
    void smell(FishQiwei qiwei_in){
        System.out.println("狗闻到"+ qiwei_in.getName() + "：不感兴趣");
    }
}



class Qiwei{
    private final String qiwei_name;
    Qiwei(String name){
        qiwei_name = name;
    }
    public String getName(){
        return qiwei_name;
    }
}

class FishQiwei extends Qiwei{
    FishQiwei(){
        super("鱼");
    }
}

class TigerQiwei extends Qiwei{
    TigerQiwei(){
        super("老虎");
    }
}

class MasterQiwei extends Qiwei{
    MasterQiwei(){
        super("主人");
    }
}

class BoneQiwei extends Qiwei{
    BoneQiwei(){
        super("骨头");
    }
}


