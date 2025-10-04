void rfidHardReset();   // RST 脚硬复位 RC522
uidStore.begin();       // 白名单初始化
door.openThenClose();   // 触发开门
door.update();          // 舵机状态机
uidToHex(...);          // UID 转 HEX 工具
uidStore.contains(...); // 白名单检查 