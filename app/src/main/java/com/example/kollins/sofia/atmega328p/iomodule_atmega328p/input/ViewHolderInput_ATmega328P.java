/*
 * Copyright 2018
 * Kollins Lima (kollins.lima@gmail.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.example.kollins.sofia.atmega328p.iomodule_atmega328p.input;

import android.widget.Button;
import android.widget.ImageView;
import android.widget.SeekBar;
import android.widget.Spinner;
import android.widget.TextView;

/**
 * Created by kollins on 3/21/18.
 */

public class ViewHolderInput_ATmega328P {

    Spinner pinSpinner;

    //Digital Pin
    Spinner pinModeSpinner;
    Button pushButton;
    ImageView inputPinState;

    //Analogic Pin
    SeekBar voltageLevel;
    TextView voltageDisplay;

    public ViewHolderInput_ATmega328P(Spinner pinSpinner, Spinner pinModeSpinner, Button pushButton, ImageView inputPinState) {
        this.pinSpinner = pinSpinner;
        this.pinModeSpinner = pinModeSpinner;
        this.pushButton = pushButton;
        this.inputPinState = inputPinState;
    }

    public ViewHolderInput_ATmega328P(Spinner pinSpinner, SeekBar voltageLevel, TextView voltageDisplay) {
        this.pinSpinner = pinSpinner;
        this.voltageLevel = voltageLevel;
        this.voltageDisplay = voltageDisplay;
    }
}
