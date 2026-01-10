MAX_SIZE = 100

stack = [0] * MAX_SIZE
top = -1

def push(value):
    global top
    if top >= MAX_SIZE - 1:
        print("Stack Overflow")
        return
    top += 1
    stack[top] = value

def pop():
    global top
    if top < 0:
        print("Stack Underflow")
        return -1
    value = stack[top]
    top -= 1
    return value

def peek():
    if top < 0:
        print("Stack is empty")
        return -1
    return stack[top]

def is_empty():
    return top == -1

def is_full():
    return top >= MAX_SIZE - 1

# Main
push(10)
push(20)
push(30)

print("Top element is:", peek())
print("Popped element is:", pop())
print("Is stack empty?", "Yes" if is_empty() else "No")
