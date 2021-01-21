# raspi2png

Utility to take a snapshot of the raspberry pi screen and save it as a PNG file

Modified fork to allow streaming. The streams can be viewed from any computer on the local network in the web browser, or you can restrict viewing to a specific IP address and it will refuse connections from other devices. Performance is not very high, so using the "scale" parameter to reduce the quality (such as 0.5 for 50% quality) and turning down the Raspberry Pi's resolution in `raspi-config` (and scaling up the font-size in `dpkg-recongifure console-setup` to make sure the text is still clear even when the quality is reduced) can get a stable framerate.

You can use this to turn your smartphone into a Pi display in order to use your Pi on-the-go. You can see an example of this here: https://www.youtube.com/watch?v=TCD0oboQ4EQ

The reason I made this fork is because the remote desktop applications require an X server to run and SSH only does the command-line interface but not graphical programs. What if you want something that can stream graphical programs that don't use X? Could not find anything, so I forked raspi2png and added the option here.

I also added keyboard emulation. If "control" is set to 1 (e.g. `raspi2png stream 8888 0.5 192.168.0.111 1`) then you can type in the browser window and it simulates those as keyboard presses on the Raspberry Pi. 

    Usage: raspi2png [--pngname name] [--width <width>] [--height <height>] [--compression <level>] [--delay <delay>] [--display <number>] [--stdout] [--help]
    
        --pngname,-p - name of png file to create (default is snapshot.png)
        --height,-h - image height (default is screen height)
        --width,-w - image width (default is screen width)
        --compression,-c - PNG compression level (0 - 9)
        --delay,-d - delay in seconds (default 0)
        --display,-D - Raspberry Pi display number (default 0)
        --stdout,-s - write file to stdout
        --help,-H - print this usage information
    
    Streaming usage: 
        Streams the contents of the screen to the web browser at http://ip_address:port_number/view
    
        raspi2png stream - Start streaming on port 8888
        raspi2png stream [port] - Start streaming on port [port]
        raspi2png stream [port] [quality] - Stream quality, e.g. 0.5 for 50% or 1 for 100%
        raspi2png stream [port] [quality] [ip_addr] - Only allow a specific IP to connect
        raspi2png stream [port] [quality] [ip_addr] [control] - Use 1 for the control to enable keyboard input
        raspi2png stop - Stop streaming

## Simple Install

Run this command through terminal or CLI screen.

curl -sL https://raw.githubusercontent.com/AndrewFromMelbourne/raspi2png/master/installer.sh | bash -

## Manual Building

You will need to install libpng,  libmicrohttpd, and libevdev before you build the program. On Raspbian

sudo apt-get install libpng12-dev libmicrohttpd-dev libevdev-dev

Then just type 'make' in the raspi2png directory you cloned from github.


