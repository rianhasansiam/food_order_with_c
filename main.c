#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ORDERS 100
#define MAX_NAME_LENGTH 50
#define MAX_ITEM_LENGTH 100

// Order structure
struct Order {
    int orderId;
    char customerName[MAX_NAME_LENGTH];
    char foodItem[MAX_ITEM_LENGTH];
    float price;
};

// Queue structure for pending orders (Array-based)
struct OrderQueue {
    struct Order orders[MAX_ORDERS];  // Array to store orders
    int front;
    int rear;
    int count;
};

// Stack structure for order history (Array-based)
struct OrderStack {
    struct Order orders[MAX_ORDERS];  // Array to store orders
    int top;
};

// ==================== QUEUE OPERATIONS (FIFO) ====================

// Initialize the queue
void initQueue(struct OrderQueue* queue) {
    queue->front = 0;
    queue->rear = -1;
    queue->count = 0;
}

// Check if queue is empty
int isQueueEmpty(struct OrderQueue* queue) {
    return (queue->count == 0);
}

// Check if queue is full
int isQueueFull(struct OrderQueue* queue) {
    return (queue->count == MAX_ORDERS);
}

// Add order to queue (Enqueue operation)
int enqueue(struct OrderQueue* queue, struct Order order) {
    if (isQueueFull(queue)) {
        printf("\n[ERROR] Queue is full! Cannot accept more orders.\n");
        return 0;
    }
    
    queue->rear = (queue->rear + 1) % MAX_ORDERS;
    queue->orders[queue->rear] = order;
    queue->count++;
    
    printf("\n[SUCCESS] Order #%d placed successfully!\n", order.orderId);
    printf("Customer: %s | Item: %s | Price: $%.2f\n", 
           order.customerName, order.foodItem, order.price);
    
    return 1;
}

// Remove order from queue (Dequeue operation)
struct Order dequeue(struct OrderQueue* queue) {
    struct Order emptyOrder = {-1, "", "", 0.0};
    
    if (isQueueEmpty(queue)) {
        printf("\n[ERROR] No pending orders to serve!\n");
        return emptyOrder;
    }
    
    struct Order order = queue->orders[queue->front];
    queue->front = (queue->front + 1) % MAX_ORDERS;
    queue->count--;
    
    return order;
}

// Display all pending orders in the queue
void displayPendingOrders(struct OrderQueue* queue) {
    if (isQueueEmpty(queue)) {
        printf("\n[INFO] No pending orders in the queue.\n");
        return;
    }
    
    printf("\n========== PENDING ORDERS (Queue) ==========\n");
    printf("%-10s %-20s %-30s %-10s\n", "Order ID", "Customer Name", "Food Item", "Price");
    printf("------------------------------------------------------------\n");
    
    int index = queue->front;
    for (int i = 0; i < queue->count; i++) {
        struct Order order = queue->orders[index];
        printf("%-10d %-20s %-30s $%-9.2f\n", 
               order.orderId, order.customerName, order.foodItem, order.price);
        index = (index + 1) % MAX_ORDERS;
    }
    
    printf("============================================\n");
    printf("Total Pending Orders: %d\n", queue->count);
}

// ==================== STACK OPERATIONS (LIFO) ====================

// Initialize the stack
void initStack(struct OrderStack* stack) {
    stack->top = -1;
}

// Check if stack is empty
int isStackEmpty(struct OrderStack* stack) {
    return (stack->top == -1);
}

// Check if stack is full
int isStackFull(struct OrderStack* stack) {
    return (stack->top == MAX_ORDERS - 1);
}

// Push order to stack (for served/cancelled orders)
int push(struct OrderStack* stack, struct Order order) {
    if (isStackFull(stack)) {
        printf("\n[ERROR] Order history is full!\n");
        return 0;
    }
    
    stack->top++;
    stack->orders[stack->top] = order;
    
    return 1;
}

// Pop order from stack (to view/cancel last served order)
struct Order pop(struct OrderStack* stack) {
    struct Order emptyOrder = {-1, "", "", 0.0};
    
    if (isStackEmpty(stack)) {
        printf("\n[ERROR] No order history available!\n");
        return emptyOrder;
    }
    
    struct Order order = stack->orders[stack->top];
    stack->top--;
    
    return order;
}

// Display order history (served/cancelled orders)
void displayOrderHistory(struct OrderStack* stack) {
    if (isStackEmpty(stack)) {
        printf("\n[INFO] No order history available.\n");
        return;
    }
    
    printf("\n========== ORDER HISTORY (Stack - Most Recent First) ==========\n");
    printf("%-10s %-20s %-30s %-10s\n", "Order ID", "Customer Name", "Food Item", "Price");
    printf("----------------------------------------------------------------\n");
    
    for (int i = stack->top; i >= 0; i--) {
        struct Order order = stack->orders[i];
        printf("%-10d %-20s %-30s $%-9.2f\n", 
               order.orderId, order.customerName, order.foodItem, order.price);
    }
    
    printf("================================================================\n");
    printf("Total Orders in History: %d\n", stack->top + 1);
}

// ==================== UTILITY FUNCTIONS ====================

// Utility function to display a single order
void displayOrder(struct Order order) {
    printf("Order ID: %d\n", order.orderId);
    printf("Customer: %s\n", order.customerName);
    printf("Food Item: %s\n", order.foodItem);
    printf("Price: $%.2f\n", order.price);
}

