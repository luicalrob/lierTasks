#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>

#include "finanzas.h"

bool esFechaValida(const std::string& fecha) {
    std::tm tm = {};
    std::istringstream ss(fecha);
    return (ss >> std::get_time(&tm, "%d/%m/%Y")) && (ss.eof());
}


bool comprobarTransaccion(const std::string& fecha, double importe, const std::string& tipoTransaccion) {
    if (tipoTransaccion == "ingreso" && (importe <= 0.0 || importe > 50000.0)) {
        std::cerr << "Importe fuera de rango para ingreso (0, 50000): " << importe << " euros\n";
        return false;
    }
    if (tipoTransaccion == "egreso" && (importe < 1.0 || importe > 10000.0)) {
        std::cerr << "Importe fuera de rango para egreso (1, 10000): " << importe << " euros\n";
        return false;
    }
    if (tipoTransaccion == "transferencia" && importe <= 0.0) {
        std::cerr << "El importe de una transferencia debe ser mayor que 0: " << importe << " euros\n";
        return false;
    }

    if (!esFechaValida(fecha)) {
        std::cerr << "Fecha no válida: " << fecha << "\n";
        return false;
    }

    std::tm fechaTransaccion = {};
    std::istringstream ss(fecha);
    ss >> std::get_time(&fechaTransaccion, "%d/%m/%Y");

    std::tm fechaMin = {};
    std::tm fechaMax = {};
    std::istringstream("01/01/2000") >> std::get_time(&fechaMin, "%d/%m/%Y");
    std::istringstream("31/12/2050") >> std::get_time(&fechaMax, "%d/%m/%Y");

    time_t tiempoTransaccion = std::mktime(&fechaTransaccion);
    time_t tiempoMin = std::mktime(&fechaMin);
    time_t tiempoMax = std::mktime(&fechaMax);

    if (tiempoTransaccion < tiempoMin || tiempoTransaccion > tiempoMax) {
        std::cerr << "Fecha fuera de rango permitido: " << fecha << "\n";
        return false;
    }

    return true;
}