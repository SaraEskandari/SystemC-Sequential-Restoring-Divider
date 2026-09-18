#include <systemc.h>

template <int T> 
SC_MODULE (Adder) {
    sc_in<sc_lv<T>> in1, in2;
    sc_out<sc_lv<T>> out;

    SC_CTOR(Adder) {
        SC_METHOD(Adding);
        sensitive << in1 << in2;
    }

    void Adding() {
        sc_lv<T> vout;
        vout = (sc_uint<T>) in1.read() + (sc_uint<T>) in2.read();
        out= vout;
    }
};