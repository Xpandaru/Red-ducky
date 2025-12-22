# Journal
### Total time spent : 17.2 hours
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
