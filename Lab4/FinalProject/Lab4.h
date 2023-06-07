#ifndef LAB4_H
#define LAB4_H

#include <Arduino_FreeRTOS.h>
#include <LiquidCrystal.h>
#include <arduinoFFT.h>
// #include <ChatGPT.hpp>

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

#define PIN12 12
#define PIN11 11
#define PIN10 10
#define PIN9 9
#define PIN8 8
#define PIN7 7
#define PIN6 6
#define PIN5 5

#define XVALUEPIN A0
#define YVALUEPIN A1



char* adjectives[91] = {
    "Adventurous ", "Amazing ", "Amiable ", "Awesome ", "Balanced ", "Blissful ", "Brilliant ", "Caring ", "Cheerful ", "Creative ", "Dazzling ", "Delightful ", "Dynamic ", "Eager ", "Effervescent ", "Enthusiastic ", "Faithful ", "Fearless ", "Friendly ", "Fulfilled ", "Gentle ", "Genuine ", "Gracious ", "Grateful ", "Happy ", "Harmonious ", "Heartfelt ", "Innovative ", "Inspiring ", "Jolly ", "Joyful ", "Joyous ", "Jubilant ", "Keen ", "Kind ", "Kindhearted ", "Kindred ", "Liberal ", "Lively ", "Loving ", "Lucky ", "Magnificent ", "Modest ", "Motivating ", "Motivated ", "Natural ", "Nifty ", "Noble ", "Nurturing ", "Optimal ", "Optimistic ", "Original ", "Passionate ", "Patient ", "Peaceful ", "Positive ", "Quaint ", "Quick ", "Quick-witted ", "Quirky ", "Radiant ", "Rejuvenating ", "Reliable ", "Resilient ", "Satisfied ", "Sincere ", "Spirited ", "Sunny ", "Talented ", "Thoughtful ", "Thriving ", "Tranquil ", "Understanding ", "Unstoppable ", "Upbeat ", "Upstanding ", "Valuable ", "Versatile ", "Vibrant ", "Vivacious ", "Wholesome ", "Wise ", "Wonderful ", "Wondrous ", "Xenial ", "Xtraordinary ", "Yearning ", "Youthful ", "Zealotic ", "Zealous ", "Zestful "
};

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



#endif