import React, { createContext, useState } from 'react';

// Create the context
export const IsFullscreenContext = createContext();

// Context provider component
export const FullscreenDataProvider = ({ children }) => {
  const [fullscreenData, setFullscreenData] = useState(true);

  return (
    <IsFullscreenContext.Provider value={{ fullscreenData, setFullscreenData }}>
      {children}
    </IsFullscreenContext.Provider>
  );
};