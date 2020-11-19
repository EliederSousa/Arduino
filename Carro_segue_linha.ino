/**
 * Carrinho seguidor de linha
 * Projeto da disciplina de Circuitos Elétricos e Eletrônicos
 * Universidade Presbiteriana Mackenzie, 2020
 *
 * Autores: Elieder Damasceno Sousa
 *          José Eduardo Bernardino Jorge
 *
 * Componentes utilizados: Arduino Nano, Ponte-H L298N, HC-SR04, Sensores Óptico Reflexivos.
 * Link para visualização do projeto em: https://youtu.be/-V28nO94t70
 */

#include <NewPing.h>

int pin_mtEsquerdo1     = 2;
int pin_mtEsquerdo2     = 3;
int pin_mtDireito1      = 5;
int pin_mtDireito2      = 6;
int pin_sensorLinhaE    = 7;
int pin_sonarECHO       = 8;
int pin_sonarTRIG       = 9;
int pin_velocidadeD     = 10;
int pin_velocidadeE     = 11;
int pin_sensorLinhaD    = 12;

#define FRENTE  true
#define TRAS    false
#define NALINHA true
#define VELOCIDADE 200
#define DELAY 0

// Constantes usadas na lógica do sensor ultrassônico
#define MAX_DISTANCE 300 // Distância máxima que vamos verificar no sensor ultrassônico (em centímetros). O máximo é 400-500cm.
#define DIST_PARADA 10 // Distância mínima antes do carrinho parar para evitar colisões (em centimetros).
#define TEMPO_ESPERA 1500 // Por quanto tempo o carrinho esperará após ter parado para evitar uma colisão (em milésimos).

// Configura a biblioteca NewPing, os pinos e a distância máxima.
NewPing sonar(pin_sonarTRIG, pin_sonarECHO, MAX_DISTANCE);

void girarRodaDireita( bool sentido ) {
  analogWrite( pin_velocidadeD, VELOCIDADE );
  if ( sentido ) {
    digitalWrite(pin_mtDireito1, LOW);
    digitalWrite(pin_mtDireito2, HIGH);
  } else {
    digitalWrite(pin_mtDireito1, HIGH);
    digitalWrite(pin_mtDireito2, LOW);
  }
}

void girarRodaEsquerda( bool sentido ) {
  analogWrite( pin_velocidadeE, VELOCIDADE );
  if ( sentido ) {
    digitalWrite(pin_mtEsquerdo1, LOW);
    digitalWrite(pin_mtEsquerdo2, HIGH);
  } else {
    digitalWrite(pin_mtEsquerdo1, HIGH);
    digitalWrite(pin_mtEsquerdo2, LOW);
  }
}

void andar() {
  girarRodaDireita( FRENTE );
  girarRodaEsquerda( FRENTE );
  delay(30);
}

void parar() {
  digitalWrite(pin_mtDireito1, LOW);
  digitalWrite(pin_mtDireito2, LOW);
  digitalWrite(pin_mtEsquerdo1, LOW);
  digitalWrite(pin_mtEsquerdo2, LOW);
  delay(5);
}

void setup() {
  // Inicializa os pinos.
  pinMode(pin_mtDireito1, OUTPUT);
  pinMode(pin_mtDireito2, OUTPUT);
  pinMode(pin_mtEsquerdo1, OUTPUT);
  pinMode(pin_mtEsquerdo2, OUTPUT);
  pinMode(pin_velocidadeD, OUTPUT);
  pinMode(pin_velocidadeE, OUTPUT);
  pinMode(pin_sonarTRIG, INPUT);
  pinMode(pin_sonarECHO, INPUT);
  pinMode(pin_sensorLinhaD, INPUT);
  pinMode(pin_sensorLinhaE, INPUT);
  Serial.begin(9600);
}

// Função para debug do código. 
void saida( const char* mensagem, int valor ) {
  Serial.print( mensagem );
  Serial.println( valor );
}

void loop() {
  
  // Lemos as informações dos sensores.
  int distancia = sonar.ping_cm();
  bool sensorDireito = digitalRead( pin_sensorLinhaD );
  bool sensorEsquerdo = digitalRead( pin_sensorLinhaE );
  
  // Para o carrinho se encontrar um obstáculo na frente.
  while ( (distancia <= DIST_PARADA) && (distancia > 0) ) {
    parar();
    delay( TEMPO_ESPERA );
    distancia = sonar.ping_cm();
  }
  
  // Após verificar que não há obstáculos, anda segundo o estado dos sensores.
  if ( sensorDireito ) {
    girarRodaEsquerda( TRAS );
    girarRodaDireita( FRENTE );
    delay(50);
    parar();
  } else if ( sensorEsquerdo ) {
    girarRodaDireita( TRAS );
    girarRodaEsquerda( FRENTE );
    delay(50);
    parar();
  } else {
    andar();
    parar();
  }
  delay( 20 );
}
