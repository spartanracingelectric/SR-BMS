# Spartan Racing BMS R&D Repository
A senior project with a goal to produce an in-house BMS using the LTC6813 to support a 600V pack, as well as analysis software to view cell data and configure the BMS.<br/>
<br/>

## Dependencies
TODO<br/>
<br/>

## Environment Setup
### Version Control
1. Install git ([Windows](https://git-scm.com/downloads))
2. Clone this repo into any reachable folder using, in a command line of your choice (WSL Ubuntu, PowerShell, Terminal, etc), `git clone https://github.com/spartanracingelectric/SR-BMS.git`
    1. Change your branch if necessary by using `git checkout <BRANCH_NAME>`
<br/>

###  Software
1. after cloning repository open bms_app
	- install the react scripts using the following command: 'npm install react-scripts' 
	 otherwise you cannot run app on local host 
2. to use the backend you must run both the backend and frontend parts simultaneously 
	- frontend: open terminal in bms_app folder use: 'npm start' 
	- backend: open terminal in serialcomm folder 'npm run dev' 
	- backend deals w/ serial communication 
	- to view the backend use the url: "http://localhost:8000/graphdata" 

## SR BMS R&D Senior Project Team
_Vincent Saw_, SRE-5 & SRE-6 Ex-Software Lead, Firmware & Hardware & Integration<br/>
_Vincent Pham_, Project Member, Firmware & Hardware<br/>
_Josh Samoy_, Project Member, Firmware & Software<br/>
_Abegail Palad_, Project Member, Firmware & Software<br/>
<br/>

## Links
[Spartan Racing Website](https://www.sjsuformulasae.com/)<br/>
# Senior_project_GUI
React GUI code base

Note:



# In Progress
1. change graph info dynamically 
	-if it takes long default to just show graph info using list 
2. UML diagrams
