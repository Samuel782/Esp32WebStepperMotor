#ifndef MAIN_SERVER_H
#define MAIN_SERVER_H

#include <WebServer.h>

extern WebServer mainServer;  

String generateMainPage(); 
void setupSTAServer();
void handleSTAServer();

#endif