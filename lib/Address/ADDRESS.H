#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define ADDRESS_TO_STRING_LEN 25
#define IP_LOOPBACK "127.0.0.1"
#define PORT_ZERO 0

class Address
{
    private:    char* ip;
                int port;

    public:     Address(const char* ip, const int port);
                Address();
                Address(const Address& address);
                Address(struct sockaddr sockaddrObject);
                ~Address();
                char* getIp();
                int getPort();
                void setIp(const char* ip);
                void setPort(const int port);
                char* toString();
                struct sockaddr toSockaddr();
};

Address::Address(const char* ip, const int port)
{
    this->ip = strdup(ip);
    this->port = port;
}

Address::Address()
{
    this->ip = strdup(IP_LOOPBACK);
    this->port = PORT_ZERO;
}

Address::Address(const Address& address)
{
    this->ip = strdup(address.ip);
    this->port = address.port;
}

Address::Address(struct sockaddr sockaddrObject)
{
	this->port = ntohs(sockaddrObject.sin_port);

	char* temp = inet_ntoa(sockaddrObject.sin_addr); 	//ottengo il puntatore alla stringa dove è scritto l'indirizzo ip del sockaddr (allocata dinamicamente)
	this->ip = strdup(temp);	//duplico la stringa e la alloco dinamicamente per salvarla all'interno dell'oggetto corrente
	free(temp);
}

Address::~Address()
{
    printf("\n  Distruttore di %s\n", this->toString());
    free(this->ip);
}

char* Address::getIp()
{
    return strdup(this->ip);
}

int Address::getPort()
{
    return this->port;
}

void Address::setIp(const char* ip)
{
    this->ip = strdup(ip);
}

void Address::setPort(const int port)
{
    this->port = port;
}

char* Address::toString()
{
    char temp[ADDRESS_TO_STRING_LEN];
    sprintf(temp, "[%s:%d]", this->ip, this->port);
    return strdup(temp);
}

struct sockaddr Address::toSockaddr()
{
	struct sockaddr ret* = (sockaddr*) malloc(sizeof(sockaddr));
	ret->sin_family = AF_INET;

	//riempo il campo sin_zero con zeri insignificanti
	int i;
	for(i=0; i<8; i++)
	{
		ret->sin_zero[i] = 0;
	}

	ret->sin_port = htons(this->port);
	ret->sin_ip = inet_aton(this->ip);

	return ret;
}



#endif // ADDRESS_INCLUDED
