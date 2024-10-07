# sdl2 (2d) game engine c++

Avoid bots, kill them with your projectile gun. Top-down 2d view.
Here I was more focused on functionality, than creating an actual game.

Framework of a game:
- Finite state machine for game states (main menu, play state, pause, game over)
- collision detection for player against world objects, bots, and projectiles
- basic bots that move towards player ( eventually I'll try to implement A* or Dijkstra's algo to get around objects that cause collisions)
- an inventory for the player (with items such as healing potion)
- resource manager for textures
- delta timing for movement based on time and not frames
- my own level parser, which also uses a zmap file to define a height for each texture object, which we can use to create stairs
