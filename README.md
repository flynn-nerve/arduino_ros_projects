# I have not formatted this at all yet, just writing down all the notes in shorthand for the moment

Arduino IDE installer link:
https://www.arduino.cc/en/software

This will download a zipped file that will contain the installer, follow the instructions in the next step after extracting this folder (I extracted it to my desktop but somewhere like your documents might be better, not super important)

Do not get rid of this folder (will be called something like arduino-1.8.15 or whatever version they are on) because it holds the IDE's important files and will also be the location where the Teensyduino add-on's files are stored. Keep in mind this is not where your sketches will be stored, they will usually default to ~/$USER/Arduino on Ubuntu and ~/$USER/Documents/Arduino on Windows as far as I've seen.

Arduino IDE setup instructions:
https://www.arduino.cc/en/guide/linux

After you extract the 

Don't forget to do this:
sudo usermod -a -G dialout $USER
 -$USER is an environment variable, this will be your username but you can type it out instead if you prefer

Installation/setup guide for Teensyduino, an add-on for the Arduino IDE that lets you program Teensy boards with Arduino code
Teensy boards are used in my projects because they are more powerful than arduinos, I'll probably elaborate later
https://www.pjrc.com/teensy/td_download.html

Follow the instructions for Linux installation on the page
OR
you can do it all over the terminal which is probably easier, the instructions for this are a bit down the page under \*Commmand Line Install\*

No matter which option you choose, when you run the install script it will ask you where you want to install the files to and the only location it will accept is the location where your Arduino IDE was installed as mentioned previously

wget https://downloads.arduino.cc/arduino-1.8.15-linux64.tar.xz
wget https://www.pjrc.com/teensy/td_154/TeensyduinoInstall.linux64
wget https://www.pjrc.com/teensy/00-teensy.rules
sudo cp 00-teensy.rules /etc/udev/rules.d/
tar -xf arduino-1.8.15-linux64.tar.xz
chmod 755 TeensyduinoInstall.linux64
./TeensyduinoInstall.linux64 --dir=arduino-1.8.15
cd arduino-1.8.15/hardware/teensy/avr/cores/teensy4
make

To reiterate, the Teensyduino add-on's files will be installed into the location where your Arduino IDE files were installed/stored (arduino-\<version\>) so do not delete this file.

You will need to install rosserial on your linux device (PC or Pi, I have a PC as well as a Raspberry Pi 4 running Ubuntu Mate version 18.04 with ROS melodic installed) to be able to communicate over ros with your arduino/Teensy/arduino-variant board.

rosserial - ROS wiki page:
http://wiki.ros.org/rosserial

There are some tutorials here:
http://wiki.ros.org/rosserial_arduino/Tutorials

The instructions I am providing will guide you through all the steps needed to run my code/examples but it can't hurt to read more tutorials. The only issue is that in tutorial 6. - Adding Custom Messages (Generating Message Header File) they instruct you to use a node that does not work. The process is more or less the same except you use a node that will convert all of your message types into arduino libraries. It has the same effect, just does more than you want. Feel free to look into this more if you want but it doesn't bother me to create more than I need because the folders in the destination location are clearly labeled so it doesn't make anything difficult, just gives you more message types to use in case they aren't included in the arduino ros_lib folder.

you can install rosserial on your linux machines using:
sudo apt install ros-$ROS_DISTRO-rosserial
sudo apt install ros-$ROS_DISTRO-rosserial-arduino

TODO: at this particular moment in time I don't know if both are necessary, I'll look into it more

In order to use custom ROS messages you need to run a script on the computer and from the workspace where your custom messages were created (whichever workspace has the package where your message was generated).

Go into your workspace and run the following command:
rosrun rosserial\_arduino make\_libraries.py \<destination_folder\>

Your destination folder should ultimately be ~/$USER/Arduino/libraries if you're programming your Arduino device on your linux machine, but if you need to put them on a flash drive or want to upload to git or something they can really go anywhere. In order for the Arduino IDE to actually use the custom messages, however, the folder that has the package name of the package where you created your custom ros message (which contains \<your_message_type\>.h) has to be placed into your ~/$USER/Arduino/libraries/Rosserial_Arduino_Library/src folder on Ubuntu or ~/$USER/Documents/Arduino/libraries/ros_lib/src folder on Windows (I'll double check the file path later but it should be pretty comparable if not completely correct, you get the idea).

Regardless of which OS you are using, once your library is in the right place you can include the library and message type header in your Arduino code and make sure everything works. Please refer to how I've done this in my packages and eventual instructions for reference.

Run the following command to listen to your arduino device when plugged into your linx machine:
(make sure that you have added yourself to the dialout group --> sudo usermod -a -G dialout $USER)
rosrun rosserial\_arduino serial\_node.py /dev/ttyACM0

Note that your device may not be on ACM0, but if you run it on a pi with nothing else plugged in this will probably be the case
You can find out what is plugged in by using:
lsusb
dmesg
dmesg | grep tty
usb-devices

Assuming you have properly set up your arduino code as in including \<ros.h\> and any custom message libraries, you will see the node indicate what topics you are subscribed to and publishing on and then you will be ready to go.
