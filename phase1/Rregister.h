#include <systemc.h>

template <int N>
class RRegister : public sc_module {
public:
    sc_in<sc_logic> clk, rst, init, load;
    sc_in<sc_lv<N>> regin;
    sc_out<sc_lv<N>> regout;

    SC_HAS_PROCESS(RRegister);
    RRegister(sc_module_name);

    void registering();
};

template <int N>
RRegister<N>::RRegister(sc_module_name)
{
    SC_METHOD(registering);
    sensitive << clk << rst; 
}

template <int N>
void RRegister<N>::registering()
{
    sc_lv<N> tmp;
    if (rst == '1') 
    {
        for (int i = 0; i < N; i++) 
            tmp[i] = sc_logic(0);
        regout = tmp;
    } 
    else if ((clk->event()) && (clk == '1')) 
    {
        if (init == '1')
        {
            for (int i = 0; i < N; i++) 
                tmp[i] = sc_logic(0);
            regout = tmp;
        }
        else if (load == '1')
            regout = regin; 
    }
};
