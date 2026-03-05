# Journal
### Total time spent : 40.8 hours
All entries below are a transcription of the journal on the [blueprint program platform](https://blueprint.hackclub.com/projects/5896) because I created the github page afterwards.

## Day 1 (12/10/2025, session of 2 hours) : Preparation and schematic start
There we go !
With the help of the Custom Devboard tutorial, I succeed to make the base of my project by placing the first components in the schematic.
For now there is just this two components :
- RP2040
- USB-A

It doesn't look like much at the moment, but I'm going to improve it for the future.

<img width="1245" height="916" alt="image" src="https://github.com/user-attachments/assets/e7364a9e-5695-44ab-8d7d-a35958166385" />

## Day 2 (12/11/2025, session of 2 hours) : Finished the schematic !
So today, I've finally finished the schematic ! I don't really know if all is correct but I'm counting on you to tell me if I made something bad.
Still with the help of the Custom Devboard tutorial, I successfully set up all the components needed in my project :
- RP2040
- USB-A
- 3.3V LDO
- Quad SPI flash memory
- 12 MHz crystal oscillator

Here's the result :

<img width="1653" height="1146" alt="image" src="https://github.com/user-attachments/assets/d7ae3b09-0a74-4e12-96ce-5f503515168a" />

## Day 3 (12/12/2025, session of 1.7 hours) : Assigning footprints and starting the board
Today I've finished to assign footprints to each component, so here's the result :

<img width="632" height="636" alt="image" src="https://github.com/user-attachments/assets/7202089d-0322-488f-a1a2-8fd19a1d0a0d" />

After I started to organise all of the components on the board and wiring some of them. But I'm still far from finished. Here's a screenshot showing where I'm at :

<img width="518" height="1154" alt="image" src="https://github.com/user-attachments/assets/a57638f2-653c-4060-b85c-5ce7c97643e3" />

## Day 4 (12/16/2025, session of 2 hours) : Routing
During this session, I continued routing all my components. It took me a long time because I had particular difficulty to cross the two D- and D+ routes, I thought I shouldn't use vias. Finally, after a few complications, here's the result :

<img width="1901" height="644" alt="image" src="https://github.com/user-attachments/assets/c92f90dc-f6f7-4ba8-ab31-892982ca4d02" />

## Day 4, 2nd entry (12/16/2025, session of 1.3 hours) : Finishing PCB
I've finally finished the PCB ! I've completed the routing and fixed the errors flagged by the DRC. I've tweaked a few details here and there, so I've included the schematic, PCB layout, and 3D rendering below.

<img width="1431" height="830" alt="image" src="https://github.com/user-attachments/assets/e79960da-3727-415c-b09d-b4bd8f98138e" />
<img width="1933" height="747" alt="image" src="https://github.com/user-attachments/assets/a58cb8d9-9058-4f86-8141-bb9d500272c7" />
<img width="1626" height="1133" alt="image" src="https://github.com/user-attachments/assets/db5465db-abfa-4238-8d28-40d59814801c" />

## Day 5 (12/17/2025, session of 2 hours) : Designing the box
Today I started 3D modeling the box that will house my PCB. I chose to use Fusion 360 software for this. I haven't made the lid yet, but here's what it looks like :

<img width="1022" height="699" alt="image" src="https://github.com/user-attachments/assets/08971839-ace5-4538-8d90-f4d3ba12a68a" />

I opted for a sliding cover to make it easier to open and provide easy access to the circuit board. Here's a zoomed-in image of the mounting system.

<img width="1207" height="764" alt="image" src="https://github.com/user-attachments/assets/7fd1b7dd-d677-4155-8249-4aac1f7449a7" />

## Day 5, 2nd entry (12/17/2025, session of 0.2 hours) : Patched PCB
I noticed I had placed vias directly on the solder pads, which is not recommended. So I corrected everything by offsetting the vias each time. Here's a screenshot of the patched PCB.

<img width="2106" height="773" alt="image" src="https://github.com/user-attachments/assets/3fc153d0-1551-4007-89b9-0daabd93f905" />

## Day 5, 3rd entry (12/17/2025, session of 1.5 hours) : Continuation of the box design
I continued designing the box, making a few improvements. First, I changed the mounting system by adding a ramp on each side of the pinion to prevent it from jamming. Next, I made the top part of the box. Finally, to soften the shape, I rounded the edges. Next time, I'll make the cap for the USB port. Here's what the box looks like :

<img width="2560" height="1082" alt="image" src="https://github.com/user-attachments/assets/396c9e9b-0161-4f9c-9221-e26dd2057447" />
<img width="2560" height="1082" alt="image" src="https://github.com/user-attachments/assets/c49c75f6-2d79-49c8-ae64-609f533d7614" />

## Day 6 (12/20/2025, session of 1 hour) : Finishing the box
Today I've finaly finished the box design ! I added a cap for the USB and a little hole filled with a transparent texture for the LED. To finish I changed the color to red because it looks better than in white ! Here are two screenshots of the result :

<img width="2560" height="1082" alt="image" src="https://github.com/user-attachments/assets/70890270-5c7c-4be3-8c77-6db594e405ed" />
<img width="2560" height="1082" alt="image" src="https://github.com/user-attachments/assets/bfb636b4-c254-4bfa-90ec-0eb4dd240bb0" />

## Day 7 (12/21/2025, session of 2.5 hours) : Creation of the GitHub repository
I finally created the project's GitHub page by following the submission guidelines step by step. I had a lot of trouble choosing the components on JLCPCB because I was completely lost; some components on Kicad didn't exist on JLCPCB, so I had to choose equivalents, but it was complicated to know which ones to select. Well, after two and a half hours of struggling, I finally succeeded, so I'm quite happy to have completed this step. All that's left is to create the firmware to validate the project.

## Day 8 (12/22/2025, session of 1 hour) : Creating the firmware
To finalize the design, I created the firmware. Since I don't know the C programming language and the project needs to be completed before January 1st, I had the firmware generated by AI. I still understand the main coded actions, though, because I like to know how things work. To create the firmware, I used the Pico SDK, which I referenced in Dependencies.txt.

## Day 9 (02/24/2026, session of 4 hours) : Soldering parts
After finally receiving all the necessary parts, I was finally able to start soldering. I had never soldered onto a PCB before. So I started by soldering the parts of my macropad to practice, and it wasn't easy! After hours of struggling, I finally managed to solder everything. And I had the wonderful news that my computer recognized a new device, a sign that everything is working correctly. So I've finally finished the physical part and I'm going to start working on the firmware. Below is a photo of the fully soldered Red Ducky :

<img width="1440" height="1920" alt="image" src="https://github.com/user-attachments/assets/24bc479f-fc8d-43cb-9ab7-e1cc000572d5" />

## Day 10 (02/25/2026, session of 2.5 hours) : Making my first firmware !
After finishing the physical part of the project, I had to start working on the firmware. While researching, I learned that it have to be coded in C, but I had never coded in C before ! So I used an AI that taught me the basics to create a first "blink" firmware that simply makes the LED blink. Again, I encountered many problems that ultimately led me to use WSL to finally compile the firmware. So here's a picture of my first working firmware :

<img width="1440" height="1920" alt="image" src="https://github.com/user-attachments/assets/8a5f98a1-8290-42ff-bf1f-f845a4c1f93d" />

## Day 11 (02/26/2026, session of 3 hours) : Finally Recognized by Windows !
After creating my first "blink" firmware, I started improving it so my Red Ducky would be recognized as a device by the computer by using TinyUSB. Again, after encountering tons of bugs, I managed to get it working. For now, it only lights up an LED and is recognized by Windows, but that's already a small victory for me. The next step will be to make it work as a keyboard-like device (fingers crossed I don't run into any bugs). Here's a screenshot of the device recognized by Windows :

