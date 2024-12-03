import { useState, useEffect } from 'react';

const useOrientation= () => {
    const [isLandscape, setIsLandscape] = useState(window.innerWidth > window.innerHeight);

    useEffect(() => {
        function handleResize() {
            setIsLandscape(window.innerWidth > window.innerHeight);
        }
        window.addEventListener("resize", handleResize);
        return () => window.removeEventListener("resize", handleResize);
    }, []);

    return isLandscape;
}

export default useOrientation;