#include "gtest/gtest.h"
#include "finanzas.h"

TEST(ComprobarTransaccionTest, FechaValida) {
    EXPECT_TRUE(comprobarTransaccion("15/03/2023", 100.0, "ingreso"));
    EXPECT_FALSE(comprobarTransaccion("31/02/2023", 100.0, "ingreso"));
}

TEST(ComprobarTransaccionTest, ImporteValido) {
    EXPECT_TRUE(comprobarTransaccion("15/03/2023", 500.0, "ingreso"));
    EXPECT_FALSE(comprobarTransaccion("15/03/2023", -10.0, "ingreso"));
    EXPECT_FALSE(comprobarTransaccion("15/03/2023", 150000.0, "ingreso"));

    EXPECT_TRUE(comprobarTransaccion("15/03/2023", 500.0, "egreso"));
    EXPECT_FALSE(comprobarTransaccion("15/03/2023", -10.0, "egreso"));
    EXPECT_FALSE(comprobarTransaccion("15/03/2023", 15000.0, "egreso"));
    
    EXPECT_TRUE(comprobarTransaccion("15/03/2023", 200.0, "transferencia"));
    EXPECT_FALSE(comprobarTransaccion("15/03/2023", -5.0, "transferencia"));
    EXPECT_FALSE(comprobarTransaccion("15/03/2023", 0.0, "transferencia"));
}

TEST(ComprobarTransaccionTest, RangoDeFechas) {
    EXPECT_TRUE(comprobarTransaccion("01/01/2023", 100.0, "ingreso"));
    EXPECT_FALSE(comprobarTransaccion("31/12/1999", 100.0, "ingreso"));
    EXPECT_FALSE(comprobarTransaccion("01/01/2051", 100.0, "ingreso"));
}

TEST(ComprobarTransaccionTest, TipoDeTransaccionValido) {
    EXPECT_TRUE(comprobarTransaccion("15/03/2023", 1000.0, "ingreso"));
    EXPECT_FALSE(comprobarTransaccion("15/03/2023", 60000.0, "ingreso"));  // fuera de rango

    EXPECT_TRUE(comprobarTransaccion("15/03/2023", 8000.0, "egreso"));
    EXPECT_FALSE(comprobarTransaccion("15/03/2023", 15000.0, "egreso"));  // fuera de rango
    
    EXPECT_TRUE(comprobarTransaccion("15/03/2023", 200.0, "transferencia"));
    EXPECT_FALSE(comprobarTransaccion("15/03/2023", -5.0, "transferencia")); // importe negativo
}
