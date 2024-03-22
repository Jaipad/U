// Login.js
import React, { useState } from 'react';
import { StyleSheet, View, TextInput, Pressable, Text } from 'react-native';
import { useNavigation } from '@react-navigation/native';
export default function Login({ onLogin }) {
    const [username, setUsername] = useState('');
    const [password, setPassword] = useState('');
    const navigation = useNavigation();
    const usuarios = [
        { usuario: 'Admin', contraseña: 'Super' },
        { usuario: 'usuario2', contraseña: 'contraseña2' },
    ];
    const handleLogin = () => {
        const usuarioEncontrado = usuarios.find(
            (user) => user.usuario === username && user.contraseña === password
        );
        if (usuarioEncontrado) {
            onLogin && onLogin();
            navigation.navigate('Home');
        } else {
            alert('Nombre de usuario o contraseña incorrectos');
        }
    };
    return (
        <View style={styles.container}>
            <Text style={styles.title}>Login</Text>
            <Text style={styles.subtitle}>Ingresa tus credenciales</Text>
            <View style={styles.loginContainer}>
                <View style={styles.inputContainer}>
                    <TextInput
                        style={styles.input}
                        placeholder="Nombre de usuario"
                        value={username}
                        onChangeText={(text) => setUsername(text)}
                    />
                </View>
                <View style={styles.inputContainer}>
                    <TextInput
                        style={styles.input}
                        placeholder="Contraseña"
                        secureTextEntry
                        value={password}
                        onChangeText={(text) => setPassword(text)}
                    />
                </View>
                <Pressable style={styles.loginButton} onPress={handleLogin}>
                    <Text style={styles.buttonLabel}>Iniciar sesión</Text>
                </Pressable>
            </View>
        </View>
    );
}
const styles = StyleSheet.create({
    container: {
        flexGrow: 1,
        backgroundColor: '#007bff',
        alignItems: 'center',
    },
    title: {
        marginTop: 20,
        fontSize: 30,
        paddingTop: 58,
    },
    subtitle: {
        fontSize: 20,
        textAlign: 'center',
        color: '#000',
    },
    footerContainer: {
        flex: 1 / 3,
        alignItems: 'center',
    },
    loginContainer: {
        width: 300,
        padding: 20,
        borderRadius: 10,
    },
    inputContainer: {
        marginBottom: 20,
    },
    input: {
        height: 40,
        borderColor: '#000',
        borderWidth: 1,
        borderRadius: 40,
        paddingHorizontal: 10,
        backgroundColor: '#E6EBEB',
    },
    loginButton: {
        borderRadius: 40,
        height: 40,
        alignItems: 'center',
        justifyContent: 'center',
        backgroundColor: '#000',
        borderColor: '#000',
        borderWidth: 1,
    },
    buttonLabel: {
        color: '#fff',
        fontSize: 16,
    },
});
