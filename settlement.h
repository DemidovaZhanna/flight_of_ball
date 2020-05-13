#ifndef SETTLEMENT_H
#define SETTLEMENT_H

#include <QMainWindow>

std::pair<double, double> create_ser_without_resistance (double V_x, double V_y, double g, double t, double x0, double y0); //без сопротивления
std::pair<double, double> create_numer_approx (const int N, double k, double m, double g,
											   double V_x, double V_y, int i);   //с учетом сопротивления (численное приближение)
std::pair<double, double> create_relativism (double V_y, double V_x,
											  double m, double k, double g, int N, int i);
std::pair<double, double> create_arbitrary_angle (double &m_p, double k, double &V_xp,
												  double &V_yp, double m_p2, double g, double V_xt, double V_yt,
												  double t_detach, double &x0, double &y0, double t); //резкое изменение массы

#endif // SETTLEMENT_H
