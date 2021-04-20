import React from 'react';
import '../App.css';
import { Header } from './Header';
import { BrowserRouter, Switch, Route } from 'react-router-dom';
import { routes } from '../routes';

function App() {
  return <>
    <BrowserRouter>
      <Header/>
      <Switch>
      {
        routes.map((route, id) => {
          return <Route key={id} exact {...route}/>
        })
      }
      </Switch>
    </BrowserRouter>
  </>;
}

export default App;
