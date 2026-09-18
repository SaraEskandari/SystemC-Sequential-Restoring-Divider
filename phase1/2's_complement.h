#include <systemc.h>
#include "Adder.h"
#include "PARTSLIBRARY.h" 

template <int T>
SC_MODULE(TwosComplement) {
    sc_in<sc_lv<T>> in_data;
    sc_out<sc_lv<T>> out_data;

    sc_signal<sc_lv<T>> inverted_data;
    sc_signal<sc_lv<T>> constant_one;

    Inverter<T>* inverter;
    Adder<T>* adder;

    SC_CTOR(TwosComplement) {
        SC_METHOD(drive_constant);
   
        inverter = new Inverter<T>("Inverter");
        inverter->in_data(in_data);
        inverter->out_data(inverted_data);

        adder = new Adder<T>("TwosComp_Adder");
        adder->in1(inverted_data);
        adder->in2(constant_one);
        adder->out(out_data);
    }

    void drive_constant() 
    {
        sc_lv<T> one_val = 1; 
        constant_one= one_val;
    }
};
