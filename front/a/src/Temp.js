import { DataContext } from "./DataContext";
import React, { useContext, useState, useEffect, useRef } from 'react';
import useOrientation from "./useOrientation";

const Temp_Display = () => {
    const { dataToSend } = useContext(DataContext);
    const [currentTemp, setCurrentTemp] = useState(0);
    const animationRef = useRef(null);
    const lastUpdateTime = useRef(Date.now());
    
    const calculateTargetValue = (throttlePos) => {
        // Scale throttle position (0-100) to temperature range (0-999)
        return (throttlePos / 100) * 999;
    };

    useEffect(() => {
        const targetValue = calculateTargetValue(dataToSend.throttlePos);
        
        const updateTemp = () => {
            const now = Date.now();
            const deltaTime = (now - lastUpdateTime.current) / 1000; // Convert to seconds
            lastUpdateTime.current = now;
            
            setCurrentTemp(prevTemp => {
                // Heating and cooling rates (adjust these for different feel)
                const heatingRate = 100; // units per second (increased for larger range)
                const coolingRate = 60; // units per second (increased for larger range)
                
                let newTemp = prevTemp;
                
                if (dataToSend.throttlePos > 0) {
                    // Heating - move towards target value
                    if (prevTemp < targetValue) {
                        newTemp = Math.min(prevTemp + (heatingRate * deltaTime), targetValue, 999);
                    }
                    else if(prevTemp>targetValue){
                        newTemp = Math.max(prevTemp - (coolingRate * deltaTime), targetValue);
                    }
                } else {
                    // Cooling - move towards zero when throttle is 0
                    newTemp = Math.max(prevTemp - (coolingRate * deltaTime), 0);
                }
                
                // If we're close enough to target, snap to it
                if (Math.abs(newTemp - targetValue) < 0.5) {
                    newTemp = targetValue;
                }
                
                // Ensure temperature doesn't exceed 999
                newTemp = Math.min(newTemp, 999);
                return newTemp;
            });
            
            animationRef.current = requestAnimationFrame(updateTemp);
        };
        
        // Start the animation
        animationRef.current = requestAnimationFrame(updateTemp);
        
        // Cleanup
        return () => {
            if (animationRef.current) {
                cancelAnimationFrame(animationRef.current);
            }
        };
    }, [dataToSend.throttlePos]);

    // Format temperature display
    const formatTemperature = (temp) => {
        const roundedTemp = Math.round(temp);
        if (roundedTemp >= 100) {
            return roundedTemp;
        } else if (roundedTemp >= 10) {
            return '0' + roundedTemp;
        } else {
            return '00' + roundedTemp;
        }
    };

    if(useOrientation()){
        return (
            <div className="temp-background">
                <p className="text">Temp:</p>
                <div className="temp-label">
                    <div className="temp-back-text">888&deg;C</div>
                    <div className="temp-front-text">{formatTemperature(currentTemp)}&deg;C</div>
                </div>
            </div>
        );
    } else {
        return (
            <div className="temp-background-ho">
                <p className="text-ho">Temp:</p>
                <div className="temp-label-ho">
                    <div className="temp-back-text-ho">888&deg;C</div>
                    <div className="temp-front-text-ho">{formatTemperature(currentTemp)}&deg;C</div>
                </div>
            </div>
        );
    }
};

export default Temp_Display;