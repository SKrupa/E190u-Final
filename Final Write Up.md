##Introduction

For a final design project, I wanted to build off of Labs 1 and 2 since I enjoyed being able to work in both hardware and software. I decided to create a combination of a handheld console and a wireless touchscreen controller for PC. I would implement the console by attaching the Jetson TK1 to it, enabling it to run a variety of ARM compatible games. Furthermore, there are lots of emulators writter for ARM computers because of the rise of mobile gaming platforms.

##Design Methodology
I also liked the idea of being able to use the controller with a more powerful PC in much the same way the Wii U tablet controller works in conjunction with a Wii U. I felt that getting a game streaming to the Jetson without large amounts of latency was outside of the scope of this project, so instead I focused on simply getting user inputs from the controller to the PC.

Ultimately, this controller is intended to be protable in the way a laptop is portable rather than how other game consoles like the PlayStation Portable or the Gameboy series are portable. 

![](https://github.com/SKrupa/E190u-Final/blob/master/20150502_162149.jpg)

I chose to make the controller out of wood since it is a very easy material to work with for an initial prototype. It is easy to to rapidly put together a design and then modify it based on feel. This is in direct contract to the option of vaccuum forming, which would give a result similar to that of professionally made controllers albeit thinner. Vaccuum forming would still require a model made out of a different material such as clay, would take a long time to get right, and any modification would require a whole new model. 

Ultimately, the designing of this controller was very similar to Lab 1, but I took into consideration some things that worked poorly in that controller. For example, in that controller all of the wires were routed along the top of the controller, making it very messy for the user. For this controller, I drilled holed into the controller and passed all of the wired through that. Thus the front of the controller had very few visible wires.

![](https://github.com/SKrupa/E190u-Final/blob/master/20150502_162241.jpg)

There was still the problem of very messy wires in the back, which could be slightly mitigated by measuring the wire lengths to just barely reach their desired ports. Furthermore, in a final design, PCBs would be used rather than breadboards, which would also clean the back up. I kept it as long wires on breadboards for debugging purposes.

![](https://raw.githubusercontent.com/SKrupa/E190u-Final/master/enclosurebox-Model.png)

Furthermore, these wires would ultimately sit in an acrylic enclosure alongside the display driver and the Jetson TK1. I went through 4 iterations of the enclosure, each one getting progressively larger. Pictured above is iteration 3, the last that was physically constructed. This was almost the right size, but I found that I had trouble plugging in USB cables, so a last revision increased the box size from 13 inches to 13.5 inches in length.

The display is 7 inch 800x600 display/touch screen combo. The display works for any system and the touchscreen has drivers which work for all major operating systems and computer architectures, including ARM. I had some trouble getting the drivers to work for the Jetson, but ultimately, I managed to get the touchscreen calibrated and working as a mouse input.

The controller itself has 2 modes, wired mode which plugs into the Jetson and wireless mode which communicated to any connected device over Bluetooth. In order to be able to use all the buttons I wante dwith the Arduino Micro, I used 6 of the analog pins to read 12 digital values by creating 6 2 bit DACs. Each dac output Vcc if no buttons were pressed, 1/2 Vcc if the first was pressed, 1/3 Vcc if the other was pressed, and 1/4 Vcc if both were pressed.

Unlike in Lab 2, I wanted to have true analog values for both thumbsticks as well as the triggers. To do this, I created a Joystick structure in the HID descriptor for Arduino which stored analog values along side digital values for buttons and a 3 bit number for the D-Pad. I then modified the Arduino USB-API to send this struct as a Joystick to the connected computer. I went with a Joystick instead of a Controller because lots of PC applications are preconfigured to work with Joysticks whereas if I went with a controller, I would have to make sure that the controller I designed was functionally identical to a standard controller, which would require a lot more testing.

For Bluetooth communcation, I chose to use a Bluetooth HID module which could be identified as a controller. This made it behave very similarly to the USB Joystick. The major difference was that I could only send 6 bytes of data since the packet size for the module I had was 8 bytes 9tbhe first two bytes specify data type and device type, which in this case were raw data and controller.) Which this little data, I could onyl send 4 analog axes rather than 6 like I did with USB. I chose to interpret trigger data as digital values because of this. 

##Results and Discussion

The USB mode worked perfectly. It was automatically detected by the computer and required no driver updates to function most of the time (sometimes the device would not detect immediately, but the issue would resolve itself by reloading the drivers.)  All analog axes worked perfectly, even the triggers which were mapped to a single analog axis. I mapped the controls to be identical to an xBox controller, which meant games did not see a difference between my controller and the xBox controller.

I tested this controller on my x86 machine running both Windows 7 and Linux Mint, the Jetson running Debian under an ARM architecture, and a Playstation 3. The controller worked perfectly for the first 3 configurations. Supprisingly, it also worked when plugged into the PS3, the only problem was that the buttons were mapped incorrectly and the analog axes behaved strangely in some games. I'm sure that with some light tweaking, the controller could function perfectly for the PS3.

The Bluetooth mode was more finnicky. I could connect to the device, but sometimes it would immediately disconnect. I did not have such problems in my room, but in the classroom and the lab I found that this was a common problem. This leads me to believe that there must be some kind of interference which easily messes up the controller, which is troublesome. When it does manage to stay paired, the controller works perfectly fine, but it does require some rebinding in games since the D-Pad and the triggers had to be interpretted as digital buttons. Furthermore, there is 32 milliseconds of latency when using the Bluetooth, which is noticible in some high precision games. It is easy to account for in most games, but it is definitely there. This is in contract to the USB mode which has zero noticible latency.


The controller itself was suprisingly comfortable. It looks extremyl bulky, and while it does feel a little too large, I had little problem using it. However, if someone had smaller hands, the controller would definitely be very hard to use. The controller is also quite heavy, requiring the user to rest it on their lap while using it to prevent wrist strain after prolonged use.

The enclosure was a complete fairule. Adding a Jetson TK1 doubled the weight of the controller, but more importantly, it added the weight 2.5 inches from the center of mass, which ended up generating a lot of torque on the wrists while holding it up. The controller was extremly unwieldy to use with the full enclosure. Stuffing everything in the enclosure was also a problem since many of the cables did not have right angle adapters, requiring a either a larger enclosure or strain on the wires.

##Conclusions

Ulimately the controller portion of this project worked really well. It managed to behave exactly the same as a commercially available controller in games and emulators, which was the goal. However, as a handheld console, it failed since mounting the Jetson was not really feasable if we still want to consider the device to be "handheld" rather than a laptop.
