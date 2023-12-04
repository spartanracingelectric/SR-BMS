import "./home.css";
import logo from "./SJSU_logo.png";

function Home() {
    return(
        <div className = "HomePage">
            <hr className = "Divider" />
            <img className = "Img" alt = "homePic" src = {logo} />
            <div className = "Disclaimer">
                <text>Senior Project Fall 2023</text>
                <text>Analysis Sofware has achieved basic functionality.</text>
                <text>To monitor cell data navigate to the General tab</text>
            </div>
        </div>
    );
}

export default Home;