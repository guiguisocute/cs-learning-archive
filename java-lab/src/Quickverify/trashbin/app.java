package Quickverify.trashbin;
/*
 TODO: 每户一张垃圾卡，团头鲂正确可获得积分，如卡片冻结，拒绝投垃圾提醒卡冻，如果垃圾已满拒绝投垃圾提醒桶已满，投放成功按重量奖励积分
 */
public class app {

}

class PointCard{
    String id;
    int points;
    boolean isFrozen;+

    PointCard(String id_in, int initialPoints){
        this.id = id_in;
        this.points = initialPoints;
        this.isFrozen = false;
    }


    void setFrozen(boolean status){
        this.isFrozen = status;
    }
}

class CommunityStation{
    Trashbin[] trashBins;
    CommunityStation(){
        trashBins = new Trashbin[3];
        trashBins[0] = new HarmfulTrashbin();
        trashBins[1] = new RecoverableTrashbin();
        trashBins[2] = new OtherTrashbin();
    }
}



abstract class Trashbin{
    int currentLoad;
    int size;
    boolean isFull;
    
    abstract boolean checkStatus();
    abstract int getPoint();
}

class HarmfulTrashbin extends Trashbin{
    HarmfulTrashbin(){
        this.size = 30;
        this.isFull = false;
    }

    @Override
    boolean checkStatus() {
        isFull = currentLoad >= size;
        return isFull;
    }
}

class RecoverableTrashbin extends Trashbin{
    RecoverableTrashbin(){
        this.size = 25;
        this.trashPoint = 10;
        this.isFull = false;
    }

    @Override
    boolean checkStatus() {
        isFull = currentLoad >= size;
        return isFull;
    }
}

class OtherTrashbin extends Trashbin{
     
    OtherTrashbin(){
        this.size = 20;
        this.trashPoint = 3;
        this.isFull = false;
    }

    @Override
    boolean checkStatus() {
        isFull = currentLoad >= size;
        return isFull;
    }
}


