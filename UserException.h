#ifndef _USEREXCEPTION_H_
#define _USEREXCEPTION_H_ 
#include <stdexcept>
 #include "User.h"
 using namespace std;
 class UserException:public runtime_error
 {
    private:
        User * ErrAccount;
        string ErrMessage;
    public:
        UserException(string ErrMsg,User* ErrUsr);
        string getErrMessage();
 };
 #endif