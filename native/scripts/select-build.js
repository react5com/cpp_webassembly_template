import { execSync } from "child_process";
import os from "os";
import process from "process";
import console from "console";

const ostarget = process.argv[2] || "native";
const buildtype = process.argv[3] || "Release";

console.log(`Building for target: ${ostarget} with build type: ${buildtype}`);
if (os.platform() === "win32") {
  execSync(`npm run build:${ostarget}:win ${buildtype}`, { stdio: "inherit" });
} else {
  execSync(`npm run build:${ostarget}:nix ${buildtype}`, { stdio: "inherit" });
}
