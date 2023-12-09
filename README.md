# Spartan Racing BMS R&D Repository
A senior project with a goal to produce an in-house BMS using the LTC6813 to support a 600V pack, as well as analysis software to view cell data and configure the BMS.<br/>
<br/>

## Project Demonstration
[![YouTube Video of Project Demo](https://img.youtube.com/vi/ieQdnhzClfs/0.jpg)](https://www.youtube.com/watch?v=ieQdnhzClfs)


## Project Folder Structure
- `altium/` : Altium Designer project files for the custom BMS master and slave PCB (schematic & layout)
- `doc/` : Supplementary documentation, mostly hardware-related (like datasheets)
- `examples/` : Firmware examples for the BMS master, various programs.
	- The primary example that was utilized was `stm32f105_isospi`
- `gui/` : GUI Analysis Software for the host computer , to visualize battery cell data and communicate with the BMS master PCBA.
- `media/` : Various photos and such

## Environment Setup
### Version Control
1. Install git ([Windows](https://git-scm.com/downloads))
2. Clone this repo into any reachable folder using, in a command line of your choice (WSL Ubuntu, PowerShell, Terminal, etc), `git clone https://github.com/spartanracingelectric/SR-BMS.git`
    1. Change your branch if necessary by using `git checkout <BRANCH_NAME>`

### Altium Designer PCB Design Setup
Simple, just open either the master or slave `.PrjPcb` files in Altium!

### Firmware Setup
1. Install STM32CubeIDE and STM32CubeProgrammer.
2. In STM32CubeIDE, import the projects from `examples/`.
3. In STM32CubeIDE, click the "build" hammer on the toolbar to compile/build one of the programs in `examples/`.
4. In STM32CubeProgrammer, flash the `.elf` binary generated in the specific example project's `Debug/` to the BMS master PCBA over ST-Link or USB.
5. Note: STM32CubeMX to make any initialization-level configuration changes for the microcontroller.

### GUI Setup
1. cd gui/bms_app
	- install necessary react scripts using 'npm install react-scripts' 
2. Backend and frontend must be run concurrently 
	- frontend: open terminal in bms_app folder use: 'npm start' 
	- backend: open terminal in serialcomm folder 'npm run dev' 
	- backend deals w/ serial communication. Ensure that the correct COM port is defined in server.js!
	- to view the backend use the url: "http://localhost:8000/graphdata" 
<br/>


## SR BMS R&D Senior Project Team
_Vincent Saw_, Ex-Software Lead for Spartan Racing, Firmware & Hardware & Integration<br/>
_Vincent Pham_, Project Member, Firmware & Hardware<br/>
_Josh Samoy_, Project Member, Firmware & Software<br/>
_Abegail Palad_, Project Member, Firmware & Software<br/>
<br/>

## Links
[Primary Repo for BMS Senior Project](https://github.com/spartanracingelectric/SR-BMS)<br/>
[Old GUI Analysis Software Repo](https://github.com/Sensei-Josh/Senior_project_GUI)<br/>
[Spartan Racing Website](https://www.sjsuformulasae.com/)<br/>
