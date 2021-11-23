/*
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#define MYPORT 3490     // Port du point de connexion
#define BACKLOG 10      // Combien de connexion en attente autorise-t-on ?
#define MAXDATASIZE 100 // Nombre maximal d'octets à envoyer en une fois

int main()
{
	WSADATA WSAData;
	SOCKET sock_fd;         // sock_fd : point de connexion
	SOCKET new_fd;          // new_fd : socket de communication
	SOCKADDR_IN my_addr;    // adresse de transport de la socket coté serveur
	SOCKADDR_IN their_addr; // adresse de transport de la socket coté client
	unsigned int sin_size;  // Taille d'une adresse de transport
	char date_string[100];  // Chaine de caractere contenant la date
	SYSTEMTIME time_value;

	// Appel propre à Windows : sert à initialiser l'utilisation des WinSocks par un processus
	WSAStartup(MAKEWORD(2, 0), &WSAData);

	// Creation et initialisation du point de connexion
	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		perror("Création socket de connexion : ");

	// Configuration de l'adresse de transport
	my_addr.sin_addr.s_addr = INADDR_ANY; // adresse, devrait être converti en reseau mais est egal à 0
	my_addr.sin_family = AF_INET;         // type de la socket
	my_addr.sin_port = htons(MYPORT);     // port, converti en reseau

	// Demarrage du point de connexion : on ajoute l'adresse de transport dans la socket
	if (bind(sock_fd, (SOCKADDR*)&my_addr, sizeof(my_addr)) == -1)
		perror("Démarrage du point de connexion : ");

	// Attente sur le point de connexion
	if(listen(sock_fd, BACKLOG) == -1)
		perror("Attente sur le point de connexion : ");

	// Boucle principale de traitement des demandes client
	while (1)
	{
		int sinsize = sizeof(their_addr);

		// Accept est bloquant : le processus n'avance pas tant que personne ne se connecte
		if ((new_fd = accept(sock_fd, (SOCKADDR*)&their_addr, &sinsize)) == -1)
			perror("Acceptation d'une connexion entrante : ");

		// Une connexion a eu lieu : on recupere l'adresse du client
		printf("server: got connection from %s\n",
			   inet_ntoa(their_addr.sin_addr)); // inet_ntoa : net to ascii

		// On recupere l'heure et la date
		GetLocalTime(&time_value);
		sprintf(date_string,
			    "%d-%02d-%02d %02d:%02d:%02d.%03d",
			    time_value.wYear,
			    time_value.wMonth,
			    time_value.wDay,
			    time_value.wHour,
			    time_value.wMinute,
			    time_value.wSecond,
			    time_value.wMilliseconds);

		// On envoie l'heure et la date
		if (send(new_fd, date_string, strlen(date_string), 0) == -1)
			perror("Envoi de la date et de l'heure : ");
		
		if (closesocket(new_fd) == -1)
			perror("Fermeture de la socket de communication : ");

	}

	// On devrait faire closesocket(sock_fd); puis WSACleanup(); mais puisqu'on a entré une boucle infinie ...

	return 0;
}
*/