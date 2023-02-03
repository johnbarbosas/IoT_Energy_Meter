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
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  
  client.begin("ec2-54-210-39-119.compute-1.amazonaws.com", net); // conexão ao servidor broker

  connect();
}

void loop() {
  client.loop();

  if (!client.connected()) {
    connect();
  }
  
  
  // zerando os valores
  stringTensao = "";
  stringCorrente = "";
  stringPotencia = "";
  stringEnergia = "";
  tensao = 0;
  tensaoMedia = 0;
  corrente = 0;
  correnteMedia = 0;

  for (int j = 0; j<100; j++){ // 100 ciclos da senoide 
     for (int i = 0; i<360; i++){ // leitura a cada grau da senoide e cálculo do valor RMU fazendo a "integral" (somatório)
      
        leituraT = analogRead(voltPin) - 727.5; // leitura da tensão e zerar o offset
        // Serial.print("Tensão: ");
        // Serial.println(leituraT);
        
        if ((leituraT*leituraT) < 36) leituraT = 0; // exclusão do erro para pequenas tensões

        leituraT *= VOLT_CAL; // valor de calibração
        leituraT *= leituraT; // elevado ao quadrado
        tensao += leituraT; // somatório das tensões


        leituraC = analogRead(currentPin) - 230; // leitura da corrente e zerar o offset
        // Serial.print("Senoide:");
        // Serial.println(leituraC);
        
        if ((leituraC*leituraC) < 36) leituraC = 0; // exclusão do erro para pequenas correntes
        
        leituraC /= CURRENT_CAL; // valor de calibração
        leituraC *= leituraC; // elevado ao quadrado
        corrente += leituraC; // somatório das correntes
        
        delayMicroseconds(46.29); // 1s / 60Hz = 0,0166 / 360 = 46,29 us -> período da amostragem para 1 amostra por grau da senoide
      }

    tensao /= 360; // média da tensão
    tensao = sqrt(tensao); // raiz quadrada -> valor em RMS

    corrente /= 360; // média da corrrente
    corrente = sqrt(corrente); // raiz quadrada -> valor em RMS
    
    // valores médios para não houver muita variação
    tensaoMedia += tensao;  
    correnteMedia += corrente;
   
  }

  tensaoMedia /= 100;
  // Serial.print("Tensão média: ");
  // Serial.println(tensaoMedia);
  
  correnteMedia /= 100;
  // Serial.print("Corrente média: ");
  // Serial.println(correnteMedia);

  potencia = correnteMedia * tensaoMedia / 1000; // cálculo da potência
  
  energia += potencia * 1.66644 / 3600; // a energia é a potência multiplica pelo tempo daquela potência, que nesse caso é 46,29 us * 60 * 100 / 3600 (3600 para o valor ficar em horas)

  
  // print dos valores medidos na porta serial
  Serial.print("tensão: ");
  Serial.print(tensaoMedia);
  Serial.println(" V");
  Serial.print("Corrente");
  Serial.print(correnteMedia);
  Serial.println(" A"); 
  Serial.print("Potencia: ");
  Serial.print(potencia);
  Serial.println(" kW");
  Serial.print("Energia: ");
  Serial.print(energia);
  Serial.println(" kWh"); 
  
  // salvando os valores como string para envia-lós ao broker
    
  // tensão
  stringTensao += tensaoMedia;
  client.publish("/tensao", stringTensao);
  
  // corrente
  stringCorrente += correnteMedia;
  client.publish("/corrente", stringCorrente);

  // potência
  stringPotencia += potencia;
  client.publish("/potencia", stringPotencia);
  
  // energia
  stringEnergia += energia;
  client.publish("/energia", stringEnergia);
}
