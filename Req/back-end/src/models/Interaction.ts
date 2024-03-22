const listInteraction: Interaction[] = [];
export class Interaction {
  command: string;
  message: string;
  constructor(interaction: Interaction) {
    this.command = interaction.command;
    this.message = interaction.message;
  }
}
