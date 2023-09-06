//
//  Cash.hpp
//  GestioneElettrodomestici
//
//  Created by Filippo Bianco on 18/01/2020.
//  Copyright © 2020 Filippo Bianco. All rights reserved.
//	mat:1187400

#ifndef Cash_h
#define Cash_h

#include "Orders.h"

class Cash {

    double available_cash = 0.0;
    
public:
    
    Cash(); //inizializzatore di default che legge la cassa disponibile dal file.
    void add_cash(double c) { available_cash += c; }
    void pay_order(Order o);
    double get_cash() const { return available_cash; }
    
    bool can_afford(Order o) const;
    
};


#endif /* Cash_h */
