#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

	// Aula 4-6 – Mutex

SemaphoreHandle_t mutexBus;

void writeBus(char *msg){
    printf(msg);
}


void Task1(void * params){
    while(1){
        if(xSemaphoreTake(mutexBus,1000 / portTICK_PERIOD_MS)){
            writeBus("Realizando leitura de temperatura \n");
            xSemaphoreGive(mutexBus);
        }else{
            printf("Timeout na leitura de temporatura  \n");
        }
        vTaskDelay (1000 / portTICK_PERIOD_MS);
    }
}

void Task2(void * params){
    while(1){
        if(xSemaphoreTake(mutexBus,/*1000 / portTICK_PERIOD_MS*/ portMAX_DELAY)){
            writeBus("Realizando leitura de umidade \n");
            xSemaphoreGive(mutexBus);
        }else{
            printf("Timeout na leitura de umidade \n");
        }
        vTaskDelay (1000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    mutexBus = xSemaphoreCreateMutex(); // inicializa o handler
    xTaskCreate(&Task1,"Leitura de temperatura",2048,"Task 1",2,NULL);
    xTaskCreate(&Task2,"Leitura de umidade"    ,2048,"Task 2",2,NULL);
}
