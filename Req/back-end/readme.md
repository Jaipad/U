# Bot de telegram

## Endpoints

1. GET `localhost:3000/api/command`: Entrega todas las interacciones
2. GET `localhost:3000/api/command/<command>`: recibe el nombre del comando y si existe devuelve el comando y el mensaje
3. POST: `localhost:3000/api/command`: Crea una interacción que recibe un comando y un mensaje en el body. devuelve la lista con todas las interacciónes

```
body (ejemplo)
{
    "command": "first23",
    "message": "PRIMER COMANDO!"
}
```

4. PUT: `localhost:3000/api/command/<command>`: edita una interacción que recibe un comando y un mensaje en el body. devuelve la lista con todas las interacciónes.

```
body (ejemplo), (debe tener el mismo comando en la ruta y en el campo comando en el body)
{
    "command": "<command>",
    "message": "CAMBIO DE NOMBRE"
}
```

## BOT

5. POST `localhost:3000/api/bot/start`: Iniciar el bot, debe recibir una lista de interaciones
6. GET `localhost:3000/api/bot/stop`: Detiene el bot
7. POST `localhost:3000/api/bot/update`: Actualiza el bot, debe recibir una lista de interaciones

```
(body ejemplo y update)
{
    "interactions": [
        {
            "command": "first",
            "message": "comando de prueba"
        },
        {
            "command": "second",
            "message": "Segundo comando de prueba"
        },
    ]
}
```
