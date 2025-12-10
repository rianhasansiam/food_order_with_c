#include <stdio.h>
#include <stdlib.h>

#define MAX_ORDERS 100
#define MAX_NAME_LENGTH 50
#define MAX_ITEM_LENGTH 100


struct Order {
    int orderId;
    char customerName[MAX_NAME_LENGTH];
    char foodItem[MAX_ITEM_LENGTH];
    float price;
};


struct OrderQueue {
    struct Order orders[MAX_ORDERS];
    int front;
    int rear;
    int count;
};


struct OrderStack {
    struct Order orders[MAX_ORDERS];
    int top;
};



void initQueue(struct OrderQueue* queue) {
    queue->front = -1;
    queue->rear = -1;
    queue->count = 0;
}


int isQueueEmpty(struct OrderQueue* queue) {
    return (queue->count == 0);
}


int isQueueFull(struct OrderQueue* queue) {
    return (queue->rear == MAX_ORDERS - 1);
}




int enqueue(struct OrderQueue* queue, struct Order order) {
    if (isQueueFull(queue)) {
        printf("\n\n");
        printf("    +============================================================+\n");
        printf("    |                                                            |\n");
        printf("    |   ERROR: Queue is full! Cannot accept more orders          |\n");
        printf("    |                                                            |\n");
        printf("    +============================================================+\n");
        return 0;
    }
    
    if (queue->front == -1) {
        queue->front = 0;
    }
    
    queue->rear++;
    queue->orders[queue->rear] = order;
    queue->count++;
    
    printf("\n\n");
    printf("    +============================================================+\n");
    printf("    |                                                            |\n");
    printf("    |   SUCCESS: Order #%-3d placed successfully!              |\n", order.orderId);
    printf("    |                                                            |\n");
    printf("    +------------------------------------------------------------+\n");
    printf("    |   Customer:  %-45s |\n", order.customerName);
    printf("    |   Item:      %-45s |\n", order.foodItem);
    printf("    |   Price:     $%-44.2f |\n", order.price);
    printf("    +============================================================+\n");
    
    return 1;
}


struct Order dequeue(struct OrderQueue* queue) {
    struct Order emptyOrder = {-1, "", "", 0.0};
    if (isQueueEmpty(queue)) {
        printf("\n\n");
        printf("    +============================================================+\n");
        printf("    |                                                            |\n");
        printf("    |   ERROR: No pending orders to serve!                       |\n");
        printf("    |                                                            |\n");
        printf("    +============================================================+\n");
        return emptyOrder;
    }
    
    struct Order order = queue->orders[queue->front];
    queue->front++;
    queue->count--;
    
    if (queue->count == 0) {
        queue->front = -1;
        queue->rear = -1;
    }
    
    return order;
}


void displayPendingOrders(struct OrderQueue* queue) {
    if (isQueueEmpty(queue)) {
        printf("\n\n");
        printf("    +============================================================+\n");
        printf("    |                                                            |\n");
        printf("    |        INFO: No pending orders in the queue                |\n");
        printf("    |                                                            |\n");
        printf("    +============================================================+\n");
        return;
    }
    
    printf("\n\n");
    printf("    +======================================================================+\n");
    printf("    ||                                                                    ||\n");
    printf("    ||                  PENDING ORDERS (Queue)                           ||\n");
    printf("    ||                                                                    ||\n");
    printf("    +======================================================================+\n");
    printf("    | %-10s | %-20s | %-28s | %-10s |\n", "Order ID", "Customer Name", "Food Item", "Price");
    printf("    +------------+----------------------+------------------------------+------------+\n");
    
    for (int i = queue->front; i <= queue->rear; i++) {
        struct Order order = queue->orders[i];
        printf("    | %-10d | %-20s | %-28s | $%-9.2f |\n", 
               order.orderId, order.customerName, order.foodItem, order.price);
    }
    
    printf("    +------------+----------------------+------------------------------+------------+\n");
    printf("    ||  Total Pending Orders: %-44d ||\n", queue->count);
    printf("    +======================================================================+\n");
}




void initStack(struct OrderStack* stack) {
    stack->top = -1;
}


int isStackEmpty(struct OrderStack* stack) {
    return (stack->top == -1);
}


int isStackFull(struct OrderStack* stack) {
    return (stack->top == MAX_ORDERS - 1);
}


int push(struct OrderStack* stack, struct Order order) {
    if (isStackFull(stack)) {
        printf("\n[ERROR] Order history is full!\n");
        return 0;
    }
    
    stack->top++;
    stack->orders[stack->top] = order;
    
    return 1;
}


