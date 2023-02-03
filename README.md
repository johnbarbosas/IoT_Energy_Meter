# IoT_Energy_Meter

<p align="justify">    Há uma grande discussão hoje sobre o uso da energia elétrica, e em como a sociedade pode utilizá-la de maneira inteligente. A Europa tem se preocupado com esse tópico e já está colocando incentivos no mercado para isso acontecer.
Um dos maiores problemas do consumo energético no Brasil e no mundo são os picos, que acontecem principalmente após o horário comercial, quando as pessoas chegam em suas casas e utilizam mais energia. E somado com isso há equipamentos ineficientes que trabalham nesse horário, contribuindo para o “caos” energético.
Já existem diversos medidores de energia que podem monitorar o consumo de cada circuito de sua casa ou comércio, porém poucos são capazes de fazer uma integração com a nuvem e disponibilizar históricos. Além do mais, os que fazem ainda não são de fácil utilização e possuem um alto valor.</p>

<h2>Objetivo</h2>
<p align="justify">O intuito deste projeto é desenvolver um sistema IoT que seja capaz de medir a potência elétrica e a energia consumida de um equipamento e/ou sistema por meio da tensão de entrada e da corrente que o sistema drena e com estes dados armazená-los para futuras análises.</p>

<h2>Descrição do projeto</h2>
<p align="justify"> Este projeto tem como objetivo a construção de um dispositivo que faça a medição do consumo de energia elétrica de um equipamento ou sistema de forma prática e menos invasiva possível com componentes acessiveis. O funcionamento do dispositivo se dá por dois sensores, um de corrente e outro de tensão elétrica, os valores obtidos por eles são enviados a um microcontrolador que irá realizar os cálculos de potência, energia consumida e o custo financeiro desta energia.</p>

***Materiais utilizados:***
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


<div style="display: inline_block" align="center">
 <img height="350em" src="https://docs.arduino.cc/static/a4d65079ebe3058e37153eb0f93890a8/ABX00053-pinout.png"/>
 <p>Fig.1. Pinagens do Arduino RP2040.</p> 
  </div>
  </ br>
***Sensores:***

<div style="display: inline_block" align="center">
 <img height="350em" src="https://docs.arduino.cc/static/a4d65079ebe3058e37153eb0f93890a8/ABX00053-pinout.png"/>
 <p>Fig.1. Pinagens do Arduino RP2040.</p> 
  </div>

  
  <h2>Virtual Machine | Broker | NodeRED</h2>
  
  Um dos protocolos mais simples para trocas de mensagem, via internet, no mundo do IoT é o [MQTT] (MQ Telemetry Transport). Nele há um agente central que irá receber todas as notificações, chamado de servidor broker. Os dispositivos podem publicar em *tópicos* desse broker, assim como se inscrever nos tópicos para receber as mensagens.
  
  Foi criada uma máquina virtual (MV), gratuitamente, no [Amazon Web Service] e instalado um broker MQTT através do [vídeo] tutorial do YouTube. Nessa MV foi instalado também o NodeRED seguindo o [passo a passo] da própria plataforma.
  
  
  [MQTT]: https://mqtt.org/
  [Amazon Web Service]: https://aws.amazon.com/pt/
  [vídeo]: https://www.youtube.com/watch?v=z5vx93uKr_U
  [passo a passo]: https://nodered.org/docs/getting-started/aws
