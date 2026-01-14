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

| Item | Description | Quantity | Unit price (\$) | Total prince (\$) | URL |
| --- | --- | ---: | ---: | ---: | --- |
| 0402CG330J500NT | 33pF 50V C0G ±5% 0402 Multilayer Ceramic Capacitors MLCC - SMD/SMT ROHS | 4   | 0.001 | 0.004 | https://jlcpcb.com/partdetail/1914-0402CG330J500NT/C1562 |
| DSX321G 12MHz | SMD3225-4P Crystals ROHS | 5   | 0.4003 | 2.0015 | https://jlcpcb.com/partdetail/KDSDaishinku-DSX321G12MHz/C93234 |
| KT-0603W | 100mW 120° 2.6V~3.1V 360mcd 5mA Discrete Diode White Yellow Lens op View Mount 0603 LED Indication - Discrete ROHS | 2   | 0.0104 | 0.0208 | https://jlcpcb.com/partdetail/Hubei_KENTOElec-KT0603W/C2290 |
| CL05A105KA5NQNC | 1uF 25V X5R ±10% 0402 Multilayer Ceramic Capacitors MLCC - SMD/SMT ROHS | 4   | 0.0029 | 0.0116 | https://jlcpcb.com/partdetail/53938-CL05A105KA5NQNC/C52923 |
| RP2040 | 12bit 133MHz 30 LQFN-56(7x7) Microcontrollers (MCU/MPU/SOC) ROHS | 2   | 0.9298 | 1.8596 | https://jlcpcb.com/partdetail/RaspberryPi-RP2040/C2040 |
| 0402WGF1001TCE | \-55℃~+155℃ 1kΩ 50V 62.5mW Thick Film Resistor ±1% ±100ppm/℃ 0402 Chip Resistor - Surface Mount ROHS | 6   | 0.0006 | 0.0036 | https://jlcpcb.com/partdetail/12256-0402WGF1001TCE/C11702 |
| W25Q16JVUXIQ | \-40℃~+85℃ 100,000 Cycles 10uA 133MHz 16Mbit 2.7V~3.6V 20 Years 3ms SPI USON-8-EP(2x3) NOR FLASH ROHS | 2   | 0.5448 | 1.0896 | https://jlcpcb.com/partdetail/WinbondElec-W25Q16JVUXIQ/C2843335 |
| CL05B104KO5NNNC | 100nF 16V X7R ±10% 0402 Multilayer Ceramic Capacitors MLCC - SMD/SMT ROHS | 22  | 0.0012 | 0.0264 | https://jlcpcb.com/partdetail/1877-CL05B104KO5NNNC/C1525 |
| 0402WGF1002TCE | \-55℃~+155℃ 10kΩ 50V 62.5mW Thick Film Resistor ±1% ±100ppm/℃ 0402 Chip Resistor - Surface Mount ROHS | 2   | 0.0005 | 0.001 | https://jlcpcb.com/partdetail/26487-0402WGF1002TCE/C25744 |
| CL10A106KP8NNNC | 10V 10uF X5R ±10% 0603 Multilayer Ceramic Capacitors MLCC - SMD/SMT ROHS | 4   | 0.0057 | 0.0228 | https://jlcpcb.com/partdetail/20411-CL10A106KP8NNNC/C19702 |
| 0402WGF220JTCE | \-55℃~+155℃ 22Ω 50V 62.5mW Thick Film Resistor ±1% ±100ppm/℃ 0402 Chip Resistor - Surface Mount ROHS | 4   | 0.0006 | 0.0024 | https://jlcpcb.com/partdetail/25835-0402WGF220JTCE/C25092 |
| MCP1700T-3302E/TT | IC REG LINEAR 3.3V 250MA SOT23-3 | 2   | 0.51 | 1.02 | https://www.lcsc.com/product-detail/C39051.html |
| MOLEX 48037-2200 | USB-A (USB TYPE-A) Receptacle Connector 4 Position Solder Cup | 2   | 2.0539 | 4.1078 | https://www.lcsc.com/product-detail/C2765195.html |
| SKRKAHE020 | SWITCH TACTILE SPST-NO 0.05A 12V | 2   | 0.41 | 0.82 | https://www.lcsc.com/product-detail/C202388.html |
| PCB | Green, 1.6 Thickness, HASL(with lead) | 5   | 0.4 | 2   |     |
| PCBA | Assemble top side | 2   | 12.875 | 25.75 |     |
| 3D printing | 3D printing of the case | 1   | 0.87 | 0.87 |     |
