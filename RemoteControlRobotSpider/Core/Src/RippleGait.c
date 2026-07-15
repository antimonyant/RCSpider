#include <Controller.h>

extern I2C_HandleTypeDef *i2c;

extern uint8_t walkingStage;
extern uint8_t moveOS;

void rippleWalk(uint8_t direction)
{
	if(walkingStage == 0)
		{
			if(!moveOS)
			{
				// Lifted Leg Hip
				setServoAngle(i2c, 12, 0.0);
				setServoAngle(i2c, 15, -40.0);

				// Dropped Leg Hip
				setServoAngle(i2c, 13, -20.0);
				setServoAngle(i2c, 14, 20.0);
				setServoAngle(i2c, 16, 0.0);
				setServoAngle(i2c, 17, 20.0);

				TIM16->CNT = 0;
				moveOS = 1;
			}

			if(TIM16->CNT > counterVal/2)
			{
				// Drop Legs
				setServoAngle(i2c, 6, -30.0);
				setServoAngle(i2c, 9, 30.0);

				setServoAngle(i2c, 0, 0.0);
				setServoAngle(i2c, 3, 0.0);
			}
			else
			{
				// Lift Legs
				setServoAngle(i2c, 6, 0.0);
				setServoAngle(i2c, 9, 0.0);

				setServoAngle(i2c, 0, 30.0);;
				setServoAngle(i2c, 3, -30.0);
			}

			if(TIM16->CNT > counterVal)
			{
				moveOS = 0;
				walkingStage = 1;
			}
		}
		else if(walkingStage == 1)
		{
		if(!moveOS)
		{
			// Lifted Leg Hip
			setServoAngle(i2c, 13, 20.0);
			setServoAngle(i2c, 17, 0.0);

			// Dropped Leg Hip
			setServoAngle(i2c, 12, -20.0);
			setServoAngle(i2c, 14, 0.0);
			setServoAngle(i2c, 15, -20.0);
			setServoAngle(i2c, 16, 20.0);

			TIM16->CNT = 0;
			moveOS = 1;
		}

		if(TIM16->CNT > counterVal/2)
		{
			// Drop Legs
			setServoAngle(i2c, 7, -30.0);
			setServoAngle(i2c, 11, 30.0);

			setServoAngle(i2c, 1, 0.0);
			setServoAngle(i2c, 5, 0.0);
		}
		else
		{
			// Lift Legs
			setServoAngle(i2c, 7, 0.0);
			setServoAngle(i2c, 11, 0.0);

			setServoAngle(i2c, 1, 30.0);;
			setServoAngle(i2c, 5, -30.0);
		}

		if(TIM16->CNT > counterVal)
		{
			moveOS = 0;
			walkingStage = 2;
		}
	}
	else
	{
		if(!moveOS)
		{
			// Lifted Leg Hip
			setServoAngle(i2c, 14, 40.0);
			setServoAngle(i2c, 16, -20.0);

			// Dropped Leg Hip
			setServoAngle(i2c, 12, -40.0);
			setServoAngle(i2c, 13, 0.0);
			setServoAngle(i2c, 15, 0.0);
			setServoAngle(i2c, 17, -20.0);

			TIM16->CNT = 0;
			moveOS = 1;
		}

		if(TIM16->CNT > counterVal/2)
		{
				// Drop Legs
			setServoAngle(i2c, 8, -30.0);
			setServoAngle(i2c, 10, 30.0);

			setServoAngle(i2c, 2, 0.0);
			setServoAngle(i2c, 4, 0.0);
		}
		else
		{
				// Lift Legs
			setServoAngle(i2c, 8, 0.0);
			setServoAngle(i2c, 10, 0.0);

			setServoAngle(i2c, 2, 30.0);;
			setServoAngle(i2c, 4, -30.0);
		}

		if(TIM16->CNT > counterVal)
		{
			moveOS = 0;
			walkingStage = 0;
		}
	}
}

void rippleTurn(uint8_t direction)
{

}
