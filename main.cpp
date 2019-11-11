#include "System.h"
int main() 
{
	System *os = new System();
	os -> Start();
	delete os;
}
