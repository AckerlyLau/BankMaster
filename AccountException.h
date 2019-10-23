#ifndef _ACCOUNTEXCEPTION_H_
#define _ACCOUNTEXCEPTION_H_
 #include <stdexcept>
 #include "Account.h"
 using namespace std;
 class AccountException:public runtime_error
 {
    private:
        Account * ErrAccount;
        string ErrMessage;
    public:
        AccountException(string ErrMsg,Account* ErrAcc);
        string getErrMessage();
 };
 #endif