import ModuleFactory, { type EmbindModule } from "@cpp_webassembly_template/nlplib";
import { vectorToArray } from "./utils/converters";

describe("Tokenizer Tests", () => {
  let Module: EmbindModule;

  beforeAll(async () => {
    Module = (await ModuleFactory()) as EmbindModule;
  });

  test("Tokenizes a simple sentence", async () => {
    const text = "Hello, world! This is a test.";

    const tokenizer = new Module.Tokenizer(true);
    let vector = null;
    try {
      vector = tokenizer.tokenize(text);
      // Convert the result to a JavaScript array
      const tokens = vectorToArray(vector);
      expect(tokens).toEqual(["Hello", ",", "world", "!", "This", "is", "a", "test", "."]);

      const jsArray = tokenizer.tokenize2(text);
      expect(jsArray).toEqual(["Hello", ",", "world", "!", "This", "is", "a", "test", "."]);
    } finally {
      vector?.delete();
      tokenizer.delete();
    }
  });

  test("Points array calculation", async () => {
    const n = 2;
    const Module = (await ModuleFactory()) as EmbindModule;
    const tokenizer = new Module.Tokenizer(true);
    const pointsVector = tokenizer.calculatePoints(n);

    expect(pointsVector.get(0)?.x).toEqual(0.0);
    expect(pointsVector.get(0)?.y).toEqual(0.0);
    expect(pointsVector.get(1)?.x).toEqual(1.0);
    expect(pointsVector.get(1)?.y).toEqual(2.0);

    pointsVector.delete();
    tokenizer.delete();
  });
});
