#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_STORES 5
#define INITIAL_STOCK 500
#define NUM_CUSTOMERS 3
#define MIN_NEED 10000
#define MAX_NEED 12000

int stores[NUM_STORES];
pthread_spinlock_t store_spinlocks[NUM_STORES];

typedef struct {
    int id;
    int need;
} CustomerData;

void* customer(void* arg) {
    CustomerData* data = (CustomerData*) arg;
    int id = data->id;
    int need = data->need;

    while (need > 0) {
        clock_t start = clock();

        int store_index = rand() % NUM_STORES;
        pthread_spin_lock(&store_spinlocks[store_index]);

        int stock = stores[store_index];
        if (stock > 0) {
            int taken = (stock > need) ? need : stock;
            stores[store_index] -= taken;
            need -= taken;

            printf("Я покупатель %d, проснулся, у меня потребность %d, зашел в магазин %d, там было %d товаров, взял %d, теперь у меня потребность %d\n",
                   id, need + taken, store_index, stock, taken, need);
        }

        pthread_spin_unlock(&store_spinlocks[store_index]);

        clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Время выполнения операции покупателем %d: %f секунд\n", id, time_spent);

        if (need > 0) {
            sleep(2);
        }
    }

    printf("Я покупатель %d, моя потребность удовлетворена, завершаю работу\n", id);
    return NULL;
}

void* loader(void* arg) {
    while (1) {
        clock_t start = clock();

        int store_index = rand() % NUM_STORES;
        pthread_spin_lock(&store_spinlocks[store_index]);

        stores[store_index] += 500;
        printf("Я погрузчик, зашел в магазин %d, добавил 500 товаров, теперь там %d товаров\n",
               store_index, stores[store_index]);

        pthread_spin_unlock(&store_spinlocks[store_index]);

        clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Время выполнения операции погрузчиком: %f секунд\n", time_spent);

        sleep(1);
    }
    return NULL;
}

int main() {
    srand(time(NULL));

    for (int i = 0; i < NUM_STORES; i++) {
        stores[i] = INITIAL_STOCK;
        pthread_spin_init(&store_spinlocks[i], PTHREAD_PROCESS_PRIVATE);
    }

    pthread_t customers[NUM_CUSTOMERS];
    CustomerData customer_data[NUM_CUSTOMERS];

    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        customer_data[i].id = i + 1;
        customer_data[i].need = MIN_NEED + rand() % (MAX_NEED - MIN_NEED + 1);
        pthread_create(&customers[i], NULL, customer, &customer_data[i]);
    }

    pthread_t loader_thread;
    pthread_create(&loader_thread, NULL, loader, NULL);

    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        pthread_join(customers[i], NULL);
    }

    pthread_cancel(loader_thread);
    pthread_join(loader_thread, NULL);

    for (int i = 0; i < NUM_STORES; i++) {
        pthread_spin_destroy(&store_spinlocks[i]);
    }

    printf("Все покупатели удовлетворены, программа завершена\n");

    return 0;
}
