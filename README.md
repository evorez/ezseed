# EZseed

A browser-based Minecraft seed map created by 𝙴𝚅𝙾𝚁𝙴𝚉. Explore sampled biomes and predicted structures for Java and Bedrock seeds across the Overworld, Nether, and End.

- **Website:** https://ezseed.vercel.app _________________ https://evorez.github.io/ezseed/
- Open `index.html` in a modern browser or serve the repository as a static website.
- On phones, tap **Move map** to pan or pinch; switch it off to scroll the page normally.
- Bedrock support and structure locations are experimental predictions. Spawn is approximate; check locations and teleport destinations in-game. Coordinates beyond Minecraft's normal world border are experimental.
- The loaded map is a moving 8,192-block window; finder results search the loaded region. Biomes are sampled, not block-level terrain.

The world generators use [Cubiomes](https://github.com/Cubitect/cubiomes) and [cubiomes-bedrock](https://github.com/FragrantResult186/cubiomes-bedrock). Their source and MIT license notices are included under `worldgen/`. See `webui-spec.md` for versions, limitations and implementation details.

Independent concept; not affiliated with Mojang or Chunkbase.
