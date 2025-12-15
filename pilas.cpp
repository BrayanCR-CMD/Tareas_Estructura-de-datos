#include <iostream>
#define max_size 100

int stack[max_size];
int top = -1;

void push(int value) {
    if (top >= max_size - 1) {
        std::cout << "Stack Overflow" << std::endl;
        return;
    }
    stack[++top] = item;
}

int pop() {
    if (top < 0) {
        std::cout << "Stack Underflow" << std::endl;
        return -1; // Indicate stack is empty
    }
    return stack[top--];
}

int peek() {
    if (top < 0) {
        std::cout << "Stack is empty" << std::endl;
        return -1; // Indicate stack is empty
    }
    return stack[top];
}

bool isEmpty() {
    return top == -1;
}

boll isFull() {
    return top >= max_size - 1;
}
int main() {
    push(10);
    push(20);
    push(30);
    
    std::cout << "Top element is: " << peek() << std::endl;
    
    std::cout << "Popped element is: " << pop() << std::endl;
    
    std::cout << "Is stack empty? " << (isEmpty() ? "Yes" : "No") << std::endl;
    
    return 0;
}
