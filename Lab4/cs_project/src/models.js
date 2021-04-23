import axios from 'axios'

const baseURL = "http://127.0.0.1:5000"

function sendImage(img) {
    const formData = new FormData();
    formData.append("image", img);
    axios.post(baseURL + '/images', formData, {
    headers: {
        "Content-Type" : "image/png",
        }
    })
}
    

export default sendImage