void pop(struct OrderStack* stack) {
    if (isStackEmpty(stack)) {
        printf("\n\n");
        printf("    +============================================================+\n");
        printf("    |                                                            |\n");
        printf("    |   ERROR: No order history available!                       |\n");
        printf("    |                                                            |\n");
        printf("    +============================================================+\n");
        return;
    }
    
    struct Order order = stack->orders[stack->top];
    stack->top--;
    
    printf("\n\n");
    printf("    +============================================================+\n");
    printf("    |                                                            |\n");
    printf("    |   Last served order has been cancelled!                    |\n");
    printf("    |                                                            |\n");
    printf("    +------------------------------------------------------------+\n");
    printf("    |   Order ID:   %-44d |\n", order.orderId);
    printf("    |   Customer:   %-44s |\n", order.customerName);
    printf("    |   Food Item:  %-44s |\n", order.foodItem);
    printf("    |   Price:      $%-43.2f |\n", order.price);
    printf("    +------------------------------------------------------------+\n");
    printf("    |   Note: Order removed from history                         |\n");
    printf("    +============================================================+\n");
}


void displayOrderHistory(struct OrderStack* stack) {
    if (isStackEmpty(stack)) {
        printf("\n\n");
        printf("    +============================================================+\n");
        printf("    |                                                            |\n");
        printf("    |        INFO: No order history available                    |\n");
        printf("    |                                                            |\n");
        printf("    +============================================================+\n");
        return;
    }
    
    printf("\n\n");
    printf("    +======================================================================+\n");
    printf("    ||                                                                    ||\n");
    printf("    ||            ORDER HISTORY (Stack - Most Recent First)              ||\n");
    printf("    ||                                                                    ||\n");
    printf("    +======================================================================+\n");
    printf("    | %-10s | %-20s | %-28s | %-10s |\n", "Order ID", "Customer Name", "Food Item", "Price");
    printf("    +------------+----------------------+------------------------------+------------+\n");
    
    for (int i = stack->top; i >= 0; i--) {
        struct Order order = stack->orders[i];
        printf("    | %-10d | %-20s | %-28s | $%-9.2f |\n", 
               order.orderId, order.customerName, order.foodItem, order.price);
    }
    
    printf("    +------------+----------------------+------------------------------+------------+\n");
    printf("    ||  Total Orders in History: %-41d ||\n", stack->top + 1);
    printf("    +======================================================================+\n");
}



void displayOrder(struct Order order) {
    printf("Order ID: %d\n", order.orderId);
    printf("Customer: %s\n", order.customerName);
    printf("Food Item: %s\n", order.foodItem);
    printf("Price: $%.2f\n", order.price);
}



int createOrder(struct OrderQueue* queue, int* nextOrderId) {
    char customerName[MAX_NAME_LENGTH];
    char foodItem[MAX_ITEM_LENGTH];
    float price;
    int i;
    
    printf("\n\n");
    printf("    +============================================================+\n");
    printf("    |                                                            |\n");
    printf("    |                   PLACE NEW ORDER                          |\n");
    printf("    |                                                            |\n");
    printf("    +============================================================+\n");
    printf("\n    >> Enter customer name: ");
    fgets(customerName, MAX_NAME_LENGTH, stdin);
    for (i = 0; i < MAX_NAME_LENGTH; i++) {
        if (customerName[i] == '\n') {
            customerName[i] = '\0';
            break;
        }
    }
    
    printf("    >> Enter food item: ");
    fgets(foodItem, MAX_ITEM_LENGTH, stdin);
    for (i = 0; i < MAX_ITEM_LENGTH; i++) {
        if (foodItem[i] == '\n') {
            foodItem[i] = '\0';
            break;
        }
    }
    
    printf("    >> Enter price: $");
    if (scanf("%f", &price) != 1 || price < 0) {
        printf("\n\n");
        printf("    +============================================================+\n");
        printf("    |                                                            |\n");
        printf("    |   ERROR: Invalid price!                                    |\n");
        printf("    |                                                            |\n");
        printf("    +============================================================+\n");
        while (getchar() != '\n');
        return 0;
    }
    getchar();
    
    struct Order newOrder;
    newOrder.orderId = *nextOrderId;
    
    for (i = 0; i < MAX_NAME_LENGTH - 1 && customerName[i] != '\0'; i++) {
        newOrder.customerName[i] = customerName[i];
    }
    newOrder.customerName[i] = '\0';
    
    for (i = 0; i < MAX_ITEM_LENGTH - 1 && foodItem[i] != '\0'; i++) {
        newOrder.foodItem[i] = foodItem[i];
    }
    newOrder.foodItem[i] = '\0';
    
    newOrder.price = price;
    
    if (enqueue(queue, newOrder)) {
        (*nextOrderId)++;
        return 1;
    }
    return 0;
}




