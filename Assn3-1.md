Use the fixed pipeline of OpenGL, i.e., use traditional OpenGL APIs
- Find or make 3D models to represent player and other components such as car, map, etc (check if the meshes are UV-mapped before using them)
  *do not need to consider hierarchical structures and animation loops for characters and trucks
- Field is a little higher than the road
- Set a certain area of the ground as the border of the game. In this boundary, the game is played.
- Car should be created outside this border and naturally appear in the game window regardless of each viewing mode.
## Viewing modes:
- 3rd-person view (Default): the camera is placed somewhere behind the player (following the player).
- 1st-person view: The camera is placed right in front of the character. You cannot see the character, but you can see the character’s perspective.
- Side view: the camera is looking toward a diagonal of the map.
- *change viewing mode by pressing ‘v’ key
## Rendering modes:
- Mode 1 (Default): wire-frame without hidden line removal
- Mode 2: wire-frame with hidden line removal
- *change rendering mode by pressing ‘r’ key
