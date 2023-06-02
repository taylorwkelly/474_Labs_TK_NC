/* University of Washington
 * ECE/CSE 474,  05/26/2023
 *
 *   Noah Crouch
 *   Taylor Kelly
 *
 *   Lab 3: Schedulers
 *
 */

#include "Lab3_DDS.h";

#define DEAD 4

typedef struct Task {
    unsigned int id;
    char* name;
    unsigned int timesStarted_Restarted;
} Task;

typedef struct TCB {
    Task task;
    void (*fn) ();    // function pointer
    void *arg_ptr;    // arg pointer
    unsigned int status;
    unsigned int delay;
} TCB;
