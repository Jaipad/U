import express from "express";
import { updateBot, stopBot, startBot } from "../controllers/botController";

const router = express.Router();

router.post("/start", startBot);
router.post("/update", updateBot);
router.get("/stop", stopBot);

export { router as botRouter };
