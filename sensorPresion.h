#pragma once

#include "SFE_BMP180.h"
#include "Wire\src\Wire.h"
enum class tipoAltura
{
	NIVEL_DEL_MAR,
	DESPEGUE
};
/*	SDA(A4)	*/
/*	SCL(A5)	*/
class sensorPresion {
private:
	SFE_BMP180 bmp180;
	double temperatura;
	double presionInicial;
	double presion;
	double alturaInicial;
	double altura;
	char tiempoLectura;
public:
	sensorPresion(){}
	const double presionNivelMar = 1013.25;
	void setup() {
		if (bmp180.begin()) {
			Serial.println("Barometro iniciado correctamente");
			Serial.println("Leyendo presion atcual...");
			presionInicial = this->getPresion();
			alturaInicial = this->altitud();
			Serial.println("Presion Inicial: " + String(presionInicial));
			Serial.println("Altura inicial: " + String(alturaInicial));
		}
		else {
			Serial.println("Error al iniciar el barometro");
			while (true);
		}
	}
	double getTemperatura() {
		double temperatura;
		tiempoLectura = bmp180.startTemperature();
		if (tiempoLectura != 0)
		{
			delay(tiempoLectura);
			bmp180.getTemperature(temperatura); //Obtener la temperatura
		}
		else
		{
			Serial.println("Error en la obtencion de temperatura...");
			Serial.println("ERROR: " + bmp180.getError());
		}
		return temperatura;
	}
	double getPresion() {
		this->getTemperatura();//Actualizamos valor de la temperatura, para medir presion.
		tiempoLectura = bmp180.startPressure(3);
		if (tiempoLectura != 0)
		{
			delay(tiempoLectura);
			bmp180.getPressure(presion, temperatura);
		}
		else
		{
			Serial.println("Error en la obtencion de presión...");
			Serial.println("ERROR: " + bmp180.getError());
		}
		return presion;
	}
	double altitud(const double Po = sensorPresion().presionNivelMar) {
		return altura = bmp180.altitude(this->getPresion(), Po);
	}
	double altitud(tipoAltura tipoDeMedida) {
		switch (tipoDeMedida)
		{
		case tipoAltura::NIVEL_DEL_MAR:
			return altitud();
			break;
		case tipoAltura::DESPEGUE:
			return altitud(presionInicial);
			break;
		}
	}
	char getUltimoTiempoDeLectura()
	{
		return tiempoLectura;
	}
};