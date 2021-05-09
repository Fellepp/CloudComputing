import Button from './RouteButton'
import React, { useEffect, useState } from 'react'
import { BrowserRouter as Router, Route} from 'react-router-dom'
import Service from './Service'
import { Link } from 'react-router-dom'
import { useHistory } from 'react-router-dom'


const Services = () => {
    const [services, setServices] = useState([])
    const history = useHistory();

    useEffect(() => {
        const getServices = async() => {
            const servicesFromServer = await fetchServices()
            setServices(servicesFromServer)
        }

        getServices()
    }, [])

    //Fetch services
    const fetchServices = async () => {
        const res = await fetch('http://localhost:5000/services')
        const data = await res.json()

        return data
    }

    const onClick = (props) => {
        history.push({
            pathname: "/service", 
            state: {...props}
        })
    }

    return (
        <div>
            <h3>Choose your service:</h3>
            {services.length > 0 ? services.map((service) => (
            <Button key={service.id} onClick={() => onClick(service)} color='gray' text={service.title}/>
            )) : <p>There are currently no services to show.</p>}
        </div>
    )
}

export default Services
