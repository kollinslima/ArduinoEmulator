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

package com.example.kollins.sofia.ucinterfaces;

public interface Timer2Module extends Runnable {

    int NO_CLOCK_SOURCE                 = 0;
    int CLOCK_PRESCALER_1               = 1;
    int CLOCK_PRESCALER_8               = 2;
    int CLOCK_PRESCALER_32              = 3;
    int CLOCK_PRESCALER_64              = 4;
    int CLOCK_PRESCALER_128             = 5;
    int CLOCK_PRESCALER_256             = 6;
    int CLOCK_PRESCALER_1024            = 7;

    void clockTimer2();
}
