import '../App.css';
import { getImage, clearImage } from '../models'
import React, { useEffect, useState } from 'react';
import { connect } from 'react-redux';
import { changeSentStatus, setCurrentImageId } from '../store/actions';

const mapStateToProps = state => {
  return { 
    sentStatus: state.sentStatus,
    currentImageId: state.currentImageId
  };
}

function mapDispatchToProps (dispatch) {
  return {
    changeSentStatus: event => dispatch(changeSentStatus()),
    setCurrentImageId: image_id => dispatch(setCurrentImageId(image_id))
  }
}

function ConnectedDisplay({ sentStatus, changeSentStatus, currentImageId, setCurrentImageId }) {
  const [image, setImage] = useState(null)

  function wipeImage () {
    clearImage(currentImageId);
    setCurrentImageId(null);
  }

  async function getData() {
    const data = getImage(currentImageId);
    const data_resolved = await data;
    setImage(data_resolved)
    wipeImage();
  }

  function didUpdate() {
    if (sentStatus){
      getData()
      changeSentStatus()
    }
  }

  useEffect(didUpdate);

  return (
    <div className="App">
      <img alt="" src={image}/>
      {image === null ? <p>Image will be displayed here when processed</p> : <></>}
    </div>
  );
}

const Display = connect(mapStateToProps, mapDispatchToProps)(ConnectedDisplay);

export default Display;
