/**
 * @file Queue.hpp
 * @brief Declaration of the Queue class template.
 *
 * This file contains the declaration of the Queue class template,
 * which implements a basic queue data structure. It supports standard
 * queue operations such as enqueue, dequeue, and inspection of the front
 * and back elements.
 */

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "../EmptyQueue.hpp"

/**
 * @class Queue<T>
 * @brief Template class implementing a queue data structure.
 *
 * This class implements a queue using a linked list. It supports operations
 * to add elements to the back, remove elements from the front, and view
 * the front and back elements without removing them. The class also provides
 * functionality to check the size, check if the queue is empty, empty the
 * queue, and print its contents.
 *
 * @tparam T The data type of the elements stored in the queue.
 */
template<typename T = int>
class Queue {
public:
    /**
     * @brief Default constructor.
     * Initializes an empty queue.
     */
    Queue();

    /**
     * @brief Destructor.
     * Destroys the queue and releases all allocated resources.
     */
    ~Queue();

    /**
     * @brief Copy constructor.
     * Creates a new queue as a copy of an existing queue.
     * 
     * @param q Reference to the queue to be copied.
     */
    Queue(const Queue<T> &q);

    /**
     * @brief Copy assignment operator.
     * Replaces the contents of the queue with a copy of the contents of another queue.
     * 
     * @param q Reference to the queue to be copied.
     * @return Reference to the current queue after copying.
     */
    Queue<T> &operator=(const Queue<T> &q);

    /**
     * @brief Enqueues a new element at the back of the queue.
     * 
     * @param value The value to be enqueued.
     */
    void enqueue(T value);

    /**
     * @brief Dequeues the front element from the queue.
     * Throws EmptyQueue exception if the queue is empty.
     */
    void dequeue();

    /**
     * @brief Gets the current size of the queue.
     * 
     * @return The number of elements in the queue.
     */
    int getSize() const;

    /**
     * @brief Gets the value of the front element of the queue.
     * Throws EmptyQueue exception if the queue is empty.
     * 
     * @return The value of the front element.
     */
    T getFront() const;

    /**
     * @brief Gets the value of the back element of the queue.
     * Throws EmptyQueue exception if the queue is empty.
     * 
     * @return The value of the back element.
     */
    T getBack() const;

    /**
     * @brief Checks if the queue is empty.
     * 
     * @return True if the queue is empty, false otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief Empties the queue, removing all elements.
     */
    void empty();

    /**
     * @brief Prints the contents of the queue to the standard output.
     */
    void Print() const;

private:
    int size; ///< The number of elements in the queue.

    /**
     * @struct Element
     * @brief Represents an element in the queue.
     * 
     * Each element contains a value and a pointer to the next element in the queue.
     */
    struct Element {
        T value; ///< The value of the element.
        Element *next; ///< Pointer to the next element in the queue.

        /**
         * @brief Constructor for Element.
         * Initializes an element with a value and an optional next element pointer.
         * 
         * @param v The value of the element.
         * @param nxt Pointer to the next element, defaults to nullptr.
         */
        Element(T v, Element *nxt = nullptr);
    } *back; ///< Pointer to the last element in the queue.
};

#include "../templates/Queue.tpp"

#endif //QUEUE_HPP
