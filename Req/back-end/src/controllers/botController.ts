import { Telegraf } from "telegraf";
import { Interaction } from "../models/Interaction";
import { Request, Response } from "express";
import { getListInteraction } from "./InteractionController";

let bot = new Telegraf("6923508589:AAGhrH8tS2WO4TZYAvC4TGg-7AOm2VRzOrk");
let botIsRunning = false;

export const startBot = (req: Request, res: Response) => {
  if (botIsRunning) {
    res.status(409).json({ ok: "fail", error: "El bot ya ha sido encendido" });
    return;
  }
  const listInteraction = getListInteraction();

  for (let i = 0; i < listInteraction.length; i++) {
    bot.command(listInteraction[i].command, (ctx) =>
      ctx.reply(listInteraction[i].message)
    );
  }
  botIsRunning = true;
  bot.launch();
  res.json({ ok: "success" });
};

export const updateBot = (req: Request, res: Response) => {
  if (!botIsRunning) {
    res.status(409).json({ ok: "fail", error: "El bot no ha sido encendido" });
    return;
  }
  bot.stop();

  let listInteraction: Interaction[] = [];
  const interactions = req.body?.interactions;
  listInteraction = [...interactions];

  for (let i = 0; i < listInteraction.length; i++) {
    bot.command(listInteraction[i].command, (ctx) =>
      ctx.reply(listInteraction[i].message)
    );
  }
  bot.launch();

  res.json({ ok: "success" });
};

export const stopBot = (req: Request, res: Response) => {
  if (!botIsRunning) {
    res.status(409).json({ ok: "fail", error: "El bot no ha sido encendido" });
    return;
  }
  bot.stop();
  botIsRunning = false;
  res.json({ ok: "success" });
};
