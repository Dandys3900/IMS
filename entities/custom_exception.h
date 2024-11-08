#ifndef CUST_EXCEPTION_H
#define CUST_EXCEPTION_H

#include "includes.h"

class ProgramException: public exception {
    private:
        const string message;
    public:
        ProgramException(const string& msg)
            : message(msg)
        {
        }

        // Override what() method to return error message
        const char* what() const noexcept {
            return this->message.c_str();
        }
};

#endif // CUST_EXCEPTION_H
