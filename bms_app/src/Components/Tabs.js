import { Tab, Tabs, TabList, TabPanel } from 'react-tabs';
import './reactTabs.css';
import DataAnalysis from './allTabs/DataAnalysis/DataAnalysis.js';
import Connection from './allTabs/Connection/Connection.js';

//main block for the Tab page

const TabPage = () => (
	<Tabs>
		<TabList>
			{/*Add Tabs here, presented in order*/}
			<Tab> Connection </Tab>
			<Tab> Firmware </Tab>
			<Tab> DataAnalysis </Tab>
			<Tab> Terminal </Tab>
			<Tab> Debug Console </Tab>
		</TabList>
		
		{/*
			Add tab contents here correspond to a 'Tab' above:
				Import tab pages from tabs you create in allTabs folder for consistency
				Invoke the tab in a 'TabPanel'
		*/}
		
		<TabPanel>
      			<Connection />
    		</TabPanel>
    		
    		<TabPanel>
      			{/*Firmware*/}
    		</TabPanel>
    		
    		<TabPanel>
      			<DataAnalysis />
    		</TabPanel>
    		
    		<TabPanel>
      			{/*Terminal*/}
    		</TabPanel>
    		
    		<TabPanel>
      			{/*Debug Console*/}
    		</TabPanel>
	</Tabs>
);

export default TabPage;
