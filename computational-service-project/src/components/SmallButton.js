import PropTypes from 'prop-types'

const SmallButton = (props) => {
    return <button style={{ backgroundColor: props.color }} className='btn'> {props.text} </button>
}

SmallButton.defaultProp={
    color: 'green',
    text: 'Add new service',
}

SmallButton.propTypes= {
    text: PropTypes.string,
    color: PropTypes.string,
}

export default SmallButton
