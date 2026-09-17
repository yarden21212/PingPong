# PingPong

PingPong is my version of Atari's classic game, **Pong**.

## The purpose of the game

One day I was bored, so I decided to develop a tiny game to play with my girlfriend. I wanted to create it without the use of AI in order to practice C++ and OpenGL.

There was no deeper meaning behind it, I was simply curious to see how fun it could be.

The first version was a game for two players. One player controlled a ball, while the other controlled a paddle/racket.

If the ball crossed the paddle's line, the first player got a point. If the paddle managed to stop the ball, the second player got a point.

https://github.com/user-attachments/assets/11022ea4-2ab9-4345-af8d-3f4a3af26c52

Later, I understood that the game was too static and became boring quite quickly. It was challenging and fun in some ways, but it wasn't very exciting, so I decided to upgrade it into the Pong game we know and love:

https://github.com/user-attachments/assets/92537773-0b33-476c-b56b-b2be2f25a921

The game went through several different versions until I managed to achieve the result I was aiming for. I'll show each stage below.

## Stage 1

### Wall physics

First, I made sure that collisions worked correctly.

I implemented the following behavior:

* If the ball hits a wall, it changes its direction along the x-axis and moves in the opposite direction.

https://github.com/user-attachments/assets/249ab88b-ff39-4a31-9f7f-9d5a8d159e1f

## Stage 2

### Paddle location detection

I implemented collision detection between the ball and the paddle.

* Once the ball reached a position between the paddle's edges, it reacted by changing its y-direction to the opposite of its current one.

https://github.com/user-attachments/assets/aef6289c-7077-409f-b4f4-7a4bcaefe719

## Stage 3

### Basic physics

I tried to implement my own physics system.

* As you can see, it wasn't exactly a complete success!

https://github.com/user-attachments/assets/0f24e5ac-5493-4dea-8640-dac91cbd087a

## Stages 4 + 5

I explored the internet in search of better Pong physics until I found an amazing source that explained the idea behind the game's physics.

I was still proud of the physics I had created myself, even though it wasn't a complete success, so I decided to combine the two approaches and make the game even more challenging.

This way, your opponent can't easily predict your next move.

* You can see the text at the top of the screen, which includes the current score and the current physics mode being used. The physics mode can be changed freely by pressing a button.

https://github.com/user-attachments/assets/bb2a5217-c20a-4dda-8141-0af27358c40f
