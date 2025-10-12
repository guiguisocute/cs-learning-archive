#include <iostream>
#include <cstdio> // 用于scanf和printf

typedef struct Order {
    char name[50];
    float unitprice;
    int quantity;
    float total;
} Order;

void sum(Order* table) {
    table->total = table->unitprice * table->quantity;
}

void exchange(Order* x, Order* y) {
    Order temp = *x;
    *x = *y;
    *y = temp;
}

void BubbleSort(Order table[]) {
    for (int i = 9; i >= 1; i--) {
        for (int j = 0; j < i; j++) {
            if (table[j].total < table[j + 1].total) { // 修正比较逻辑
                exchange(&table[j], &table[j + 1]);
            }
        }
    }
}

void find(Order table[], float target) {
    int start = 0;
    int end = 9;
    int mid;
    int position = -1;
    while (start <= end) {
        mid = (start + end) / 2;
        if (table[mid].total > target) {
            end = mid - 1;
        } else if (table[mid].total < target) {
            start = mid + 1;
        } else {
            position = mid;
            break;
        }
    }
    if (position == -1) {
        printf("Not Found\n");
    } else {
        printf("%s\t%.2f\t%d\t%.2f\n",
               table[position].name,
               table[position].unitprice,
               table[position].quantity,
               table[position].total);
    }
}

void print(Order table[]) {
    for (int i = 0; i < 10; i++) {
        printf("%s\t%.2f\t%d\t%.2f\n",
               table[i].name,
               table[i].unitprice,
               table[i].quantity,
               table[i].total);
    }
}

int main() {
    Order table[10];

    for (int i = 0; i < 10; i++) {
        scanf("%49s %f %d", table[i].name, &table[i].unitprice, &table[i].quantity);
        sum(&table[i]);
    }

    float target;
    scanf("%f", &target);

    BubbleSort(table);
    print(table);
    find(table, target);

    return 0;
}