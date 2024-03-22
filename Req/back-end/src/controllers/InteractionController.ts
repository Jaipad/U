import { Interaction } from "../models/Interaction";
import { Request, Response } from "express";

let listInteraction: Interaction[] = [];

export const getListInteraction = () => {
  return listInteraction;
};
export const createInteraction = (req: Request, res: Response) => {
  const interaction = new Interaction(req.body);
  listInteraction.push(interaction);
  return res.json({ ok: "success", data: listInteraction });
};
export const getAllInteractions = (req: Request, res: Response) => {
  res.json({ ok: "success", data: listInteraction });
};

export const getOneInteraction = (req: Request, res: Response) => {
  const { command } = req.params;
  const commandFinded = listInteraction.find((i) => i.command === command);
  res.json({ ok: "success", data: commandFinded });
};

export const removeInteraction = (req: Request, res: Response) => {
  const { command } = req.params;

  listInteraction = listInteraction.filter((i) => i.command !== command);
  res.json({ ok: "success", data: listInteraction });
};

export const editInteraction = (req: Request, res: Response) => {
  const { command } = req.params;
  const interaction = new Interaction(req.body);

  listInteraction = listInteraction.map((i) =>
    i.command === command ? interaction : i
  );
  res.json({ ok: "success", data: listInteraction });
};
