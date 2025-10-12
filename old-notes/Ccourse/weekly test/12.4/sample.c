#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义订单结构体
typedef struct {
    char name[50];  // 商品名称
    float price;    // 单价
    int quantity;   // 数量
    float total_price;  // 总价
} Order;

// 计算订单总价
void calculateTotalPrice(Order* order) {
    order->total_price = order->price * order->quantity;
}

// 比较函数（用于排序）
int compareOrders(const void* a, const void* b) {
    Order* orderA = (Order*)a;
    Order* orderB = (Order*)b;
    
    if (orderA->total_price < orderB->total_price) return -1;
    if (orderA->total_price > orderB->total_price) return 1;
    return 0;
}

// 二分查找函数
int binarySearchOrder(Order* orders, int n, float target_price) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // 精确匹配
        if (orders[mid].total_price == target_price) {
            return mid;
        }
        
        if (orders[mid].total_price < target_price) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1; // 未找到
}

int main() {
    Order orders[10];
    int i;

    // 输入订单信息
    for (i = 0; i < 10; i++) {
        scanf("%s %f %d", 
            orders[i].name, 
            &orders[i].price, 
            &orders[i].quantity
        );
        // 计算总价
        calculateTotalPrice(&orders[i]);
    }

    // 输入目标总价
    float target_price;
    scanf("%f", &target_price);

    // 排序订单
    qsort(orders, 10, sizeof(Order), compareOrders);

    // 输出排序后的订单信息
    for (i = 0; i < 10; i++) {
        printf("%s %.2f %d %.2f\n", 
            orders[i].name, 
            orders[i].price, 
            orders[i].quantity, 
            orders[i].total_price
        );
    }

    // 二分查找目标总价
    int found_index = binarySearchOrder(orders, 10, target_price);

    // 输出查找结果
    if (found_index != -1) {
        printf("%s %.2f %d %.2f\n", 
            orders[found_index].name, 
            orders[found_index].price, 
            orders[found_index].quantity, 
            orders[found_index].total_price
        );
    } else {
        printf("Not found\n");
    }

    return 0;
}