<img width="391" height="418" alt="Capture d&#39;écran 2026-02-26 155719" src="https://github.com/user-attachments/assets/72c99369-04f6-495c-a882-1066007a339f" />

## Day 12 (02/27/2026, session of 3 hours) : First keys typings
To continue working on the firmware, I again asked an AI agent for help. This allowed me to first get my Red Ducky recognized as an HID device (keyboard). Then I implemented a system for typing keys. I managed to get it to type "Hello World" when plugged in.

The next step was to create a mini-language like "STRING Hello World" that would allow me to change the payload without modifying the firmware. I finally got it working after many problems and implemented the STRING, DELAY, ENTER, and KEYCOMBO commands. But while trying to fix an error caused by the KEYCOMBO commands, I realized I had overused vibe coding and no longer understood my own code.

Since I'm stuck, I'm going to go back a bit, but this time without vibe coding, to fully understand what I'm doing. We'll see how it goes in the next journal entry.

## Day 12, 2nd entry (02/27/2026, session of 2.5 hours) : New start without vibe coding
For this new firmware version, which I'm coding myself, I've recreated a function that allows the Red Ducky to type a string, currently accepting only lowercase and uppercase letters, numbers, and certain characters like ".", "!", and spaces. I then put the function that converts the characters to HID code in a separate file for better organization. I've also added a parameter to this function that allows you to convert the keys to either AZERTY or QWERTY layout. And I'm quite proud of the result !

