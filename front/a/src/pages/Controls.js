import JoystickX from "../JoystickX";
import ThrottleSlider from "../ThrottleSlider";
import Visualisation from "../Visualisation";
import useOrientation from "../useOrientation";

const Controls = () => {
  if(useOrientation()){
    return (
      <div className="controlPage">
        <div className="controlJoystick">
          <JoystickX></JoystickX>
        </div>
        <div className="controlThrottle">
          <ThrottleSlider></ThrottleSlider>
        </div>
      </div>
    );
  }
  else{
    return(
      <></>
    )
  }
  };
  
  export default Controls;