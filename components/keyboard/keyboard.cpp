/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>

#include "keyboard.h"

TaskHandle_t tskKeyboard;
 
KeyboardConfig_t _keyCfg;

BaseType_t keyboard_run(KeyboardConfig_t cfg){
    _keyCfg = cfg;
    adc1_config_width(ADC_WIDTH_12Bit);
    return xTaskCreate(_kbd_run,"Keyboard",512,NULL,10,&tskKeyboard);
}

void _kbd_run(void *param){
    uint8_t c;
    int val;
    for(;;){
        c = 0;
        val = adc1_get_raw(_keyCfg.channel);
        if(val <= 4000){
            vTaskDelay(5 / portTICK_PERIOD_MS);
            val = adc1_get_raw(_keyCfg.channel);
        }else
        {
            vTaskDelay(100 / portTICK_PERIOD_MS);
            continue;
        }      
        if(val == 0){
            c = 1;
        }else if(300 < val && val < 500){
            c = 2;
        }else if(1700 < val && val < 1800){
           c = 3;  
        }else if(1000 < val && val < 1200){
           c = 4;  
        }else if(2400 < val && val < 2800){
           c = 5;  
        }
        if (c !=0){
          xQueueSend(*(_keyCfg.query),&c,portMAX_DELAY);        
        }
        vTaskDelay(_keyCfg.delay / portTICK_PERIOD_MS);
    }
}


