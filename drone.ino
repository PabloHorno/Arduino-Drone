/*
 Name:		drone.ino
 Created:	1/27/2017 3:41:21 PM
 Author:	Pablo
*/
#include "sensorDisntacia.h"
#include "sensorPresion.h"
#include "vector.h"

sensorDistancia sensorFrontal(5, 4);
sensorPresion barometro;

void setup() {
	Serial.begin(9600);
	sensorFrontal.setup();
	barometro.setup();
}


void loop() {
	Serial.println("Distancia: " + String(sensorFrontal.getDistancia()) + "cm");
	Serial.println("Ultima medida: " + String(sensorFrontal.duracionUltimaMedida));
	Serial.println("Presion: " + String(barometro.getPresion()));
	Serial.println("Temperatura: " + String(barometro.getTemperatura()) + "*C");
	Serial.println("Altura nivel del mar: " + String(barometro.altitud(tipoAltura::NIVEL_DEL_MAR)));
	Serial.println("Altura pto despegue: " + String(barometro.altitud(tipoAltura::DESPEGUE)));
	sensorFrontal.duracionUltimaMedida;
	delay(5000);
}