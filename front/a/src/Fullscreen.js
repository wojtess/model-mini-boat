import { useState, useEffect, useContext } from "react"
import { IsFullscreenContext } from "./IsFullscreenContext";

const Fullscreen = () => {

    const { fullscreenData, setFullscreenData }= useContext(IsFullscreenContext);

    const openFullscreen = () => {
      const elem = document.documentElement;
      if (elem.requestFullscreen) {
        elem.requestFullscreen();
      } else if (elem.webkitRequestFullscreen) {
        elem.webkitRequestFullscreen(); // Safari
      } else if (elem.msRequestFullscreen) {
        elem.msRequestFullscreen(); // IE11
      }
      setFullscreenData(false);
    };

    useEffect(() => {
        const handleFullscreenChange = () => {
          if (!document.fullscreenElement) {
            console.log("Exited fullscreen");
            // Call your function here
            setFullscreenData(true);
          }
        };
    
        document.addEventListener("fullscreenchange", handleFullscreenChange);
    
        // Cleanup on unmount
        return () => {
          document.removeEventListener("fullscreenchange", handleFullscreenChange);
        };
      }, []);

    return (<>{fullscreenData && (<div>
        <button onClick={openFullscreen} className="save-color-input">FULL</button>
        </div>)}</>   
    );
  };

  export default Fullscreen;