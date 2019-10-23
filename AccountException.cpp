#include "AccountException.h"
#include "Account.h"
AccountException::AccountException(string ErrMsg,Account* ErrAcc):runtime_error(ErrMsg)
{
    ErrAccount = ErrAcc;
    ErrMessage = ErrMsg;
}
string AccountException::getErrMessage()
{
    return ErrMessage;
}