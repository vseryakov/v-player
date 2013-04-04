v-player
========

Generic application viewer for V-Play Game Engine

This utility will allow to render QML games or files without compiling. 
Once compiled with V-Play engine all V-Play demos and examples can just
be rendered. Tested only of Mac OS X but should work on Windows or Linux
as well.

Even developing new games or QML applications can be done by using this 
generic player. Starting new project will just be a matter of creating QML files 
with images and other required files in the same folder and executing vplay with 
main QML file.

## Build and installation

- Clone this repo: git clone https://github.com/vseryakov/v-player.git
- Download V-Play SDK, install it for example in /opt/local/v-play
- cd v-player
- Assuming previous SDK install path, run /opt/local/v-play/Desktop/Qt/4.8.1/gcc/bin/qmake
- make
- vplay utility is ready to be used, copy it for easier access for example into ~/bin

## Usage

- Browse V-Play SDK Demos now and run games using vplay
- cd /opt/local/v-play/Demos/V-PlaySDK/CarChallenge/qml
- vplay CarChallengeMain.qml

## Creating new project

- mkdir MyNewGame
- cd MyNewGame
- vi main.qml ....
- vplay
- vi main.qml ...
...

## Author
Vlad Seryakov

##License

MIT license - [http://www.opensource.org/licenses/mit-license.php](http://www.opensource.org/licenses/mit-license.php)





