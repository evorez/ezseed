# EZseed

A browser-based Minecraft seed map created by 𝙴𝚅𝙾𝚁𝙴𝚉. Explore sampled biomes and predicted structures for Java and Bedrock seeds across the Overworld, Nether, and End.

- **Website:** https://ezseed.vercel.app
-  https://evorez.github.io/ezseed/
- Open `index.html` in a modern browser or serve the repository as a static website.
- On phones, tap **Move map** to pan or pinch; switch it off to scroll the page normally.
- Bedrock support and structure locations are experimental predictions. Spawn is approximate; check locations and teleport destinations in-game. Coordinates beyond Minecraft's normal world border are experimental.
- Biome Finder and structure finder search the loaded 8,192-block region; biome results are approximate samples.
- Save named waypoints on your device, convert Nether and Overworld portal coordinates, and download a PNG of the visible map. Waypoints are separate on each website and are removed if that site’s browser storage is cleared.
- Install from the browser menu or the Install app button. Offline use works after the first successful online visit on HTTPS; app assets must be served together.

The world generators use [Cubiomes](https://github.com/Cubitect/cubiomes) and [cubiomes-bedrock](https://github.com/FragrantResult186/cubiomes-bedrock). Their source and MIT license notices are included under `worldgen/`. See `webui-spec.md` for versions, limitations and implementation details.

Independent concept; not affiliated with Mojang or Chunkbase.
