/** Simple On-board LED flashing program - written in C++ by Derek Molloy
*    simple functional struture for the Exploring BeagleBone book
*
*    This program uses USR LED 3 and can be executed in three ways:
*         makeLED on
*         makeLED off
*         makeLED flash  (flash at 100ms intervals - on 50ms/off 50ms)
*         makeLED status (get the trigger status)
*	  makeLED blink 5 (blink led 5 times) *ADDITION TO CODE*
*
*	  edited by lucian dupont 3/20/25
*
*
* * Written by Derek Molloy for the book "Exploring BeagleBone: Tools and 
* Techniques for Building with Embedded Linux" by John Wiley & Sons, 2014
* ISBN 9781118935125. Please see the file README.md in the repository root 
* directory for copyright and GNU GPLv3 license information.            */

#include<iostream>
#include<fstream>
#include<string>
#include<unistd.h>
#include<cstdlib>

using namespace std;

#define LED3_PATH "/sys/class/leds/beaglebone:green:usr3"

void writeLED(string filename, string value){
   fstream fs;
   string path(LED3_PATH);
   fs.open((path + filename).c_str(), fstream::out);
   fs << value;
   fs.close();
}


void removeTrigger(){
  writeLED("/trigger", "none");
}

int main(int argc, char* argv[]){
   if(argc!=3){
	cout << "Usage is makeLED and one of: " << endl;
        cout << "   on, off, flash or status" << endl;
	cout << " e.g. makeLED flash" << endl;
        return 2;
   }
   string cmd(argv[1]);
   int cmd2 = std::atoi(argv[2]);
   cout << "Starting the makeLED program" << endl;
   cout << "Blinking the LED" << cmd2 << "times" << endl;
   cout << "The current LED Path is: " << LED3_PATH << endl;

   // select whether command is on, off, flash or status
   if(cmd=="on"){
        cout << "Turning the LED on" << endl;
	removeTrigger();
        writeLED("/brightness", "1");
   }
   else if (cmd=="off"){
        cout << "Turning the LED off" << endl;
	removeTrigger();
        writeLED("/brightness", "0");
   }
   else if (cmd=="flash"){
        cout << "Flashing the LED" << endl;
        writeLED("/trigger", "timer");
        writeLED("/delay_on", "50");
        writeLED("/delay_off", "50");
   }
   else if (cmd=="status"){
	// display the current trigger details
        std::fstream fs;
	fs.open( LED3_PATH "/trigger", std::fstream::in);
	string line;
	while(getline(fs,line)) cout << line << endl;
	fs.close();
   }
   else if (cmd=="blink"){
        //command that has been added
	for (int i = 0; i <= cmd2; i++)
	{
        	writeLED("/brightness","1");
		sleep(1);
		writeLED("/brightness","0");
                sleep(1);

	}
   }
   else{
        cout << "Invalid command!" << endl;
   }

   cout << "Finished the makeLED Program" << endl;
   return 0;
}
