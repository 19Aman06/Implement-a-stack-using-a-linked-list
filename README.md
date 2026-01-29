# Implement-a-stack-using-a-linked-list

A stack implementation in C using a linked list to store sensor error codes.  
- Maximum stack size: 32 nodes  
- Supports push and pop operations  
- On overflow, the oldest entry is overwritten (circular behavior)  

## Features
- Implemented using linked list (no arrays, no recursion)
- Maximum size: 32 nodes
- Push operation (adds new sensor error code)
- Pop operation (removes most recent error code)
- Overflow handling: oldest entry is removed automatically
- Clean memory management (freeing nodes)

## Requirements
- C compiler (e.g., GCC)
- Basic knowledge of C programming

##Complie
gcc code.c -o code
./code

##Output
--- Pushing 35 sensor codes (Max size is 32) ---
--- Current Stack State (Top to Bottom) ---
132 -> 131 -> 130 -> ... -> 103 -> NULL (Bottom)

--- Popping 5 items ---
Popped: 134
Popped: 133
Popped: 132
Popped: 131
Popped: 130

--- Final Stack State ---
129 -> 128 -> ... -> 103 -> NULL (Bottom)

