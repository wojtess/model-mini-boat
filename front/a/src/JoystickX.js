import { Joystick } from "react-joystick-component";
import { JoystickShape } from "react-joystick-component";
import { DataContext } from "./DataContext";
import useOrientation from "./useOrientation";
import React, { useContext, useState, useEffect } from 'react';

const JoystickX = () => {
    const { dataToSend, setDataToSend } = useContext(DataContext);

    const [joySize, setJoySize] = useState(window.innerHeight * 0.5);


    //RESIZING JOYSTICK
    useEffect(() => {
      const handleFullscreenChange = () => {
        if (!document.fullscreenElement) {
          console.log("Exited fullscreen");
          // Call your function here
          setJoySize(window.innerHeight * 0.6);
        }
      };
  
      document.addEventListener("fullscreenchange", handleFullscreenChange);
  
      return () => {
        document.removeEventListener("fullscreenchange", handleFullscreenChange);
      };
    }, []);

    const updateMessage = (x) => {
        setDataToSend((prev) => ({
          ...prev,
          joyPos: x
        }));
      };

    const onMove = (stick) => {
        updateMessage(stick.x);
    };

    const onStop = (stick) => {
        updateMessage(0);
    };

    if(useOrientation()){
    return (<Joystick controlPlaneShape={JoystickShape.AxisX} size={joySize} move={onMove} stop={onStop}></Joystick>);}
    else{return (<Joystick controlPlaneShape={JoystickShape.AxisX} size={joySize*0.7} move={onMove} stop={onStop}></Joystick>);}
}
export default JoystickX;