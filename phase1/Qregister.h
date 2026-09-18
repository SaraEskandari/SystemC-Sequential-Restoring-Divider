#include <systemc.h>

template <int N>
class QRegister : public sc_module {
public:
    sc_in<sc_logic> clk, rst, load, shl, ser_in;
    sc_in<sc_lv<N>> regin;
    sc_out<sc_lv<N>> regout;

    SC_HAS_PROCESS(QRegister);
    QRegister(sc_module_name);

    void registering();
};

template <int N>
QRegister<N>::QRegister(sc_module_name)
{
    SC_METHOD(registering);
    sensitive << clk << rst; 
}

template <int N>
void QRegister<N>::registering()
{
    sc_lv<N> tmp;
    if (rst == '1') 
    {
        
        for (int i = 0; i < N; i++) 
            tmp[i] = sc_logic(0);
        regout = tmp;
    } 
    else if ((clk->event()) && (clk == '1')) {
        if (load == '1')regout = regin; 
        else if (shl == '1') 
            regout = (regout.read().range(N-2, 0), ser_in);
    }
};

