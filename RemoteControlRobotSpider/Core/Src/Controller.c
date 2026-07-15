#include <Controller.h>

#define lowerLegBase 0
#define upperLegBase -30.0

I2C_HandleTypeDef *i2c;

uint8_t walkingStage = 0;
uint8_t moveOS = 0;

enum walkType curWalk = Ripple;
enum movement curMovement = Stop;

//void periodicJointyBointy(uint8_t)
//{
//	//TIM16->CNT = 0;
//}

void legsToFloor()
{
	setServoAngle(i2c, 0, -lowerLegBase);
	setServoAngle(i2c, 1, -lowerLegBase);
	setServoAngle(i2c, 2, -lowerLegBase);
	setServoAngle(i2c, 3, lowerLegBase);
	setServoAngle(i2c, 4, lowerLegBase);
	setServoAngle(i2c, 5, lowerLegBase);
	setServoAngle(i2c, 6, upperLegBase);
	setServoAngle(i2c, 7, upperLegBase);
	setServoAngle(i2c, 8, upperLegBase);
	setServoAngle(i2c, 9, -upperLegBase);
	setServoAngle(i2c, 10, -upperLegBase);
	setServoAngle(i2c, 11, -upperLegBase);
}

void init(I2C_HandleTypeDef *hi2c1)
{
	i2c = hi2c1;

	legsToFloor();

	// Hips to Position

	setServoAngle(i2c, 12, -40.0);
	setServoAngle(i2c, 13, 0.0);
	setServoAngle(i2c, 14, 40.0);
	setServoAngle(i2c, 15, 0.0);
	setServoAngle(i2c, 16, -20.0);
	setServoAngle(i2c, 17, -20.0);
}

void stop()
{
	// Legs to floor
	legsToFloor();
	curMovement = Stop;
}

void controllerInput(uint8_t forward, uint8_t rotate)
{
	// SELECT MOVEMENT TYPE (FORWARD/BACKWARD HAS PRECEDENT)

	uint8_t direction;

	if(forward > 200)
	{
		direction = 1;
		curMovement = Walk;
	}
	else if(forward < 50)
	{
		direction = -1;
		curMovement = Walk;
	}
	else if(rotate > 200)
	{
		direction = -1;
		curMovement = Turn;
	}
	else if(rotate < 50)
	{
		direction = 1;
		curMovement = Turn;
	}
	else
	{
		curMovement = Stop;
	}

	// MOVE, BITCH (ENDEARING)

	switch(curMovement)
	{
	case Walk:
		walk(direction);
		break;

	case Turn:
		turn(direction);
		break;

	case Stop:
		stop();
		break;
	}
}

void gaitChange(enum walkType gait)
{
	// IF WE WANT IT TO DYNAMICALLY CHANGE DURING GAIT, IMPLEMENT HERE!!!
	curMovement = Stop;

	// Change gait
	curWalk = gait;

	// MAYBE RETURN TO BASE POSITION (HAVE EACH GAIT START FROM THE SAME BASE POSITION)
}

void walk(uint8_t direction)
{
	switch(curWalk)
	{
	case Tripod:
		//tripodWalk(direction);
		break;

	case Ripple:
		rippleWalk(direction);
		break;

	case Bipod:
		//bipodWalk(direction);
		break;
	}
}

void turn(uint8_t direction)
{
	switch(curWalk)
	{
	case Tripod:
		//tripodTurn(direction);
		break;

	case Ripple:
		rippleTurn(direction);
		break;

	case Bipod:
		//bipodTurn(direction);
		break;
	}
}


