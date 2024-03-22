import "./App.css";
import styled from "styled-components";
import { useState, useEffect } from "react";
const url = import.meta.env.VITE_URL_ENDPOINTS;

const Header = styled.header`
  background-color: #fbfbfe;
  margin: 0;
  padding: 1rem;
  border-bottom: 1px solid black;
`;

const Title = styled.h1`
  color: #050315;
  font-size: 2rem;
  font-weight: 400;
`;

interface Interaction {
  command: string;
  message: string;
}

const initalState = {
  command: "",
  message: "",
};

function App() {
  const [isModalOpen, setIsModalOpen] = useState(false); // Estado para controlar la ventana modal
  const [interactions, setInteractions] = useState<Interaction[]>([]);
  const [formInteraction, setFormInteraction] =
    useState<Interaction>(initalState);

  useEffect(() => {
    fetch(`${url}/api/command`)
      .then((response) => response.json())
      .then(({ data }) => setInteractions(data));
  }, [interactions]);

  const botEventStop = (action: string) => {
    fetch(`${url}/api/bot/${action}`)
      .then((response) => response.json())
      .then((data) => console.log(data));
  };

  const botEventStart = (action: string) => {
    fetch(`${url}/api/bot/${action}`, {
      method: "POST",
      body: JSON.stringify({ interactions: interactions }),
      headers: { "Content-type": "application/json; charset=UTF-8" },
    })
      .then((response) => response.json())
      .then((data) => console.log(data));
  };

  const botEventUpdate = (action: string) => {
    fetch(`${url}/api/bot/${action}`, {
      method: "POST",
      body: JSON.stringify({ interactions: interactions }),
      headers: { "Content-type": "application/json; charset=UTF-8" },
    })
      .then((response) => response.json())
      .then((data) => console.log(data));
  };

  const onEventHandler = (
    e: React.ChangeEvent<HTMLInputElement | HTMLTextAreaElement>
  ) => {
    setFormInteraction({ ...formInteraction, [e.target.name]: e.target.value });
  };

  const createInteraction = () => {
    fetch(`${url}/api/command`, {
      method: "POST",
      body: JSON.stringify(formInteraction),
      headers: { "Content-type": "application/json; charset=UTF-8" },
    })
      .then((response) => response.json())
      .then((json) => console.log(json))
      .catch((err) => console.log(err));
    setInteractions([...interactions, formInteraction]);
    setFormInteraction(initalState);
  };

  const searchInteraction = (event: React.ChangeEvent<HTMLInputElement>) => {
    setInteractions(
      interactions.filter((interaction) =>
        interaction.command.includes(event.target.value)
      )
    );
    console.log(interactions);
  };

  if (interactions.length === 0) return <div> Cargando..</div>;

  return (
    <>
      <Header>
        <Title>Bot APP</Title>
        <button onClick={() => botEventUpdate("update")}>Reiniciar</button>
        <button onClick={() => botEventStart("start")}>Iniciar</button>
        <button onClick={() => botEventStop("stop")}>Parar</button>
      </Header>

      <article>
        <input
          placeholder="Search"
          onChange={(event) => searchInteraction(event)}
        ></input>

        {/* Botón para abrir la ventana modal */}
        <button onClick={() => setIsModalOpen(true)}>Create Interaction</button>

        {/* Ventana modal */}
        {isModalOpen && (
          <Modal>
            <div>
              <input
                placeholder="command"
                name="command"
                onChange={(event) => onEventHandler(event)}
                value={formInteraction.command}
              ></input>
              <textarea
                placeholder="message"
                name="message"
                onChange={(event) => onEventHandler(event)}
                value={formInteraction.message}
              ></textarea>
              <button className="aceptarButton" onClick={() => createInteraction()}>Aceptar</button>
              <button className="cancelarButton" onClick={() => setIsModalOpen(false)}>Cancelar</button>
            </div>
          </Modal>
        )}

        {/* Interactions */}
        {interactions.map((interaction: Interaction, Index) => (
          <div key={Index}>
            <p>{interaction.command}</p>
            <p>{interaction.message}</p>
          </div>
        ))}
        {/* Más código... */}
      </article>
    </>
  );
}

// Estilos para la ventana modal
const Modal = styled.div`
position: fixed;
top: 0;
left: 0;
width: 100%;
height: 100%;

background-color: rgba(0, 0, 0 , 0.5);
display: flex;
justify-content: center;
align-items: center;

  div {
    background-color: white;
    padding: 1rem;
    border-radius: 5px;
  }
`;

export default App;