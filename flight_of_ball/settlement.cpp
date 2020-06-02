#include "settlement.h"

#include <math.h>

double f_V_x( double V_x, double k, double m)
{
	return -k/m*V_x;
}

double f_V_y( double V_y, double k, double m, double g)
{
	return -k/m*V_y- g;
}

double f_Vx1( double V_x1, double V_y1, double k, double m)
{
	return -k*V_x1*sqrt(V_x1*V_x1 + V_y1*V_y1)/m;
}

double f_Vy1( double V_x1, double V_y1, double k, double m, double g)
{
	return -k*V_y1*sqrt(V_x1*V_x1 + V_y1*V_y1)/m - g;
}



std::vector<double> create_ser_without_resistance(double V_x, double V_y, double g, double t, double x0, double y0)
{
	std::vector<double> coord (3);
	coord[0] = x0 + V_x*t; //х координата
	coord[1] = - y0 - (V_y*t-g*t*t/2); // у координата
	coord[2] = (V_y - g*t); // скорость по y

	return coord;
}

//std::vector<double> create_numer_approx(const int N, double k, double m, double g,
//										double V_x, double V_y, int i, double x0, double y0)
//{
//	std::vector<double> coord;
//	double t = 0.1;
//	double k1 = 0, k2 = 0, k3 = 0, k4 = 0, l1 = 0, l2 = 0, l3 = 0, l4 = 0;
//	static double *pY = new double [N]; pY[0] = y0;
//	static double *pX = new double [N]; pX[0] = x0;
//	static double *pV_x = new double [N]; pV_x[0] = V_x;		//массив - скорость: проекция на горизонталь
//	static double *pV_y = new double [N]; pV_y[0] = V_y;		//массив - скорость: проекция на вертикаль
//	static double *pV = new double [N]; pV[0] = sqrt(pV_x[0]*pV_x[0] + pV_y[0]*pV_y[0]);


//			k1 = t * f_V_x( pV_x[i-1], k, m);
//			l1 = t * f_V_y( pV_y[i-1], k, m, g);
//			k2 = t * f_V_x( pV_x[i-1] + k1/2, k, m);
//			l2 = t * f_V_y( pV_y[i-1] + l1/2, k, m, g);
//			k3 = t * f_V_x( pV_x[i-1] + k2/2, k, m);
//			l3 = t * f_V_y( pV_y[i-1] + l2/2, k, m, g);
//			k4 = t * f_V_x( pV_x[i-1] + k3, k, m);
//			l4 = t * f_V_y( pV_y[i-1] + l3, k, m, g);


//			// получаем проекции скорости из предварительно полученных приближенных значений
//			pV_x[i] = pV_x[i-1] + (k1+2*k2+2*k3+k4)/6;
//			pV_y[i] = pV_y[i-1] + (l1+2*l2+2*l3+l4)/6;

//			pV[i] = sqrt(pV_x[i]*pV_x[i] + pV_y[i]*pV_y[i]);	//величина вектора скорости из проекций

//			pY[i] =  (pY[i-1]+pV_y[i]*t);
//			pX[i] = pX[i-1]+pV_x[i]*t;	//пересчет координат

//			coord[0] = pX[i];
//			coord[1] = pY[i];
//			coord[2] = pV_y[i];



////	delete [] pY;
////	delete [] pX;
////	delete [] pV_x;
////	delete [] pV_y;
////	delete [] pV;

//	return coord;
//}


std::vector<double> create_relativism(double V_y, double V_x, double m, double k,
									  double g, int N, int j, double x0, double y0)
{
	std::vector<double> coord;

	double t = 0.02;
	double k1 = 0, k2 = 0, k3 = 0, k4 = 0, l1 = 0, l2 = 0, l3 = 0, l4 = 0;
	static double *pY = new double[N]; pY[0] = y0;
	static double *pX = new double[N]; pX[0] = x0;
	static double *pV_x = new double [N]; pV_x[0] = V_x;	//массив - скорость: проекция на горизонталь
	static double *pV_y = new double [N]; pV_y[0] = V_y;	//массив - скорость: проекция на вертикаль
	static double *pV = new double[N]; pV[0] = sqrt(pV_x[0]*pV_x[0] + pV_y[0]*pV_y[0]);


			k1 = t * f_Vx1( pV_y[j-1], pV_x[j-1], k, m);
			l1 = t * f_Vy1( pV_y[j-1], pV_x[j-1], k, m, g);
			k2 = t * f_Vx1( pV_y[j-1] + l1/2, pV_x[j-1]+k1/2, k, m);
			l2 = t * f_Vy1( pV_y[j-1] + l1/2, pV_x[j-1]+k1/2, k, m, g);
			k3 = t * f_Vx1( pV_y[j-1] + l2/2, pV_x[j-1]+k2/2, k, m);
			l3 = t * f_Vy1( pV_y[j-1] + l2/2, pV_x[j-1]+k2/2, k, m, g);
			k4 = t * f_Vx1( pV_y[j-1] + l3, pV_x[j-1]+k3, k, m);
			l4 = t * f_Vy1( pV_y[j-1] + l3, pV_x[j-1]+k3, k, m, g);

			// получаем проекции скорости из предварительно полученных приближенных значений
			pV_x[j] = pV_x[j-1] + (k1+2*k2+2*k3+k4)/6;
			pV_y[j] = pV_y[j-1] + (l1+2*l2+2*l3+l4)/6;

			pV[j] = sqrt(pV_x[j]*pV_x[j] + pV_y[j]*pV_y[j]); //величина вектора скорости из проекций

			pY[j] = pY[j-1] + pV_y[j]*t;
			pX[j] = pX[j-1] + pV_x[j]*t; //пересчет координат

			coord[0] = pX[j];
			coord[1] = pY[j];
			coord[2] = pV_y[j];


//	delete[] pY;
//	delete[] pX;
//	delete[] pV;
//	delete[] pV_x;
//	delete[] pV_y;

	return coord;
}


std::vector<double> create_arbitrary_angle(double &m_p, double k, double &V_xp, double &V_yp,
												 double m_p2, double g, double V_xt, double V_yt,
												 double t_detach, double &x_det, double &y_det, double t, double x0, double y0)
{
	std::vector<double> coord; //поменять как в differ (ты добавляла x0 и y0)

	static bool detached = false;
	double dt = 0;

		coord[0] = x0 + m_p*V_xp/k*(1 - exp(-k*(t-dt)/m_p));
		coord[1] = -(y0 + m_p/k*((V_yp+m_p*g/k)*(1 - exp(-k*(t-dt)/m_p)) - g*(t-dt)));
		coord[2] = V_yp;

		if(t >= t_detach && !detached){
			double V_x0 = V_xp*exp(-k/m_p * t);
			double V_y0 = V_yp*exp(-k/m_p * t) - g*m_p/k*(1 - exp(-k/m_p* t));
			x0 = m_p*V_xp/k*(1-exp(-k*t/m_p));
			y0 = m_p/k*((V_yp+m_p*g/k)*(1 - exp(-k*t/m_p)) - g*t);

			V_xp = (m_p*V_x0 - (m_p - m_p2)*V_xt)/m_p2;
			V_yp = (m_p*V_y0 - (m_p - m_p2)*V_yt)/m_p2;
			m_p = m_p2;
			detached = true;
			dt = t;
		}

	return coord;
}
