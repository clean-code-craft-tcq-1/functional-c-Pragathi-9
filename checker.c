/* Include Headerfiles													*/
/* ===================													*/


#include <stdio.h>
#include <assert.h>	
#include <stdbool.h>


#define MAXCHARGERATE 0.5
#define MAXTEMP 45
#define MINTEMP 0
#define MAXSOC 80
#define MINSOC 20

/********************************************************************************
 * A function that gives the State-of -Health status of a battery management system.
 * if the current SOH rating us below the threshold 0.5%, then the battery is unacceptable.
 * The SOH at the manufacturing unit is 100%
 * input: Current SOH value
 * returns: Check if the value is greater than the threshold
 *********************************************************************************/
int StateOfHealth_check (float currentsoh)
{
  return (currentsoh > 0.5 ? 1:0);
}

/*************************************************************************************************
 * Process: Display the State of Health of the battery currently as compared to ideal conditions
 ************************************************************************************************/
int BMS_StateOfHealth (float soh)
{
 
 int sohcheck = StateOfHealth_check(soh);
 if (sohcheck)
  {
    printf(" State-of-Health of battery is %f, Battery conditions are good as compared to ideal conditions \n", soh );
	return 0;
  }
  else
  {
    printf (" State-of-Health of battery is %f, Battery conditions are poor and cannot be used for the application \n", soh);
	return 1;
  } 
}


/********************************************************************************
 * A function that gives Charge rate of a Battery management system.
 * if the current Charge rating is above the threshold, then the battery is unacceptable.
 * input: Current charge rate in decimal (percentage converted to floating value)
 * returns: Check if the charge rate is out of boundary conditions
 *********************************************************************************/
int BMS_ChargeRateCheck(float charge_rate)
{
	int chargerate_check=(charge_rate>MAXCHARGERATE);
	 if(chargerate_check)
	   {
		printf("Charge Rate is %f and is out of range!\n", charge_rate);
		return 0;
	   }
	printf("Charge Rate is %f within the maximum threshold\n", charge_rate);  
	return 1;
}

/********************************************************************************
 * A function that gives State-of-Charge parameter check of a Battery management system.
 * if the current SOC is outside the boundary conditions, then the battery is unacceptable.
 * if the SOC exceeds the 80% threshold, that reduces the life span of the battery, and losses are incurred
 * input: SOC in decimal (percentage converted to decimal)
 * returns: Check if the SOC is out of boundary conditions
 *********************************************************************************/
 
int BMS_StateOfCharge(float soc)
{
  int soc_check= ((soc < MINSOC) || (soc > MAXSOC));
  if (soc_check)
  {
     printf("State of Charge is %f percent, and is out of range!\n", soc);
    /* if (soc >= MAXSOC)
     { printf(" Charging is being carried out outside/public stations, avoid charging above 80 percent to reduce the losses. \n");}*/
     return 0;
  }
  return 1;
}

/********************************************************************************
 * A function that gives Safe operating temperature during the charging of a Battery.
 * There could be loss of charge if the temperature is beyond the boundary conditions
 * input: Temperature in degrees
 * returns: Check if the Temperature is out of boundary conditions
 *********************************************************************************/
 
int BMS_TemperatureCheck(float temperature_deg)
{
  int temperature_check= ((MINTEMP < temperature_deg) || (temperature_deg < MAXTEMP));
  if(temperature_check)
  {
    printf(" The current BMS temperature is %f, and the conditions are ideal for charging the battery. \n", temperature_deg);
    return 1;
  } 
  printf("Temperature is %f and is out of range!\n", temperature_deg);
  return 0;
  
}



/********************************************************************************
 * A function that gives overall status of a BAttery management system
 * Factors such as: Charging Temperature,Charge rate, SoH, SoC are considered to check if the BMS is good to function.
 * input: Fators to check the plausibility of BMS
 * returns: True is the factors meet the requirement
 *********************************************************************************/
 
bool batteryIsOk(float StateofHealth, float ChargeRate, float stateofcharge, float temperature) 
{
  bool socstatus, sohstatus, temperaturecheck, chargeratecheck,status;
     sohstatus =  (bool)BMS_StateOfHealth(StateofHealth);
     socstatus = (bool)BMS_StateOfCharge(stateofcharge);
     chargeratecheck = (bool)BMS_ChargeRateCheck(ChargeRate);
     temperaturecheck = (bool)BMS_TemperatureCheck(temperature);
     status= (sohstatus & sohstatus & chargeratecheck & temperaturecheck);
     return (status);
}

bool batteryIsOk(float StateofHealth, float ChargeRate, float stateofcharge, float temperature);
/********************************************************************************
 * Process: Main function that checks all possible test scenarios to check the BMS plausibility
 *********************************************************************************/

int main() {
  
  assert(batteryIsOk(0.7, 0.8, 70, 25));
  assert(batteryIsOk(0.4,0,85,50));
}
