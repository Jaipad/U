// CommandInput.js
import React, { useState } from 'react';
import { View, Text, StyleSheet, TextInput, Pressable, Alert } from 'react-native';

import axios from 'axios';

export default function CommandInput({ navigation }) {

    const [command, setCommand] = useState('');
    
    const [instruction, setInstruction] = useState('');
    const [interactionCreated, setInteractionCreated] = useState(false);
    const [BotRunning, setBotRunning] = useState(false);
    const [commands, setCommands] = useState([]);



    const sendCommand = async () => {
        try {
            const response = await axios.post('http://localhost:3000/api/command', {
                command: command,
                message: instruction,
            })
            console.log(response.data);
        } catch (error) {
            console.log('Error al enviar el comando:', error);
        }
    }
    const startBot = async () => {
        try {
            const response = await axios.post('http://localhost:3000/api/bot/start');
            const responseData = response.data;
            if (responseData.ok === "success") {
                Alert.alert("Bot iniciado con éxito");
                setBotRunning(true);
            } else {
                console.error('Error al iniciar el bot:', responseData.error);
            }

        } catch (error) {
            console.error('Error al iniciar el bot:', error);
        }
    }   
    const stopBot = async () => {
        try {
            const response = await axios.get('http://localhost:3000/api/bot/stop');
            if (response.data.ok === "success") {
                Alert.alert("Bot detenido con éxito");
                setBotRunning(false);
            } else {
                console.error('Error al detener el bot:', response.data.error);
            }
        } catch (error) {
            console.error('Error al detener el bot:', error);
        }
    };
    const getCommands = async () => {
        try {
            const response = await axios.get('http://localhost:3000/api/command');
            const responseData = response.data;

            if (responseData.ok === 'success') {
                const commandsData = responseData.data || [];
                setCommands(commandsData);
                console.log('Comandos obtenidos:', commandsData);
                setInteractionCreated(true);
            } else {
                console.error('Error al obtener los comandos:', responseData.error);
            }
        } catch (error) {
            console.error('Error al obtener los comandos:', error);
        }
    };
    const updateBot = async () => {
        try {
            const response = await axios.post('http://localhost:3000/api/bot/update', {
            })
        } catch (error) {

        }
    }
    const handleSendCommand = async () => {
        await sendCommand();
        alert(`Comando: ${command}\nInstrucción: ${instruction}`);
        setInteractionCreated(true);
    }
    return (
        <View style={styles.container}>
            <View style={styles.innerContainer}>
                <Text style={styles.title}>Comando</Text>
                <Text style={styles.subtitle}>Ingrese su comando</Text>
                <View style={styles.inputContainer}>
                    <TextInput
                        style={styles.input}
                        placeholder="Nombre del comando"
                        value={command}
                        onChangeText={(text) => setCommand(text)}
                    />
                </View>
                <View style={styles.inputContainer}>
                    <TextInput
                        style={styles.input}
                        placeholder="Instrucción"
                        value={instruction}
                        onChangeText={(text) => setInstruction(text)}
                    />
                </View>
                <Pressable style={styles.sendButton} onPress={handleSendCommand}>
                    <Text style={styles.buttonLabel}>Enviar Comando</Text>
                </Pressable>
                {interactionCreated && (
                    <View style={styles.buttonContainer}>
                        <Pressable style={styles.startStopButton} onPress={startBot}>
                            <Text style={styles.buttonLabel}>Iniciar Bot</Text>
                        </Pressable>
                        {BotRunning && (
                            <Pressable style={styles.startStopButton} onPress={stopBot}>
                                <Text style={styles.buttonLabel}>Detener Bot</Text>
                            </Pressable>
                        )}
                    </View>
                )}

                {interactionCreated && (
                    <Pressable style={styles.getCommandsButton} onPress={getCommands}>
                        <Text style={styles.buttonLabel}>Obtener Comandos</Text>
                    </Pressable>
                )}
                {commands.length > 0 && (
                    <View style={styles.commandsContainer}>
                        <Text style={styles.title}>Comandos Obtenidos:</Text>
                        <View style={styles.commandsBox}>
                            {commands.map((cmd, index) => (
                                <View key={index} style={styles.commandItem}>
                                    <Text style={styles.commandText}>Comando: {cmd.command}</Text>
                                    <Text style={styles.commandText}>Mensaje: {cmd.message}</Text>
                                </View>
                            ))}
                        </View>
                    </View>
                )}
            </View>
        </View>
    );
};
const styles = StyleSheet.create({
    container: {
        flex: 1,
        backgroundColor: '#007bff',
        alignItems: 'center',
        justifyContent: 'center',
    },
    innerContainer: {
        marginBottom: 20,
    },
    title: {
        fontSize: 30,
        color: '#fff',
        marginBottom: 20,
        textAlign: 'center',
    },
    subtitle: {
        fontSize: 20,
        color: '#fff',
        marginBottom: 20,
        textAlign: 'center',
    },
    inputContainer: {
        marginBottom: 20,
    },
    input: {
        backgroundColor: '#fff',
        height: 40,
        borderColor: '#000',
        borderWidth: 1,
        borderRadius: 40,
        paddingHorizontal: 10,
    },
    sendButton: {
        borderRadius: 40,
        height: 40,
        marginBottom: 10,
        alignItems: 'center',
        justifyContent: 'center',
        backgroundColor: '#000',
        borderColor: '#000',
        borderWidth: 1,
    },
    buttonLabel: {
        color: '#fff',
        fontSize: 16,
        textAlign: 'center',
    },
    buttonContainer: {
        flexDirection: 'row',
        justifyContent: 'space-between',
        width: '100%',
    },
    startStopButton: {
        borderRadius: 40,
        height: 40,
        flex: 1,
        marginLeft: 5,
        alignItems: 'center',
        justifyContent: 'center',
        backgroundColor: '#000',
        borderColor: '#000',
        borderWidth: 1,
    },

    getCommandsButton: {
        borderRadius: 40,
        height: 40,
        marginTop: 10,
        alignItems: 'center',
        justifyContent: 'center',
        backgroundColor: '#000',
        borderColor: '#000',
        borderWidth: 1,
    },
    commandsContainer: {
        marginTop: 20,
    },
    commandsBox: {
        borderColor: '#fff',
        borderWidth: 1,
        borderRadius: 10,
        padding: 10,
    },
    commandText: {
        fontSize: 16,
        color: '#fff',
        marginBottom: 5,
    },
    commandItem: {
        marginBottom: 10,
        padding: 10,
        backgroundColor: '#333', // Puedes ajustar el color de fondo según tus preferencias
        borderRadius: 8,
    },
});
