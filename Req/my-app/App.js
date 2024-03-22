// App.js
import React from 'react';

import { NavigationContainer } from '@react-navigation/native';
import { createStackNavigator } from '@react-navigation/stack';


import Login from "./screens/Login";
import Home from './screens/Home';
import Command from './screens/Command';

const Stack = createStackNavigator();

export default function App() {
  return (
    <NavigationContainer>
      <Stack.Navigator initialRouteName="Login">
        <Stack.Screen name="Login" component={Login}/>
        <Stack.Screen name="Home" component={Home} />
        <Stack.Screen name="Command" component={Command} />
      </Stack.Navigator>
    </NavigationContainer>
  );
}
