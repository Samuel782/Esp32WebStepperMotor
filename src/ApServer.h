#ifndef AP_SERVER_H
#define AP_SERVER_H

#include <WebServer.h>
#include <Preferences.h>

extern WebServer serverAP;    // Dichiarazione del server dell'AP
extern Preferences preferences;  // Dichiarazione di `preferences` come extern

String generateApPage();
void setupAPServer();         // Funzione per configurare il server dell'AP
void handleAPServer();        // Funzione per gestire le richieste del server

#endif