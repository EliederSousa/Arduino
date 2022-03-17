#include <virtuabotixRTC.h>           
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// 16/03/2022
// Author: Elieder Damasceno Sousa

// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

// Coloque os pinos ligado no módulo (digitais) RTC(clock, data, rst)
virtuabotixRTC RTC(7, 8, 9);

void setup() {      
	lcd.begin(16,2);

	// Informacoes iniciais de data e hora
	// Apos setar as informacoes, comente a linha abaixo
	// OBEDEÇA ao critério de usar DOIS algarismos, mesmo que o número seja menor que 10, use 04.
	// USE HORÁRIO 00-23hs
	// Enquanto houver fonte de energia alimentando o chip, não será preciso configurar a hora novamente.
	// (segundos, minutos, hora, dia da semana, dia do mes, mes, ano)
	// RTC.setDS1302Time(00, 51, 11, 1, 01, 01, 2017);
}

void loop() {
	// Le as informacoes do CI
	RTC.updateTime(); 
	lcd.clear();
	lcd.setCursor(0,0);
	
	// Chama a rotina que imprime o dia da semana
	imprime_dia_da_semana(RTC.dayofweek);
	
	// DATA
	lcd.print("Data: ");
	lcd.print(RTC.dayofmonth);
	lcd.print('/');
	lcd.print(RTC.month);
	lcd.print('/');
	lcd.print(RTC.year);
	lcd.setCursor(0,1);

	// HORA
	lcd.print("Hora: ");
	lcd.print(RTC.hours);
	lcd.print(":");
	(RTC.minutes < 10) ? lcd.print("0") : lcd.print(""); 
	lcd.print(RTC.minutes);
	lcd.print(":");
	(RTC.seconds < 10) ? lcd.print("0") : lcd.print(""); 
	lcd.print(RTC.seconds);

	delay(1000);
}

void imprime_dia_da_semana(int dia) {
	switch (dia) {
		case 1:
		Serial.print("Domingo");
		break;
		case 2:
		Serial.print("Segunda");
		break;
		case 3:
		Serial.print("Terca");
		break;
		case 4:
		Serial.print("Quarta");
		break;
		case 5:
		Serial.print("Quinta");
		break;
		case 6:
		Serial.print("Sexta");
		break;
		case 7:
		Serial.print("Sabado");
		break;
	}
}