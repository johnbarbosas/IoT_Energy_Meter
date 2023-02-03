# IoT_Energy_Meter

<p align="justify">    Há uma grande discussão hoje sobre o uso da energia elétrica, e em como a sociedade pode utilizá-la de maneira inteligente. A Europa tem se preocupado com esse tópico e já está colocando incentivos no mercado para isso acontecer.
Um dos maiores problemas do consumo energético no Brasil e no mundo são os picos, que acontecem principalmente após o horário comercial, quando as pessoas chegam em suas casas e utilizam mais energia. E somado com isso há equipamentos ineficientes que trabalham nesse horário, contribuindo para o “caos” energético.
Já existem diversos medidores de energia que podem monitorar o consumo de cada circuito de sua casa ou comércio, porém poucos são capazes de fazer uma integração com a nuvem e disponibilizar históricos. Além do mais, os que fazem ainda não são de fácil utilização e possuem um alto valor.</p>

<h2>Objetivo</h2>
<p align="justify">O intuito deste projeto é desenvolver um sistema IoT que seja capaz de medir a potência elétrica e a energia consumida de um equipamento e/ou sistema por meio da tensão de entrada e da corrente que o sistema drena e com estes dados armazená-los para futuras análises.</p>

<h2>Descrição do projeto</h2>
<p align="justify"> Este projeto tem como objetivo a construção de um dispositivo que faça a medição do consumo de energia elétrica de um equipamento ou sistema de forma prática e menos invasiva possível com componentes acessiveis. O funcionamento do dispositivo se dá por dois sensores, um de corrente e outro de tensão elétrica, os valores obtidos por eles são enviados a um microcontrolador que irá realizar os cálculos de potência, energia consumida e o custo financeiro desta energia.</p>

<h3>Materiais utilizados:</h3>
<p> Para a prototipagem inicial foram utilizados os materiais disponibilizados pelo FIT e sensores próprios dos alunos, sendos listados a seguir. </p>
- 2x resistores de 10 kΩ;<br />
- 1x resistor de 33 Ω;<br />
- 1x capacitor de 100 uF e 35V;<br />
- 1x Arduino RP2040;<br />
- 1x Protoboard de 400 furos;<br />
- Jumpers;<br />
- 1x conector jack para P2;<br />
- 1x sensor SCT 013;<br />
- 1x módulo sensor Zmpt101b;<br />
- MDF;<br />

<h3>Microcontrolador:</h3>

<p align="justify">Para realizar os cálculos, processamentos e envios de dados para a nuvem utilizou-se o microcontrolador nano RP2040, que faz parte da linha de Arduinos. Este microcontrolador traz diversos benefícios: ótimo processamento, pequenas dimensões físicas e módulo WiFi embarcado, diferente dos outros arduinos. Este microcontrolador poderia ser substituído pelo ESP826 ou ESP32, mas estes deveriam ter suas ADCs calibradas. 
A seguir, tem-se o diagrama das pinagens do RP2040.</p>

<div style="display: inline_block" align="center">
 <img height="350em" src="https://docs.arduino.cc/static/a4d65079ebe3058e37153eb0f93890a8/ABX00053-pinout.png"/>
 <p>Fig.1. Pinagens do Arduino RP2040.</p> 
 </div>
 </ br>
  
 <h3> Sensores:</h3>
 <p align="justify">Para a medição da tensão utilizou-se o módulo sensor de tensão AC Zmpt101b, figura 2, cujo a maior tensão que pode ser aferida sendo de 250 Vrms, necessitando apenas de 5V para a alimentação do circuito de condicionamento de sinal e de 2 mA, sendo assim uma excelente opção.</p>
<div style="display: inline_block" align="center">
 <img height="350em" src="https://raw.githubusercontent.com/johnbarbosas/IoT_Energy_Meter/main/README_img/zmpt101b.jpeg"/>
 <p>Fig.2. Sensor de tensão zmpt101b.</p> 
  </div>
  
 <p align="justify">Para a medição da corrente utilizou-se de um sensor não invasivo, pois assim, tornaria a montagem do circuito mais simples, além de trazer um fácil acesso a medição. Com isso, utilizou-se o sensor SCT 013, figura 3, que é um sensor transformador de corrente, que através da sua relação de espiras consegue fornecer na saída do sensor uma corrente de 50 mA no plug com conexão P2 quando no cabo da carga estiver passando uma corrente de 100A.</p>
 
<div style="display: inline_block" align="center">
 <img height="350em" src="https://raw.githubusercontent.com/johnbarbosas/IoT_Energy_Meter/main/README_img/Sensor_de_corrente.jpeg"/>
 <p>Fig.3. Sensor de corrente SCT013.</p> 
 </div>

