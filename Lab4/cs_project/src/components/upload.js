import '../App.css';
import sendImage from '../models'

function Upload() {
  const fileUpload = event => {
    if (event.target.files && event.target.files[0]) {
      let img = event.target.files[0];
      const res = sendImage(img);
    }
  };
  return (
    <div className="App">
      <input type="file" onChange={fileUpload}/>
    </div>
  );
}

export default Upload;
