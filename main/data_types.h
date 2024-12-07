#ifndef DATA_TYPES_H_
#define DATA_TYPES_H_

typedef struct {
    float throttle;
    float yaw;
} state_t;

typedef struct {
    char text[200];
    int throttle;
} shared_t;

#endif