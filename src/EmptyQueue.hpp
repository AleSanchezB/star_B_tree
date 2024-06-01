/**
 * @file EmptyQueue.hpp
 * @brief Declaration of the EmptyQueue exception class.
 *
 * This file contains the declaration of the EmptyQueue exception class,
 * which is designed to be thrown when queue operations are attempted on an
 * empty queue. This exception class inherits from the standard exception class.
 */

#ifndef EMPTYQUEUE_HPP
#define EMPTYQUEUE_HPP

#include <exception>

/**
 * @class EmptyQueue
 * @brief Exception class for empty queue errors.
 *
 * This class represents an exception that is thrown when an operation that
 * cannot be performed on an empty queue is attempted, such as dequeuing from
 * an empty queue. It provides a custom error message indicating that the queue
 * is empty.
 */
class EmptyQueue : public std::exception {
public:
    /**
     * @brief Retrieves the error message associated with the exception.
     *
     * Overrides the `what` method from the std::exception class to provide
     * a custom error message indicating that the queue is empty.
     *
     * @return A constant C-string with the error message.
     * @exception No-throw guarantee. This function is guaranteed not to throw any exceptions.
     */
    virtual const char *what() throw();
};

#endif // EMPTYQUEUE_HPP
