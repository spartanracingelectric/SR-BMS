import './App.css';
import AppHeader from './header/Header.js';
import TabPage from './Components/Tabs';

/*
    AppHeader controls top portion of GUI
    	-can create links to lead to different pages
    	-for now there is only the TabPage
    TabPage hold the multiple tabs as shown in GUI mockup
    	-lower portion of GUI
    	-tabs seem more convenient than using buttons to navigate between pages
*/

function App() {
  	return (
    	<div className="App">
    		<AppHeader />
    		<TabPage />
    	</div>
  );
}

export default App;
