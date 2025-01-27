#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "server.h"
#include "packets.h"

#define MAX_BINS 1000000
#define UPDATE_TIME 0

typedef enum Bin_type{
    BIN_BIODEGRADABLE_WASTE,
    BIN_NON_BIODEGRADABLE_WASTE,
    BIN_METALIC_WASTE,
    BIN_MEDICAL_WASTE,
    BIN_ELECTRONIC_WASTE,
    BIN_MIXED,
}Bin_type;

typedef struct Bin{
    unsigned long long id;  //8
    Bin_type type;          //4
    float fill_level;       //4
    float temp;             //4
    float humidity;         //4
}Bin;

static Bin *bins[MAX_BINS];
static unsigned long long index = 0;

Bin *make_bin_by_type(Bin_type type)
{
    static unsigned long long bin_id = 1; 

    Bin *temp = (Bin*)malloc(sizeof(Bin));
    temp->id = bin_id++;
    temp->type = type;
    temp->fill_level = 0.0;
    temp->temp = 32.0;
    temp->humidity = 90;
    return temp;
}

Bin *make_bin()
{
    return make_bin_by_type(BIN_MIXED);
}

void add_bin(Bin *bin)
{
    if(index >= MAX_BINS){
        perror("Bin array Overflow, cannot add more bins.\n");
        exit(1);
    }
    bins[index++] = bin;
}

void set_bin_level(float level,unsigned long long id){
    if((id<0)||(id>=index)){
        perror("Bin does not exist, cannnot set level.\n");
        exit(1);
    }
    bins[id]->fill_level = level;
}

char *get_bin_type_string(Bin_type type){

    switch (type)
    {
        case BIN_BIODEGRADABLE_WASTE: return "BIN_BIODEGRADABLE_WASTE";
        case BIN_NON_BIODEGRADABLE_WASTE: return "BIN_NON_BIODEGRADABLE_WASTE";
        case BIN_METALIC_WASTE: return "BIN_METALIC_WASTE";
        case BIN_MEDICAL_WASTE: return "BIN_MEDICAL_WASTE";
        case BIN_ELECTRONIC_WASTE: return "BIN_ELECTRONIC_WASTE";
        case BIN_MIXED: return "BIN_MIXED_WASTE";
        default:
            perror("Bin type does not exsist\n");
            exit(1);
    }
}

void show_bins()
{
    for(unsigned long long i=0;i<index;i++){
        printf("Bin ID: %u , Type: %s , Fill level: %.1f , Temp: %.1f, Humidity: %.1f\n",
                bins[i]->id,
                get_bin_type_string(bins[i]->type),
                bins[i]->fill_level,
                bins[i]->temp,
                bins[i]->temp);
    }
}

void update_bin(Packet *packet)
{
    if((packet->id>index) || (packet->id<1)){
        printf("Incorrect id in packet, cannot update.\n");
        printf("Id : %u \n",packet->id);
        return;
    }
    bins[packet->id-1]->fill_level = packet->fill_level;
    bins[packet->id-1]->temp = packet->temp;
    bins[packet->id-1]->humidity = packet->humidity;
}

void *server_update(void *arg)
{
    time_t start_time,current_time;
    time(&start_time);

    Packet packet = {0};

    while(1){
        time(&current_time);
        if((current_time-start_time)<UPDATE_TIME){
            continue;
        }
        get_Packet(&packet);
        printf("Packet fetched.\n");
        update_bin(&packet);
        show_bins();
        
        start_time = current_time;
    }
    return NULL;
}

int main()
{
    server_init();

    for(int i=0;i<10;i++){
        add_bin(make_bin());
    }
    show_bins();
    
    pthread_t update_thread;
    if(pthread_create(&update_thread,NULL,&server_update,NULL)!=0){
        printf("Failed to create thread.\n");
        exit(1);
    }
    pthread_join(update_thread,NULL);

    server_close();
    
    return 0;
}