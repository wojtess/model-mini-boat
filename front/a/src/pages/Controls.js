import JoystickX from "../JoystickX";
import ThrottleSlider from "../ThrottleSlider";
import Visualisation from "../Visualisation";
import useOrientation from "../useOrientation";
import SpeedometerComponent from "../Speedometr";
import Temp_Display from "../Temp";
//import Fullscreen from "../Fullscreen";

const Controls = () => {
  if(useOrientation()){
    return (
      <div className="controlPage">
        
        <div className="controlJoystick">
          <JoystickX></JoystickX>
        </div>
        <div className="controlPanel">
          <div className="controlSpeed"><SpeedometerComponent></SpeedometerComponent></div>
          <div className="controlTemp"><Temp_Display></Temp_Display></div>
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
          <div className="controlTemp-ho"><Temp_Display></Temp_Display></div>
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