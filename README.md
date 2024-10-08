# sdl2 (2d) game engine c++

Avoid bots, kill them with your projectile gun. Top-down 2d view.
Core focus is functionality, not creating an actual game, so no fancy art work, etc.

Framework of a game:
- Finite state machine for game states (main menu, play state, pause, game over)
- collision detection for player against world objects, bots, and projectiles
- basic bots that move towards player ( eventually try to implement A* or Dijkstra's algo to get around objects that cause collisions)
- an inventory for the player (with items such as healing potion)
- resource management for textures & sounds
- my own level parser, uses a zmap file to define a height for each texture object, which we can use to create stairs
- typical stuff like delta timing, also used in collision detection w/ velocity
