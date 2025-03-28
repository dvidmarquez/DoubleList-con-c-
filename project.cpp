#include <iostream>
using namespace std;


template <typename T>
class Node {
private:
    T data;             
    Node<T>* next;      
    Node<T>* prev;     

public:
      Node(T val) : data(val), next(nullptr), prev(nullptr) {}

    
    T getData() const {
        return data;
    }
    Node<T>* getNext() const {
        return next;
    }
    Node<T>* getPrev() const {
        return prev;
    }

    
    void setData(T val) {
        data = val;
    }
    void setNext(Node<T>* n) {
        next = n;
    }
    void setPrev(Node<T>* p) {
        prev = p;
    }
};

// Clase genérica para la lista doblemente enlazada
template <typename T>
class DoubleList {
private:
    Node<T>* head;  
    Node<T>* tail;  

public:
    
    DoubleList() : head(nullptr), tail(nullptr) {}

    bool isEmpty() {
        return head == nullptr;
    }

 
    void push(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            tail->setNext(newNode);
            newNode->setPrev(tail);
            tail = newNode;
        }
    }

   
    void remove(T val) {
        if (isEmpty())
            return;

        Node<T>* current = head;
        while (current != nullptr) {
            if (current->getData() == val) {
              
                if (current == head) {
                    head = head->getNext();
                    if (head != nullptr)
                        head->setPrev(nullptr);
                }
                
                else if (current == tail) {
                    tail = tail->getPrev();
                    if (tail != nullptr)
                        tail->setNext(nullptr);
                }
                
                else {
                    current->getPrev()->setNext(current->getNext());
                    current->getNext()->setPrev(current->getPrev());
                }
                delete current;
                return;
            }
            current = current->getNext();
        }
    }

    
    T pull() {
        if (isEmpty()) {
            cout << "La lista está vacía. No hay elementos para extraer.\n";
            return T(); 
        }

        T val = tail->getData();
    
        if (head == tail) {
            delete tail;
            head = tail = nullptr;
        } else {
            Node<T>* temp = tail;
            tail = tail->getPrev();
            tail->setNext(nullptr);
            delete temp;
        }
        return val;
    }

sta
    void display() {
        if (isEmpty()) {
            cout << "La lista está vacía.\n";
            return;
        }
        Node<T>* temp = head;
        while (temp != nullptr) {
            cout << temp->getData() << " <-> ";
            temp = temp->getNext();
        }
        cout << "NULL\n";
    }

  
    ~DoubleList() {
        while (!isEmpty()) {
            pull();
        }
    }

int main() {

    DoubleList<int> list;

  
    list.push(10);
    list.push(20);
    list.push(30);
    list.push(40);

    cout << "Lista después de inserciones: ";
    list.display();

    cout << "Elemento extraído con pull: " << list.pull() << endl;
    cout << "Lista después de pull: ";
    list.display();

   
    list.remove(20);
    cout << "Lista después de eliminar 20: ";
    list.display();

    cout << "¿La lista está vacía? " << (list.isEmpty() ? "Sí" : "No") << endl;

    return 0;
}
