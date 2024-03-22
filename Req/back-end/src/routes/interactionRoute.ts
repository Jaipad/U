import express from "express";
import {
  createInteraction,
  editInteraction,
  getAllInteractions,
  getOneInteraction,
  removeInteraction,
} from "../controllers/InteractionController";

// Crear instancia del router ()
const router = express.Router();

// Lo utilizamos igual que antes app.post -> router.post
router.post("/", createInteraction);
router.get("/", getAllInteractions);
router.get("/:command", getOneInteraction);

// Solución
router.delete("/:command", removeInteraction);
router.put("/:command", editInteraction);

// exportamos el router con el nombre commandRouter
export { router as interactionRouter };
