#lista circular doblemente enlazada en python
class Node:
    def __init__(self, data):
        self.data = data
        self.next = None
        self.prev = None

class CircularDoublyLinkedList:
    def __init__(self):
        self.head = None

    def append(self, data):
        new_node = Node(data)
        if not self.head:
            self.head = new_node
            new_node.next = new_node
            new_node.prev = new_node
        else:
            tail = self.head.prev
            tail.next = new_node
            new_node.prev = tail
            new_node.next = self.head
            self.head.prev = new_node

    def display(self):
        if not self.head:
            print("List is empty")
            return
        current = self.head
        while True:
            print(current.data, end=" <-> ")
            current = current.next
            if current == self.head:
                break
        print("(head)")

    def display_reverse(self):
        if not self.head:
            print("List is empty")
            return
        current = self.head.prev
        while True:
            print(current.data, end=" <-> ")
            current = current.prev
            if current == self.head.prev:
                break
        print("(head)")
    def delete(self, key):
        if not self.head:
            return
        current = self.head
        while True:
            if current.data == key:
                if current.next == current:  # Only one node
                    self.head = None
                else:
                    current.prev.next = current.next
                    current.next.prev = current.prev
                    if current == self.head:  # Deleting head
                        self.head = current.next
                return
            current = current.next
            if current == self.head:
                break

# Ejemplo de uso
if __name__ == "__main__":
    cdll = CircularDoublyLinkedList()
    cdll.append(10)
    cdll.append(20)
    cdll.append(30)
    cdll.display()          # Output: 10 <-> 20 <-> 30 <-> (head)
    cdll.display_reverse()  # Output: 30 <-> 20 <-> 10 <-> (head)
    cdll.delete(20)
    cdll.display()          # Output: 10 <-> 30 <-> (head)
