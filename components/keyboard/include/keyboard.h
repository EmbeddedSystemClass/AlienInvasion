
/* 
 * File:   keyboard.h
 * Author: Kuranov Dmitry
 * 
 * Keyes_AD_Key Keyboard driver
 *
 * Created on 28 октября 2018 г., 17:14
 */

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/adc.h"

/**
 keyboard task for reference
 */
extern TaskHandle_t tskKeyboard;

typedef struct {
    QueueHandle_t* query;
    adc1_channel_t channel;  
    uint16_t delay;
} KeyboardConfig_t;

/*
 * main keyboard task
 */
void _kbd_run(void *param);
/**
 construct keyboard task and run it
 */
BaseType_t keyboard_run(KeyboardConfig_t cfg);


#endif /* KEYBOARD_H */

