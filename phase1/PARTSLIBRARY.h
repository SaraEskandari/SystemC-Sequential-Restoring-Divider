

#include <systemc.h>
#pragma once
template <int W = 8>
class Mux2to1 : public sc_module {
public:
    sc_in<sc_logic> sel;
    sc_in<sc_lv<W>> in0, in1;
    sc_out<sc_lv<W>> out;

    SC_CTOR(Mux2to1)
    {
        SC_METHOD(muxing);
        sensitive << in0 << in1 << sel;
    }
    void muxing();

};

template <int N>
class LeftShifter : public sc_module {
public:

    sc_in<sc_lv<N>> in_data;
    sc_in<sc_logic> ser_in;
    sc_out<sc_lv<N>> out_data;

    SC_CTOR(LeftShifter)
    {
       SC_METHOD(shifting);
       sensitive << in_data << ser_in; 
    }
    void shifting();
};

template <int N = 4>
class Counter : public sc_module {
public:

    sc_in<sc_logic> clk, rst;
    sc_in<sc_logic> clr, en;
    sc_out<sc_lv<N>> cnt_out;

    SC_CTOR(Counter)
    {
        SC_METHOD(counting);
        sensitive << rst << clk;
    }
    void counting();
};

template <int W >
class Inverter : public sc_module {
public:
    sc_in<sc_lv<W>> in_data;
    sc_out<sc_lv<W>> out_data;

    SC_CTOR(Inverter) {
        SC_METHOD(inverting);
        sensitive << in_data;
    }
    void inverting();
};

 class XorGate2 : public sc_module {
public:
    sc_in<sc_logic> in1;
    sc_in<sc_logic> in2;
    sc_out<sc_logic> out;

    SC_CTOR(XorGate2) 
    {
        SC_METHOD(evl);
        sensitive << in1 << in2;
    }
    void evl();
};

 class AndGate2 : public sc_module {
public:
    sc_in<sc_logic> in1, in2;
    sc_out<sc_logic> out;
    SC_CTOR(AndGate2) {
        SC_METHOD(evl);
        sensitive << in1 << in2;
    }
    void evl();
};


template <int N>
class DFlipflop : public sc_module {
public:
    sc_in<sc_logic> clk, rst, en;
    sc_in <sc_lv<N>> D;
    sc_out<sc_lv<N>> Q;

    SC_CTOR(DFlipflop) {
        SC_THREAD(evl);
        sensitive << clk << rst;
    }
    void evl();
};


template <int W>
void Mux2to1<W>::muxing() {
    if (sel == '1') out= in1;
    else out=in0;
}

template <int N>
void LeftShifter<N>::shifting()
{
    out_data = (in_data.read().range(N-2, 0), ser_in.read());
}

template <int N>
void Counter<N>::counting()
{
    if (rst == '1')  cnt_out = 0; 
    else if (clk.event() && (clk == '1')) {
        if (clr.read() == '1') cnt_out = 0;
        else if (en == '1') 
            cnt_out = cnt_out.read().to_uint() + 1;
    }
}

template <int W>
void Inverter<W> :: inverting() 
{  
        sc_lv<W> temp = in_data;
        out_data= ~temp;
}


inline void XorGate2 :: evl() 
{
    if ( in1 -> read() == in2 -> read())
        out= sc_logic_0;
    else
        out= sc_logic_1;
}

 inline void AndGate2 :: evl() {
    if ( in1 -> read() == in2 -> read())
        out= sc_logic_1;
    else
        out= sc_logic_0;
  }  
template <int N>
void DFlipflop<N>::evl() { 
        while(true)
        {
            if( rst == sc_logic_1)
              Q= 0;
            else if( (clk -> event()) && (clk=='1'))
              Q= D;
            wait();
        }
  }










