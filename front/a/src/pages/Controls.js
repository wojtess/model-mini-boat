import JoystickX from "../JoystickX";
import ThrottleSlider from "../ThrottleSlider";
import Visualisation from "../Visualisation";
import useOrientation from "../useOrientation";
import SpeedometerComponent from "../Speedometr";
import Display from "../Display";
//import Fullscreen from "../Fullscreen";

const Controls = () => {
  if(useOrientation()){
    return (
      <div className="controlPage">
        
        <div className="controlJoystick">
          <SpeedometerComponent></SpeedometerComponent>
        </div>
        <div className="controlPanel">
          <div className="controlTemp"><Display name="Ciśnienie" unit="Hg"></Display></div>
          <div className="controlTemp"><Display name="Temperatura" unit="&deg;C"></Display></div>
        </div>
        <div className="controlThrottle">
          <ThrottleSlider></ThrottleSlider>
        </div>
      </div>
    );
  }
  else{
    return(
      <div className="controlPage-ho">
        <div className="controlPanel-ho">
          <div className="controlSpeed-ho"><SpeedometerComponent></SpeedometerComponent></div>
          <div className="controlTemp-ho"><Display name="Temperatura" unit="&deg;C"></Display></div>
        </div>
        <div className="controlThrottle-ho">
          <ThrottleSlider></ThrottleSlider>
        </div>
        <div className="controlJoystick-ho">
          <JoystickX></JoystickX>
        </div>
      </div>
    )
  }
  };
  
  export default Controls;