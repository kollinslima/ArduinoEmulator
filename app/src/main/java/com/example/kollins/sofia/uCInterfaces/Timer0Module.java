package com.example.kollins.sofia.uCInterfaces;

public interface Timer0Module extends Runnable {

    int NO_CLOCK_SOURCE                 = 0;
    int CLOCK_PRESCALER_1               = 1;
    int CLOCK_PRESCALER_8               = 2;
    int CLOCK_PRESCALER_64              = 3;
    int CLOCK_PRESCALER_256             = 4;
    int CLOCK_PRESCALER_1024            = 5;
    int EXTERNAL_CLOCK_T0_FALLING_EDGE  = 6;
    int EXTERNAL_CLOCK_T0_RISING_EDGE   = 7;

    void clockTimer0();
}