import { Link } from 'react-router-dom'

const Service = (props) => {
    return (
        <div>
            <h2>{props.location.state.title}</h2>
            <h4>{props.location.state.description}</h4>









            <Link to="/">Go Back</Link>
        </div>
    )
}

export default Service