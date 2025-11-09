import { describe, test, before, after } from "node:test";
import * as assert from "node:assert/strict";
import ModuleFactory, { type EmbindModule } from "@cpp_webassembly_template/nlplib";
import { vectorToArray } from "./utils/converters";

describe("Tokenizer Tests", () => {
  let Module: EmbindModule;

  before(async () => {
    Module = (await ModuleFactory()) as EmbindModule;
  });
  after(() => {
    (Module as any).ccall("lsan_check_now", null, [], []);
  });

  test("Tokenizes a simple sentence", async () => {
    const text = "Hello, world! This is a test.";

    using tokenizer = new Module.Tokenizer(true);
    using vector = tokenizer.tokenize(text);
    // Convert the result to a JavaScript array
    const tokens = vectorToArray(vector);
    assert.deepStrictEqual(tokens, ["Hello", ",", "world", "!", "This", "is", "a", "test", "."]);

    const jsArray = tokenizer.tokenize2(text);
    assert.deepStrictEqual(jsArray, ["Hello", ",", "world", "!", "This", "is", "a", "test", "."]);
  });

  test("Points array calculation", async () => {
    const n = 2;
    using tokenizer = new Module.Tokenizer(true);
    using pointsVector = tokenizer.calculatePoints(n);
    using pt1 = pointsVector.get(0);
    using pt2 = pointsVector.get(1);
    assert.strictEqual(pt1?.x, 0.0);
    assert.strictEqual(pt1?.y, 0.0);
    assert.strictEqual(pt2?.x, 1.0);
    assert.strictEqual(pt2?.y, 2.0);
  });
});
