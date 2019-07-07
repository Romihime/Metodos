#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only
#include "catch.hpp"
#include <vector>
#include <iostream>
#include "matrix.h"


bool epsilon_equal(double x, double y) 
{ 
	return fabs(x - y) <= EPS; 
}

using namespace std;

TEST_CASE( "Si creo una Matrix con constructor por defecto", "[Matrix]" ) {
    auto matrix = Matrix(3, 3);

    SECTION("todos sus valores deben ser cero") {
        for (int i = 0; i < 3; ++i)
            for (int j= 0; j < 3; ++j)
                REQUIRE( epsilon_equal(matrix(i, j) , 0) );
    }
}


TEST_CASE( "Si creo una Matrix con un vector de vectores", "[Matrix]" ) {
    SECTION(" y es correcta debe asignar los valores correspondientes") {
        auto matrix = Matrix({
            {1.0, 0.0},
            {0.0, 1.0}
        });
        REQUIRE( epsilon_equal(matrix(0, 0) , (1)) );
        REQUIRE( epsilon_equal(matrix(0, 1) , (0)) );
        REQUIRE( epsilon_equal(matrix(1, 0) , (0)) );
        REQUIRE( epsilon_equal(matrix(1, 1) , (1)) );
    }

}

TEST_CASE( "Si creo una Matrix por copia", "[Matrix]" ) {
    SECTION("debe asignar los mismos valores") {
        Matrix id({
            {1.0, 0.0},
            {0.0, 1.0}
        });

        auto matrix(id);

        REQUIRE( epsilon_equal(matrix(0, 0) , (1)) );
        REQUIRE( epsilon_equal(matrix(0, 1) , (0)) );
        REQUIRE( epsilon_equal(matrix(1, 0) , (0)) );
        REQUIRE( epsilon_equal(matrix(1, 1) , (1)) );
    }
}


TEST_CASE( "Igualdad entre matrices", "[Matrix]" ) {
    Matrix mat1({
        {1.0, 0.0},
        {0.0, 1.0}
    });

    SECTION("de distinta dimensión debe dar falso") {

        Matrix mat2({
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0},
        });

        REQUIRE(!(mat1 == mat2));
    }
}

TEST_CASE( "Asignando un valor", "[Matrix]" ) {
    Matrix mat({
        {1.0, 0.0},
        {0.0, 1.0}
    });

    SECTION("tengo que poder accederlo luego") {
        mat.SetValue(0, 1, 3);

        REQUIRE( epsilon_equal(mat(0, 1) , (3)) );
    }
}

TEST_CASE("Probar esCuadrada", "[Matrix]") {

    SECTION("si la Matrix es cuadrada, debe dar verdadero") {
        Matrix mat({
            {1.0, 0.0},
            {0.0, 0.0}
        });

        REQUIRE( mat.RowCount() == mat.ColCount() );
    }


    SECTION("si la Matrix no es cuadrada, debe dar falso") {
        Matrix mat({
            {1.0, 0.0, 0.0},
            {0.0, 0.0, 1.0}
        });

        REQUIRE( mat.RowCount() != mat.ColCount() );
    }
}

