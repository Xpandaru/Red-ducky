# Red-ducky
<img width="2560" height="1082" alt="render_2" src="https://github.com/user-attachments/assets/f3e22eeb-b566-41cc-9a84-e5670925437a" />
In this project I'll make my own Rubber Ducky, named Red ducky ! A Rubber Ducky is a hacking tool that mimics a keyboard to inject a sequence of keys. I started this project with no knowledge of PCB design, so it promises to be very educational.

## The story of the project

It all started when a friend introduced me to [Hack Club](https://hackclub.com/) during the [Cyber ​​Ninja CTF](https://www.cyber-ninja-ctf.fr/) (a cybersecurity competition organized by [Oteria Cyber ​​School](https://www.oteria.fr/)). I was quickly drawn to the [Blueprint program](https://blueprint.hackclub.com) because I knew absolutely nothing about electronics, and being very curious, I saw it as the perfect opportunity to explore the field. I soon had the idea to recreate a Rubber Ducky (a very popular cybersecurity tool) to understand how it worked and have my own by the end of the project. From there, I began learning all the necessary knowledge and developing my project based on the [custom devboard](https://blueprint.hackclub.com/starter-projects/devboard) guided project.
## Some screenshots
<img width="2560" height="1082" alt="rendu_1" src="https://github.com/user-attachments/assets/78ed0a53-a1b9-423d-932a-13b90140d5e0" />

### The PCB :

<img width="1746" height="602" alt="image" src="https://github.com/user-attachments/assets/15f25b52-6d29-4fac-bc19-6ec46261b0af" />

### The schematic :

<img width="1636" height="1130" alt="image" src="https://github.com/user-attachments/assets/4dd36a92-4d46-405a-9d63-89dce725ef0b" />

# Bill of materials

| Designator | Footprint | Quantity | Comment |
| :--- | :--- | ---: | :--- |
| R2,R1 | R_0402_1005Metric | 2   | 22  |
| D1  | LED_0603_1608Metric | 1   | LED |
| C17,C2,C4,C12,C5,C7,C8,C3,C9,C6,C11 | C_0402_1005Metric | 11  | 0.1uF |
| C13,C14 | C_0603_1608Metric | 2   | 10uF |
| TP2,TP1,TP3 | TestPoint_Pad_1.5x1.5mm | 3   | TestPoint |
| Y1  | Crystal_SMD_3225-4Pin_3.2x2.5mm | 1   | 12 MHz |
| C10,C1 | C_0402_1005Metric | 2   | 1uF |
| R5,R3,R6 | R_0402_1005Metric | 3   | 1K  |
| U1  | QFN-56-1EP_7x7mm_P0.4mm_EP3.2x3.2mm | 1   | RP2040 |
| R4  | R_0402_1005Metric | 1   | 10K |
| J1  | USB_A_CNCTech_1001-011-01101_Horizontal | 1   | USB_A |
| U3  | Winbond_USON-8-1EP_3x2mm_P0.5mm_EP0.2x1.6mm | 1   | W25Q16JVUXIQ TR |
| C16,C15 | C_0402_1005Metric | 2   | 33pF |
| U2  | SOT-23 | 1   | MCP1700x-330xxTT |
| SW1 | SW_Push_SPST_NO_Alps_SKRK | 1   | SW_Push |
