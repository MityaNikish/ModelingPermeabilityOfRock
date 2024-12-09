#include "Controller.h"
#include "DiagonalMatrix.h"

int main()
{
    Controller ctrl;
    ctrl.run();

    //DiagonalMatrix mtrx("SLAU_2.raw");
    //mtrx.print();
    //mtrx.write(std::filesystem::current_path() / "matrix_1.raw");

    return 0;
}