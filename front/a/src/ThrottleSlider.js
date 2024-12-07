import { DataContext } from "./DataContext";
import React, { useContext } from 'react';
import useOrientation from "./useOrientation";

const ThrottleSlider = () => {
    const { dataToSend, setDataToSend } = useContext(DataContext);

    const updateMessage = (x) => {
      setDataToSend((prev) => ({
        ...prev,
        throttlePos: x
      }));
    };


    const handleChange = (e) => {
        updateMessage(e.target.value)
    }
    if(useOrientation()){
    return (
        <div className="throttle-container">
          <div className="throttle-slider-wrapper">
          <input
            type="range"
            min="0"
            max="100"
            value={dataToSend["throttlePos"]}
            onChange={handleChange}
            className="throttle-slider"
          />
          </div>
          <div className="throttle-label">
            <div className="throttle-back-text">888%</div>
            <div className="throttle-front-text">{dataToSend["throttlePos"] == 100 ? 100 : dataToSend["throttlePos"] < 10 ? '00' + dataToSend["throttlePos"] : '0' + dataToSend["throttlePos"]}%</div>
          </div>
        </div>
      );}
      else{
        return(
        <div className="throttle-container-ho">
          <div className="throttle-slider-wrapper-ho">
          <input
            type="range"
            min="0"
            max="100"
            value={dataToSend["throttlePos"]}
            onChange={handleChange}
            className="throttle-slider-ho"
          />
          </div>
          <div className="throttle-label-ho">
            <div className="throttle-back-text-ho">888%</div>
            <div className="throttle-front-text-ho">{dataToSend["throttlePos"] == 100 ? 100 : dataToSend["throttlePos"] < 10 ? '00' + dataToSend["throttlePos"] : '0' + dataToSend["throttlePos"]}%</div>
          </div>
        </div>)
      }
    };
export default ThrottleSlider;