#include "UserException.h"
#include "User.h"
UserException::UserException(string ErrMsg,User* ErrUsr):runtime_error(ErrMsg)
{
    ErrAccount = ErrUsr;
    ErrMessage = ErrMsg;
}
string UserException::getErrMessage()
{
    return ErrMessage;
}