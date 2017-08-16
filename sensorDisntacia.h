#pragma once
/*
Sensor de Presion

@author Pablo Horno
@version 1.0 27/01/2017
*/
enum class tipoLectura { UNICA, MULTIPLE, MEDIA };

class sensorDistancia
{
public:
	int trig;
	int eco;
	long duracionUltimaMedida;

	sensorDistancia(int trig, int eco)
	{
		this->trig = trig;
		this->eco = eco;
	}
	sensorDistancia()
	{
		trig = NULL;
		eco = NULL;
	}
	void setup()
	{
		pinMode(trig, OUTPUT);
		pinMode(eco, INPUT);
		Serial.println("Sensor de Distancia iniciado correctamente");
	}
	float getDistancia(tipoLectura tipoLect = tipoLectura::UNICA)
	{
		float duracion, distancia;

		if (tipoLect == tipoLectura::UNICA)
		{
			digitalWrite(trig, LOW);
			delayMicroseconds(2);
			digitalWrite(trig, HIGH); 
			delayMicroseconds(10); 
			digitalWrite(trig, LOW); 
			duracion = pulseIn(eco, HIGH);
			distancia = duracion / 2 / 29.1;
			duracionUltimaMedida = duracion;
		}
		else if (tipoLect == tipoLectura::MULTIPLE)
		{
			int numMedidas = 5;
			for (int i = 0; i < numMedidas; i++)
			{
				digitalWrite(trig, LOW);
				delayMicroseconds(2);
				digitalWrite(trig, HIGH);
				delayMicroseconds(10);
				digitalWrite(trig, LOW);
				duracion = pulseIn(eco, HIGH);
				distancia += duracion / 2 / 29.1;
				duracionUltimaMedida = duracion;
			}
			distancia = distancia / numMedidas;
		}

		return distancia;

	}

};