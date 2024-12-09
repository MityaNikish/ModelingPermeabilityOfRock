/* @mainpage My Personal Index Page
 *
 * @section intro_sec Introduction
 *
 * This is the introduction.
 *
 * @section install_sec Installation
 *
 * @subsection step1 Step 1: Opening the box
 *
 * etc...
 */

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