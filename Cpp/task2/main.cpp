
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>

#include "finanzas.h"

int main() {
    std::string fecha = "15/08/2025";
    double importe = 10000;
    std::string tipoTransaccion = "ingreso";

    if (comprobarTransaccion(fecha, importe, tipoTransaccion)) {
        std::cout << "Transacción válida.\n";
    } else {
        std::cout << "Transacción inválida.\n";
    }

    return 0;
}