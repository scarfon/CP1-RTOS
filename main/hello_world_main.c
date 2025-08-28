#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
              
static SemaphoreHandle_t xBinarySemaphore1;
static SemaphoreHandle_t xBinarySemaphore2;
static SemaphoreHandle_t xBinarySemaphore3;


void Task1(void *param)
{
    while (1)
    {
        if (xSemaphoreTake(xBinarySemaphore1, portMAX_DELAY))
        {
            printf("[Tarefa 1] Executou - Andres Arboleda\n");
            vTaskDelay(pdMS_TO_TICKS(1000));
            xSemaphoreGive(xBinarySemaphore2);
        }
    }
}
void Task2(void *param)
{
    while (1)
    {
        if (xSemaphoreTake(xBinarySemaphore2, portMAX_DELAY))
        {
            printf("[Tarefa 2] Executou - Andres Arboleda\n");
            vTaskDelay(pdMS_TO_TICKS(1000));
            xSemaphoreGive(xBinarySemaphore3);
            
        }
    }
}

void Task3(void *param)
{
    while (1)
    {
        if (xSemaphoreTake(xBinarySemaphore3, portMAX_DELAY))
        {
            printf("[Tarefa 3] Executou - Andres Arboleda\n");
            vTaskDelay(pdMS_TO_TICKS(1000));
            xSemaphoreGive(xBinarySemaphore1);
        }
    }
}

void app_main(void)
{

    // 3 semaforos
    xBinarySemaphore1 = xSemaphoreCreateBinary(); // Cria um semáforo binário

    if (xBinarySemaphore1 == NULL)
    {
        printf("Falha ao criar semáforo binário\n");
        return;
    }
    xBinarySemaphore2 = xSemaphoreCreateBinary(); // Cria um semáforo binário

    if (xBinarySemaphore2 == NULL)
    {
        printf("Falha ao criar semáforo binário\n");
        return;
    }
    
    xBinarySemaphore3 = xSemaphoreCreateBinary(); // Cria um semáforo binário

    if (xBinarySemaphore3 == NULL)
    {
        printf("Falha ao criar semáforo binário\n");
        return;
    }

    // 3 Task
    xTaskCreate(Task1,   // Função da task
                "Task1", // Nome da task
                2048,    // Stack size em bytes
                NULL,    // Parâmetros da task
                5,       // Prioridade da task
                NULL /* Handle da task (opcional) */);
    xTaskCreate(Task2,   // Função da task
                "Task2", // Nome da task
                2048,    // Stack size em bytes
                NULL,    // Parâmetros da task
                5,       // Prioridade da task
                NULL /* Handle da task (opcional) */);
    xTaskCreate(Task3,   // Função da task
                "Task3", // Nome da task
                2048,    // Stack size em bytes
                NULL,    // Parâmetros da task
                5,       // Prioridade da task
                NULL /* Handle da task (opcional) */);
    
    xSemaphoreGive(xBinarySemaphore1);
}