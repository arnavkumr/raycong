# Raycong: A Pong Game!

Raycong is a simple pong game made using the C programming language with the help of [Raylib](https://www.raylib.com) library.

Raycong is my first C project after learning C programming in my first semester of college.

![Main Menu Screenshot](resources/Main%20Menu%20Screenshot.png)
![Gameplay Screenshot](resources/Gameplay%20Screenshot.png)

## Development
I initially followed [this](https://youtu.be/VLJlTaFvHo4) YouTube tutorial while working on this project but I have since further built upon the basic game independently.

In the tutorial, the programming language used was C++ but I have used C in this game. I have made use of structs, functions, and pointers in C to replicate C++ concepts such as classes and using functions inside of classes. I have also further developed the game to now have a main menu and in it, an option to enable local multiplayer, toggle endless mode and a game pace selector. 

## Playing
If you just wanna play the game, head on over to the [releases](https://github.com/arnavkumr/raycong/releases) page and download the latest release. Alternatively you can build the game yourself by following the steps listed in the [next section](#setup).

The controls are ```↑``` and ```↓``` (or ```w``` and ```s```) to move up and down respectively. 

The player (your) paddle is the one on the right if local multiplayer is disabled. If local multiplayer is enabled,  ```w``` & ```s``` are used to control the left paddle and ```↑``` & ```↓``` are used to control the right paddle.

If endless game is disabled, first to reach 10 points wins the game. If endless game is enabled, the game unsurprisingly goes on endlessly.

## Setup
To setup this project locally on your windows machine:
1. Install Raylib using one of their binary [releases](https://github.com/raysan5/raylib/releases) on GitHub.
2. Install VScode. 
3. Clone or download this repository and open the Raycong folder in VScode. 
4. Open the ```main.c``` file and go to ```Run``` then ``` Start Debugging```  or just press ```F5``` to build the project. 
5. You're ready to make your own changes to the project!

## Contributing
Feel free to report any bugs by opening an issue. Also, if you'd like to contribute, I would recommend forking the project or if it's a minor bugfix/issue, a pull request would be welcome.

## Contact
If you have any thoughts, suggestions or criticisms regarding the project, feel free to open a thread in the [discussions](https://github.com/arnavkumr/raycong/discussions) panel. If you'd like to reach out to me personally, kindly send me an [email](mailto:contact@arnav.me) or DM/tag me over on [Mastodon](https://fosstodon.org/@arnav).