import { Outlet, Link } from "react-router-dom";
import useOrientation from '../useOrientation';
import logo from "../powerTrainLogo.png"

const Layout = () => {
  const style = useOrientation() ? "vertical" : "horizontal";

  return (
    <>
      <nav className={style}>
        <ul className={style}>
          <li className={style}>
            <Link to="/"><h1 class="navbar-vertical-text">Controls</h1></Link>
          </li>
          <li className={style}>
            <Link to="/leds"><h1 class="navbar-vertical-text">Leds</h1></Link>
          </li>
          <li>
            <div className="imageWrapper"><img src={logo} alt="" className={style}></img></div>
          </li>
        </ul>
      </nav>

      <Outlet />
    </>
  )
};

export default Layout;