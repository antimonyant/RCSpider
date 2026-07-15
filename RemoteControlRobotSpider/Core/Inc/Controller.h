#pragma once

#include <PCA9685.h>

enum walkType
{
	Tripod = 0,
	Ripple,
	Bipod
};

enum movement
{
	Walk = 0,
	Turn,
	Stop
};

extern I2C_HandleTypeDef *i2c;

extern uint8_t walkingStage;
extern uint8_t moveOS;

#define counterVal (30)

//void periodicJointyBointy(uint8_t );

void legsToFloor();

void init(I2C_HandleTypeDef *hi2c1);

void stop();

void controllerInput(uint8_t forward, uint8_t turn);

void gaitChange(enum walkType gait);

void walk(uint8_t direction); // Positive is forward

void turn(uint8_t direction);  // Positive is ccw

void tripodWalk(uint8_t direction);
void tripodTurn(uint8_t direction);

void rippleWalk(uint8_t direction);
void rippleTurn(uint8_t direction);

void bipodWalk(uint8_t direction);
void bipodTurn(uint8_t direction);


