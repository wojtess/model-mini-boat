import { Joystick } from "react-joystick-component";
import { JoystickShape } from "react-joystick-component";
import { DataContext } from "./DataContext";
import React, { useContext } from 'react';

const JoystickX = () => {
    const { dataToSend, setDataToSend } = useContext(DataContext);

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


    return (<Joystick controlPlaneShape={JoystickShape.AxisX} size={window.innerHeight * 0.6} move={onMove} stop={onStop}></Joystick>);
}
export default JoystickX;