<h3>Processos de medição:</h3>
<p align="justify">Nesta etapa utilizou-se o módulo zmpt101b ligado ao Arduino RP2040 juntamente com a protoboard e jumpers para conexão. Os dois pinos GNDs do módulo foram ligados ao GND do Arduino, o pino VCC ao pino Vin e o Vout conectou-se à porta analógica A2.
A montagem do circuito em protoboard pode ser visto na figura a seguir.
</p>

<div style="display: inline_block" align="center">
 <img height="350em" src="https://raw.githubusercontent.com/johnbarbosas/IoT_Energy_Meter/main/README_img/montagem_do_sensor_de_tensao.jpeg"/>
 <p>Fig.4. Montagem do sensor de tensão na protoboard.</p> 
</div>

<p>Para utilizar este sensor foi desenvolvido um código onde inicialmente analisou-se o sinal de uma tomada da sala de instruções do curso para realizar a calibração. Primeiro foi analisada a forma de onda emita pelo sensor ligada à tomada, e depois, atribui-se o valor para a variável CAL_VOLT, que iria realizar a calibração dos valores dados pelo ADC e converte-los para volts, o valor definido foi com base nas tentativas empíricas onde os valores da curva mais se adequavam aos valores reais, medidos com um multímetro Fluke.</p>
<p>O código elaborado realiza o cálculo do valor rms no laço "for" mais interno realiza a coleta de 360 amostras de um ciclo da senoide, ou seja, a cada um grau dela, guardando este valor na variável leitura, depois este valor é elevado ao quadrado, e com isso, acrescentado a variável tensão.</p>

<p>Como já mencionado, usou-se o sensor SCT013 para medir a corrente do circuito. Como este sensor é um transformador de corrente, sua saída não pode ser ligada direta a entrada analógica do Arduino, precisou-se adicionar um resistor na saída do sensor para limitar a tensão de entrada do MCU. Além de adicionar um sensor de carga é necessário aplicar um offset de 2,5V na forma de onda, para que o microcontrolador não receba valores negativos. 
Para realizar o offset utilizou-se um divisor de tensão com os resistores de 10k e um capacitor de filtragem de 100uF e para o resistor de carga utilizou-se de 33. A montagem pode ser vista na figura abaixo.</p>	


  
  <div style="display: inline_block" align="center">
 <img height="350em" src="https://raw.githubusercontent.com/johnbarbosas/IoT_Energy_Meter/main/README_img/montagem_do_sensor_de_corrente.jpeg"/>
 <p>Fig.5. Montagem do sensor de corrente na protoboard.</p> 
</div>

<div style="display: inline_block" align="center">
 <img height="350em" src="https://raw.githubusercontent.com/johnbarbosas/IoT_Energy_Meter/main/README_img/Esquema_final.jpeg"/>
 <p>Fig.6. Montagem completo do circuito.</p> 
</div>



  <h2>Virtual Machine | Broker | NodeRED</h2>
  
  Um dos protocolos mais simples para trocas de mensagem, via internet, no mundo do IoT é o [MQTT] (MQ Telemetry Transport). Nele há um agente central que irá receber todas as notificações, chamado de servidor broker. Os dispositivos podem publicar em *tópicos* desse broker, assim como se inscrever nos tópicos para receber as mensagens.
  
  Foi criada uma máquina virtual (MV), gratuitamente, no [Amazon Web Service] e instalado um broker MQTT através do [vídeo] tutorial do YouTube. Nessa MV foi instalado também o NodeRED seguindo o [passo a passo] da própria plataforma.
  
  O NodeRED foi usado para fazer o front-end do projeto, disponibilizando os dados numericamente e em forma gráfica ao longo do tempo. Seu funcionamento é através de blocos e da linguagem JavaScript. Todos os blocos estão disponíveis na pasta chamada NodeRED.
  
  
  [MQTT]: https://mqtt.org/
  [Amazon Web Service]: https://aws.amazon.com/pt/
  [vídeo]: https://www.youtube.com/watch?v=z5vx93uKr_U
  [passo a passo]: https://nodered.org/docs/getting-started/aws
  
  <div style="display: inline_block" align="center">
 <img height="350em" src="https://raw.githubusercontent.com/johnbarbosas/IoT_Energy_Meter/main/README_img/node1.jpg"/>
 <p>Fig.5. Diagrama de blocos do NodeRED.</p> 
</div>

<div style="display: inline_block" align="center">
 <img height="350em" src="https://raw.githubusercontent.com/johnbarbosas/IoT_Energy_Meter/main/README_img/node2.jpg"/>
 <p>Fig.6. Informações do Arduino enviadas para o NodeRED.</p> 
</div>
