//
//  main.cpp
//  Bilinear_Interpolation
//
//  Created by  Maulik Patel on 18/07/2020.
//  Copyright © 2020 Maulik Patel. All rights reserved.
//
#include <cstdlib>
#include "Matrix.h"
#include "Display.h"


void Usage(){
    std::cout << "  \
     The program should be invoked by the following command line:       \n   \
    C:>ramp.exe display tl tr [bl] [br]                                \n   \
    where                                                              \n   \
    •    display is the name of the display device                     \n   \
    •    tl is the top left colour value                               \n   \
    •    tr is the top right colour value                              \n   \
    •    bl is the bottom left colour value [optional, defaults to tl] \n   \
    •    br is the bottom right colour value [optional, defaults to tr] " << std::endl;
}

void RunFunction ( uint16_t tl, uint16_t tr, uint16_t bl, uint16_t br ){
    Matrix m2{"GUI"};
    m2.setCornerValues(tl, tr, bl, br);
    m2.performBilinearInterpolation();
    m2.print();
    
}

int main(int argc, const char * argv[]) {
   if (argc < 4)
   {
       std::cout << "    There are " << argc << " input arguments:\n";
       Usage();
       std::exit(1);
   }
   else{
       uint16_t tl, tr, bl, br;
//       std::cout << argv[1] << "," << argv[2] << "," << argv[3] << ","<< argv[4] << '\n';
       if (argc == 4){
                tl = std::stoi(argv[2]);
                tr = std::stoi(argv[3]);
                bl = tl;
                br = tr;
        }
        else if (argc == 5){
                tl = std::stoi(argv[2]);
                tr = std::stoi(argv[3]);
                bl = std::stoi(argv[4]);
                br = tr;
        }
        else if (argc == 6){
               tl = std::stoi(argv[2]);
               tr = std::stoi(argv[3]);
               bl = std::stoi(argv[4]);
               br = std::stoi(argv[5]);
        }
        else
        {
           std::cout << "       There are " << argc << " input arguments:\n";
           Usage();
           std::exit(1);
        }
//        std::cout << tl << "," << tr << "," << bl << ","<< br << '\n';
        RunFunction( tl, tr, bl, br );
        return 0;
   }
}
