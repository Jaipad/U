// Home.js
import React from 'react';
import { View, Text, StyleSheet, Pressable } from 'react-native';

export default function Home({ navigation }) {
    const handleCommand = () => {
        navigation.navigate('Command');
    };

    return (
        <View style={styles.container}>
            <Text style={styles.title}>Home</Text>
            <View style={styles.messageContainer}>
                <Text style={styles.message}>Esta aplicación tiene como finalidad...</Text>
            </View>
            <Pressable style={styles.customButton} onPress={handleCommand}>
                <Text style={styles.buttonLabel}>Ir a la pantalla bot</Text>
            </Pressable>
        </View>
    );
}
const styles = StyleSheet.create({
    container: {
        flex: 1,
        backgroundColor: '#007bff',
        alignItems: 'center',
        justifyContent: 'center',
    },
    title: {
        fontSize: 30,
        color: '#fff',
        marginBottom: 20,
    },
    messageContainer: {
        backgroundColor: '#fff',
        padding: 60,
        marginBottom: 20,
        borderColor: '#000',
        borderWidth: 1,
        borderRadius: 20,
    },
    message: {
        fontSize: 20,
        color: '#000',

    },
    customButton: {
        borderRadius: 40,
        height: 40,
        alignItems: 'center',
        justifyContent: 'center',
        backgroundColor: '#000',
        borderColor: '#000',
        borderWidth: 1,
        width: 200,
    },
    buttonLabel: {
        color: '#fff',
        fontSize: 16,
    },
});
