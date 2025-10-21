import React, { useContext, useState, useEffect, useRef } from 'react';
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
    const [currentSpeed, setCurrentSpeed] = useState(0);
    const animationRef = useRef(null);
    const lastUpdateTime = useRef(Date.now());
    
    // Calculate target value based on throttlePos
    const calculateTargetValue = (throttlePos) => {
        if (throttlePos <= 50) {
            return (throttlePos / 50) * 90;
        } else {
            const above50 = throttlePos - 50;
            return 90 + (above50 / 50) * 90;
        }
    };
    
    useEffect(() => {
        const targetValue = calculateTargetValue(dataToSend.throttlePos);
        
        const updateSpeed = () => {
            const now = Date.now();
            const deltaTime = (now - lastUpdateTime.current) / 1000; // Convert to seconds
            lastUpdateTime.current = now;
            
            setCurrentSpeed(prevSpeed => {
                // Acceleration and deceleration factors (adjust these for different feel)
                const acceleration = 15; // units per second
                const deceleration = 25; // units per second
                
                let newSpeed = prevSpeed;
                
                if (dataToSend.throttlePos > 0) {
                    // Accelerating - move towards target value
                    if (prevSpeed < targetValue) {
                        newSpeed = Math.min(prevSpeed + (acceleration * deltaTime), targetValue);
                    }
                    else if(prevSpeed>targetValue){
                        newSpeed = Math.max(prevSpeed - (deceleration * deltaTime), targetValue);
                    }
                } else {
                    // Decelerating - slowly return to zero when throttle is 0
                    newSpeed = Math.max(prevSpeed - (deceleration * deltaTime), 0);
                }
                
                // If we're close enough to target, snap to it
                if (Math.abs(newSpeed - targetValue) < 0.5) {
                    newSpeed = targetValue;
                }
                
                return newSpeed;
            });
            
            animationRef.current = requestAnimationFrame(updateSpeed);
        };
        
        // Start the animation
        animationRef.current = requestAnimationFrame(updateSpeed);
        
        // Cleanup
        return () => {
            if (animationRef.current) {
                cancelAnimationFrame(animationRef.current);
            }
        };
    }, [dataToSend.throttlePos]);

    if(useOrientation()){
    return (
          <Speedometer value={currentSpeed} fontFamily="squada-one" 
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