#include "MainServer.h"
#include "stepper.h"

WebServer mainServer(80);

String generateMainPage() {
    String html = R"rawliteral(
        <!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>Height Control</title>
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
                #main {
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
                button {
                    padding: 0.7rem;
                    border: none;
                    border-radius: 10px;
                    background-color: #8183ff;
                    color: #f7f7f7;
                    font-size: 1rem;
                    font-weight: bold;
                    cursor: pointer;
                }
                button:hover {
                    background-color: #6b6dff;
                }
                #Up, #Down {
                    display: flex;
                    gap: 16px;
                    margin-bottom: 1rem;
                }
            </style>
        </head>
        <body>
            <div id="main">
                <h1>Height Control</h1>
                <div id="Up">
                    <button onclick="fetch('/up?value=1')">UP [+1]</button>
                    <button onclick="fetch('/up?value=5')">UP [+5]</button>
                    <button onclick="fetch('/up?value=10')">UP [+10]</button>
                </div>
                <div id="Down">
                    <button onclick="fetch('/down?value=1')">Down [-1]</button>
                    <button onclick="fetch('/down?value=5')">Down [-5]</button>
                    <button onclick="fetch('/down?value=10')">Down [-10]</button>
                </div>
            </div>
        </body>
        </html>
    )rawliteral";
    return html;
}

void setupSTAServer() {
    mainServer.on("/", []() {
        mainServer.send(200, "text/html", generateMainPage());
    });

    mainServer.on("/up", []() {
        if (mainServer.hasArg("value")) {
            int rotations = mainServer.arg("value").toInt();
            spinAntiClockwise(rotations);
            mainServer.send(200, "text/plain", "Rotating UP " + mainServer.arg("value"));
        } else {
            mainServer.send(400, "text/plain", "Bad Request");
        }
    });

    mainServer.on("/down", []() {
        if (mainServer.hasArg("value")) {
            int rotations = mainServer.arg("value").toInt();
            spinClockwise(rotations);
            mainServer.send(200, "text/plain", "Rotating DOWN " + mainServer.arg("value"));
        } else {
            mainServer.send(400, "text/plain", "Bad Request");
        }
    });

    mainServer.begin();
}

void handleAPServer() {
    mainServer.handleClient();
}