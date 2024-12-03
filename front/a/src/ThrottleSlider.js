import { useState } from "react";
import { DataContext } from "./DataContext";
import React, { useContext } from 'react';

const ThrottleSlider = () => {
    const [throttle, setThrottle] = useState(0);
    const { dataToSend, setDataToSend } = useContext(DataContext);

    const updateMessage = (x) => {
      setDataToSend((prev) => ({
        ...prev,
        throttlePos: x
      }));
    };


    const handleChange = (e) => {
        setThrottle(e.target.value)
        updateMessage(e.target.value)
    }
    return (
        <div className="throttle-container">
          <div className="throttle-slider-wrapper">
          <input
            type="range"
            min="0"
            max="100"
            value={throttle}
            onChange={handleChange}
            className="throttle-slider"
          />
          </div>
          <div className="throttle-label">
            <div className="throttle-back-text">888%</div>
            <div className="throttle-front-text">{throttle == 100 ? 100 : throttle < 10 ? '00' + throttle : '0' + throttle}%</div>
          </div>
        </div>
      );
    };
export default ThrottleSlider;