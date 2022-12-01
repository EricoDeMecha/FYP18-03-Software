//
// Created by erico on 9/23/22.
//
#include "LA_T8.h"

LA_T8::LA_T8(PinName in1, PinName in2): _in1(in1, 0),
                                        _in2(in2, 1){}

void LA_T8::operate(bool switch_val) {
    _switch_val = switch_val;
    if(switch_val){
        _in1 = 1;
        _in2 = 0;
    }else{
        _in1 = 0;
        _in2 = 1;
    }
}
