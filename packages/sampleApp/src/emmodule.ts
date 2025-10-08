import ModuleFactory, { EmbindModule } from "@cpp_webassembly_template/nlplib";

let Module: EmbindModule;
async function init() {
  Module = (await ModuleFactory()) as EmbindModule;
}
init();

export async function getEmModule(): Promise<EmbindModule> {
  if (!Module) {
    // Wait until the module is initialized
    await new Promise<void>((resolve) => {
      const check = () => {
        if (Module) {
          resolve();
        } else {
          setTimeout(check, 10);
        }
      };
      check();
    });
  }
  return Module;
}
