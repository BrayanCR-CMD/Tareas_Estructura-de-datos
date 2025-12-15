using System;

class StackExample
{
    const int MAX_SIZE = 100;
    static int[] stack = new int[MAX_SIZE];
    static int top = -1;

    static void Push(int value)
    {
        if (top >= MAX_SIZE - 1)
        {
            Console.WriteLine("Stack Overflow");
            return;
        }
        stack[++top] = value;
    }

    static int Pop()
    {
        if (top < 0)
        {
            Console.WriteLine("Stack Underflow");
            return -1;
        }
        return stack[top--];
    }

    static int Peek()
    {
        if (top < 0)
        {
            Console.WriteLine("Stack is empty");
            return -1;
        }
        return stack[top];
    }

    static bool IsEmpty()
    {
        return top == -1;
    }

    static bool IsFull()
    {
        return top >= MAX_SIZE - 1;
    }

    static void Main()
    {
        Push(10);
        Push(20);
        Push(30);

        Console.WriteLine("Top element is: " + Peek());
        Console.WriteLine("Popped element is: " + Pop());
        Console.WriteLine("Is stack empty? " + (IsEmpty() ? "Yes" : "No"));
    }
}
