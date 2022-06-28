#ifndef PUNTO_H
#define PUNTO_H


class Punto
{
private:
    double ejeX;
    double ejeY;

public:
    Punto(double ejeX, double ejeY);

    double getX() const { return ejeX; };
	void setX(double ejeX) {this->ejeX = ejeX; };
	double getY() const { return ejeY; };
	void setY(double ejeY) {this->ejeY = ejeY; };

};

#endif // PUNTO_H
