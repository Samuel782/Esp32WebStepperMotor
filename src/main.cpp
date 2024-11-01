#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>

#include "APServer.h"
#include "MainServer.h"

Preferences preferences;

const char *ap_ssid = "ESP32_AccessPoint";
const char *ap_password = "12345678";

bool connected = false;

// Funzione per tentare la connessione alla rete Wi-Fi salvata
void connectToWiFi()
{
    String ssid = preferences.getString("ssid", "");
    String password = preferences.getString("password", "");

    if (ssid != "" && password != "")
    {
        Serial.print("Connettendo a SSID: ");
        Serial.println(ssid);
        WiFi.mode(WIFI_AP_STA); // Modalità Dual: sia Access Point che Station
        WiFi.begin(ssid.c_str(), password.c_str());

        unsigned long startAttemptTime = millis();
        while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000)
        {
            Serial.print(".");
            delay(500);
        }

        if (WiFi.status() == WL_CONNECTED)
        {
            Serial.println("\nConnesso alla rete WiFi!");
            Serial.print("IP come client: ");
            Serial.println(WiFi.localIP());

            connected = true;
            setupSTAServer();
        }
        else
        {
            Serial.println("\nConnessione fallita! Continuo solo come AP.");
        }
    }
    else
    {
        Serial.println("Credenziali WiFi non trovate. Continuo solo come AP.");
        WiFi.mode(WIFI_AP);
    }

    // Avvia l'AP indipendentemente dallo stato della connessione come client
    WiFi.softAP(ap_ssid, ap_password);
    Serial.print("IP dell'AP: ");
    Serial.println(WiFi.softAPIP());
    setupAPServer();
}

void setup()
{
    Serial.begin(115200);
    preferences.begin("WiFiCreds", false);
    connectToWiFi();
}

void loop()
{
    handleAPServer();
    if(connected){
        handleAPServer();
    }
}