# About

This Library is intended for use with NCD 16 Relay Particle Core/Photon compatible PWM controllers.

The intention of this library is to make use of the NCD 16 channel PWM controller with Particle development web IDE as simple as possible for users.
###Developer information
NCD has been designing and manufacturing computer control products since 1995.  We have specialized in hardware design and manufacturing of Relay controllers for 20 years.  We pride ourselves as being the industry leader of computer control relay products.  Our products are proven reliable and we are very excited to support Particle.  For more information on NCD please visit www.controlanything.com 

###Requirements
- NCD 16 Channel Particle Core/Photon Compatible PWM board
- Particle Core/Photon module
- Knowledge base for developing and programming with Particle Core/Photon modules.

### Version
1.0.0

### How to use this library

The libary must be imported into your application.  This can be done through the Particle WEB IDE by selecting Libraries, then select the NCD16PWM.  Click Include in App button.  Select the App you want to include the library in.  Finally click Add to this app.  For more information see [Particles's documentation] [sparkIncludeLibrary] 

### Example use

Once the Library is included in your applicaiton you should see an include statement at the top like this:
```cpp
//This #include statement was automatically added by the Particle IDE.
#include "NCD16PWM/NCD16PWM.h"
```
Now you need to instanciate an object of the library for use in your application like this:
```cpp
NCD16PWM controller;
```

Here is an example use case for the class
```cpp
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
```

###Public accessible methods
```cpp
void setAddress(int a0, int a1, int a2, int a3, int a4, int a5);
```
>Must be called first before using the object.  This method should also be called any time communication with
>the controller is lost or broken to recover communication.  This method accepts six int arguments.  This
>tells the Library what address to direct commands to.  a0 a1, a2, a3, a4, and a5 ints are representations of the six
>jumpers on the PWM controller which are labeled on the board ADDRESS 0, 1, 2, 3, 4, 5.  If the jumper is
>installed then that int in this call should be set to 1.  If it is not installed then the int should be set to 0
So if I have jumpers 0, 1, and 2 installed and 3, 4, and 5 not installed You would call 
>```controller.setAddress(1, 1, 1, 0, 0, 0).```


```cpp
void turnOnRelay();
```
>A call to this method will turn on the relay.


```cpp
void setChannelBrightness(int channel, int val);
```
>A call to this method will set the brighness of 1 PWM channel on the board.  This method accepts 2 int arguments(channel, and val).  Channel specifies the channel on the board the command should be directed to.  Valid channel arguments are 1-16.  val specifies the position to set the channel brightness/speed to.  Valid val arguments are 0-4095.  0 being all the way off and 4095 being all the way on.


```cpp
void setAllChannelsBrightness(int* vals);
```
>A call to this method will set the brightness of all 16 channels on the board.  This method accepts 1 int pointer argument.  This int pointer should be an int array with 16 values.  Each of the 16 ints in the array are used to set the brighness of the corresponding channels.  Valid int arguments in array are 0-4095.


```cpp
void setAllChannelsBrightness(int val);
```
>A call to this method will set the brightness of all 16 channels on the board to a single value.  This method accepts 1 int argument(val).  The Val argument specifies the brightness level to set all 16 channels on the board to.  A val argument of 4095 will turn all 16 channels on to full brighness.  A val argument of 0 will turn all channels off.


```cpp
int readChannelBrightness(int channel);
```
>A call to this method will return an int value specifying the current brightness level of a specified channel.  This method accepts 1 int argument and returns 1 int.  The channel int argument specifies the channl to be read.  Valid channel values are 1-16.  Valid int returns are 0-4095.  4096 is returned if there is an error.  A return of 4095 indicates the channel is at full brighness.  A return of 0 indicates the channel is off.


```cpp
byte readAllInputs();
```
>This method accepts no arguments and returns one byte.  A call to this
>method will read and return the status of all 7 inputs on the board. 
>Each input on the board is represented as a bit in the returned byte.  Valid returns are 0-128.  If the input is closed 
>the bit in the byte is set to 1, if the input is open the bit in the byte is set to 0.  256 will be
>returned if an error has occured(generally due to lack of communciation with controller).

```cpp
int* readAllChannelsBrightness(int* buffer);
```
>A call to this method will return the current brightness of all 16 channels.  This method accepts 1 int pointer argument and returns 1 int pointer.  A 16 position int array should be created and passed to this method.  To call this method create an int array with 16 positions.  Then create a new int pointer and initialize it with the return value of this method.  The newly initialized int pointer will be populated with a 16 position int array containing the current status of all 16 channels.  See usage sample below:
```cpp
int channelStatusBuffer[16];
int* brighness = controller.readAllChannelsBrightness(channelStatusBuffer);
for(int i = 0; i < 16; i++){
Serial.print("Channel ");
Serial.print(i+1);
Serial.print(" brightness: ");
Serial.println(brighness[i]);
}
```

###Public accessible variables
```cpp
bool initialized;
```
>This boolean indicates the current status of the interface connection to the controller.  This variable should
>be checked often throughout your application.  If communication to the board is lost for any reason this
>boolean variable will return false.  If all is well it will return true.


License
----

GNU
[sparkIncludeLibrary]:http://docs.spark.io/build/#flash-apps-with-spark-build-using-libraries