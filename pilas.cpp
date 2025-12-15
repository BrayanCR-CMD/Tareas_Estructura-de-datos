public class StackExample {
    static final int MAX_SIZE = 100;
    static int[] stack = new int[MAX_SIZE];
    static int top = -1;

    static void push(int value) {
        if (top >= MAX_SIZE - 1) {
            System.out.println("Stack Overflow");
            return;
        }
        stack[++top] = value;
    }

    static int pop() {
        if (top < 0) {
            System.out.println("Stack Underflow");
            return -1;
        }
        return stack[top--];
    }

    static int peek() {
        if (top < 0) {
            System.out.println("Stack is empty");
            return -1;
        }
        return stack[top];
    }

    static boolean isEmpty() {
        return top == -1;
    }

    static boolean isFull() {
        return top >= MAX_SIZE - 1;
    }

    public static void main(String[] args) {
        push(10);
        push(20);
        push(30);

        System.out.println("Top element is: " + peek());
        System.out.println("Popped element is: " + pop());
        System.out.println("Is stack empty? " + (isEmpty() ? "Yes" : "No"));
    }
}
