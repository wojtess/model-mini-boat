import React, { createContext, useState } from 'react';

// Create the context
export const DataContext = createContext();

// Context provider component
export const DataProvider = ({ children }) => {
  const [dataToSend, setDataToSend] = useState({
    joyPos: 0,
    throttlePos: 0,
    text: "PUT Powertrain",
    color: '#0000ff',
  });

  return (
    <DataContext.Provider value={{ dataToSend, setDataToSend }}>
      {children}
    </DataContext.Provider>
  );
};