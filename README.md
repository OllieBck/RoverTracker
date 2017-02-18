# RoverTracker

## Instructions

Folder for Raspberry Pi: wsexpress
Folder for Huzzah/Arduino: ScanWithWS-Huzzah

### Creating the Raspberry Pi Server
Below are instructions for setting up the server.  Where it says type and then some instructions, don't include "" -- probably obvious, but just incase

1. Plug the Raspberry Pi into power and into the router
2. Connect a computer into the router
3. Open Terminal (Mac) or PuTTY or similar program on (Windows) and execute below
4. Determine the IP address of the Raspberry Pi (can check router at 192.168.2.1)
  -- might be able to access it by typing "ssh pi@raspberrypi.local"
  -- enter password "raspberry" is the default but could be different
5. Install latest version of node.js onto the Raspberry Pi (detailed here: http://thisdavej.com/beginners-guide-to-installing-node-js-on-a-raspberry-pi/)
  -- type "curl -sL https://deb.nodesource.com/setup_7.x | sudo -E bash -"
  -- type "sudo apt install nodejs"
  -- check version by typing "node -v", this should print out 7.5 or so
6. Download the zip file off the Github page onto Raspberry Pi by typing "git clone https://github.com/OllieBck/RoverTracker.git"
7. Enter the file by typing "cd RoverTracker/wsexpress"
8. Install the necessary libraries for the program by typing "npm install"
9. You can view the various files using nano -- ex. "sudo nano server.js"
  -- note the port number in the server.js file
  -- on keyboard, typing "control x" will exit the editor -- if you make changes and want to save them click "y" and enter
10. Modify the "index.html" file found in the "public" folder
  -- type "sudo nano public/index.html" or "cd public && sudo nano index.html"
11. Change the server information in the "index.html" file
  -- either enter in the IP address of the pi or if raspberrypi.local worked to ssh can use that
12. In the wsexpress folder, launch the server by typing "node server.js"
13. You can navigate to the webpage by typing "raspberrypi.local:8080" into a browser's address bar or if you changed the port, whatever the port is; can also type in the Pi's IP address
  -- Chrome works best usually as it supports a lot of features

### Updating the Huzzah Code

1. On a Mac or PC download the files from Github: https://github.com/OllieBck/RoverTracker
2. Extract the "ScanWithWS--Huzzah" and put it in the computers Arduino folder
3. Setup the Arduion IDE to work with either the Feather Huzzah: https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide or the vanilla Huzzah: https://learn.adafruit.com/adafruit-huzzah-esp8266-breakout/overview
4. Download the necessary libraries for Websockets: https://github.com/OllieBck/arduinoWebSockets and rename the file "arduinoWebSockets" and place the whole folder in the "libraries" folder in the Arduino folder (if there isn't a libraries folder, make one)
5. In the "ScanWithWS--Huzzah" file, there should be a tab that says "config.h"
  -- write in the SSID and password in corresponding fields in this file
6. Can download other libraries by opening up Arduino IDE and then going to "Sketch >> Include Library >> Manage Libraries..." and then search for the missing libraries
7. Update the code with the address for the server on the Raspberry Pi
8. Load the code onto the Huzzah and hopefully if the server is on and webpage is open they will talk to each other
