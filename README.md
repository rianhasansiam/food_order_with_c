# Food Order Management System Using Stack and Queue

## Project Overview
A C-based application that simulates a restaurant's food order management system using fundamental data structures: **Queue (FIFO)** and **Stack (LIFO)**.

## Problem Statement
Design and implement a simple Food Order Management System using Queue and Stack to simulate real-life restaurant order handling. The system manages customer orders efficiently while maintaining order sequence and history.

## Data Structures Used

### Queue (FIFO - First In, First Out)
- **Purpose**: Stores active/pending food orders
- **Structure**: 
  ```c
  struct OrderQueue {
      struct Order orders[MAX_ORDERS];  // Array to store orders
      int front;   // Index of front element
      int rear;    // Index of rear element
      int count;   // Number of elements
  };
  ```
- **Operations**: 
  - Enqueue: Add new orders to the rear
  - Dequeue: Serve orders from the front
- **Implementation**: Circular array-based queue

### Stack (LIFO - Last In, First Out)
- **Purpose**: Stores served/cancelled order history
- **Structure**:
  ```c
  struct OrderStack {
      struct Order orders[MAX_ORDERS];  // Array to store orders
      int top;  // Index of top element
  };
  ```
- **Operations**:
  - Push: Add served orders to the top
  - Pop: Remove last served order
- **Implementation**: Array-based stack

## Features

1. **Place New Order** (Enqueue)
   - Add customer orders to the pending queue
   - Automatically assigns unique order IDs
   - Captures customer name, food item, and price
   - Screen clears after operation for better UI

2. **Serve Next Order** (Dequeue → Push to Stack)
   - Processes orders in FIFO sequence
   - Moves completed orders to history stack
   - Displays served order details

3. **Cancel Last Served Order** (Pop from Stack)
   - Removes most recent served order from history
   - Demonstrates LIFO behavior
   - Shows cancelled order information

4. **Display Pending Orders** (Queue)
   - Shows all orders waiting to be served
   - Maintains insertion order (FIFO)
   - Formatted table display

5. **Display Order History** (Stack)
   - Shows served/cancelled orders
   - Most recent orders appear first (LIFO)
   - Formatted table display

6. **Exit System**
   - Displays final statistics
   - Clean shutdown with clear screen

**UI Enhancement**: Uses `system("cls")` to clear screen between operations for a professional, clean interface.

## Project Structure

```
project/
├── main.c                    # Complete program (all code in one file)
├── food_order_system.exe     # Compiled executable
└── README.md                 # This file
```

## Compilation and Execution

### Compilation
```cmd
gcc -Wall -Wextra -std=c11 -o food_order_system.exe main.c
```

### Run the Program
```cmd
food_order_system.exe
```

## Usage Example

```
1. Place a New Order (Enqueue)
   - Enter customer name: John Doe
   - Enter food item: Burger and Fries
   - Enter price: $12.99

2. Serve Next Order (Dequeue -> Push to History)
   - Serves the oldest pending order
   - Moves it to order history

3. Cancel Last Served Order (Pop from History)
   - Removes most recently served order

4. Display All Pending Orders (Queue)
   - Shows all orders in FIFO order

5. Display Order History (Stack)
   - Shows served orders in LIFO order

6. Exit System
```

## Sample Workflow

1. Place 3 orders: Pizza, Burger, Pasta
2. Queue: [Pizza → Burger → Pasta]
3. Serve Pizza → Stack: [Pizza]
4. Serve Burger → Stack: [Burger, Pizza]
5. Cancel last served (Burger) → Stack: [Pizza]
6. Queue now: [Pasta]

## Key Learning Outcomes

✅ **Queue (FIFO)**: Orders are processed in the sequence they arrive
✅ **Stack (LIFO)**: Last served order is first to be cancelled
✅ **Practical Application**: Real-world restaurant order management
✅ **C Programming**: Structures, functions, file organization
✅ **Menu-Driven Interface**: User-friendly interaction

## Technical Details

- **Language**: C (C11 standard)
- **Maximum Orders**: 100 (configurable via MAX_ORDERS)
- **Queue Implementation**: Circular array with front, rear, and count pointers
- **Stack Implementation**: Array-based with top pointer
- **Error Handling**: Overflow/underflow checks with user-friendly messages
- **Code Structure**: Single file (main.c) with all implementations
- **Syntax**: Uses `struct` declarations (not typedef) and arrow operator (`->`) for pointers

## System Requirements

- GCC compiler (MinGW for Windows)
- Windows OS with cmd.exe
- Make utility (optional)

## Author
Data Structures Lab Project

## Date
December 9, 2025

---

**Note**: This project demonstrates the fundamental difference between Queue (FIFO) and Stack (LIFO) operations in a practical, real-world scenario.
