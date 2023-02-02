// This example uses an ESP32 Development Board
// to connect to shiftr.io.
//
// You can check on your device after a successful
// connection here: https://www.shiftr.io/try.
//
// by Joël Gähwiler
// https://github.com/256dpi/arduino-mqtt

#include <WiFiNINA.h>
#include <MQTT.h>
#include <String>

#define VOLT_CAL 36.45 //VALOR DE CALIBRAÇÃO (DEVE SER AJUSTADO EM PARALELO COM UM MULTÍMETRO)
#define voltPin A2
#define CURRENT_CAL 8.1165 //VALOR DE CALIBRAÇÃO (DEVE SER AJUSTADO EM PARALELO COM UM MULTÍMETRO)
#define currentPin A1

const char ssid[] = "Projeto-Lader";
const char pass[] = "Lader1234@";

long randomNumber;

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;
float tensao = 0, tensaoMedia = 0, leituraT = 0;
float corrente = 0, correnteMedia = 0, leituraC = 0;
float potencia = 0;
double energia = 0;
String stringTensao = "";
String stringCorrente = "";
String stringPotencia = "";
String stringEnergia = "";

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("esp32")) { // Para acesso não anônimo -> ("arduino", "public", "public") nome, login, senha
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);

  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported
  // by Arduino. You need to set the IP address directly.
  client.begin("ec2-54-210-39-119.compute-1.amazonaws.com", net); //alterar para DNS de acesso
  client.onMessage(messageReceived);

  connect();
}

void loop() {
  client.loop();
  //delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }

  stringTensao = "";
  stringCorrente = "";
  stringPotencia = "";
  stringEnergia = "";
  tensao = 0;
  tensaoMedia = 0;
  corrente = 0;
  correnteMedia = 0;

  for (int j = 0; j<100; j++){
     for (int i = 0; i<360; i++){
      
        leituraT = analogRead(voltPin) - 727.5;
        // Serial.print("Tensão: ");
        // Serial.println(leituraT);
        
        if ((leituraT*leituraT) < 36) leituraT = 0;

        leituraT *= VOLT_CAL;
        leituraT *= leituraT;
        tensao += leituraT;


        leituraC = analogRead(currentPin) - 230;
        // Serial.print("Senoide:");
        // Serial.println(leituraC);
        
        if ((leituraC*leituraC) < 36) leituraC = 0;
        
        leituraC /= CURRENT_CAL;
        leituraC *= leituraC;
        corrente += leituraC;
        
        delayMicroseconds(46.29);
      }

    tensao /= 360;
    tensao = sqrt(tensao);

    tensaoMedia += tensao;

    corrente /= 360;
    corrente = sqrt(corrente);

    correnteMedia += corrente;
   
  }

  tensaoMedia /= 100;
  // Serial.print("Tensão média: ");
  // Serial.println(tensaoMedia);
  
  correnteMedia /= 100;
//  Serial.print("Corrente média: ");
//  Serial.println(correnteMedia);
    
  stringTensao += tensaoMedia;
  client.publish("/tensao", stringTensao);

  stringCorrente += correnteMedia;
  client.publish("/corrente", stringCorrente);

  correnteMedia = 200;
  tensaoMedia = 220;

  potencia = correnteMedia * tensaoMedia / 1000; 
  
  energia += potencia * 1.66644 / 3600;

  Serial.print("Potencia: ");
  Serial.print(potencia);
  Serial.println(" kW");
  Serial.print("Energia: ");
  Serial.print(energia);
  Serial.println(" kWh");  

  stringPotencia += potencia;
  client.publish("/potencia", stringPotencia);

  stringEnergia += energia;
  client.publish("/energia", stringEnergia);
}