<img width="480" height="343" alt="image" src="https://github.com/user-attachments/assets/0f699540-2864-4481-8d36-3b901b028d38" />

## Day 13 (02/28/2026, session of 2.8 hours) : Making my own script language
To improve the firmware, I had the idea of ​​creating my own version of DuckyScript. This will allow me to avoid recompiling the firmware later, but since my C skills are very limited, I had a lot of trouble setting this up. So I started by coding a parser, which will be the basis of the language. I first implemented the STRING command, which simply allows you to type the following text. And after many struggles, I managed to retype "Hello World!" using the parser. For now, the script is stored in a simple array within the firmware, but I will later implement a system to read a script from a separate file. I then added the DELAY command (waits the specified number of milliseconds) and ENTER (presses Enter). Below is a screenshot of a small example DuckyScript :

<img width="199" height="177" alt="image" src="https://github.com/user-attachments/assets/4e7136d2-ed14-4735-86eb-b6ade8b6f8bb" />

## Day 13, 2nd entry (02/28/2026, session of 3 hours) : Improved DuckyScript and list of supported characters
Since my last journal entry, the firmware has changed a lot. I started by adding two features to my parser (DuckyScript) that now allow me to type key combinations (like CTRL+C) or special keys (like TAB). I encountered many problems again, especially when coding the parser function that read the key combinations. I then added many useful keyboard keys, which also took a lot of time. The most time-consuming part was completely redesigning the AZERTY layout so that Red Ducky works equally well in both AZERTY and QWERTY.
I'll update the firmware on the repository so you can see it in more detail.

## Day 14 (03/05/2026, session of 2.8 hours) : Patching and upgrading the firmware
To begin, I fixed some major firmware bugs :
- The first was that the `DELAY` command no longer worked. Upon investigation, I noticed that it was being overridden by the `global_delay` variable, which creates a delay between each script command. I then implemented conditions that would give `DELAY` priority over `global_delay`.
- The second bug was that special keys would remain pressed indefinitely. I investigated and found that this was due to the `hid_type_task()` function returning because there was no text to type. I then added an exception for special keys so that the function would still execute.

I then added several new commands :

- `LAYOUT`, which takes `AZERTY` or `QWERTY` as an argument, allows you to change the keyboard layout directly in the script.
- `REM` ignores everything written after it on the line, this allows for comments in the script.
- `REPEAT`, which takes an integer as an argument, allows you to repeat the following command the specified number of times.
- `STRINGLN` behaves like `STRING` but always presses enter after the text.

Finally, I increased the maximum size of a `STRING` to 1000 characters.
