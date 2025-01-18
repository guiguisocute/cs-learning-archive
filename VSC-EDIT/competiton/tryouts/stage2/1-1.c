#include <stdio.h>
#include <string.h>

#define MAX_ORDERS 10

typedef struct {
    char name[50];
    float unit_price;
    int quantity;
    float total_price;
} Order;

// 冒泡排序函数
void bubble_sort(Order orders[], int n) {
    int i, j;
    Order temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (orders[j].total_price > orders[j + 1].total_price) {
                temp = orders[j];
                orders[j] = orders[j + 1];
                orders[j + 1] = temp;
            }
        }
    }
}

// 二分查找函数
int binary_search(Order orders[], int size, float target) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (orders[mid].total_price == target)
            return mid;
        else if (orders[mid].total_price < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1; // 未找到
}

int main() {
    Order orders[MAX_ORDERS];
    float target_price;

    // 读取订单信息
    for (int i = 0; i < MAX_ORDERS; i++) {
        scanf("%s %f %d", orders[i].name, &orders[i].unit_price, &orders[i].quantity);
        orders[i].total_price = orders[i].unit_price * orders[i].quantity;
        // 确保总价精确到小数点后两位
        orders[i].total_price = (int)(orders[i].total_price * 100 + 0.5) / 100.0;
    }

    // 读取目标总价
    scanf("%f", &target_price);

    // 使用冒泡排序对订单按总价进行升序排序
    bubble_sort(orders, MAX_ORDERS);

    // 输出排序后的订单信息
    for (int i = 0; i < MAX_ORDERS; i++) {
        printf("%s %.2f %d %.2f\n", orders[i].name, orders[i].unit_price, orders[i].quantity, orders[i].total_price);
    }

    // 二分查找目标总价
    int index = binary_search(orders, MAX_ORDERS, target_price);

    // 输出结果
    if (index != -1) {
        printf("%s %.2f %d %.2f\n", orders[index].name, orders[index].unit_price, orders[index].quantity, orders[index].total_price);
    } else {
        printf("Not found\n");
    }

    return 0;
}
