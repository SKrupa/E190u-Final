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

The controller itself has 2 modes, wired mode which plugs into the Jetson and wireless mode which communicated to any connected device over Bluetooth. Unlike in Lab 2, I wanted to have true analog values for both thumbsticks as well as the triggers. To do this, I created a Joystick structure in the HID descriptor for Arduino which stored analog values along side digital values for buttons and a 3 bit number for the D-Pad. I then modified the Arduino USB-API to send this struct as a Joystick to the connected computer. I went with a Joystick instead of a Controller because lots of PC applications are preconfigured to work with Joysticks whereas if I went with a controller, I would have to make sure that the controller I designed was functionally identical to a standard controller, which would require a lot more testing.

##Results and Discussion

##Conclusions
