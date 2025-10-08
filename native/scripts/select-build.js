import { execSync } from "child_process";
import os from "os";

if (os.platform() === "win32") {
  execSync("npm run build:win", { stdio: "inherit" });
} else {
  execSync("npm run build:nix", { stdio: "inherit" });
}
