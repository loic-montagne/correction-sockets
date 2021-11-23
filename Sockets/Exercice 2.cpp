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
	SOCKET sock_fd;                   // sock_fd : point de connexion
	SOCKET new_fd;                    // new_fd : socket de communication
	SOCKADDR_IN my_addr;              // adresse de transport de la socket coté serveur
	SOCKADDR_IN their_addr;           // adresse de transport de la socket coté client
	unsigned int sin_size;            // Taille d'une adresse de transport
	char buffer[MAXDATASIZE];         // Message recu
	int length;                       // Taille du message reçu
	char date_string[MAXDATASIZE];    // Chaine de caractere contenant la date
	time_t time_value;
	struct tm* time_info;


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
	if (listen(sock_fd, BACKLOG) == -1)
		perror("Attente sur le point de connexion : ");

	// Boucle principale de traitement des demandes client
	while (1)
	{
		// Accept est bloquant : le processus n'avance pas tant que personne ne se connecte
		int sinsize = sizeof(their_addr);
		if ((new_fd = accept(sock_fd, (SOCKADDR*)&their_addr, &sinsize)) == -1)
			perror("Acceptation d'une connexion entrante : ");

		// Une connexion a eu lieu : on recupere l'adresse du client
		printf("server: got connection from %s\n",
			inet_ntoa(their_addr.sin_addr)); // inet_ntoa : net to ascii

		// On boucle jusqu'à ce que le client se déconnecte
		while (1)
		{
			// On attend une demande du client
			if ((length = recv(new_fd, buffer, MAXDATASIZE, 0)) == -1)
			{
				// S'il y eu une erreur, c'est certainement que le client s'est déconnecté
				// On affiche l'erreur
				perror("Reception d'un message : ");
				// On ferme la socket de communication
				if (closesocket(new_fd) == -1)
					perror("Fermeture de la socket de communication : ");
				// Et on quitte la boucle de traitement des messages du client
				break;
			}

			// Suppression des retours chariots (\n et \r)
			while (length > 0 && (buffer[length - 1] == '\n' || buffer[length - 1] == '\r'))
				length--;
			// Ajout de backslash zero a la fin pour en faire une chaine de caracteres
			if (length >= 0 && length < MAXDATASIZE)
				buffer[length] = '\0';

			// Affichage du message
			printf("Message recu : %s \n", buffer);

			// On recupere l'heure et la date
			time(&time_value);
			time_info = localtime(&time_value);

			// Traitement du message reçu
			if (strcmp(buffer, "DATE") == 0)
			{
				strftime(date_string, MAXDATASIZE, "%e/%m/%Y", time_info);
				// On envoie l'heure et la date
				if (send(new_fd, date_string, strlen(date_string), 0) == -1)
					perror("Envoi d'un message : ");
			}
			else if (strcmp(buffer, "JOUR") == 0)
			{
				strftime(date_string, MAXDATASIZE, "%A", time_info);
				// On envoie l'heure et la date
				if (send(new_fd, date_string, strlen(date_string), 0) == -1)
					perror("Envoi d'un message : ");
			}
			else if (strcmp(buffer, "MOIS") == 0)
			{
				strftime(date_string, MAXDATASIZE, "%B", time_info);
				// On envoie l'heure et la date
				if (send(new_fd, date_string, strlen(date_string), 0) == -1)
					perror("Envoi d'un message : ");
			}
			else if (strcmp(buffer, "QUITTER") == 0)
			{
				// On ferme la socket de communication
				if (closesocket(new_fd) == -1)
					perror("Fermeture de la socket de communication : ");
				// Et on quitte la boucle de traitement des messages du client
				break;
			}
		}
	}

	// On devrait faire closesocket(sock_fd); puis WSACleanup(); mais puisqu'on a entré une boucle infinie ...

	return 0;
}
*/