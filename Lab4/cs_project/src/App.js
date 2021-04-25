import logo from './logo.svg';
import './App.css';
import Upload from './components/upload';
import Display from './components/displayImage';
import { useState, useEffect } from 'react'

function App() {
  return (
    <div className="App">
      <h1>
        Computational Service!
      </h1>
      <h2>
        Upload an image and wait for it to process
      </h2>
      <Upload />
      <Display />
    </div>
  );
}

export default App;
