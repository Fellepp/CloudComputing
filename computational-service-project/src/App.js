import './index.css';
import { BrowserRouter as Router, Route} from 'react-router-dom'
import Header from "./components/Header"
import Services from './components/Services'
import Footer from './components/Footer'
import About from './components/About'
import Service from './components/Service'

function App() {
  return (
    <Router>
      <div className="container">
        <Header/>
        <Route path="/" exact render={(props)=> (
          <>
            <Services/>
          </>
        )}/>
        <Route path="/about" component={About}/>
        <Route path="/service" component={Service}/>
        <Footer/>
      </div>
    </Router>
  );
}

export default App;
