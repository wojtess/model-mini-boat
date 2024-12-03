import { DataContext } from "./DataContext";
import { useRef, useContext } from "react";


const LedsInput = () =>{
    const { dataToSend, setDataToSend } = useContext(DataContext);

    const textRef = useRef();
    const colorRef = useRef();

    const updateMessage = (x, y) => {
        setDataToSend((prev) => ({
          ...prev,
          text: x,
          color: y
        }));
      };

    const butonHandle = (e) => {
        updateMessage(textRef.current.value, colorRef.current.value);
    }

    return(
        <div className="led-div-input   ">
            <input type="text" value="PUT Powertrain" ref={textRef} className="led-text-input"/>
            <div class="led-color-and-button">
                <input type="color" defaultValue="#0000ff" ref={colorRef}  className="led-color-input"/>
                <div className="save-color-input-wrapper"><input type="button" className="save-color-input" value="SAVE" onClick={butonHandle}/></div>
            </div>
        </div>
    )
}

export default LedsInput;