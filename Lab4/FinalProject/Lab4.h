// Include block to make sure that code isnt being defined more
// than once
#ifndef LAB4_H
#define LAB4_H

// Include all necessary header files
#include <Arduino_FreeRTOS.h>
#include <LiquidCrystal.h>
#include <arduinoFFT.h>

// Pin definitions for code clarity
// pins 31 - 22, used for the LCD
#define PIN31 31
#define PIN30 30
#define PIN29 29
#define PIN28 28
#define PIN27 27
#define PIN26 26
#define PIN25 25
#define PIN24 24
#define PIN23 23
#define PIN22 22

// Pins 12 - 8 used for the LEDs
#define PIN12 12
#define PIN11 11
#define PIN10 10
#define PIN9 9
#define PIN8 8

// Pins A0 and A1, used with the joystick
#define XVALUEPIN A0
#define YVALUEPIN A1

// String definitions used for string generation, these ones are not formatted for the LCD and are used exclusively
// in the generation of the string
char* adjectives[91] = {
    "Adventurous ", "Amazing ", "Amiable ", "Awesome ", "Balanced ", "Blissful ", "Brilliant ", "Caring ", "Cheerful ", "Creative ", "Dazzling ", "Delightful ", "Dynamic ", "Eager ", "Effervescent ", "Enthusiastic ", "Faithful ", "Fearless ", "Friendly ", "Fulfilled ", "Gentle ", "Genuine ", "Gracious ", "Grateful ", "Happy ", "Harmonious ", "Heartfelt ", "Innovative ", "Inspiring ", "Jolly ", "Joyful ", "Joyous ", "Jubilant ", "Keen ", "Kind ", "Kindhearted ", "Kindred ", "Liberal ", "Lively ", "Loving ", "Lucky ", "Magnificent ", "Modest ", "Motivating ", "Motivated ", "Natural ", "Nifty ", "Noble ", "Nurturing ", "Optimal ", "Optimistic ", "Original ", "Passionate ", "Patient ", "Peaceful ", "Positive ", "Quaint ", "Quick ", "Quick-witted ", "Quirky ", "Radiant ", "Rejuvenating ", "Reliable ", "Resilient ", "Satisfied ", "Sincere ", "Spirited ", "Sunny ", "Talented ", "Thoughtful ", "Thriving ", "Tranquil ", "Understanding ", "Unstoppable ", "Upbeat ", "Upstanding ", "Valuable ", "Versatile ", "Vibrant ", "Vivacious ", "Wholesome ", "Wise ", "Wonderful ", "Wondrous ", "Xenial ", "Xtraordinary ", "Yearning ", "Youthful ", "Zealotic ", "Zealous ", "Zestful "
};

// String definitions used for the LCD, these ones are padded to length 16 for use in the LCD
char* adjectives_lcd[91] = {
    "Adventurous    ",
"Amazing        ",
"Amiable        ",
"Awesome        ",
"Balanced       ",
"Blissful       ",
"Brilliant      ",
"Caring         ",
"Cheerful       ",
"Creative       ",
"Dazzling       ",
"Delightful     ",
"Dynamic        ",
"Eager          ",
"Effervescent   ",
"Enthusiastic   ",
"Faithful       ",
"Fearless       ",
"Friendly       ",
"Fulfilled      ",
"Gentle         ",
"Genuine        ",
"Gracious       ",
"Grateful       ",
"Happy          ",
"Harmonious     ",
"Heartfelt      ",
"Innovative     ",
"Inspiring      ",
"Jolly          ",
"Joyful         ",
"Joyous         ",
"Jubilant       ",
"Keen           ",
"Kind           ",
"Kindhearted    ",
"Kindred        ",
"Liberal        ",
"Lively         ",
"Loving         ",
"Lucky          ",
"Magnificent    ",
"Modest         ",
"Motivating     ",
"Motivated      ",
"Natural        ",
"Nifty          ",
"Noble          ",
"Nurturing      ",
"Optimal        ",
"Optimistic     ",
"Original       ",
"Passionate     ",
"Patient        ",
"Peaceful       ",
"Positive       ",
"Quaint         ",
"Quick          ",
"Quick-witted   ",
"Quirky         ",
"Radiant        ",
"Rejuvenating   ",
"Reliable       ",
"Resilient      ",
"Satisfied      ",
"Sincere        ",
"Spirited       ",
"Sunny          ",
"Talented       ",
"Thoughtful     ",
"Thriving       ",
"Tranquil       ",
"Understanding  ",
"Unstoppable    ",
"Upbeat         ",
"Upstanding     ",
"Valuable       ",
"Versatile      ",
"Vibrant        ",
"Vivacious      ",
"Wholesome      ",
"Wise           ",
"Wonderful      ",
"Wondrous       ",
"Xenial         ",
"Xtraordinary   ",
"Yearning       ",
"Youthful       ",
"Zealotic       ",
"Zealous        ",
"Zestful        "
};

// end include block
#endif