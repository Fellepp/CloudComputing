import { CHANGE_SENT_STATUS, CURRENT_IMAGE_ID } from './constants'

export function changeSentStatus() {
    return { type: CHANGE_SENT_STATUS }
  }

export function setCurrentImageId(payload){
  return { type: "CURRENT_IMAGE_ID", payload }
}
