

#include <iostream>

//***********************************************************
template<typename T>
Queue<T>::Queue() : size(0), back(nullptr) {}

//***********************************************************
template<typename T>
Queue<T>::~Queue() {
    if(!isEmpty()) empty();
}

//***********************************************************
template<typename T>
Queue<T>::Queue(const Queue<T> &q) : back(nullptr), size(0) { *this = q; }

//**********************************************************
template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T> &q) {
    if (this == &q) return *this;
    empty();
    if (q.isEmpty())
        return *this;
    
    Element *aux = q.back->next;
    while (aux != q.back) {
        enqueue(aux->value);
        aux = aux->next;
    }
    enqueue(aux->value);
    return *this;
}

//***********************************************************
template<typename T>
void Queue<T>::enqueue(T value) {
    try {
        Element *aux = new Element(value, isEmpty() ? nullptr : back->next);
        (isEmpty() ? aux->next : back->next) = aux;
        back = aux;
        ++size;
    } catch (std::bad_alloc &) {
        throw "Error: It's not possible to push the value in the queue.";
    }
}

//***********************************************************
template<typename T>
void Queue<T>::dequeue() {
    if (!isEmpty()) {
        if (size == 1) {
            delete back;
            back = nullptr;
        } else {
            Element *aux = back->next;
            back->next = back->next->next;
            delete aux;
        }
        --size;
    } else {
        throw EmptyQueue();
    }
}

//***********************************************************
template<typename T>
int Queue<T>::getSize() const { return size; }

//***********************************************************
template<typename T>
T Queue<T>::getFront() const {
    if (isEmpty()) throw "";   
    return back->next->value;
}

//***********************************************************
template <typename T> T Queue<T>::getBack() const {
    if(isEmpty()) throw EmptyQueue();
    return back->value;
}

//***********************************************************
template<typename T>
bool Queue<T>::isEmpty() const { return size == 0; }

//***********************************************************
template<typename T>
void Queue<T>::empty() {
    if(isEmpty()) return;
    Element *aux = back->next;
    while (back->next != back) {
        back->next = back->next->next;
        delete aux;
        aux = back->next;
    }
    delete back;
    back = nullptr;
    size = 0;
}

//***********************************************************
template <typename T> void Queue<T>::Print() const {
    if(isEmpty()) return;
    Element *aux = back->next;
    std::cout << "(";
    for (int i = 0; i < size; ++i) {
        std::cout << aux->value << ", ";
        aux = aux->next;
    }
    std::cout << "\b\b)" << std::endl;
}

//***********************************************************
template<typename T>
Queue<T>::Element::Element(T v, Queue<T>::Element *nxt) : value(v), next(nxt) {}







