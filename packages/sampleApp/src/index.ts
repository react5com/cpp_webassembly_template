import "./style.css";
import { getEmModule } from "./emmodule";

function connectUi() {
  const button = document.getElementById("tokenizeButton") as HTMLButtonElement;
  const textarea = document.getElementById("textToTokenize") as HTMLTextAreaElement;
  const treatPunctuationAsToken = document.getElementById(
    "treatPunctuationAsToken"
  ) as HTMLInputElement;
  const output = document.getElementById("output") as HTMLDivElement;

  button.onclick = async () => {
    const text = textarea.value;
    output.innerHTML = "Tokenizing...";

    try {
      const Module = await getEmModule();
      const tokenizer = new Module.Tokenizer(treatPunctuationAsToken.checked);
      const tokens = tokenizer.tokenize2(text);
      tokenizer.delete();

      output.innerHTML = `<strong>Tokens:</strong> ${tokens.join(", ")}`;
    } catch (error) {
      output.innerHTML = `<span style="color: red;">Error: ${(error as Error).message}</span>`;
    }
  };
}

window.onload = () => {
  connectUi();
};
