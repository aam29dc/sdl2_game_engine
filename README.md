# sdl2 (2d) game engine c++

Avoid bots, kill them with your projectile gun. Top-down 2d view.
Core focus is functionality, and game design patterns; not creating an actual game, so no fancy art work.

I'll be rewriting the code base to make it more flexible as I learn more/better design patterns.

- Finite state machine for game states (main menu, play state, pause, game over)
- collision detection for player against world objects, bots, and projectiles
- basic bots that move towards player ( eventually try to implement A* or Dijkstra's algo to get around objects that cause collisions)
- an inventory for the player
- resource management for textures & sounds
- a level parser which uses a zmap to define a height for each texture object, which we can use to create stairs
- typical stuff like delta timing, also used in collision detection w/ velocity
