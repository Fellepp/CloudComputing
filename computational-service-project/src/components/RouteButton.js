import PropTypes from 'prop-types'
import { Link } from 'react-router-dom'

const Button = (props) => {
    return <button onClick={props.onClick} style={{ backgroundColor: props.color }} className='btn-block'> {props.text} </button>
}

Button.propTypes={
    text: PropTypes.string,
    color: PropTypes.string,
    onClick: PropTypes.func,
}

Button.defaultProp={
    color: 'grey',
    text: 'Service',
}

export default Button
