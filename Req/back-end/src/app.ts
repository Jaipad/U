import express from "express";
import cors from "cors";
import "dotenv/config";
//Importar la mini aplicación que definimos
import { interactionRouter } from "./routes/interactionRoute";
import { botRouter } from "./routes/botRoute";

const app = express();
app.use(express.json());
app.use(cors());
const port = 3000;
//Utilizar la mini aplicación
app.use("/api/command", interactionRouter);
app.use("/api/bot", botRouter);

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`);
});
