/*
 * This code was imported and modified by our team from https://github.com/MarginallyClever/GcodeCNCDemo/tree/master/GcodeCNCDemo2Axis
*/
#ifndef CONFIG_H
#define CONFIG_H

#define VERSION        (1)  // firmware version
#define BAUD           (57600)  // How fast is the Arduino talking?
#define MAX_BUF        (64)  // What is the longest message Arduino can store?
#define STEPS_PER_TURN (4)  // depends on your stepper motor.  most are 200.
#define MIN_STEP_DELAY (50.0)
#define MAX_FEEDRATE   (1000000.0/MIN_STEP_DELAY)
#define MIN_FEEDRATE   (0.1)

int DELAYvar    =      5;

// for arc directions
#define ARC_CW          (1)
#define ARC_CCW         (-1)
// Arcs are split into many line segments.  How long are the segments?
#define MM_PER_SEGMENT  (0.2)

#endif
