import React from 'react'
import Button from './RouteButton'
import SmallButton from './SmallButton'
import { useLocation } from 'react-router-dom'

const Header = () => {
    const location = useLocation()

    const onClick = () => {
        console.log('Click')
    }

    return (
        <div>
            <header className='header'>
                <h1> Computational Service! </h1>
                {location.pathname === '/' && 
                <SmallButton color='green' text='Add new service'/>}
            </header>
        </div>
    )
}

export default Header
