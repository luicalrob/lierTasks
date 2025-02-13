#ifndef finanzas_H
#define finanzas_H

#include <string>

bool comprobarTransaccion(const std::string& fecha, double importe, const std::string& tipoTransaccion);
bool esFechaValida(const std::string& fecha);

#endif // finanzas_H
