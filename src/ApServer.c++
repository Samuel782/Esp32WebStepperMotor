#include "APServer.h"

WebServer serverAP(80);
Preferences preferences;

// Funzione che genera la pagina HTML dinamica
String generateMainPage()
{
    String html = R"rawliteral(
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Connect to WiFi</title>
        <style>
            body {
                background-color: #1f1d2c;
                color: #f7f7f7;
                display: flex;
                align-items: center;
                justify-content: center;
                min-height: 100vh;
                margin: 0;
                font-family: Arial, sans-serif;
            }
            form {
                display: flex;
                flex-direction: column;
                background-color: #2d2f48;
                width: 22rem;
                padding: 2rem;
                border-radius: 15px;
                box-shadow: 0 8px 16px rgba(0, 0, 0, 0.3);
            }
            h1 {
                margin-bottom: 1rem;
                font-size: 1.5rem;
                color: #8183ff;
            }
            label {
                color: #a5a5a5;
                margin-bottom: 0.3rem;
                font-size: 0.9rem;
            }
            select, input[type='password'] {
                padding: 0.7rem;
                border-radius: 10px;
                border: none;
                margin-bottom: 1rem;
                font-size: 0.9rem;
                background-color: #393c5a;
                color: #f7f7f7;
            }
            input[type='submit'] {
                padding: 0.7rem;
                border: none;
                border-radius: 10px;
                background-color: #8183ff;
                color: #f7f7f7;
                font-size: 1rem;
                font-weight: bold;
                cursor: pointer;
            }
            input[type='submit']:hover {
                background-color: #6b6dff;
            }
        </style>
    </head>
    <body>
        <div id="form">
            <h1>Login to your WiFi Network</h1>
            <form action='/connect' method='POST'>
                <label for='ssid'>SSID:</label>
                <select name='ssid'>
    )rawliteral";

    // Scansione delle reti Wi-Fi e aggiunta delle opzioni
    int n = WiFi.scanNetworks();
    for (int i = 0; i < n; ++i)
    {
        html += "<option value='" + WiFi.SSID(i) + "'>" + WiFi.SSID(i) + "</option>";
    }

    // Continuazione del codice HTML
    html += R"rawliteral(
                </select>
                <label for='password'>Password:</label>
                <input type='password' name='password' placeholder="Enter network password">
                <input type='submit' value='Connect'>
            </form>
        </div>
    </body>
    </html>
    )rawliteral";

    return html;
}

void setupAPServer()
{
    // Configura il server e la risposta alla richiesta principale
    serverAP.on("/", []()
                { serverAP.send(200, "text/html", generateMainPage()); });

    serverAP.on("/connect", HTTP_POST, []()
                {
                    String ssid = serverAP.arg("ssid");
                    String password = serverAP.arg("password");

                    // Salvataggio delle credenziali nella memoria flash
                    preferences.putString("ssid", ssid);
                    preferences.putString("password", password);

                    serverAP.send(200, "text/html", "<h1>Connessione in corso... Riavvio in corso</h1>");
                    delay(2000);
                    ESP.restart(); // Riavvio per attivare la connessione Wi-Fi
                });

    // Avvia il server
    serverAP.begin();
}
void handleAPServer()
{
    serverAP.handleClient();
}
