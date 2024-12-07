import ReactDOM from "react-dom/client";
import { BrowserRouter, Routes, Route } from "react-router-dom";
import Layout from "./pages/Layout";
import Controls from "./pages/Controls";
import Leds from "./pages/Leds";
import NoPage from "./pages/NoPage";
import DataSender from "./DataSender";
import "./App.css"
import { DataProvider } from "./DataContext";
import { FullscreenDataProvider } from "./IsFullscreenContext";

export default function App() {
  return (
    <>
    <DataProvider>
      <FullscreenDataProvider>
        <BrowserRouter>
          <Routes>
            <Route path="/" element={<Layout />}>
            <Route index element={<Controls />} />
              <Route path="leds" element={<Leds />} />
              <Route path="*" element={<NoPage />} />
            </Route>
          </Routes>
        </BrowserRouter>
      </FullscreenDataProvider>
      <DataSender></DataSender>
    </DataProvider>
    </>
  );
}

const root = ReactDOM.createRoot(document.getElementById('root'));
root.render(<App />);
/*ReactDOM.render(
  <React.StrictMode>
    <DataProvider>
      <App />
    </DataProvider>
  </React.StrictMode>,
  document.getElementById('root')
);*/

