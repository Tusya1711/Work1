#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <locale.h>
#include <stdio.h>
#include <iostream>
#include <ostream>
#include <conio.h>
#include <math.h>
#include <windows.h>
#include <cstring>
#include <chrono>
#include <string.h>

SOCKET Connect; 
SOCKET * Connections; 
SOCKET Listen; 

int ClientCount=0;
char s1[15];
char str3[]="MW>5";
int rez=0;

unsigned int Hash37(char str)
{
	int hash = (int)(str);
	return hash;
}

char str2[]=")@1*";
unsigned int toHash37(int str)
{
	char hash = (char)(str);
	return hash;
}

unsigned int function(int p)
{
	int o=(sin(p)/cos(p)+4*p*p)/1000+32-(sin(p)*cos(p)+4*cos(p)*5)*0;
	return o;
}

char str4[]=":SY,";
void SendMessageToClient(int ID)
{

	char*buffer=new char[1024];
	for(;;Sleep(75))
	{
		memset(buffer,0,sizeof(buffer)); 
		if (recv(Connections[ID],buffer,1024,NULL)) 
		{
			printf(buffer); 
			printf("\n");
			for (int i=0; i<=ClientCount; i++) 
			{
				send(Connections[i],buffer,strlen(buffer),NULL); 
			}
		}
	}
	delete buffer;
}

int main()
{
	auto begin = std::chrono::steady_clock::now(); //начало таймера
	
	char str1[]="+H<K";
	setlocale(LC_ALL, "russian"); 
	printf("Введите пароль: ");
	scanf("%s1", &s1);
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	std::cout << "Время: " << elapsed_ms.count()/1000 << " s\n";
	if (elapsed_ms.count()/1000 >= 25)
	{
		std::cout << "Время истекло";
		return 0;
	}

	for (int i=0; i<=sizeof(s1); i++)
	{
		int p=Hash37(s1[i]);
		int o=function(p);
		char w1=toHash37(o);
		if (i<=3)
		{
			int j=i%3;
			if (str3[j]==w1 || str3[3]==w1)
				rez=rez+1;
		}
		if(i>3 && i<=7)
		{
			int j=i%4;;
			if (str4[j]==w1 || str4[3]==w1)
				rez=rez+1;

		}
		if(i>7 && i<=11)
		{
			int j=i%8;
			if (str2[j]==w1 || str2[3]==w1)
				rez=rez+1;

		}
		if(i>11 && i<=15 || str1[3]==w1)
		{
			int j=i%12;
			if (str1[j]==w1)
				rez=rez+1;
		}
	}


	if (rez!=16)
		ExitProcess(0);

	WSAData data;
	WORD version=MAKEWORD(2,2); 
	int res = WSAStartup(version, &data); 
	if (res!=0)
	{
		return 0;
	}

	struct addrinfo hints;
	struct addrinfo * result;

	Connections = (SOCKET*)calloc(64,sizeof(SOCKET)); 

	ZeroMemory(&hints,sizeof(hints));


	hints.ai_family=AF_INET; 
	hints.ai_flags=AI_PASSIVE; 
	hints.ai_socktype=SOCK_STREAM; 
	hints.ai_protocol=IPPROTO_TCP;

	getaddrinfo(NULL,"5896",&hints,&result);

	Listen=socket(result->ai_family,result->ai_socktype,result->ai_protocol);
	bind(Listen,result->ai_addr, result->ai_addrlen); 
	listen(Listen,SOMAXCONN); 

	freeaddrinfo(result);

	printf("\n");
	printf("Сервер начал работу....\n");
	for (;;Sleep(75)) 
	{
		if (Connect=accept(Listen,NULL,NULL))
		{
			printf("Клиент подключен...\n");
			Connections[ClientCount]=Connect; 
			ClientCount++;
			CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)SendMessageToClient,(LPVOID)(ClientCount-1),NULL,NULL); 
		}
	}
	return 1;

}
