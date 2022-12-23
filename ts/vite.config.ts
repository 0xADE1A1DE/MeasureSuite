import { defineConfig } from "vitest/config";

export default defineConfig({
  test: {
    coverage: {
      reporter: ["text", "json", "html", "cobertura"],
    },
    include: ["**/test/**/*.test.ts"],
  },
});