int main() {
    struct OrderQueue pendingOrders;
    struct OrderStack orderHistory;
    
    initQueue(&pendingOrders);
    initStack(&orderHistory);
    
    int choice;
    int nextOrderId = 1;
    
    while (1) {
        system("cls");


        printf("\n");
        printf("    ================================================================\n");
        printf("    ||                                                            ||\n");
        printf("    ||            FOOD ORDER MANAGEMENT SYSTEM                   ||\n");
        printf("    ||                Queue (FIFO) & Stack (LIFO)                ||\n");
        printf("    ||                                                            ||\n");
        printf("    ================================================================\n");
        printf("\n");
        printf("    +=============================+  +=============================+\n");
        printf("    |  [1]  Place a New Order     |  |  [2]  Serve Next Order      |\n");
        printf("    +=============================+  +=============================+\n");
        printf("\n");
        printf("    +=============================+  +=============================+\n");
        printf("    |  [3]  Cancel Last Served    |  |  [4]  View Pending Orders   |\n");
        printf("    +=============================+  +=============================+\n");
        printf("\n");
        printf("    +=============================+  +=============================+\n");
        printf("    |  [5]  View Order History    |  |  [6]  Exit System           |\n");
        printf("    +=============================+  +=============================+\n");
        printf("\n");
        printf("    >> Enter your choice (1-6): ");


        
        if (scanf("%d", &choice) != 1) {
            printf("\n\n");
            printf("    +============================================================+\n");
            printf("    |                                                            |\n");
            printf("    |   ERROR: Invalid input! Please enter a number              |\n");
            printf("    |                                                            |\n");
            printf("    +============================================================+\n");
            while (getchar() != '\n');
            printf("\n    >> Press Enter to continue...");
            getchar();
            continue;
        }
        getchar();
        
        switch (choice) {
            case 1: {
                createOrder(&pendingOrders, &nextOrderId);
                printf("\n    >> Press Enter to continue...");
                getchar();
                break;
            }
            
            case 2: {
                printf("\n\n");
                printf("    +============================================================+\n");
                printf("    |                                                            |\n");
                printf("    |                  SERVE NEXT ORDER                          |\n");
                printf("    |                                                            |\n");
                printf("    +============================================================+\n");
                struct Order servedOrder = dequeue(&pendingOrders);
                
                if (servedOrder.orderId != -1) {
                    push(&orderHistory, servedOrder);
                    printf("\n\n");
                    printf("    +============================================================+\n");
                    printf("    |                                                            |\n");
                    printf("    |   Order #%-3d has been served successfully!              |\n", servedOrder.orderId);
                    printf("    |                                                            |\n");
                    printf("    +------------------------------------------------------------+\n");
                    printf("    |   Customer:  %-45s |\n", servedOrder.customerName);
                    printf("    |   Item:      %-45s |\n", servedOrder.foodItem);
                    printf("    |   Price:     $%-44.2f |\n", servedOrder.price);
                    printf("    +============================================================+\n");
                }
                printf("\n    >> Press Enter to continue...");
                getchar();
                break;
            }
            
            case 3: { 
                printf("\n\n");
                printf("    +============================================================+\n");
                printf("    |                                                            |\n");
                printf("    |              CANCEL LAST SERVED ORDER                      |\n");
                printf("    |                                                            |\n");
                printf("    +============================================================+\n");
                pop(&orderHistory);
                printf("\n    >> Press Enter to continue...");
                getchar();
                break;
            }
            
            case 4: { 
                displayPendingOrders(&pendingOrders);
                printf("\n    >> Press Enter to continue...");
                getchar();
                break;
            }
            
            case 5: { 
                displayOrderHistory(&orderHistory);
                printf("\n    >> Press Enter to continue...");
                getchar();
                break;
            }
            
            case 6: { 
                system("cls");
                printf("\n\n");
                printf("    ============================================================\n");
                printf("    ||                                                        ||\n");
                printf("    ||                                                        ||\n");
                printf("    ||        THANK YOU FOR USING OUR SYSTEM!                ||\n");
                printf("    ||                                                        ||\n");
                printf("    ||         Food Order Management System                  ||\n");
                printf("    ||                                                        ||\n");
                printf("    ||                                                        ||\n");
                printf("    ============================================================\n");
                printf("    ||                 System Statistics                     ||\n");
                printf("    ============================================================\n");
                printf("    ||                                                        ||\n");
                printf("    ||    Pending Orders:       %-26d    ||\n", pendingOrders.count);
                printf("    ||    Orders in History:    %-26d    ||\n", orderHistory.top + 1);
                printf("    ||                                                        ||\n");
                printf("    ============================================================\n");
                printf("    ||                                                        ||\n");
                printf("    ||              Goodbye! See you soon!                   ||\n");
                printf("    ||                                                        ||\n");
                printf("    ============================================================\n");
                printf("\n\n");
                return 0;
            }
            
            default:
                printf("\n\n");
                printf("    +============================================================+\n");
                printf("    |                                                            |\n");
                printf("    |   ERROR: Invalid choice! Please select 1-6                 |\n");
                printf("    |                                                            |\n");
                printf("    +============================================================+\n");
                printf("\n    >> Press Enter to continue...");
                getchar();
                break;
        }
    }
    
    return 0;
}
