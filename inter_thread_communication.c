/*
 Name        : inter_thread_communication.c
 Author      : Abdurrahman Nurhakim
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Simple communication between thread in c
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 10

// Buffer untuk berbagi pesan antara thread
char buffer[BUFFER_SIZE];
int buffer_index = 0;

// Mutex untuk mengamankan akses ke buffer
pthread_mutex_t buffer_mutex = PTHREAD_MUTEX_INITIALIZER;

// Fungsi yang akan dijalankan oleh thread pengirim
void *sender_thread(void *arg) {
    const char *message = "Hello, Thread!";
    
    // Mengunci mutex sebelum menulis ke buffer
    pthread_mutex_lock(&buffer_mutex);
    
    // Menyalin pesan ke buffer
    for (int i = 0; message[i] != '\0'; i++) {
        buffer[buffer_index++] = message[i];
    }
    
    // Membuka kunci mutex setelah selesai menulis
    pthread_mutex_unlock(&buffer_mutex);
    
    pthread_exit(NULL);
}

// Fungsi yang akan dijalankan oleh thread penerima
void *receiver_thread(void *arg) {
    // Menunggu sedikit sebelum membaca dari buffer
    // untuk memberi waktu sender_thread menulis pesan
    usleep(1000);
    
    // Mengunci mutex sebelum membaca dari buffer
    pthread_mutex_lock(&buffer_mutex);
    
    // Membaca dan mencetak pesan dari buffer
    for (int i = 0; i < buffer_index; i++) {
        putchar(buffer[i]);
    }
    putchar('\n');
    
    // Membuka kunci mutex setelah selesai membaca
    pthread_mutex_unlock(&buffer_mutex);
    
    pthread_exit(NULL);
}

int main() {
    pthread_t sender, receiver;
    
    // Membuat thread pengirim dan penerima
    pthread_create(&sender, NULL, sender_thread, NULL);
    pthread_create(&receiver, NULL, receiver_thread, NULL);
    
    // Menunggu kedua thread selesai
    pthread_join(sender, NULL);
    pthread_join(receiver, NULL);
    
    return 0;
}