// Utility function to create an order
struct Order createOrder(int orderId, const char* customerName, const char* foodItem, float price) {
    struct Order order;
    order.orderId = orderId;
    strncpy(order.customerName, customerName, MAX_NAME_LENGTH - 1);
    order.customerName[MAX_NAME_LENGTH - 1] = '\0';
    strncpy(order.foodItem, foodItem, MAX_ITEM_LENGTH - 1);
    order.foodItem[MAX_ITEM_LENGTH - 1] = '\0';
    order.price = price;
    return order;
}

void displayMenu() {
    printf("\n");
    printf("*********************************************************\n");
    printf("*      FOOD ORDER MANAGEMENT SYSTEM                    *\n");
    printf("*      Using Queue (FIFO) and Stack (LIFO)             *\n");
    printf("*********************************************************\n");
    printf("\n");
    printf("1. Place a New Order (Enqueue)\n");
    printf("2. Serve Next Order (Dequeue -> Push to History)\n");
    printf("3. Cancel Last Served Order (Pop from History)\n");
    printf("4. Display All Pending Orders (Queue)\n");
    printf("5. Display Order History (Stack)\n");
    printf("6. Exit System\n");
    printf("\n");
    printf("Enter your choice: ");
}

int main() {
    struct OrderQueue pendingOrders;
    struct OrderStack orderHistory;
    
    initQueue(&pendingOrders);
    initStack(&orderHistory);
    
    int choice;
    int nextOrderId = 1;
    
    printf("\n");
    printf("========================================================\n");
    printf("    Welcome to Food Order Management System!           \n");
    printf("========================================================\n");
    
    while (1) {
        system("cls");
        displayMenu();
        
        if (scanf("%d", &choice) != 1) {
            printf("\n[ERROR] Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            printf("Press Enter to continue...");
            getchar();
            continue;
        }
        getchar(); // Consume newline
        
        switch (choice) {
            case 1: { // Place a new order
                char customerName[MAX_NAME_LENGTH];
                char foodItem[MAX_ITEM_LENGTH];
                float price;
                
                printf("\n--- Place New Order ---\n");
                printf("Enter customer name: ");
                fgets(customerName, MAX_NAME_LENGTH, stdin);
                customerName[strcspn(customerName, "\n")] = '\0'; // Remove newline
                
                printf("Enter food item: ");
                fgets(foodItem, MAX_ITEM_LENGTH, stdin);
                foodItem[strcspn(foodItem, "\n")] = '\0'; // Remove newline
                
                printf("Enter price: $");
                if (scanf("%f", &price) != 1 || price < 0) {
                    printf("\n[ERROR] Invalid price!\n");
                    while (getchar() != '\n'); // Clear input buffer
                    break;
                }
                getchar(); // Consume newline
                
                struct Order newOrder = createOrder(nextOrderId, customerName, foodItem, price);
                if (enqueue(&pendingOrders, newOrder)) {
                    nextOrderId++;
                }
                printf("\nPress Enter to continue...");
                getchar();
                break;
            }
            
            case 2: { // Serve next order
                printf("\n--- Serve Next Order ---\n");
                struct Order servedOrder = dequeue(&pendingOrders);
                
                if (servedOrder.orderId != -1) {
                    push(&orderHistory, servedOrder);
                    printf("\n[SUCCESS] Order #%d has been served!\n", servedOrder.orderId);
                    printf("Customer: %s | Item: %s | Price: $%.2f\n", 
                           servedOrder.customerName, servedOrder.foodItem, servedOrder.price);
                }
                printf("\nPress Enter to continue...");
                getchar();
                break;
            }
            
            case 3: { // Cancel last served order
                printf("\n--- Cancel Last Served Order ---\n");
                struct Order cancelledOrder = pop(&orderHistory);
                
                if (cancelledOrder.orderId != -1) {
                    printf("\n[SUCCESS] Last served order has been cancelled!\n");
                    printf("Order ID: %d\n", cancelledOrder.orderId);
                    printf("Customer: %s\n", cancelledOrder.customerName);
                    printf("Food Item: %s\n", cancelledOrder.foodItem);
                    printf("Price: $%.2f\n", cancelledOrder.price);
                    printf("\nNote: Order removed from history.\n");
                }
                printf("\nPress Enter to continue...");
                getchar();
                break;
            }
            
            case 4: { // Display pending orders
                displayPendingOrders(&pendingOrders);
                printf("\nPress Enter to continue...");
                getchar();
                break;
            }
            
            case 5: { // Display order history
                displayOrderHistory(&orderHistory);
                printf("\nPress Enter to continue...");
                getchar();
                break;
            }
            
            case 6: { // Exit
                system("cls");
                printf("\n========================================================\n");
                printf("    Thank you for using Food Order Management System!  \n");
                printf("========================================================\n");
                printf("\nSystem Statistics:\n");
                printf("  - Pending Orders: %d\n", pendingOrders.count);
                printf("  - Orders in History: %d\n", orderHistory.top + 1);
                printf("\nGoodbye!\n\n");
                return 0;
            }
            
            default:
                printf("\n[ERROR] Invalid choice! Please select 1-6.\n");
                printf("\nPress Enter to continue...");
                getchar();
                break;
        }
    }
    
    return 0;
}
