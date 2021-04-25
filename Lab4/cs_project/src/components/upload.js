import '../App.css';
import { sendImage } from '../models'
import React, { useState, useEffect } from 'react';
import { changeSentStatus, setCurrentImageId } from '../store/actions';
import { connect } from 'react-redux';

const mapStateToProps = state => {
  return {
    sentStatus: state.sentStatus
  };
}

function mapDispatchToProps(dispatch) {
  return {
    changeSentStatus: event => dispatch(changeSentStatus()),
    setCurrentImageId: image_id => dispatch(setCurrentImageId(image_id))
  }
}

function makeId(length) {
  var result = [];
  var characters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz123456789';
  var charactersLength = characters.length;
  for ( var i = 0; i < length; i++) {
    result.push(characters.charAt(Math.floor(Math.random() * charactersLength)));
  }
  return result.join("");
}

function ConnectedUpload(props) {
  //add state
  const [state, setState] = useState({
    status: '',
    uploaded: false,
    sent: false,
    received: false
  });

  async function fileUpload (event) {
    if (event.target.files && event.target.files[0]) {
      if (event.target.files.length > 1){
        setState({status: "Too many files uploaded. Please upload one at a time.", uploaded: false});
        return null;
      }
      if (event.target.files[0]['type'] !== "image/png") {
        setState({status: "Service can only handle PNG images", uploaded: false});
        return null;
      }
    }
  };

  async function sendFile () {
    setState({sent: true, uploaded: false});
    let input = document.getElementById('image-upload');
    let img = input.files[0];
    let id = makeId(8);
    props.setCurrentImageId(id);
    input.value = "";
    let res = sendImage(img, id)
    let res_resolved = await res;
    setState({received: true, sent: false});
    console.log("Sent");
    props.changeSentStatus();
  }

  const didUpdate = event => {
    if (props.sentStatus){
      setState({sent: false, received: false});
    }
  }

  return (
    <div className="App">
      <input type="file" id="image-upload" onChange={sendFile}/>
      {state.uploaded ? <button className="waves-effect waves-light btn" onClick={sendFile} >Upload Image</button> : null}
    </div>
  );
}

const Upload = connect(mapStateToProps, mapDispatchToProps)(ConnectedUpload)

export default Upload;
