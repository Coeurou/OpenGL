//
//  main.cpp
//  RandomWordGenerator
//
//  Created by Guillaume Trollé on 25/11/2014.
//  Copyright (c) 2014 Guillaume Trollé. All rights reserved.
//

#include <iostream>
#include "RandomWordGenerator.h"

int main(int argc, const char * argv[]) {
    std::string nameDatabase = "FrenchName.txt";
    
    Invocat::Tools::RandomWordGenerator rwg( nameDatabase );
    rwg.Init();
    for (int i = 0; i < 31; i++) {
        std::cout << rwg.GenerateWord() << std::endl; // loop infini
    }

    return 0;
}
