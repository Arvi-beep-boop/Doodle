# Doodle
You can shoot, jump, dodge, stomp, climb - pretty much everything!

## Description
- I used AABB collision detection (maybe not the best solution, but works fine enough)
- Some vector math, normalized vector, calculating direction etc.
- Mind it is my first game in C++ and the architecture is pretty bad (especially inheritance aspects, I should do some kind of entity class and implement Update() function in Enemy, Player, Platform etc. I decided to move on instead of rewrite whole project) 

## Controls

- press UP Arrow key to enable immunity ability. 
- immunity ability lasts 20 seconds and has cooldown before each use
- in the start of the game you will be able to use immunity AFTER 30 seconds
- left and right arrow key to move
- player jumps if detects platform/ground beneath 

## RESTARTING GAME

- to restart game press DOWN arrow key after dying.

## SCORE 
 
 Score is shown both in upper left and right corner.
 - Left upper corner shows platforms passed
 - Right upper corner shows distance passed
