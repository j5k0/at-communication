#include "devices/initialization.h"
#include "modem_list.h"

void init_device_functions(int device){
    switch(device){
        case DEVICE_EG06:
            EG06_initialise_commands();
            break;
    }
}