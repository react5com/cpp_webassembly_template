import ModuleFactory from "@cpp_webassembly_template/nlplib";

async function play() {
  const Module = await ModuleFactory();

  return Module;
}

play()
  .then((Module) => {
    Module.ccall("lsan_check_now", null, [], []);
  })
  .catch(() => {
    //console.error("Error:", err);
  });
