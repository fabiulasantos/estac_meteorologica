# estac_meteorologica
Estação meteorológica desenvolvida para a disciplina de Objetos Inteligentes Conectados do curso de Análise e Desenvolvimento de Sistemas (EaD) da Universidade Mackenzie

O protótipo da estação meteorológica opera da seguinte maneira:
●	O Arduino Uno R3 atua como a unidade central do sistema, responsável por coletar dados dos sensores e enviar informações para a internet.
●	O sensor DHT11 mede a temperatura e umidade no ambiente e envia os dados para o Arduino.
●	O sensor LDR mede a luminosidade ambiente e envia os dados para o Arduino.
●	O sensor BMP180 mede a pressão atmosférica e temperatura e envia os dados para o Arduino.
●	O Arduino processa os dados dos sensores e, em seguida, utiliza o módulo WiFi ESP8266 ESP-01 para enviar esses dados para um servidor na internet, usando o protocolo MQTT.
●	Os dados coletados podem ser acessados remotamente por meio de um aplicativo ou plataforma web para monitorar as condições meteorológicas em tempo real.
