import axios from 'axios'

const baseURL = "http://127.0.0.1:4000";

function sendImage(img, id) {
    return axios.post(baseURL + '/images?id=' + id, img, {
        headers:{
            'Content-Type': "image/png"
        }
    })
    .then(function(response){
        return response;
    });
}

function getImage(image_id) {
    return axios.get(baseURL + '/images?id=' + image_id, { responseType: 'arraybuffer'})
    .then(response => {
        let blob = new Blob(
            [response.data],
            { type: response.headers['content-type'] }
        )
        let image = URL.createObjectURL(blob)
        return image
    });
}

function clearImage (image_id) {
    return axios.get(baseURL + '/cleanup?id=' + image_id)
    .then(response => {return response});
}

export {
    sendImage,
    getImage,
    clearImage
};