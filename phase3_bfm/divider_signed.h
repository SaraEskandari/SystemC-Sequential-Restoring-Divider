#include <iostream>
#include <systemc.h>

template <int W, int NumClk>
SC_MODULE(divider) 
{
    sc_in<sc_lv<W>>  Dividend,Divisor;     
    sc_in<sc_logic>  clk, rst, start;  
    
    sc_out<sc_lv<W>> Quotient, Remainder ;    
    sc_out<sc_logic> ready; 

    SC_CTOR(divider) 
    {
        SC_THREAD(operation);
        sensitive << clk << rst;
    }
     void operation() ;
};


template <int W, int NumClk>
    void divider<W, NumClk> :: operation() 
    {
        sc_int<W> Q_var;

        while (true) 
        {
            if (rst == SC_LOGIC_1) 
            {
                ready= SC_LOGIC_0;
                Quotient= 0;
                Remainder = 0;
            }
            else if ((clk == '1') && (clk->event()) )
            {
                if (start == '1') 
                {
                    ready= SC_LOGIC_0;

                    sc_lv<W> unknown_val;
                    for(int k=0; k<W; k++) unknown_val[k] = SC_LOGIC_X;
                    Quotient= unknown_val;
                    Remainder= unknown_val;

                    // Mimicking hardware clock cycles delay
                    for (int i = 0; i < NumClk; i++) 
                        wait(clk->posedge_event());

                    ready= SC_LOGIC_1;


                    if (Divisor.read() != 0) {
                      
                    Q_var = sc_int<W>(Dividend.read()) / sc_int<W>(Divisor.read());
                    Quotient=  Q_var;
                    Remainder = sc_int<W>(Dividend.read()) - (sc_int<W>(Divisor.read()) * Q_var);

                    } 
                    else {
                        Q_var = 0;
                        Quotient = Q_var;
                        Remainder = sc_int<W>(Dividend.read()) - (sc_int<W>(Divisor.read()) * Q_var);
                    }


                }
            }
            wait();
        }
    };

