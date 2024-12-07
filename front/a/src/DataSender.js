import { useEffect, useRef, useContext } from "react";
import { DataContext } from "./DataContext";

const DataSender = () => {
  const { dataToSend } = useContext(DataContext);
  const intervalRef = useRef(null);
  const dataRef = useRef(dataToSend);

  // Update the reference whenever the data changes
  useEffect(() => {
    dataRef.current = dataToSend;
  }, [dataToSend]);

  useEffect(() => {
    // Function to send data
    const sendData = async () => {
      try {
        const response = await fetch("http://192.168.4.1/api/v1/controls", {
          method: "POST",
          headers: {
            "Content-Type": "application/json",
          },
          body: JSON.stringify(dataRef.current), // Use the latest data
        });
        if (!response.ok) {
          console.error("Error sending data:", response.statusText);
        }
      } catch (error) {
        console.error("Network error:", error);
      }
    };

    // Start the interval
    intervalRef.current = setInterval(() => {
      sendData();
    }, 100);

    // Cleanup function
    return () => clearInterval(intervalRef.current);
  }, []); // Empty dependency ensures this runs only once
};

export default DataSender;