#include <stdio.h>
#include <stdlib.h>

#include "Address.h"

#define IP "168.12.0.2"
#define PORT 88

int main(int argv, char** args)
{
    Address address = Address();
    printf("\n  Creato Address vuoto %s", address.toString());

	/*Address()*/
    if(strcmp(address.getIp(), IP_LOOPBACK)==0 && address.getPort()==PORT_ZERO)
    {
        printf("\n  OK Address()");
    }else
    {
        printf("\n  PROBLEM: Address()");
    }

	/*setIp()*/
    address.setIp(IP);

    if(strcmp(address.getIp(), IP)==0)
    {
        printf("\n  OK setIp()");
    }else
    {
        printf("\n  PROBLEM: setIp()");
    }

	/*setPort()*/
    address.setPort(PORT);

    if(address.getPort()==PORT)
    {
        printf("\n  OK setPort()");
    }else
    {
        printf("\n  PROBLEM: setPort()");
    }

    delete(&address);

    Address* maniglia = new Address(IP, PORT);

    char* temp = maniglia->toString();
    printf("\n  Creato nuovo Address: %s", temp);
    free(temp);

	/*Address(ip, port)*/
    if(strcmp(address.getIp(), IP)==0 && address.getPort() == PORT)
    {
        printf("\n  OK Address(ip, port)");
    }else
    {
        printf("\n  PROBLEM: Address(ip, port)");
    }

    struct sockaddr sockaddrObject = maniglia->toSockaddr();

    delete(maniglia);

    Adress addr = Address(sockaddrObject);

    if(strcmp(address.getIp(), IP)==0 && address.getPort() == PORT)
    {
        printf("\n  OK Address(sockaddr)");
    }else
    {
        printf("\n  PROBLEM: Address(sockaddr)");
    }

    system("pause");

    /*Address(sockaddrObject)*/
    struct sockaddr sockaddrObject;

    Address address = Address()

}
