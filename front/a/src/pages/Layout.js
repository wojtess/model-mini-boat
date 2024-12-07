import { Outlet, Link, NavLink } from "react-router-dom";
import useOrientation from '../useOrientation';
import logo from "../powerTrainLogo.png";
import Fullscreen from "../Fullscreen";

const Layout = () => {
  const style = useOrientation() ? "vertical" : "horizontal";

  return (
    <>
      <nav className={style}>
      <div className="menu">
          <span></span>
          <span></span>
          <span></span>
        </div>
        <ul className={style}>
        <li>
            <div className="imageWrapper"><img src={logo} alt="logo" className={style}></img></div>
          </li>
          <li className={style}>
            <NavLink to="/"><h1 class="navbar-vertical-text">Controls</h1></NavLink>
          </li>
          <li className={style}>
            <NavLink to="/leds"><h1 class="navbar-vertical-text">Leds</h1></NavLink>
          </li>
          <li>
          <Fullscreen></Fullscreen>
          </li>
        </ul>
       
      </nav>
      <Outlet />
    </>
  )
};

export default Layout;