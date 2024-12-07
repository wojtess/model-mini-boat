import React, { useContext,useState } from 'react';
import { DataContext } from "./DataContext";
import useOrientation from "./useOrientation";
import Speedometer, {
    Background,
    Arc,
    Needle,
    Progress,
    Marks,
    Indicator,
  } from 'react-speedometer';
 const SpeedometerComponent = () => {
    const { dataToSend} = useContext(DataContext);
    const [height] = useState(window.innerHeight * 0.4);
    if(useOrientation()){
    return (
          <Speedometer value={115} fontFamily="squada-one" 
          height={height} width={height}>
            <Background/>
            <Arc />
            <Needle color='#def2f5' circleColor='#3A6D8C'/>
            <Progress />
            <Marks fontSize={height*0.08}/>
            <Indicator fontSize={height*0.1}/>
          </Speedometer>
        );}
        else{
        return (
          <Speedometer value={115} fontFamily="squada-one" 
          height={height*0.7} width={height*0.7}>
            <Background/>
            <Arc />
            <Needle color='#def2f5' circleColor='#3A6D8C'/>
            <Progress />
            <Marks fontSize={height*0.08}/>
            <Indicator fontSize={height*0.1}/>
          </Speedometer>
        );
        }
      };
      
      export default SpeedometerComponent;