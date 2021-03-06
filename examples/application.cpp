/* Includes ------------------------------------------------------------------*/
#include "application.h"

SYSTEM_MODE(MANUAL);

NCD16PWM controller;
int initialStatus[16] = {0,0,0,0,0,0,0,0,4096,4096,4096,4096,4096,4096,4096,4096};

/* This function is called once at start up ----------------------------------*/
void setup()
{
	Serial.begin(115200);
	delay(3000);
	controller.setAddress(0,0,0,0,0,0);

}

/* This function loops forever --------------------------------------------*/
void loop()
{
	/*
	//Set one channel brightness and monitor
	for(int i = 0; i < 4095; i+=16){
		controller.setChannelBrightness(1, i);
		int channelStatusBuffer[16];
		int* brighness = controller.readAllChannelsBrightness(channelStatusBuffer);
		for(int i = 0; i < 16; i++){
			Serial.print("Channel ");
			Serial.print(i+1);
			Serial.print(" brightness: ");
			Serial.println(brighness[i]);
		}
		delay(2000);
	}
	for(int i = 4095; i >= 0; i-=16){
		controller.setChannelBrightness(1, i);
		int channelStatusBuffer[16];
		int* brighness = controller.readAllChannelsBrightness(channelStatusBuffer);
		for(int i = 0; i < 16; i++){
			Serial.print("Channel ");
			Serial.print(i+1);
			Serial.print(" brightness: ");
			Serial.println(brighness[i]);
		}
		delay(2000);
	}
	*/

	/*
	//Set all channels brightness test
	for(int i = 0; i < 4096; i+=8){
		int vals[16];
		for(int k = 0; k < 16; k++){
			vals[k] = i;
		}
		controller.setAllChannelsBrightness(vals);
	}
	for(int i = 4095; i >= 0; i-=8){
		int vals[16];
		for(int k = 0; k < 16; k++){
			vals[k] = i;
		}
		controller.setAllChannelsBrightness(vals);
	}
	*/
	//Set one channel brightness and monitor
	for(int i = 0; i < 4095; i+=16){
		controller.setAllChannelsBrightness(i);
		int channelStatusBuffer[16];
		int* brighness = controller.readAllChannelsBrightness(channelStatusBuffer);
		for(int i = 0; i < 16; i++){
			Serial.print("Channel ");
			Serial.print(i+1);
			Serial.print(" brightness: ");
			Serial.println(brighness[i]);
		}
		delay(2000);
	}
	for(int i = 4095; i >= 0; i-=16){
		controller.setAllChannelsBrightness(i);
		int channelStatusBuffer[16];
		int* brighness = controller.readAllChannelsBrightness(channelStatusBuffer);
		for(int i = 0; i < 16; i++){
			Serial.print("Channel ");
			Serial.print(i+1);
			Serial.print(" brightness: ");
			Serial.println(brighness[i]);
		}
		delay(2000);
	}

}
