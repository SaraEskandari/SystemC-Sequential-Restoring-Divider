#include <systemc.h>


template <int T> 
SC_MODULE (Subtractor){

    sc_in < sc_lv<T> > in1, in2;
    sc_out < sc_lv<T> > out;
    sc_out < sc_logic > signbit;

    SC_CTOR (Subtractor)
    {
        SC_METHOD(Subtracting);
        sensitive << in1 << in2;
    }

    void Subtracting()
    {
      
        sc_int<T+1> diff;
        sc_lv<T> vout;
        sc_logic vsign;

        diff = (sc_uint<T>) in1 - (sc_uint<T>) in2;
        vout = diff.range(T-1, 0);

        if (diff < 0) 
            vsign = SC_LOGIC_1;
        else 
            vsign = SC_LOGIC_0;

        out = vout;
        signbit = vsign;
    }
};
