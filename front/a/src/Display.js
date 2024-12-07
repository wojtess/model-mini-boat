import { DataContext } from "./DataContext";
import React, { useContext } from 'react';
import useOrientation from "./useOrientation";

const Display = (props) => {
    const { dataToSend,} = useContext(DataContext);
    if(useOrientation()){
    return (
        <div className="temp-background">
            <p className="text">{props.name}: </p>
          <div className="temp-label">
            <div className="temp-back-text">888{props.unit}</div>
            <div className="temp-front-text">{dataToSend["tempPos"] == 100 ? 100 : dataToSend["tempPos"] < 10 ? '00' + dataToSend["tempPos"] : '0' + dataToSend["tempPos"]}{props.unit}</div>
          </div>
          </div>
      );}
      else{
        return (
          <div className="temp-background-ho">
              <p className="text-ho">Temp:</p>
            <div className="temp-label-ho">
              <div className="temp-back-text-ho">888{props.unit}</div>
              <div className="temp-front-text-ho">{dataToSend["tempPos"] == 100 ? 100 : dataToSend["tempPos"] < 10 ? '00' + dataToSend["tempPos"] : '0' + dataToSend["tempPos"]}{props.unit}</div>
            </div>
            </div>
        );
      }
    };
export default Display;